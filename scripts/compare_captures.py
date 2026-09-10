#!/usr/bin/env python3
#
# Copyright (c) 2026 The Sokatoa Project Authors
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.
"""Compare two gfxr-sqlite databases built from the same application run.

The intended use is the acceptance check for api dump ingest: capture a scene twice, once with
gfxreconstruct and once with the api_dump layer, build a database from each, and see whether they
describe the same work. It also serves for any before and after comparison of two databases, such
as checking that a layer setting changed nothing that matters.

Two things make a naive diff useless, and this script normalises both:

  * Handle ids are assigned in creation order by whichever tool produced the database, so the same
    object has different ids on each side. Handles are renumbered by order of first appearance.
  * A .gfxr carries meta blocks that an api dump has no way to record, so a database built from an
    api dump is legitimately missing some rows. Those tables are reported separately rather than
    counted as mismatches.

Exits non-zero when the two differ outside the expected losses.
"""

import argparse
import collections
import sqlite3
import sys

# Tables a .gfxr fills from meta blocks that an api dump does not contain at all: it records no
# memory contents and none of gfxreconstruct's own bookkeeping. Differences here are expected and
# are reported as information rather than as failures.
EXPECTED_MISSING_TABLES = {
    'memory',
    'metaData',
    'displayMessages',
    'annotations',
}

# Argument types whose recorded text cannot be expected to match. Floats go through the layer's
# ostream, which rounds to six significant digits unless float_precision is set, and raw addresses
# differ between two runs of the same program.
LOSSY_ARGUMENT_TYPES = {
    'float',
    'double',
    'ADDRESS',
}


def load_calls(db):
    """The ordered list of (frameId, functionName) for real api calls, meta events excluded."""
    return db.execute(
        'select e.frameId, f.name'
        ' from apiEvents e join functionNames f on f.id = e.functionNameId'
        ' where e.apiEventTypeId = 2'
        ' order by e.id'
    ).fetchall()


def load_arguments(db):
    """Argument rows keyed by (apiEventId, index), with the argument type kept for filtering."""
    rows = db.execute(
        'select apiEventId, idx, name, type, value from apiEventArguments order by apiEventId, idx'
    ).fetchall()
    return {(r[0], r[1]): (r[2], r[3], r[4]) for r in rows}


def renumber_handles(values):
    """Maps handle ids onto their order of first appearance so two databases can be compared.

    Both tools number handles from 1 in creation order, but they see different sets of calls, so
    the same object ends up with a different id on each side. Position in the sequence is stable
    where the id is not.
    """
    mapping = {}
    out = []
    for value in values:
        if value not in mapping:
            mapping[value] = len(mapping) + 1
        out.append(mapping[value])
    return out


def compare_call_sequences(left, right, report):
    left_calls = load_calls(left)
    right_calls = load_calls(right)

    report('api calls', '%d vs %d' % (len(left_calls), len(right_calls)))

    left_names = [c[1] for c in left_calls]
    right_names = [c[1] for c in right_calls]

    if left_names == right_names:
        report('call sequence', 'identical')
        return True

    left_hist = collections.Counter(left_names)
    right_hist = collections.Counter(right_names)

    only_left = left_hist - right_hist
    only_right = right_hist - left_hist

    if not only_left and not only_right:
        report('call sequence', 'same calls, different order')
        return False

    report('call sequence', 'differs')
    for name, count in only_left.most_common(10):
        report('  only in left', '%d x %s' % (count, name))
    for name, count in only_right.most_common(10):
        report('  only in right', '%d x %s' % (count, name))
    return False


def compare_handles(left, right, report):
    """Compares handle identity per object table, after renumbering."""
    tables = [
        r[0] for r in left.execute(
            "select name from sqlite_master where type='table' order by name"
        )
    ]

    mismatched = []
    for table in tables:
        try:
            columns = [c[1] for c in left.execute('pragma table_info("%s")' % table)]
        except sqlite3.Error:
            continue
        if 'handle' not in columns:
            continue

        try:
            lh = renumber_handles([r[0] for r in left.execute('select handle from "%s" order by id' % table)])
            rh = renumber_handles([r[0] for r in right.execute('select handle from "%s" order by id' % table)])
        except sqlite3.Error:
            continue

        if lh != rh:
            mismatched.append((table, len(lh), len(rh)))

    if not mismatched:
        report('object tables', 'handle sequences agree after renumbering')
        return True

    report('object tables', '%d differ' % len(mismatched))
    for table, nl, nr in mismatched[:12]:
        report('  ' + table, '%d vs %d objects' % (nl, nr))
    return False


def compare_arguments(left, right, report):
    """Compares recorded argument values, skipping handles and the lossy types."""
    left_args = load_arguments(left)
    right_args = load_arguments(right)

    shared = set(left_args) & set(right_args)
    compared = 0
    differing = collections.Counter()

    for key in sorted(shared):
        lname, ltype, lvalue = left_args[key]
        rname, rtype, rvalue = right_args[key]

        if ltype != rtype or ltype in LOSSY_ARGUMENT_TYPES or ltype == 'HANDLE':
            continue

        compared += 1
        if lvalue != rvalue:
            differing[(lname, ltype)] += 1

    report('arguments compared', str(compared))
    if not differing:
        report('argument values', 'identical')
        return True

    report('argument values', '%d differing arguments' % sum(differing.values()))
    for (name, type_name), count in differing.most_common(10):
        report('  ' + name, '%d x (%s)' % (count, type_name))
    return False


def compare_tables(left, right, report):
    """Row counts per table, so a wholesale absence shows up even if the calls line up."""
    tables = [
        r[0] for r in left.execute("select name from sqlite_master where type='table' order by name")
    ]

    expected_losses = []
    unexpected = []

    for table in tables:
        try:
            nl = left.execute('select count(*) from "%s"' % table).fetchone()[0]
            nr = right.execute('select count(*) from "%s"' % table).fetchone()[0]
        except sqlite3.Error:
            continue

        if nl == nr:
            continue

        if table in EXPECTED_MISSING_TABLES:
            expected_losses.append((table, nl, nr))
        else:
            unexpected.append((table, nl, nr))

    for table, nl, nr in expected_losses:
        report('  expected loss', '%s %d vs %d' % (table, nl, nr))

    if not unexpected:
        report('row counts', 'agree outside the expected losses')
        return True

    report('row counts', '%d tables differ unexpectedly' % len(unexpected))
    for table, nl, nr in sorted(unexpected, key=lambda x: -abs(x[1] - x[2]))[:15]:
        report('  ' + table, '%d vs %d' % (nl, nr))
    return False


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('left', help='database built from the first capture, usually the .gfxr one')
    parser.add_argument('right', help='database built from the second capture, usually the .apidump one')
    parser.add_argument('--quiet', action='store_true', help='only print the verdict')
    args = parser.parse_args()

    left = sqlite3.connect(args.left)
    right = sqlite3.connect(args.right)

    def report(label, detail):
        if not args.quiet:
            print('  %-24s %s' % (label, detail))

    print('comparing')
    print('  left   %s' % args.left)
    print('  right  %s' % args.right)
    print()

    results = [
        compare_call_sequences(left, right, report),
        compare_handles(left, right, report),
        compare_arguments(left, right, report),
        compare_tables(left, right, report),
    ]

    print()
    if all(results):
        print('The two captures describe the same work.')
        return 0

    print('The two captures differ. See above; a difference is not automatically a defect, but')
    print('every one should be explained before treating api dump ingest as equivalent.')
    return 1


if __name__ == '__main__':
    sys.exit(main())
