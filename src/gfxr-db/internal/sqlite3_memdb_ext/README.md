# memdb_ext virtual file system

This implements a custom sqlite3 vfs based on the builtin memdb, but without the 2GB max limitation.

The memdb_ext.c file is a copy of the sqlite3 source file src/memdb.c, as of May 2025 (last changed Feb 17 2025).
The copy was taken from the sqlite3 git copy <https://github.com/sqlite/sqlite.git>,
commit SHA256 b1929b711791d6509f545cebd846c6aea99a2653
Note: sqlite is not developed with git, it has its own version control system instead.

See the top of memdb_int.c for a list of changes, the summary is that we use a custom realloc/free function
instead of sqlite3Realloc/sqlite3Free for the one allocation of of the main flat memory block memdb uses.
All other data structures are still using the sqlite3 memory operations.
Note that one issue with memdb is that it just doubles the memory block once 1 more byte than required is needed.
Hence it uses 3.2 GB to host a 1.6000001 GB database.

For updating to subsequent sqlite3 builds, updating this file is not required (it only uses the public API),
but of course updating is still recommended.
Also if sqlite3's memdb support gets extended to remove its limit, then remove this code and change back from using memdb_ext to just memdb.
The simplest way this would be possible is to change memdb.c not to allocate everything in one buffer, but instead handing an array of buffers.

Note: The memdb_ext.c file should keep its original formatting, to allow to compare it to updated versions. Do not use prettier on it.
Hence when editing with vscode always save with the 'File: Save without Formatting' command.
