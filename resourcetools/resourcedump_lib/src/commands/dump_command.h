/*
 * Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef RESOURCE_DUMP_DUMP_COMMAND_H
#define RESOURCE_DUMP_DUMP_COMMAND_H

#include "resource_dump_command.h"

namespace mft
{
namespace resource_dump
{
struct resource_dump_segment_header;

class DumpCommand : public ResourceDumpCommand
{
public:
    // File Stream c'tor
    DumpCommand(device_attributes device_attrs,
                dump_request segment_params,
                uint32_t depth,
                const std::string bin_filename,
                bool is_textual = false);

    // Buffer Stream c'tor
    DumpCommand(device_attributes device_attrs, dump_request segment_params, uint32_t depth, bool is_textual = false);

    std::string get_big_endian_string();
    void reverse_fstream_endianess();

    bool validate() override;

    resource_dump_segment_header read_header(size_t segment_idx);

    // Returns true <-> dump contains an error segment, if returns true also puts the error message
    bool get_error_message(std::string& error_message);

    const std::string to_string() const override;

private:
    bool _allocated_ostream{false};
};
} // namespace resource_dump
} // namespace mft

#endif // RESOURCE_DUMP_DUMP_COMMAND_H
