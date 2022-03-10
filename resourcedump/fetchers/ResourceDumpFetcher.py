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
# ResourceDumpFetcher.py
# Python implementation of the Class CoreDumpFetcher
# Generated by Enterprise Architect
# Created on:      14-Aug-2019 10:12:01 AM
# Original author: talve
#
#######################################################

from segments.SegmentCreator import SegmentCreator
from utils import constants
from utils import constants as cs
import sys
import os
import math
import struct
import errno

sys.path.append(os.path.join("mtcr_py"))
sys.path.append(os.path.join("reg_access"))

import mtcr  # noqa
import regaccess  # noqa


try:
    import pyverbs.enums as e
    from pyverbs.providers.mlx5.mlx5dv_objects import Mlx5DvObj
    from pyverbs.providers.mlx5.mlx5dv import Mlx5DevxObj
    from pyverbs.pd import PD
    import pyverbs.providers.mlx5.mlx5_enums as dve
    from pyverbs.providers.mlx5.mlx5dv import Mlx5Context, Mlx5DVContextAttr
    from pyverbs.providers.mlx5.mlx5dv import Mlx5UMEM
    from pyverbs.mem_alloc import read32
    import resource
    PYVERVBS_SUPPORT = True
except Exception as _:
    PYVERVBS_SUPPORT = False

try:
    from scapy.fields import *
    from scapy.packet import *
    SCAPY_SUPPORT = True
    MLX5_CMD_OP_CREATE_MKEY = 0x200

    class SwMkc(Packet):
        fields_desc = [
            BitField('reserved1', 0, 1),
            BitField('free', 0, 1),                 # 0 - memory key is in use. It can be used for address translation
                                                    # 1 - memory key is free. Cannot be used for address translation
            BitField('reserved2', 0, 1),
            BitField('access_mode_4_2', 0, 3),      # 3 MSB bits of access mode. See encoding in access_mode_1_0 field.
            BitField('alter_pd_to_vhca_id', 0, 1),    # replace pd check with cross_vhca check
            BitField('crossed_side_mkey', 0, 1),    # crossed side mkey. Valid if alter_pd_to_vhca_id==1
            BitField('reserved3', 0, 5),
            BitField('relaxed_ordering_write', 0, 1),    # If set
                                                    # ,
                                                    # issue PCIe cycle with "relaxed ordering" attribute (allows
                                                    # write after write bypassing) for writes.
                                                    # Supported only when HCA_CAP.relaxed_oredering_write==1.
            BitField('reserved4', 0, 1),
            BitField('small_fence_on_rdma_read_response', 0, 1),    # Responder will have one read request toward the PCIe (per QP).
            BitField('umr_en', 0, 1),               # Enable umr operation on this MKey
            BitField('a', 0, 1),                    # If set, atomic operation is enabled
            BitField('rw', 0, 1),                   # If set, remote write is enabled
            BitField('rr', 0, 1),                   # If set, remote read is enabled
            BitField('lw', 0, 1),                   # If set, local write is enabled
            BitField('lr', 0, 1),                   # If set, local read is enabled. Must be set for all MKeys
            BitField('access_mode_1_0', 0, 2),      # 2
                                                    # LSB bits of access mode.
                                                    # 0
                                                    # x0: PA - (VA=PA, no translation needed) if set, no virtual to physi
                                                    # cal address translation is performed for this MKey. Not valid for,
                                                    # block mode MKey, replicated MTT MKey
                                                    # 0x1: MTT - (PA is needed)
                                                    # 0x2: KLMs - (Indirect access)
                                                    # 0x3: Fixed_Buffer_Size - used when KLMs are associated with fixed
                                                    # memory size. The fixed sized is determined by log_entity_size. Sup
                                                    # ported only if HCA_CAP.fixed_buffer_size==1.
                                                    # See Table 1013,
                                                    # "
                                                    # HCA Capabilities Layout
                                                    # ," on page 1122
                                                    # 0x4: SW_ICM
                                                    # 0x5: MEMIC - Supported only when HCA_CAP.DEVICE_MEM
                                                    # ORY.memic==1. See
                                                    # Table 1051, "
                                                    # Device Memory Capabilities
                                                    # Layout
                                                    # ," on page 1182
            BitField('reserved5', 0, 1),
            BitField('tunneled_atomic', 0, 1),      # If set, part of the MSB"s of the address is set to
                                                    # in order to generate a
                                                    # command in the CPU and do atomic for RDMA WR operations in
                                                    # the memory controller instead of accessing the user"s memory
                                                    # (DMA). This is according to IBM p9 spec.
                                                    # Supported only when HCA_CAP.
                                                    # tunneled_atomic==1.
            BitField('ma_translation_mode', 0, 2),    # MA translation mode
                                                    # 0x0: None - no MA translation needed.
                                                    # 0x1: ATS -
                                                    # Supported only when HCA_CAP.ats==1, and valid only
                                                    # when access_mode==PA or MTT.
                                                    # 0x3: CAPI - valid when access_mode==PA. Then a CAPI translation
                                                    # can be performed.
            BitField('reserved6', 0, 4),
            BitField('qpn', 0, 24),                 # For type 2 memory window - indicates the QP number this memory
                                                    # window is attached to.
                                                    # otherwise -
                                                    # must be 0xffffff.
            ByteField('mkey_7_0', 0),               # Variant part of MKey specified by this MKey context
            ByteField('reserved7', 0),
            BitField('pasid', 0, 24),               # PASID associated with MKEY.
                                                    # Valid when ma_translation_mode==CAPI
            BitField('length64', 0, 1),             # Enable registering 2
                                                    # ^64
                                                    # bytes per region
            BitField('bsf_en', 0, 1),               # Enable having bsf list on this MKey
            BitField('sync_umr', 0, 1),             # Memory region to be used by synchronous UMR process
            BitField('reserved8', 0, 2),
            BitField('expected_sigerr_count', 0, 1),    # LSB of expected number of sigerr_cqes. (See
                                                    # Section 17.4.1, "
                                                    # Signa
                                                    # ture Handover Steps
                                                    # ," on page 696
                                                    # )
            BitField('reserved9', 0, 1),
            BitField('en_rinval', 0, 1),            # Enable remote invalidation
            BitField('pd', 0, 24),                  # Protection domain. Valid if alter_pd_to_vhca_id==0
            LongField('start_addr', 0),             # Start Address - Virtual address where this region/window starts
                                                    # .
                                                    # For access_mode ==MEMIC, indicates the address of an allocated
                                                    # MEMIC buffer.
            LongField('len', 0),                    # Region length. Reserved when length64 bit is set (in which case the
                                                    # region length is 2^64B).
                                                    # For access_mode ==MEMIC, indicates the size of an allocated
                                                    # MEMIC buffer.
            IntField('bsf_octword_size', 0),        # Size (in units of 16B) required for this MKey's BSFs
                                                    # Must be a multiple of 4
            StrFixedLenField('reserved10', None, length=12),
            ShortField('crossing_target_vhca_id', 0),    # crossing/crossed VHCA ID. Valid if access_mode==INTER_GVMI (crossing) or alter_pd_to_vhca_id==1 (crossed)
            ShortField('reserved11', 0),
            IntField('translations_octword_size', 0),    # Size (in units of 16B) required for this MKey's physical buffer list or
                                                    # SGEs
                                                    # access_mode: MTT - each translation is 8B
                                                    # access_mode: KLM
                                                    # /Fixed
                                                    #
                                                    # Buffer Size
                                                    # - each SGE is 16B
                                                    # access_mode: PA - reserved
                                                    # Must be a multiple of 4
            BitField('reserved12', 0, 25),
            BitField('relaxed_ordering_read', 0, 1),    # Supported only when .relaxed_oredering_read==1.
            BitField('reserved13', 0, 1),
            BitField('log_entity_size', 0, 5),      # When access_mode==MTT: log2 of Page size in bytes granularity.
                                                    # When access_mode==Fixed_Buffer_Size:
                                                    # determines the length of
                                                    # the memory buffers (KLMs) associated with the MKEY.
                                                    # otherwise: reserved.
                                                    # Must be >=12
            BitField('reserved14', 0, 3),
            BitField('crypto_en', 0, 2),            # Enable crypto. Non-UMRable. Implies one BSF of 64B or 128B must be present.
            BitField('reserved15', 0, 27),
        ]


    class CreateMkeyIn(Packet):
        fields_desc = [
            ShortField('opcode', MLX5_CMD_OP_CREATE_MKEY),
            ShortField('uid', 0),                   # Defines the user identifier for which the object was cre
                                                    # ated.
                                                    # See Section  8.24.1, "
                                                    # UCTX - User Context
                                                    # ," on page  501
            ShortField('reserved1', 0),
            ShortField('op_mod', 0),
            ByteField('reserved2', 0),
            BitField('input_mkey_index', 0, 24),    # mkey index of the created mkey. 0 means reserved and
                                                    # mkey index is returned by the device in command output.
                                                    # See Table  1309, "
                                                    # MKey Most Significant Bits Selection
                                                    # ," on
                                                    # page  1356
                                                    # .
            BitField('pg_access', 0, 1),            # Per-page access rights. If set, the
                                                    # wr_en
                                                    # and
                                                    # rd_en
                                                    # fields
                                                    # of provided translation entries are valid and must specify
                                                    # the desired access rights.
                                                    # Can be set only when access_mode==MTT.
            BitField('mkey_umem_valid', 0, 1),      # Indicates if buffer is given directly by
                                                    # MTT
                                                    # list or by
                                                    # umem_id and umem_offset.
                                                    # When 0,
                                                    # MTT/KLM
                                                    # list.
                                                    # When 1, umem_offset and umem_offset ars valid
            BitField('reserved3', 0, 30),
            PacketField('sw_mkc', SwMkc(), SwMkc),    # MKey context.
            LongField('e_mtt_pointer', 0),          # Pointer to MTTs in ICM.
                                                    # Used instead of
                                                    # pas
                                                    # when global
                                                    # e
                                                    # bit is set (
                                                    # See
                                                    # Table  1165, "
                                                    # SET_HCA_CAP Input Structure Layout
                                                    # ," on
                                                    # page  1306
                                                    # ).
                                                    # mtt index should be 64 byte aligned (mtt_index_l[2:0]
                                                    # should be 0x0).
            LongField('e_bsf_pointer', 0),
            IntField('translations_octword_actual_size', 0),    # Actual number of octwords that contain translation
                                                    # entries. Can be 0 if no KLMs/MTTs are delivered.
            IntField('mkey_umem_id', 0),
            LongField('mkey_umem_offset', 0),
            IntField('bsf_octword_actual_size', 0),    # Actual number of octwords that contain translation
                                                    # entries. Can be 0 if no KLMs/MTTs are delivered.
            StrFixedLenField('reserved4', None, length=156),
            FieldListField('klm_pas_mtt', [0 for x in range(0)], IntField('', 0), count_from=lambda pkt:0),    # Translation entries and BSFs.
        ]

    class CreateMkeyOut(Packet):
        fields_desc = [
            ByteField('status', 0),
            BitField('reserved1', 0, 24),
            IntField('syndrome', 0),
            ByteField('reserved2', 0),
            BitField('mkey_index', 0, 24),          # MKey index
            StrFixedLenField('reserved3', None, length=4),
        ]
except Exception as _:
    SCAPY_SUPPORT = False


class ResourceDumpFetcher:
    """this class is responsible for getting all the segments of a the required dump.
    """
    # very big number that represent the inf number 2^32 - 1 (we will not reach that number)
    INF_DEPTH = 4294967295

    def __init__(self, device_name):
        self._sequence_number = ResourceDumpFetcher._sequence_incrementor()
        self._device_name = device_name
        self._start_seq_number = 0
        try:
            mst_device = mtcr.MstDevice(self._device_name)
            if mst_device.is_cable() or mst_device.is_linkx():
                raise Exception("Device is not supported")
            self.reg_access_obj = regaccess.RegAccess(mst_device)
        except Exception as e:
            raise Exception("{0}".format(e))

    @staticmethod
    def _create_segments(segments_data):
        """convert the data into a list of segments by calling the SegmentCreator.
        """
        return SegmentCreator().create(segments_data)

    def fetch_data(self, **kwargs):
        """this method fetch the segments of the required dump by:
           1. read the core dump register from the reg access while more dump bit is
        equal to  "1" and the sequence number is valid.
           2. use SegmentsCreator for converting it to a list of segments.
           3. iterate stage 1 and 2 according the depth parameter and in case reference
        segments found.
        """
        # read the inline data from the resource dump register and split it to segments list
        self._start_seq_number = 0
        inline_data = self._retrieve_resource_dump_inline_data(kwargs[cs.UI_ARG_SEGMENT], **kwargs)
        segments_list = self._create_segments(inline_data)
        segments_list_last_position = 0

        # go over oll the segments from the last position till the and of the segments list
        # and repeat it according the depth parameter
        if kwargs[cs.UI_ARG_DEPTH] == "inf":
            depth = ResourceDumpFetcher.INF_DEPTH
        else:
            depth = int(kwargs[cs.UI_ARG_DEPTH]) if kwargs[cs.UI_ARG_DEPTH] else 0

        for i in range(depth):
            inner_inline_data = []
            for seg in segments_list[segments_list_last_position:]:
                if seg.get_type() == constants.RESOURCE_DUMP_SEGMENT_TYPE_REFERENCE:
                    inner_inline_data.extend(
                        self._retrieve_resource_dump_inline_data(seg.reference_type, index1=seg.index1,
                                                                 index2=seg.index2, numOfObj1=seg.num_of_obj1,
                                                                 numOfObj2=seg.num_of_obj2, vHCAid=kwargs["vHCAid"]))

            segments_list_last_position = len(segments_list)
            segments_list.extend(self._create_segments(inner_inline_data))

            # relevant for inf mode, nothing to show, we can stop search for ref segments
            # because if refs found we expect that the segments list extend to do something
            if segments_list_last_position == len(segments_list):
                break

        return segments_list

    def _validate_sequence_number(self, current_seq_number):
        """validate that the sequence number was incremented.
        """
        return current_seq_number == next(self._sequence_number)

    @staticmethod
    def _sequence_incrementor():
        cnt = 0
        while True:
            yield cnt % 16
            cnt += 1

    def _retrieve_resource_dump_inline_data(self, segment_type, **kwargs):
        """call the resource dump access register and retrieve the inline data
        till more dump is '0'
        """
        global SCAPY_SUPPORT
        segment = int(segment_type, 16)
        seg_number = self._start_seq_number
        more_dump = 0
        vhca_id_valid = 0
        index1 = int(kwargs["index1"]) if kwargs["index1"] else 0
        index2 = int(kwargs["index2"]) if kwargs["index2"] else 0
        num_of_obj_1 = int(kwargs["numOfObj1"]) if kwargs["numOfObj1"] else 0
        num_of_obj_2 = int(kwargs["numOfObj2"]) if kwargs["numOfObj2"] else 0
        device_opaque = 0
        inline_data = []
        call_res_dump = True
        inline_dump = 1
        mkey = 0
        buf_size = 0
        address = 0

        if kwargs["vHCAid"] == None:
            vhca_id = 0
        else:
            vhca_id = int(kwargs["vHCAid"])
            vhca_id_valid = 1


        if kwargs["mem"] != None:
            try:
                self._create_mr_devx(kwargs["mem"], cs.MKEY_BUF_SIZE)
            except Exception as _:
                if SCAPY_SUPPORT == False:
                    raise Exception("Missing 'scapy' package, please install scapy")
                else:
                    raise Exception("mem mode is not supported, make sure rdma-core with devx package installed (part of ofed driver)")
            inline_dump = 0
            mkey = self.lkey
            buf_size = cs.MKEY_BUF_SIZE
            address = self.umem.umem_addr

        while call_res_dump:
            results = self.reg_access_obj.sendResDump(segment,  # "segment_type"
                                                      seg_number,  # "seq_num"  * need check
                                                      inline_dump,  # "inline_dump"
                                                      more_dump,  # "more_dump" *
                                                      vhca_id,  # "vHCAid"
                                                      vhca_id_valid,  # "vHCAid_valid"
                                                      index1,  # "index_1" *
                                                      index2,  # "index_2" *
                                                      num_of_obj_2,  # "num_of_obj_2" *
                                                      num_of_obj_1,  # "num_of_obj_1" *
                                                      device_opaque,  # "device_opaque" *
                                                      mkey,  # "mkey" 0
                                                      buf_size,  # "size" 0
                                                      address)  # "address" 0

            more_dump = results["more_dump"]
            vhca_id = results["vhca_id"]
            index1 = results["index_1"]
            index2 = results["index_2"]
            num_of_obj_1 = results["num_of_obj_1"]
            num_of_obj_2 = results["num_of_obj_2"]
            device_opaque = results["device_opaque"]
            size = int(math.ceil(results["size"] / 4))

            if kwargs["mem"] != None:
                # Read all dwords and change endianness
                my_data = []
                for i in range(size):
                    my_data.append(struct.unpack("<I", struct.pack(">I",  read32(self.umem.umem_addr, i)))[0])
                inline_data.extend(my_data)
            else:
                inline_data.extend(results["inline_data"][:size])
            
            if not self._validate_sequence_number(seg_number):
                raise Exception("E - wrong sequence number while calling resource dump register with seq num = {0}"
                                .format(seg_number))

            seg_number = results["seq_num"]
            self._start_seq_number = seg_number

            if more_dump == 0:
                call_res_dump = False
            
        # Release the resorces if use mem mode
        if kwargs["mem"] != None:
            self.mkey_obj.close()
            self.umem.close()

        return inline_data

    try:
        def _create_umem(self, ctx, size,
                    access=e.IBV_ACCESS_LOCAL_WRITE,
                    alignment=resource.getpagesize()):
            return Mlx5UMEM(ctx, size=size, alignment=alignment, access=access)

        def _create_mr_devx(self, rdma_device, buf_size):
            """This method create mkey and memory buffer using devx (part of ofed driver).
            """
            mlx5dv_attr = Mlx5DVContextAttr()
            self.ctx = Mlx5Context(mlx5dv_attr, name=rdma_device)
            self.my_pd = PD(self.ctx)
            self.dv_pd = Mlx5DvObj(dve.MLX5DV_OBJ_PD, pd=self.my_pd).dvpd
            self.umem = self._create_umem(self.ctx, buf_size)
            self.mkey_ctx = SwMkc(umr_en=0, lr=1, lw=1, access_mode_1_0=0x1, pd=self.dv_pd.pdn, start_addr=self.umem.umem_addr, len=buf_size)
            mkey_in = CreateMkeyIn(sw_mkc=self.mkey_ctx, mkey_umem_id=self.umem.umem_id, mkey_umem_valid=1)
            self.mkey_obj = Mlx5DevxObj(self.ctx, mkey_in, len(CreateMkeyOut()))
            mkey_out = CreateMkeyOut(self.mkey_obj.out_view)
            if mkey_out.status:
                raise PyverbsRDMAError('Failed to create mkey with syndrome '
                                    f'({mkey_out.syndrome}')
            mkey_index = mkey_out.mkey_index
            self.lkey = mkey_index << 8
    except Exception as _ :
        pass
