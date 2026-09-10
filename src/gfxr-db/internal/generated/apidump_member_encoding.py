#!/usr/bin/python3 -i
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

import re


class ApiDumpMemberEncodingMixin:
    """Turns one struct member or command parameter into the statement that encodes it.

    Shared by the struct and command generators so the two cannot drift: a struct member and a
    command parameter are both a ValueInfo, and gfxreconstruct encodes them with the same rules,
    so the api dump side has to as well. The only difference is where the JSON node comes from,
    which subclasses supply through node_expr.
    """

    def node_expr_by_name(self, name):
        """The C++ expression yielding the JSON node for a sibling value, given its name."""
        raise NotImplementedError

    def node_expr(self, member):
        """The C++ expression yielding the JSON node for this value."""
        return self.node_expr_by_name(member.name)

    def handle_method(self, owner, member, shape):
        """The ApiDumpContext method to encode a handle of the given shape.

        `shape` is one of 'Value', 'Ptr' or 'Array'. Structs always resolve a handle through the
        map; commands override this to distinguish the output handle of a create, which starts a
        new identity, from one that is merely being referenced.
        """
        return 'VulkanHandle{0}'.format(shape)

    def length_hint(self, member, members):
        """The declared element count, for the rare array that is present but was not expanded.

        The count is normally a sibling, but it can also live inside another parameter, as in
        vkAllocateCommandBuffers where pCommandBuffers is sized by
        pAllocateInfo->commandBufferCount. Each -> step becomes a member lookup on the node.
        Trailing arithmetic such as codeSize / 4 is carried through unchanged.
        """
        if member.array_length is None:
            return None

        length = member.array_length

        if length.isdigit():
            return length

        length_value = member.array_length_value
        if length_value is None:
            return None

        if not length.startswith(length_value.name):
            return None

        node      = self.node_expr_by_name(length_value.name)
        remainder = length[len(length_value.name):]

        while remainder.startswith('->'):
            identifier = re.match(r'[A-Za-z_]\w*', remainder[2:])
            if identifier is None:
                return None

            node      = '{0}["{1}"]'.format(node, identifier.group(0))
            remainder = remainder[2 + identifier.end():]

        if remainder.strip():
            return '(ctx.Length({0}){1})'.format(node, remainder)

        return 'ctx.Length({0})'.format(node)

    def make_member_call(self, owner, member, members):
        """Produce the single statement that encodes one struct member.

        Mirrors KhronosBaseGenerator.make_encoder_method_call, which decides between value, pointer
        and array forms and picks the encoder name from the type. `owner` is the struct or command
        the value belongs to.
        """
        node = self.node_expr(member)

        if self.is_extended_struct_definition(member):
            return 'PNextFromApiDump(ctx, {0})'.format(node)

        base_type = member.base_type
        type_name = self.make_invocation_type_name(base_type)
        hint      = self.length_hint(member, members)

        # Structs.
        if self.is_struct(base_type):
            if member.is_array:
                if hint is not None:
                    return 'StructArrayFromApiDump<{0}>(ctx, {1}, {2})'.format(base_type, node, hint)
                return 'StructArrayFromApiDump<{0}>(ctx, {1})'.format(base_type, node)
            if member.is_pointer:
                return 'StructPtrFromApiDump<{0}>(ctx, {1})'.format(base_type, node)
            return 'StructFromApiDump<{0}>(ctx, {1})'.format(base_type, node)

        # Handles.
        if self.is_handle(base_type):
            object_type = self.handle_object_types.get(base_type)
            if object_type is None:
                # A handle the registry does not give an object type for cannot be tracked; encode
                # the null id and let the conversion report it rather than inventing a type.
                return 'ctx.UInt64Value({0}) /* {1} has no objtypeenum */'.format(node, base_type)
            if member.is_array:
                method = self.handle_method(owner, member, 'Array')
                if hint is not None:
                    return 'ctx.{0}({1}, {2}, {3})'.format(method, node, object_type, hint)
                return 'ctx.{0}({1}, {2})'.format(method, node, object_type)
            if member.is_pointer:
                return 'ctx.{0}({1}, {2})'.format(self.handle_method(owner, member, 'Ptr'), node, object_type)
            return 'ctx.{0}({1}, {2})'.format(self.handle_method(owner, member, 'Value'), node, object_type)

        # Strings.
        if type_name in ['String', 'WString']:
            if member.is_array and member.is_dynamic and member.pointer_count > 1:
                if hint is not None:
                    return 'ctx.StringArray({0}, {1})'.format(node, hint)
                return 'ctx.StringArray({0})'.format(node)
            return 'ctx.StringValue({0})'.format(node)

        # Function pointers and opaque pointers carry an address and nothing else.
        if type_name == 'FunctionPtr':
            return 'ctx.FunctionPtrValue({0})'.format(node)

        if base_type == 'void' and member.is_pointer:
            return 'ctx.VoidPtrValue({0})'.format(node)

        # Enums.
        if self.is_enum(base_type):
            resolver = 'EnumFromString_{0}'.format(self.canonical_enum(base_type))
            if member.is_array:
                if hint is not None:
                    return 'ctx.EnumArray({0}, {1}, {2})'.format(node, resolver, hint)
                return 'ctx.EnumArray({0}, {1})'.format(node, resolver)
            if member.is_pointer:
                return 'ctx.EnumPtr({0}, {1})'.format(node, resolver)
            return 'ctx.EnumValue({0}, {1})'.format(node, resolver)

        # Bitmasks. The bits enum, when there is one, lets a name-only value be resolved.
        if self.is_flags(base_type):
            is_64 = self.is_64bit_flags(base_type)
            bits  = self.flag_enum_bits_type(base_type)
            if bits is not None:
                bits = self.canonical_enum(bits)
            call  = 'Flags64' if is_64 else 'Flags'

            if member.is_array:
                if bits is not None:
                    args = '{0}, EnumFromString_{1}'.format(node, bits)
                else:
                    args = node
                if hint is not None:
                    args += ', {0}'.format(hint)
                return 'ctx.{0}Array({1})'.format(call, args)

            if bits is not None:
                return 'ctx.{0}Value({1}, EnumFromString_{2})'.format(call, node, bits)
            return 'ctx.{0}Value({1})'.format(call, node)

        # Plain scalars. The encoder method name carries the encoded width, so it has to come from
        # the same type naming gfxreconstruct uses rather than from sizeof.
        scalar = self.scalar_method_name(base_type, type_name)
        if scalar is None:
            return 'ctx.UInt64Value({0}) /* unmapped type {1} */'.format(node, base_type)

        if member.is_array:
            if hint is not None:
                return 'ctx.{0}Array({1}, {2})'.format(scalar, node, hint)
            return 'ctx.{0}Array({1})'.format(scalar, node)
        if member.is_pointer:
            return 'ctx.{0}Ptr({1})'.format(scalar, node)
        return 'ctx.{0}Value({1})'.format(scalar, node)

    def canonical_enum(self, enum):
        """Resolves an enum alias to the name the lookup tables were generated under.

        A member can be declared with an alias spelling such as VkComponentTypeNV, while the enum
        table is emitted once under the canonical VkComponentTypeKHR.
        """
        seen = set()
        while (enum in self.enumAliases) and (enum not in seen):
            seen.add(enum)
            enum = self.enumAliases[enum]

        return enum

    def flag_enum_bits_type(self, flags_type):
        """The FlagBits enum backing a Flags typedef, or None when the typedef reserves no bits."""
        for enum, flags in self.enum_bits_to_flag.items():
            if flags == flags_type:
                return enum

        candidate = flags_type.replace('Flags', 'FlagBits', 1)
        if candidate in self.enum_names and candidate not in self.enumAliases:
            return candidate

        return None

    def scalar_method_name(self, base_type, type_name):
        """Maps a scalar type onto the context method that encodes it at the right width."""
        if self.has_basetype(base_type):
            resolved = self.get_basetype(base_type)
            if resolved in self.encode_types:
                return self.encode_types[resolved]

        if type_name in [
            'Int8', 'Int16', 'Int32', 'Int64', 'UInt8', 'UInt16', 'UInt32', 'UInt64', 'Float', 'Double', 'SizeT'
        ]:
            return type_name

        if base_type in self.encode_types:
            return self.encode_types[base_type]

        return None
