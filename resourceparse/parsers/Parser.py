# Copyright (C) Jan 2020 Mellanox Technologies Ltd. All rights reserved.
# Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
#
# This software is available to you under a choice of one of two
# licenses.  You may choose to be licensed under the terms of the GNU
# General Public License (GPL) Version 2, available from the file
# COPYING in the main directory of this source tree, or the
# OpenIB.org BSD license below:
#
#     Redistribution and use in source and binary forms, with or
#     without modification, are permitted provided that the following
#     conditions are met:
#
#      - Redistributions of source code must retain the above
#        copyright notice, this list of conditions and the following
#        disclaimer.
#
#      - Redistributions in binary form must reproduce the above
#        copyright notice, this list of conditions and the following
#        disclaimer in the documentation and/or other materials
#        provided with the distribution.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
# BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# --


#######################################################
#
# Parser.py
# Python implementation of the Class Parser
# Generated by Enterprise Architect
# Created on:      19-Dec-2019 3:18:38 PM
# Original author: talve
#
#######################################################
import os
import math
import re

from utils import constants as cs
from resource_data.RawData import RawData
from resource_data.DataPrinter import DataPrinter
from utils.Exceptions import ResourceParseException
from parsers.AdbParser import AdbNodeDesc, AdbParser


class Parser:
    """This class responsible for parsing the segments according the given raw data
    and adb segments by organize the given inputs and print them after the parsing
    posses.
    """
    def __init__(self, **kwargs):
        """This method initialize the class members
        """
        self._raw = kwargs[cs.UI_ARG_RAW]
        self._verbosity = kwargs[cs.UI_ARG_VERBOSITY_COUNT]
        self._out_file = kwargs[cs.UI_ARG_OUT]
        self._printer = DataPrinter(self._verbosity, self._out_file)
        self._warning_counter = 0
        self._error_counter = 0
        self._notice_counter = 0

        if not self._validate_file_path(kwargs[cs.UI_ARG_DUMP_FILE]):
            raise ResourceParseException("No such file '{0}'".format(kwargs[cs.UI_ARG_DUMP_FILE]))

        if not self._validate_file_path(kwargs[cs.UI_ARG_ADB_FILE]):
            raise ResourceParseException("No such file '{0}'".format(kwargs[cs.UI_ARG_ADB_FILE]))

        try:
            self._dumped_segment_db = self._retrieve_dumped_segment_db(kwargs[cs.UI_ARG_DUMP_FILE])
        except ResourceParseException as rpe:
            raise ResourceParseException("{0}\nFail to generate segment db from raw data.".format(rpe))

        try:
            self._segment_map = self._retrieve_segment_map(kwargs[cs.UI_ARG_ADB_FILE])
        except ResourceParseException as rpe:
            raise ResourceParseException("{0}\nFail to generate segment map db from adb file.".format(rpe))

        self._validate_adb_version_with_notice(kwargs[cs.UI_ARG_ADB_FILE])

    @classmethod
    def _validate_file_path(cls, path):
        return os.path.exists(path)

    def _get_next_warning_counter(self):
        """This method return get the next free index to help generate
         the a uniq key for the warning msg.
        """
        returned_value = self._warning_counter
        self._warning_counter += 1
        return returned_value

    def _get_next_error_counter(self):
        """This method return get the next free index to help generate
        the a uniq key for the error msg.
        """
        returned_value = self._error_counter
        self._error_counter += 1
        return returned_value

    def _get_next_notice_counter(self):
        """This method return get the next free index to help generate
        the a uniq key for the notice msg.
        """
        returned_value = self._notice_counter
        self._notice_counter += 1
        return returned_value

    def parse(self):
        """This method parse the segment according the the dumped input file and the
        current configurations.
        """
        # parse all segments
        seg_parsed_counter = 0
        try:
            for seg in self._dumped_segment_db:
                seg_parsed_counter += 1
                self._parse_segment(seg)
        except ResourceParseException as rpe:
            raise ResourceParseException("{0}\nFail to parse segments, failure occur at segment number {1}.".format(rpe, seg_parsed_counter))

        # print all segments
        self._printer.print_parsed_segment(self._dumped_segment_db)

    def _is_seg_size_match_adb_seg_size(self, seg_size, seg_type):
        """This method check if the dumped segment size is same like in the ADB definitions.
        """
        adb_seg_size = math.ceil(self._segment_map[seg_type].size / 32)
        dumped_data_size = seg_size
        # first 4 dw's at the resource segment is not a part of the ADB definition so we not consider them
        if self._is_resource_segment(seg_type):
            dumped_data_size -= cs.RESOURCE_SEGMENT_START_OFFSET_IN_DW
        if adb_seg_size != dumped_data_size:
            return False
        return True

    def _parse_segment(self, seg):
        """This method responsible for the parsing algorithm that take the raw data of
        each segment and generate his content according the adb map
        """
        seg_for_parse = False
        if seg.get_type() in self._segment_map:
            segment_name = self._build_union_prefix(self._segment_map[seg.get_type()].nodeDesc) \
                + self._segment_map[seg.get_type()].name
            if not self._is_seg_size_match_adb_seg_size(len(seg.get_data()), seg.get_type()):
                seg.add_parsed_data("Warning[{}]".format(self._get_next_warning_counter()),
                                    cs.WARNING_SIZE_DOESNT_MATCH.format(
                                        len(seg.get_data()) - cs.RESOURCE_SEGMENT_START_OFFSET_IN_DW,
                                        math.ceil(self._segment_map[seg.get_type()].size / 32)))
            seg_for_parse = True
        else:
            # reference segment is missing in the adb (this will help the user understand the type)
            if seg.get_type() == cs.RESOURCE_DUMP_SEGMENT_TYPE_REFERENCE:
                segment_name = "segment_reference"
            else:
                segment_name = "UNKNOWN"

        seg.add_parsed_data(20 * " " + "Segment", "{0} ({1}){2}".format(segment_name, seg.get_type(), seg.additional_title_info()))

        if self._is_resource_segment(seg.get_type()):
            data_start_position = cs.RESOURCE_SEGMENT_START_OFFSET_IN_BYTES
        else:
            data_start_position = 0

        # offset is in bits so converting is to bit array and store it at a member is better then pass it as an argument
        # for a recursive method
        bytes_array = seg.get_data_in_bytes()[data_start_position:]
        self._current_bit_array = ''.join(format(x, '08b') for x in bytes_array)

        if seg_for_parse:
            for field in self._segment_map[seg.get_type()].subItems:
                if field.nodeDesc.isUnion and field.uSelector:
                    self._parse_union_selector_field(field, seg)
                else:
                    if(field.condition and self._segment_map[seg.get_type()].is_conditional):
                        self._calc_values_condition(field)
                        if(not field.condition.eval_expr()):
                            continue

                    prefix = self._build_union_prefix(field.nodeDesc)
                    self._parse_seg_field(field, prefix + field.name, seg)
            if self._raw:
                self._build_and_add_raw_data(seg)
        else:  # if segment not for parse, need to set raw data
            self._build_and_add_raw_data(seg)

    def _calc_values_condition(self, field):
        """This method go over all the items and perform value calculation then update
            the condition.var_details per item.
        """
        cond_elem = field.condition.var_details
        for elem in cond_elem:
            if cond_elem[elem].is_found:
                field_offset = self._calculate_aligned_to_dword_offset(cond_elem[elem].offset, cond_elem[elem].size)
                cond_elem[elem].value = hex(int(self._current_bit_array[field_offset:field_offset + cond_elem[elem].size], 2))
                field.condition.parsed_str = field.condition.parsed_str.replace(cond_elem[elem].substring, cond_elem[elem].value)

    def _parse_enum_field(self, field, field_str, seg):
        """This method parse enum field and present the enum name as well as the enum value.
        """
        field_offset = self._calculate_aligned_to_dword_offset(field.offset, field.size)
        enum_value = int(self._current_bit_array[field_offset:field_offset + field.size], 2)
        if len(self._current_bit_array) >= (field_offset + field.size):
            if enum_value in field.enum_dict:
                seg.add_parsed_data(field_str, "(" + field.enum_dict[enum_value] + " = " + hex(enum_value) + ")")
            else:
                seg.add_parsed_data(field_str, hex(int(self._current_bit_array[field_offset:field_offset + field.size], 2)))

    def _parse_union_selector_field(self, field, seg):
        """This method parse union field and present only the relevant field
        (selected by the selector)
        """
        union_field_offset = self._calculate_aligned_to_dword_offset(field.uSelector.offset, field.uSelector.size)
        selected_field_enum = field.uSelector.dict[int(self._current_bit_array[union_field_offset:union_field_offset + field.uSelector.size], 2)]
        for item in field.subItems:
            if item.attrs['selected_by'] == selected_field_enum:
                self._parse_seg_field(item, item.name, seg)

    def _parse_printf_format(self, value, format):
        """ Enables specifying how a field should be dumped
            %d - dump field as decimal
            %x – dump field as hexadecimal
            %b - dump field as binary
            %s – dump field as ASCII tex"""

        cases = ['d', 'x', 'b', 's']
        new_val = ''
        tmp_val = value.split("0x")[1]
        str_list = []
        str_list[:0] = format

        for i, c in enumerate(str_list):
            f = ""
            if(i + 1 < len(str_list)):
                if(c == '%' or c + str_list[i + 1] == '0x' or c + str_list[i + 1] == c + 'x'):
                    if(c == '%' and str_list[i + 1] in cases):
                        f = c + str_list[i + 1]
                        del str_list[i]
                    if(i + 1 < len(str_list)):
                        if(c + str_list[i + 1] == '0x'):
                            new_val += '0x'
                            del str_list[i]
                    if(f == '%d'):
                        new_val += str(int(tmp_val, 16))
                    if(f == '%x'):
                        new_val += str(tmp_val)
                    if(f == '%b'):
                        new_val += str(bin(int(tmp_val, 16)).replace("0b", ""))
                    if(f == '%s'):
                        new_val += str(tmp_val)
                    if(i + 2 < len(str_list)):
                        if(c + str_list[i + 1] + str_list[i + 2] == '%' + str_list[i + 1] + 'x'):
                            new_val += (int(str_list[i + 1]) - 1) * ' ' + str(tmp_val)
                            for _ in range(2):
                                del str_list[i]
                    if(i + 2 < len(str_list)):
                        if(c + str_list[i + 1] + str_list[i + 2] == '%' + str_list[i + 1] + str_list[i + 2] and str_list[i + 1].isdigit()):
                            new_val += (int(str_list[i + 2]) - 1) * '0' + str(tmp_val)
                            for _ in range(3):
                                del str_list[i]
                else:
                    new_val += c
            else:
                new_val += c

        return new_val

    def _parse_seg_field(self, field, field_str, seg):
        """This method is a recursive method that build the inner fields
        """
        if field.enum_dict:
            self._parse_enum_field(field, field_str, seg)
        elif len(field.subItems) > 0:
            for sub_field in field.subItems:
                if(sub_field.condition and sub_field.parent.is_conditional):
                    if(not sub_field.condition.eval_expr()):
                        continue
                prefix = self._build_union_prefix(sub_field.nodeDesc)
                self._parse_seg_field(sub_field, field_str + "." + prefix + sub_field.name, seg)
                if(field.is_unlimited_array):
                    field_offset = self._calculate_aligned_to_dword_offset(field.offset, field.size)
                    field_offset_bytes = field_offset / 8
                    field_size_bytes = field.size / 8
                    array_size_bytes = (len(seg.get_data()) - cs.RESOURCE_SEGMENT_START_OFFSET_IN_DW) * 4
                    end_index = int((array_size_bytes - field_offset_bytes) / field_size_bytes)
                    for i in range(1, end_index):
                        value = hex(int(self._current_bit_array[field_offset + 32 * i:field_offset + 32 * i + field.size], 2))
                        field_str_ = field_str.replace("0", str(i)) + "." + prefix + sub_field.name
                        seg.add_parsed_data(field_str_, value)

        else:
            field_offset = self._calculate_aligned_to_dword_offset(field.offset, field.size)
            if len(self._current_bit_array) >= (field_offset + field.size):
                value = hex(int(self._current_bit_array[field_offset:field_offset + field.size], 2))
                if("printf" in field.attrs):
                    value = self._parse_printf_format(value, field.attrs["printf"])
                seg.add_parsed_data(field_str, value)

    @classmethod
    def _build_and_add_raw_data(cls, seg):
        """This method build the raw data in the right format and add it to the
        parsed data of the segment.
        """
        hex_list = []
        line_counter = 0
        dw_counter = 0
        seg.add_parsed_data("RAW DATA", "")

        for dw in seg.get_data():
            hex_list.append('0x{0:0{1}X} '.format(dw, 8))
            dw_counter += 1

            if (dw_counter % cs.PARSER_NUM_OF_DW_IN_ROW) == 0:
                seg.add_parsed_data("{:<15}".format(
                    "DWORD [{0}-{1}]".format(line_counter * 4, (line_counter * 4) + (len(hex_list) - 1))),
                    ''.join(hex_list[:]))
                line_counter += 1
                hex_list.clear()

        if len(hex_list) > 1:
            seg.add_parsed_data(
                "{:<15}".format("DWORD [{0}-{1}]".format(line_counter * 4, (line_counter * 4) + (len(hex_list) - 1))),
                ''.join(hex_list[:]))
        elif len(hex_list) == 1:
            seg.add_parsed_data("{:<15}".format("DWORD [{0}]".format(line_counter * 4)), ''.join(hex_list[:]))

    @classmethod
    def _calculate_aligned_to_dword_offset(cls, offset, size):
        """This method calculate the new offset inside the dword
        since the data inside has a different bit index
        """
        calculated_offset = offset
        if size < 32:
            calculated_offset = (int(offset / 32) * 32) + 32 - size - (offset % 32)
        return calculated_offset

    @classmethod
    def _is_resource_segment(cls, seg_type):
        """This method check if the seg type is resource segment
        """
        return cs.RESOURCE_DUMP_SEGMENT_TYPE_RESOURCE_MAX >= seg_type >= cs.RESOURCE_DUMP_SEGMENT_TYPE_RESOURCE_MIN

    @classmethod
    def _retrieve_dumped_segment_db(cls, dumped_file_path):
        """This method get the segment list generated from the dumped input file by calling
        the RawData class.
        """
        return RawData(dumped_file_path).to_segments()

    @classmethod
    def _build_union_prefix(cls, node_desc): # cls, node_desc: AdbNodeDesc
        """This method build the prefix for the struct in order to give the user
        information indicate if the node is a union
        """
        if not node_desc:
            prefix = ""
        else:
            if node_desc.isUnion:
                prefix = "(UNION)"
            else:
                prefix = ""
        return prefix

    def _retrieve_segment_map(self, adb_file_path):
        """This method get the segment map from the adbdata class.
        """
        self._adb_obj = AdbParser(adb_file_path)
        return self._adb_obj.segment_id_nodes_dict

    def _retrieve_adb_version_from_info_segment(self):
        """This method locate the info segment and if found, return the
        fw_version at the format XX.XX.XXXX, otherwise return empty string.
        """
        for seg in self._dumped_segment_db:
            if str(seg.get_type()).upper() == cs.RESOURCE_DUMP_SEGMENT_TYPE_INFO.upper():
                return seg.get_version()
        return ""

    def _validate_adb_version_with_notice(self, adb_file_path):
        """This method perform the fw version validation stages and send a proper notice msg
        if needed.
        """
        adb_name = os.path.splitext(os.path.basename(adb_file_path))[0]
        if self._is_adb_name_in_version_format(adb_name):
            adb_fw_version = self._retrieve_adb_version_from_valid_format(adb_name)
            dump_fw_version = self._retrieve_adb_version_from_info_segment()
            if adb_fw_version != dump_fw_version:
                self._get_next_notice_counter()
                self._printer.print_notice_before_parse("Notice - {0}".format(
                    "adb fw version {0} is used for parsing while dump fw version is {1}".format(adb_fw_version,
                                                                                                 dump_fw_version)))
        else:
            self._get_next_notice_counter()
            self._printer.print_notice_before_parse(
                "Notice - {0}".format("Adb name is not according the version format, can't validate adb fw version"))

    @classmethod
    def _retrieve_adb_version_from_valid_format(cls, adb_name):
        """This method extract the fw_version from the file name assuming that
        file already checked and has the right version format.
        """
        version = re.findall("[0-9]{2}_[0-9]{2}_[0-9]{4}", adb_name)[0]
        version_list = version.split("_")
        return "{0}.{1}.{2}".format(version_list[0], version_list[1], version_list[2])

    @classmethod
    def _is_adb_name_in_version_format(cls, adb_name):
        """This method check if the adb file name has the version format define by arch.
        """
        match = re.fullmatch("fw-[0-9]+-rel-[0-9]{2}_[0-9]{2}_[0-9]{4}", adb_name)
        if match is not None:
            if match.string == adb_name:
                return True
        return False
