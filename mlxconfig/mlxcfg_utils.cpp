/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
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
 *
 *
 * mlxcfg_utils.cpp
 *
 *  Created on: Jun 21, 2016
 *      Author: ahmads
 */

#include <sstream>
#include <stdarg.h>
#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <iomanip>
#include <mft_sig_handler.h>
#include <bit_slice.h>
#include <cmdif/tools_cif.h>
#include <compatibility.h>

#include "../tools_layouts/tools_open_layouts.h"
#include "mlxcfg_utils.h"

using namespace std;

void dealWithSignal()
{
    int sig;
    sig = mft_signal_is_fired();
    if (sig) {
        // reset received signal
        mft_signal_set_fired(0);
        // retore prev handler
        mft_signal_set_handling(0);
        //raise signal to let the previous handle deal with it.
        raise(sig);
    }
    mft_signal_set_handling(0);
    return;
}

MError mnvaCom5thGen(mfile* mf, u_int8_t* buff, u_int16_t len, u_int32_t tlvType,
        reg_access_method_t method, QueryType qT)
{
    struct tools_open_nvda mnvaTlv;
    memset(&mnvaTlv, 0, sizeof(struct tools_open_nvda));

    if (method == REG_ACCESS_METHOD_GET) {
        mnvaTlv.nv_hdr.length = sizeof(mnvaTlv.data);
    } else {
        mnvaTlv.nv_hdr.length = len;
    }
    mnvaTlv.nv_hdr.rd_en = 0;
    mnvaTlv.nv_hdr.over_en = 1;
    mnvaTlv.nv_hdr.writer_id = WRITER_ID_ICMD_MLXCONFIG;
    if (qT == QueryDefault) {
        mnvaTlv.nv_hdr.default_ = 1;
    } else if (qT == QueryCurrent) {
        mnvaTlv.nv_hdr.read_current = 1;
    }
    // tlvType should be in the correct endianess
    mnvaTlv.nv_hdr.type.tlv_type_dw.tlv_type_dw =  __be32_to_cpu(tlvType);
    memcpy(mnvaTlv.data, buff, len);
    MError rc;
    // "suspend" signals as we are going to take semaphores
    mft_signal_set_handling(1);
    //DEBUG_PRINT_SEND(&mnvaTlv, nvda);
    rc = reg_access_nvda(mf, method, &mnvaTlv);
    //DEBUG_PRINT_RECEIVE(&mnvaTlv, nvda);
    dealWithSignal();
    if (rc) {
        return rc;
    }
    memcpy(buff, mnvaTlv.data, len);
    return ME_OK;
}

MError nvqcCom5thGen(mfile* mf, u_int32_t tlvType, bool& suppRead,
                          bool& suppWrite, u_int32_t& version)
{
    struct tools_open_nvqc nvqcTlv;
    memset(&nvqcTlv, 0, sizeof(struct tools_open_nvqc));

    // tlvType should be in the correct endianess
    nvqcTlv.type.tlv_type_dw.tlv_type_dw = __be32_to_cpu(tlvType);
    MError rc;
    // "suspend" signals as we are going to take semaphores
    mft_signal_set_handling(1);
    rc = reg_access_nvqc(mf, REG_ACCESS_METHOD_GET, &nvqcTlv);
    dealWithSignal();
    if (rc) {
        return rc;
    }
    suppRead = nvqcTlv.support_rd;
    suppWrite = nvqcTlv.support_wr;
    version = nvqcTlv.version;
    //printf("-D- nvqcTlv.support_rd=%d nvqcTlv.support_wr=%d\n", nvqcTlv.support_rd, nvqcTlv.support_wr);
    return ME_OK;
}

MError nvdiCom5thGen(mfile* mf, u_int32_t tlvType)
{
    struct tools_open_nvdi nvdiTlv;
    memset(&nvdiTlv, 0, sizeof(struct tools_open_nvdi));

    nvdiTlv.nv_hdr.length = 0;
    nvdiTlv.nv_hdr.rd_en = 0;
    nvdiTlv.nv_hdr.over_en = 1;

    // tlvType should be in the correct endianess
    nvdiTlv.nv_hdr.type.tlv_type_dw.tlv_type_dw =  __be32_to_cpu(tlvType);

    MError rc;
    // "suspend" signals as we are going to take semaphores
    mft_signal_set_handling(1);
    // DEBUG_PRINT_SEND(&nvdiTlv, nvdi);
    rc = reg_access_nvdi(mf, REG_ACCESS_METHOD_SET, &nvdiTlv);
    // DEBUG_PRINT_RECIEVE(&nvdiTlv, nvdi);
    dealWithSignal();
    if (rc) {
        return rc;
    }
    return ME_OK;
}

bool strToNum(string str, u_int32_t& num, int base)
{
    char *endp;
    char* numStr = strcpy(new char[str.size() + 1],str.c_str());
    num = strtoul(numStr, &endp, base);
    if (*endp) {
        delete[] numStr;
        return false;
    }
    delete[] numStr;
    // check errno
    if (errno == ERANGE) {
        return false;
    }
    return true;
}

string numToStr(u_int32_t num, bool isHex)
{
    stringstream ss;

    if (isHex) {
        ss << std::uppercase << std::setfill('0') << std::setw(4) << std::hex;
    }

    ss << num;
    return ss.str();
}

vector<string> splitStr(const string s, char d)
{
    vector<string> v;
    stringstream ss(s);
    string to;

    while(std::getline(ss, to, d)){
      v.push_back(to);
    }

    return v;
}

string mlxcfg_ltrim(string s)
{
    const char* cs = s.c_str();
    while(isspace(*cs)){
        cs++;
    }
    return string(cs);
}

string mlxcfg_rtrim(string s)
{
    //todo rewrite it
    unsigned int i = s.size();
    if(i == 0) {
        return s;
    }
    while (--i > 0 && isspace(s[i])) {
        ;
    }
    if(i == 0 && isspace(s[i])) {
        return "";
    }
    return s.substr(0, i + 1);
}

string mlxcfg_trim(string s)
{
    return mlxcfg_rtrim(mlxcfg_ltrim(s));
}

string writerIdToStr(WriterId writerId)
{
    switch(writerId) {
        case WRITER_ID_UNSPECIFIED:
            return "Unspecified";
        case WRITER_ID_CHASSIS_BMC:
            return "Chassis BMC";
        case WRITER_ID_MAD:
            return "MAD";
        case WRITER_ID_BMC:
            return "BMC";
        case WRITER_ID_CMD_IF:
            return "CMD IF";
        case WRITER_ID_ICMD:
            return "ICMD";
        case WRITER_ID_ICMD_UEFI_HII:
            return "ICMD UEFI HII";
        case WRITER_ID_ICMD_UEFI_CLP:
            return "ICMD UEFI CLP";
        case WRITER_ID_ICMD_FLEXBOOT:
            return "ICMD FLEXBOOT";
        case WRITER_ID_ICMD_MLXCONFIG:
            return "ICMD MLXCONFIG";
        case WRITER_ID_ICMD_USER1:
            return "ICMD USER1";
        case WRITER_ID_ICMD_USER2:
            return "ICMD USER2";
        case WRITER_ID_ICMD_MLXCONFIG_SET_RAW:
            return "ICMD MLXCONFIG SET RAW";
        case WRITER_ID_OTHER:
            return "OTHER";
        default:
            return "Unknown";
    }
};


void copyDwVectorToBytesVector(const vector<u_int32_t>& dwV, vector<u_int8_t>& bV)
{
    bV.resize(dwV.size() << 2);
    memcpy(bV.data(), dwV.data(), bV.size());
}

void copyBytesVectorToDwVector(const vector<u_int8_t>& bV, vector<u_int32_t>& dwV)
{
    dwV.resize(bV.size() >> 2);
    memcpy(dwV.data(), bV.data(), bV.size());
}

string parseIndexStr(const string& indexedMlxconfigName)
{
    return indexedMlxconfigName.substr(indexedMlxconfigName.find('[') + 1,
                             indexedMlxconfigName.find(']') - indexedMlxconfigName.find('[') - 1);
}

void parseIndexedMlxconfigName(const string& indexedMlxconfigName, string& mlxconfigName, u_int32_t& index)
{
   string indexStr = parseIndexStr(indexedMlxconfigName);

    if (!strToNum(indexStr, index)) {
       throw MlxcfgException("Can not parse the index of %s\n", indexedMlxconfigName.c_str());
    }

    mlxconfigName = indexedMlxconfigName.substr(0, indexedMlxconfigName.find('['));
}

void extractIndexes(const string& indexesStr, vector<u_int32_t>& indexes)
{
    if (indexesStr.find("..") != string::npos) {
        unsigned int leftIndex = 0, rightIndex = 0;
        string leftIndexStr = indexesStr.substr(0, indexesStr.find(".."));
        string rightIndexStr = indexesStr.substr(indexesStr.find("..") + 2);
        if (!strToNum(leftIndexStr, leftIndex)) {
            throw MlxcfgException("Can not parse the index %s", leftIndexStr.c_str());
        }
        if (!strToNum(rightIndexStr, rightIndex)) {
            throw MlxcfgException("Can not parse the index %s", rightIndexStr.c_str());
        }
        if (leftIndex > rightIndex) {
            throw MlxcfgException("Left index %d can not be greater than right index %d",
                                   leftIndex, rightIndex);
        }
        while (rightIndex >= leftIndex) {
            indexes.push_back(leftIndex);
            leftIndex++;
        }
    } else {
        u_int32_t index = 0;
        if (!strToNum(indexesStr, index)) {
            throw MlxcfgException("Can not parse the index %s", indexesStr.c_str());
        }
        indexes.push_back(index);
    }
    
}

bool isIndexedMlxconfigName(const string& mlxconfigName)
{
    return (mlxconfigName.find("[") != string::npos);
}

MlxcfgException::MlxcfgException(const char* fmt, ...){
    char tmp[1024];
    va_list args;

    va_start (args, fmt);
    vsprintf(tmp, fmt, args);
    va_end(args);
    _err = tmp;
}


