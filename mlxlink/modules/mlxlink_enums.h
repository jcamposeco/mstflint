/*
 * Copyright (c) 2020-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#ifndef MLXLINK_ENUMS_H
#define MLXLINK_ENUMS_H

// Common definitions
#define AMBER_VERSION       "1.64"

#define ACCESS_REG_PGUID    "PGUID"
#define ACCESS_REG_SPZR     "SPZR"
#define ACCESS_REG_SPAD     "SPAD"
#define ACCESS_REG_PPCNT    "PPCNT"
#define ACCESS_REG_PPHCR    "PPHCR"
#define ACCESS_REG_PDDR     "PDDR"
#define ACCESS_REG_PTYS     "PTYS"
#define ACCESS_REG_MPCNT    "MPCNT"
#define ACCESS_REG_MPEIN    "MPEIN"
#define ACCESS_REG_PMDR     "PMDR"
#define ACCESS_REG_PMCR     "PMCR"
#define ACCESS_REG_PLLP     "PLLP"
#define ACCESS_REG_MDDQ     "MDDQ"
#define ACCESS_REG_SLRG     "SLRG"
#define ACCESS_REG_SLTP     "SLTP"
#define ACCESS_REG_SLRIP    "SLRIP"
#define ACCESS_REG_SLRP     "SLRP"
#define ACCESS_REG_PPLL     "PPLL"
#define ACCESS_REG_SLSIR    "SLSIR"
#define ACCESS_REG_SLLM     "SLLM"
#define ACCESS_REG_MGIR     "MGIR"
#define ACCESS_REG_PMLP     "PMLP"
#define ACCESS_REG_MSGI     "MSGI"
#define ACCESS_REG_MDIR     "MDIR"
#define ACCESS_REG_MVCR     "MVCR"
#define ACCESS_REG_MTMP     "MTMP"
#define ACCESS_REG_MVCAP    "MVCAP"
#define ACCESS_REG_MTCAP    "MTCAP"
#define ACCESS_REG_SLRED    "SLRED"
#define ACCESS_REG_PLIB     "PLIB"
//define all used regs above this line

#define QSFP_CHANNELS       4
#define LANES_NUM           8
#define NUM_OF_BINS         16
#define MTMP_GEARBOX_SENSOR_OFFSET 256
#define LANES_NUM           8

// cables parse definition

#define SHIFT_0                       0
#define SHIFT_1                       1
#define SHIFT_2                       2
#define SHIFT_3                       3
#define SHIFT_4                       4
#define SHIFT_5                       5
#define SHIFT_6                       6
#define SHIFT_7                       7
#define SHIFT_8                       8
#define SHIFT_9                       9
#define SHIFT_10                      10
#define SHIFT_11                      11
#define SHIFT_12                      12
#define SHIFT_13                      13
#define SHIFT_14                      14
#define SHIFT_15                      15
/*
 * QSFP Paging, Page 0 Low
 */

/* Module Monitor Interrupt Flags - 6-8 */
#define QSFP_TEMP_AW_OFFSET         0x06
#define QSFP_TEMP_HALARM_STATUS     (1 << SHIFT_7)
#define QSFP_TEMP_LALARM_STATUS     (1 << SHIFT_6)
#define QSFP_TEMP_HWARN_STATUS      (1 << SHIFT_5)
#define QSFP_TEMP_LWARN_STATUS      (1 << SHIFT_4)

#define QSFP_VCC_AW_OFFSET          0x07
#define QSFP_VCC_HALARM_STATUS      (1 << SHIFT_7)
#define QSFP_VCC_LALARM_STATUS      (1 << SHIFT_6)
#define QSFP_VCC_HWARN_STATUS       (1 << SHIFT_5)
#define QSFP_VCC_LWARN_STATUS       (1 << SHIFT_4)

/* Channel Monitor Interrupt Flags - 9-21 */
#define QSFP_RX_PWR_12_AW_OFFSET    0x09
#define QSFP_RX_PWR_1_HALARM        (1 << SHIFT_7)
#define QSFP_RX_PWR_1_LALARM        (1 << SHIFT_6)
#define QSFP_RX_PWR_1_HWARN         (1 << SHIFT_5)
#define QSFP_RX_PWR_1_LWARN         (1 << SHIFT_4)
#define QSFP_RX_PWR_2_HALARM        (1 << SHIFT_3)
#define QSFP_RX_PWR_2_LALARM        (1 << SHIFT_2)
#define QSFP_RX_PWR_2_HWARN         (1 << SHIFT_1)
#define QSFP_RX_PWR_2_LWARN         (1 << SHIFT_0)

#define QSFP_RX_PWR_34_AW_OFFSET    0x0A
#define QSFP_RX_PWR_3_HALARM        (1 << SHIFT_7)
#define QSFP_RX_PWR_3_LALARM        (1 << SHIFT_6)
#define QSFP_RX_PWR_3_HWARN         (1 << SHIFT_5)
#define QSFP_RX_PWR_3_LWARN         (1 << SHIFT_4)
#define QSFP_RX_PWR_4_HALARM        (1 << SHIFT_3)
#define QSFP_RX_PWR_4_LALARM        (1 << SHIFT_2)
#define QSFP_RX_PWR_4_HWARN         (1 << SHIFT_1)
#define QSFP_RX_PWR_4_LWARN         (1 << SHIFT_0)

#define QSFP_TX_BIAS_12_AW_OFFSET    0x0B
#define QSFP_TX_BIAS_1_HALARM       (1 << SHIFT_7)
#define QSFP_TX_BIAS_1_LALARM       (1 << SHIFT_6)
#define QSFP_TX_BIAS_1_HWARN        (1 << SHIFT_5)
#define QSFP_TX_BIAS_1_LWARN        (1 << SHIFT_4)
#define QSFP_TX_BIAS_2_HALARM       (1 << SHIFT_3)
#define QSFP_TX_BIAS_2_LALARM       (1 << SHIFT_2)
#define QSFP_TX_BIAS_2_HWARN        (1 << SHIFT_1)
#define QSFP_TX_BIAS_2_LWARN        (1 << SHIFT_0)

#define QSFP_TX_BIAS_34_AW_OFFSET   0x0C
#define QSFP_TX_BIAS_3_HALARM       (1 << SHIFT_7)
#define QSFP_TX_BIAS_3_LALARM       (1 << SHIFT_6)
#define QSFP_TX_BIAS_3_HWARN        (1 << SHIFT_5)
#define QSFP_TX_BIAS_3_LWARN        (1 << SHIFT_4)
#define QSFP_TX_BIAS_4_HALARM       (1 << SHIFT_3)
#define QSFP_TX_BIAS_4_LALARM       (1 << SHIFT_2)
#define QSFP_TX_BIAS_4_HWARN        (1 << SHIFT_1)
#define QSFP_TX_BIAS_4_LWARN        (1 << SHIFT_0)

#define QSFP_TX_PWR_12_AW_OFFSET    0x0D
#define QSFP_TX_PWR_1_HALARM        (1 << SHIFT_7)
#define QSFP_TX_PWR_1_LALARM        (1 << SHIFT_6)
#define QSFP_TX_PWR_1_HWARN         (1 << SHIFT_5)
#define QSFP_TX_PWR_1_LWARN         (1 << SHIFT_4)
#define QSFP_TX_PWR_2_HALARM        (1 << SHIFT_3)
#define QSFP_TX_PWR_2_LALARM        (1 << SHIFT_2)
#define QSFP_TX_PWR_2_HWARN         (1 << SHIFT_1)
#define QSFP_TX_PWR_2_LWARN         (1 << SHIFT_0)

#define QSFP_TX_PWR_34_AW_OFFSET    0x0E
#define QSFP_TX_PWR_3_HALARM        (1 << SHIFT_7)
#define QSFP_TX_PWR_3_LALARM        (1 << SHIFT_6)
#define QSFP_TX_PWR_3_HWARN         (1 << SHIFT_5)
#define QSFP_TX_PWR_3_LWARN         (1 << SHIFT_4)
#define QSFP_TX_PWR_4_HALARM        (1 << SHIFT_3)
#define QSFP_TX_PWR_4_LALARM        (1 << SHIFT_2)
#define QSFP_TX_PWR_4_HWARN         (1 << SHIFT_1)
#define QSFP_TX_PWR_4_LWARN         (1 << SHIFT_0)

/* Module Monitoring Values - 22-33 */
#define QSFP_TEMP_CURR          0x16
#define QSFP_TEMP_MSB_OFFSET     0x16
#define QSFP_TEMP_LSB_OFFSET     0x17

#define QSFP_VCC_CURR           0x1A
#define QSFP_VCC_MSB_OFFSET      0x1A
#define QSFP_VCC_LSB_OFFSET      0x1B

/* Channel Monitoring Values - 34-81 */
#define QSFP_RX_PWR_1_OFFSET     0x22
#define QSFP_RX_PWR_2_OFFSET     0x24
#define QSFP_RX_PWR_3_OFFSET     0x26
#define QSFP_RX_PWR_4_OFFSET     0x28

#define QSFP_TX_BIAS_1_OFFSET    0x2A
#define QSFP_TX_BIAS_2_OFFSET    0x2C
#define QSFP_TX_BIAS_3_OFFSET    0x2E
#define QSFP_TX_BIAS_4_OFFSET    0x30

#define QSFP_TX_PWR_1_OFFSET     0x32
#define QSFP_TX_PWR_2_OFFSET     0x34
#define QSFP_TX_PWR_3_OFFSET     0x36
#define QSFP_TX_PWR_4_OFFSET     0x38

// Page 3 High
#define QSFP_TEMP_HALRM          0x00
#define QSFP_TEMP_LALRM          0x02
#define QSFP_TEMP_HWARN          0x04
#define QSFP_TEMP_LWARN          0x06

#define QSFP_VCC_HALRM           0x10
#define QSFP_VCC_LALRM           0x12
#define QSFP_VCC_HWARN           0x14
#define QSFP_VCC_LWARN           0x16

#define QSFP_RX_PWR_HALRM        0x30
#define QSFP_RX_PWR_LALRM        0x32
#define QSFP_RX_PWR_HWARN        0x34
#define QSFP_RX_PWR_LWARN        0x36

#define QSFP_TX_BIAS_HALRM       0x38
#define QSFP_TX_BIAS_LALRM       0x3A
#define QSFP_TX_BIAS_HWARN       0x3C
#define QSFP_TX_BIAS_LWARN       0x3E

#define QSFP_TX_PWR_HALRM        0x40
#define QSFP_TX_PWR_LALRM        0x42
#define QSFP_TX_PWR_HWARN        0x44
#define QSFP_TX_PWR_LWARN        0x46

// SFP 51 Paging, Page 0x1 Low
#define SFP51_BASE               0x100

/* A2-based offsets for DOM */

#define SFP51_TEMP_HALRM         0
#define SFP51_TEMP_LALRM         2
#define SFP51_TEMP_HWARN         4
#define SFP51_TEMP_LWARN         6

#define SFP51_VCC_HALRM          8
#define SFP51_VCC_LALRM          10
#define SFP51_VCC_HWARN          12
#define SFP51_VCC_LWARN          14

#define SFP51_BIAS_HALRM         16
#define SFP51_BIAS_LALRM         18
#define SFP51_BIAS_HWARN         20
#define SFP51_BIAS_LWARN         22

#define SFP51_TX_PWR_HALRM       24
#define SFP51_TX_PWR_LALRM       26
#define SFP51_TX_PWR_HWARN       28
#define SFP51_TX_PWR_LWARN       30

#define SFP51_RX_PWR_HALRM       32
#define SFP51_RX_PWR_LALRM       34
#define SFP51_RX_PWR_HWARN       36
#define SFP51_RX_PWR_LWARN       38

#define SFP51_TEMP               96
#define SFP51_VCC                98
#define SFP51_BIAS               100
#define SFP51_TX_PWR             102
#define SFP51_RX_PWR             104

#define SFP51_ALRM_FLG              112
#define SFP51_TX_PWR_LALRM_FLG      (1 << SHIFT_0)
#define SFP51_TX_PWR_HALRM_FLG      (1 << SHIFT_1)
#define SFP51_BIAS_LALRM_FLG        (1 << SHIFT_2)
#define SFP51_BIAS_HALRM_FLG        (1 << SHIFT_3)
#define SFP51_VCC_LALRM_FLG         (1 << SHIFT_4)
#define SFP51_VCC_HALRM_FLG         (1 << SHIFT_5)
#define SFP51_TEMP_LALRM_FLG        (1 << SHIFT_6)
#define SFP51_TEMP_HALRM_FLG        (1 << SHIFT_7)
#define SFP51_RX_PWR_LALRM_FLG      (1 << SHIFT_14)
#define SFP51_RX_PWR_HALRM_FLG      (1 << SHIFT_15)

#define SFP51_WARN_FLG              116
#define SFP51_TX_PWR_LWARN_FLG      (1 << SHIFT_0)
#define SFP51_TX_PWR_HWARN_FLG      (1 << SHIFT_1)
#define SFP51_BIAS_LWARN_FLG        (1 << SHIFT_2)
#define SFP51_BIAS_HWARN_FLG        (1 << SHIFT_3)
#define SFP51_VCC_LWARN_FLG         (1 << SHIFT_4)
#define SFP51_VCC_HWARN_FLG         (1 << SHIFT_5)
#define SFP51_TEMP_LWARN_FLG        (1 << SHIFT_6)
#define SFP51_TEMP_HWARN_FLG        (1 << SHIFT_7)
#define SFP51_RX_PWR_LWARN_FLG      (1 << SHIFT_14)
#define SFP51_RX_PWR_HWARN_FLG      (1 << SHIFT_15)

/*
 * QSFP-DD Paging, Page 0 Low
 */

/* Module Monitor Interrupt Flags */
#define QSFP_DD_MODULE_INFO_OFFSET     0x09
#define CMIS_TEMP_HALARM_STATUS     (1 << SHIFT_3)
#define CMIS_TEMP_LALARM_STATUS     (1 << SHIFT_2)
#define CMIS_TEMP_HWARN_STATUS      (1 << SHIFT_1)
#define CMIS_TEMP_LWARN_STATUS      (1 << SHIFT_0)
#define CMIS_VCC_HALARM_STATUS      (1 << SHIFT_7)
#define CMIS_VCC_LALARM_STATUS      (1 << SHIFT_6)
#define CMIS_VCC_HWARN_STATUS       (1 << SHIFT_5)
#define CMIS_VCC_LWARN_STATUS       (1 << SHIFT_4)

/* Channels Monitor Interrupt Flags */
// QSFP-DD from upper page 0x11
#define QSFP_DD_TX_POWER_HALARM_OFFSET  0x8b // 0:7 for 8 channels
#define QSFP_DD_TX_POWER_LALARM_OFFSET  0x8c // 0:7 for 8 channels
#define QSFP_DD_TX_POWER_HWARN_OFFSET   0x8d // 0:7 for 8 channels
#define QSFP_DD_TX_POWER_LWARN_OFFSET   0x8e // 0:7 for 8 channels

#define QSFP_DD_TX_BIAS_HALARM_OFFSET   0x8f // 0:7 for 8 channels
#define QSFP_DD_TX_BIAS_LALARM_OFFSET   0x90 // 0:7 for 8 channels
#define QSFP_DD_TX_BIAS_HWARN_OFFSET    0x91 // 0:7 for 8 channels
#define QSFP_DD_TX_BIAS_LWARN_OFFSET    0x92 // 0:7 for 8 channels

#define QSFP_DD_RX_POWER_HALARM_OFFSET  0x95 // 0:7 for 8 channels
#define QSFP_DD_RX_POWER_LALARM_OFFSET  0x96 // 0:7 for 8 channels
#define QSFP_DD_RX_POWER_HWARN_OFFSET   0x97 // 0:7 for 8 channels
#define QSFP_DD_RX_POWER_LWARN_OFFSET   0x98 // 0:7 for 8 channels

// Thresholds from upper page 0x2
#define QSFP_DD_TEMP_THR_OFFSET         0x80 // halarm 80, lalarm 82, hwarn 84, lwarn 86
#define QSFP_DD_VCC_THR_OFFSET          0x88 // halarm 88, lalarm 90, hwarn 92, lwarn 94
#define QSFP_DD_TX_POWER_THR_OFFSET     0xb0 // halarm b0, lalarm b2, hwarn b4, lwarn b6
#define QSFP_DD_TX_BIAS_THR_OFFSET      0xb8 // halarm b8, lalarm ba, hwarn bc, lwarn be
#define QSFP_DD_RX_POWER_THR_OFFSET     0xc0 // halarm c0, lalarm c2, hwar9n c4, lwarn c6

// SFP-DD from lower page 0
/* Module Monitor Interrupt Flags */
#define SFP_DD_MODULE_INFO_OFFSET      0x11
// See QSFP-DD module section for mask info

#define SFP_DD_VCC_AW_OFFSET           0x11
#define SFP_DD_VCC_HALARM_STATUS      (1 << SHIFT_7)
#define SFP_DD_VCC_LALARM_STATUS      (1 << SHIFT_6)
#define SFP_DD_VCC_HWARN_STATUS       (1 << SHIFT_5)
#define SFP_DD_VCC_LWARN_STATUS       (1 << SHIFT_4)

// Channels monitor interrupt flags from lower page 0x0
#define SFP_DD_TX_POWER_INT_OFFSET      0x8
#define SFP_DD_TX_BIAS_INT_OFFSET       0x9
#define SFP_DD_RX_POWER_INT_OFFSET      0x7
#define SFP_DD_HALARM_STATUS            SHIFT_0 // 0:1 for 2 channels
#define SFP_DD_LALARM_STATUS            SHIFT_2 // 2:3 for 2 channels
#define SFP_DD_HWARN_STATUS             SHIFT_4 // 4:5 for 2 channels
#define SFP_DD_LWARN_STATUS             SHIFT_6 // 6:7 for 2 channels

// Thresholds from upper page 0x2
#define SFP_DD_TEMP_THR_OFFSET          0xb1 // halarm b1, lalarm b3, hwarn b5, lwarn b7
#define SFP_DD_VCC_THR_OFFSET           0xb9 // halarm b9, lalarm bb, hwarn bd, lwarn bf
#define SFP_DD_TX_POWER_THR_OFFSET      0xd1 // halarm d1, lalarm d3, hwarn d5, lwarn d7
#define SFP_DD_TX_BIAS_THR_OFFSET       0xd9 // halarm d9, lalarm db, hwarn dd, lwarn df
#define SFP_DD_RX_POWER_THR_OFFSET      0xe1 // halarm e1, lalarm e3, hwarn e5, lwarn e7

// Mlxlink Values definition
#define SWID                        0
#define PPRT_PPTT_ENABLE            1
#define PPRT_PPTT_START_TUNING      1
#define PHY_TEST_MODE_STATUS        1

#define BIT_MASK_ALL_DWORD          0xffffffff

#define OB_TAP_SUM                  120
#define OB_TAP_DIFF                 10
#define OB_BIAS_LOW_THRESHOLD       15
#define OB_BIAS_MID_1_THRESHOLD     31
#define OB_BIAS_MID_2_THRESHOLD     48
#define OB_BIAS_HIGH_THRESHOLD      63

#define MAX_LOCAL_PORT_ETH          64
#define MAX_LOCAL_PORT_IB           36
#define MAX_LOCAL_PORT_QUANTUM      82
#define MAX_LOCAL_PORT_QUANTUM2     130
#define MAX_LOCAL_PORT_SPECTRUM2    128
#define MAX_LOCAL_PORT_SPECTRUM4    256

#define DBN_TO_LOCAL_PORT_BASE      60

#define MAX_LANES_NUMBER            4
#define MAX_DWORD_BLOCK_SIZE        32
#define MAX_TX_GROUP_COUNT          10

#define PCAM_FORCE_DOWN_CAP_MASK    0x2000

#define OPERATIONAL_ERROR_STR       "ME_ICMD_OPERATIONAL_ERROR"

#define MAX_SBYTE                   127
#define MIN_SBYTE                   -128
#define MAX_INPUT_LENGTH            7
#define SECOND_LEVEL_PORT_ACCESS    2
#define THIRD_LEVEL_PORT_ACCESS     3

// mlxlink commander enums
enum PPAOS_ADMIN {
    PPAOS_REGULAR_OPERATION = 0,
    PPAOS_PHY_TEST_MODE = 1
};

enum TX_INDEX_SELECTOR
{
    TX_LOCAL_PORT,
    TX_GROUP
};

enum BER_LIMIT {
    NOMINAL_25G_NO_FEC = -15,
    NOMINAL_25G_LOW_ATTN = -13,
    NOMINAL_25G_HIGH_ATTN = -9,
    NOMINAL_10G = -14,
    NOMINAL_56G_40G = -15,
    NOMINAL_DEFAULT = -15,
    CORNER_25G_NO_FEC = -14,
    CORNER_25G_LOW_ATTN = -10,
    CORNER_25G_HIGH_ATTN = -7,
    CORNER_10G = -13,
    CORNER_56G_40G = -14,
    CORNER_DEFAULT = -14
};

enum PAOS_ADMIN {
    PAOS_UP = 1,
    PAOS_DOWN = 2
};

enum PCIE_PORT_TYPE {
    PORT_TYPE_EP = 0,
    PORT_TYPE_US = 5,
    PORT_TYPE_DS = 6
};

enum MODULE_ID {
    MODULE_ID_SFP       = 0x3,
    MODULE_ID_QSFP      = 0xC,
    MODULE_ID_QSFP_PLUS = 0xD,
    MODULE_ID_QSFP28    = 0x11,
};

// common enums
typedef enum {
    NO,
    UP,
    DN,
    TG
} PAOS_CMD;

enum MPCNT_GROUPS {
    MPCNT_PERFORMANCE_GROUP = 0,
    MPCNT_LANE_GROUP = 1,
    MPCNT_TIMERS_GROUPS = 2
};

enum PDDR_PAGES {
    PDDR_OPERATIONAL_INFO_PAGE = 0,
    PDDR_TROUBLESHOOTING_INFO_PAGE = 1,
    PDDR_MODULE_INFO_PAGE = 3,
    PDDR_MODULE_LATCHED_FLAG_INFO_PAGE = 9,
};

enum GROUP_OPCODE {
    MONITOR_OPCODE = 0,
    ADVANCED_OPCODE = 1
};

enum PPCNT_GROUPS {
    PPCNT_RFC_2863_GROUP = 0x1,
    PPCNT_DISC_COUNTERS_GROUP = 0x6,
    PPCNT_PHY_GROUP = 0x12,
    PPCNT_STATISTICAL_GROUP = 0x16,
    PPCNT_IB_PORT_COUNTERS_GROUP = 0x20,
    PPCNT_EXT_IB_PORT_COUNTERS_GROUP = 0x21,
    PPCNT_PLR_GROUP = 0x22,
    PPCNT_HISTOGRAM_GROUP = 0x23,
    PPCNT_IB_PKTS_GROUP = 0x24,
    PPCNT_ALL_GROUPS = 63,
};

enum NETWORK_PORT_TYPE {
    NETWORK_PORT_TYPE = 0,
    NETWORK_PORT_TYPE_NEAR,
    NETWORK_PORT_TYPE_IC_LR,
    NETWORK_PORT_TYPE_FAR,
    NETWORK_PORT_TYPE_MAIN_USR,
    NETWORK_PORT_TYPE_TILE_USR,

    NETWORK_PORT_TYPE_LAST //PCIE always last enum
};

enum CABLE_TYPE {
    UNIDENTIFIED,
    ACTIVE,
    OPTICAL_MODULE,
    PASSIVE,
    UNPLUGGED
};

enum PCIE_LINK_SPEED {
    GEN1 = 1,
    GEN2 = 2,
    GEN3 = 4,
    GEN4 = 16,
    GEN5 = 32
};

enum POWER_CLASS {
    POWER_CLASS0,
    POWER_CLASS1,
    POWER_CLASS2,
    POWER_CLASS3,
    POWER_CLASS4,
    POWER_CLASS5,
    POWER_CLASS6,
    POWER_CLASS7,
    POWER_CLASS8
};

enum PRBS_MODES {
    PRBS_TX,
    PRBS_RX
};
enum PRBS_TX_MODE {
    SQUARE_WAVEA = 13,
    SQUARE_WAVEB,
    SQUARE_WAVEC,
    SQUARE_WAVED
};

enum PRBS_RX_MODE {
    SQUARE_WAVE = 13
};

enum PRBS_RX_TX_MODE {
    PRBS31,
    PRBS23A,
    PRBS23B,
    PRBS23C,
    PRBS23D,
    PRBS7,
    PRBS11,
    PRBS11A,
    PRBS11B,
    PRBS11C,
    PRBS11D,
    PRBS9,
    IDLE,
    PRBS13A = 17,
    PRBS13B,
    PRBS13C,
    PRBS13D,
    SSPR,
    SSPRQ,
    LT_frames,
    PRBS15,
    PRBS28,
    SQUARE_WAVE3,
    SQUARE_WAVE13,
    SQUARE_WAVE30
};

enum PRBS_CAP {
    PRBS31_CAP = 0x1,
    PRBS23A_CAP = 0x2,
    PRBS23B_CAP = 0x4,
    PRBS23C_CAP = 0x8,
    PRBS23D_CAP = 0x10,
    PRBS7_CAP = 0x20,
    PRBS11_CAP = 0x40,
    PRBS11A_CAP = 0x80,
    PRBS11B_CAP = 0x100,
    PRBS11C_CAP = 0x200,
    PRBS11D_CAP = 0x400,
    PRBS9_CAP = 0x800,
    PRBSIDLE_CAP = 0x1000,
    SQUARE_WAVEA_CAP = 0x2000,
    SQUARE_WAVEB_CAP = 0x4000,
    SQUARE_WAVEC_CAP = 0x8000,
    SQUARE_WAVED_CAP = 0x10000,
    PRBS13A_CAP = 0x20000,
    PRBS13B_CAP = 0x40000,
    PRBS13C_CAP = 0x80000,
    PRBS13D_CAP = 0x100000,
    SSPR_CAP = 0x200000,
    SSPRQ_CAP = 0x400000
};

enum LANE_RATE_CAP {
    LANE_RATE_1G_CAP    = 0x1,
    LANE_RATE_SDR_CAP   = 0x2,
    LANE_RATE_XAUI_CAP  = 0x4,
    LANE_RATE_DDR_CAP   = 0x8,
    LANE_RATE_QDR_CAP   = 0x10,
    LANE_RATE_FDR10_CAP = 0x20,
    LANE_RATE_FDR_CAP   = 0x40,
    LANE_RATE_EDR_CAP   = 0x80,
    LANE_RATE_50G_CAP   = 0x100,
    LANE_RATE_HDR_CAP   = 0x200,
    LANE_RATE_NDR_CAP   = 0x400,
};

enum PRBS_LANE_RATE {
    PRBS_SDR,
    PRBS_DDR,
    PRBS_QDR,
    PRBS_FDR10,
    PRBS_FDR,
    PRBS_EDR,
    PRBS_HDR,
    PRBS_NDR,
    PRBS_1G = 10,
    PRBS_XAUI = 11,
    PRBS_50G = 12
};

enum PRBS_TUNING_STATUS {
    PRBS_TUNING_NOT_PERFORMED,
    PRBS_TUNING_PERFORMING,
    PRBS_TUNING_COMPLETE,
    PRBS_SIGNAL_DETECT
};

enum SLRG_PARAMS {
    SLRG_PARAMS_INITIAL_FOM,
    SLRG_PARAMS_FOM_MODE,
    SLRG_PARAMS_UPPER_EYE,
    SLRG_PARAMS_MID_EYE,
    SLRG_PARAMS_LOWER_EYE,
    SLRG_PARAMS_LAST_FOM,
    SLRG_PARAMS_LAST
};

enum SLTP_40_28NM_PARAMS {
    POLARITY,
    OB_TAP0,
    OB_TAP1,
    OB_TAP2,
    OB_BIAS,
    OB_PREEMP_MODE,
    OB_REG,
    OB_LEVA,
    PARAMS_40NM_LAST
};

enum SLTP_16NM_PARAMS {
    PRE_2_TAP,
    PRE_TAP,
    MAIN_TAP,
    POST_TAP,
    OB_M2LP,
    OB_AMP,
    OB_ALEV_OUT,
    PARAMS_16NM_LAST
};

enum SLTP_7NM_PARAMS {
    FIR_PRE3,
    FIR_PRE2,
    FIR_PRE1,
    FIR_MAIN,
    FIR_POST1,
    PARAMS_7NM_LAST
};

enum FEC_MODE {
    NO_FEC = 1,
    FC_FEC = 2,
    RS_FEC = 4
};

enum FEC_REQUSET {
    FEC_REQUSET_NF = 0x1,
    FEC_REQUSET_FC = 0x2,
    FEC_REQUSET_RS528 = 0x4,
    FEC_REQUSET_RS271 = 0x8,
    FEC_REQUSET_RS277 = 0x10,
    FEC_REQUSET_RS163 = 0x20,
    FEC_REQUSET_ZLF = 0x40,
};

enum FEC_MODE_ACTIVE {
    FEC_MODE_NO_FEC = 0,
    FEC_MODE_FIRECODE_FEC = 1,
    FEC_MODE_STANDARD_RS_FEC_528_514 = 2,
    FEC_MODE_STANDARD_LL_FEC_271_257 = 3,
    FEC_MODE_INTERLEAVED_STANDARD_RS_FEC_544_514 = 6,
    FEC_MODE_STANDARD_RS_FEC_544_514 = 7,
    FEC_MODE_RS_FEC_272_257 = 9,
    FEC_MODE_INTERLEAVED_RS_FEC_272_257 = 10,
    FEC_MODE_RS_FEC_544_514_PLR = 12,
    FEC_MODE_RS_FEC_271_257_PLR = 13,
    FEC_MODE_RS_FEC_PLR_272_257 = 14,
};

enum DATA_PATH_STATE {
    DATA_PATH_STATE_RES         = 0,
    DATA_PATH_STATE_DEACTIVATED = 0x1,
    DATA_PATH_STATE_INIT        = 0x2 ,
    DATA_PATH_STATE_DEINIT      = 0x3,
    DATA_PATH_STATE_ACTIVATED   = 0x4,
    DATA_PATH_STATE_TX_TURN_ON  = 0x5,
    DATA_PATH_STATE_TX_TURN_OFF = 0x6,
    DATA_PATH_STATE_INITALIZED  = 0x7,
};

enum ERROR_CODE_RES{
    ERROR_CODE_RES_CONFIG_UNDEF             = 0,
    ERROR_CODE_RES_CONFIG_SUCC              = 0x1,
    ERROR_CODE_RES_CONFIG_REJ               = 0x2,
    ERROR_CODE_RES_CONFIG_REJ_INV_APP_SEI   = 0x3,
    ERROR_CODE_RES_CONFIG_REJ_INV_DATA_PTH  = 0x4,
    ERROR_CODE_RES_CONFIG_REJ_INV_SI        = 0x5,
    ERROR_CODE_RES_CONFIG_REJ_LANES_IN_USE  = 0x6,
    ERROR_CODE_RES_CONFIG_REJ_PART_DATA_PTH = 0x7,
    ERROR_CODE_RES_CONFIG_IN_PROG           = 0xc,
    ERROR_CODE_RES_CONFIG_REJ_CUST          = 0xd,
};

enum CABLE_IDENTIFIER {
    IDENTIFIER_QSFP28,
    IDENTIFIER_QSFP_PLUS,
    IDENTIFIER_SFP,
    IDENTIFIER_QSA,
    IDENTIFIER_BACKPLANE,
    IDENTIFIER_SFP_DD,
    IDENTIFIER_QSFP_DD,
    IDENTIFIER_QSFP_CMIS,
    IDENTIFIER_OSFP,
    IDENTIFIER_C2C,
    IDENTIFIER_DSFP,
    IDENTIFIER_QSFP_SPLIT_CABLE
};

enum CABLE_TECHNOLOGY {
    TECHNOLOGY_850NM_VCSEL = 0x0,
    TECHNOLOGY_1310NM_VCSEL,
    TECHNOLOGY_1550NM_VCSEL,
    TECHNOLOGY_1310NM_FP,
    TECHNOLOGY_1310NM_DFB,
    TECHNOLOGY_1550NM_DFB,
    TECHNOLOGY_1310NM_EML,
    TECHNOLOGY_1550NM_EML,
    TECHNOLOGY_OTHERS,
    TECHNOLOGY_1490NM_DFB,
    TECHNOLOGY_COP_UNEQ,
    TECHNOLOGY_COP_PASV,
    TECHNOLOGY_COP_NEAR_FAR_END,
    TECHNOLOGY_COP_FAR_END,
    TECHNOLOGY_COP_NEAR_END,
    TECHNOLOGY_COP_LINEAR
};

enum OUI {
    OTHER,
    MELLANOX,
    KNOWN_OUI,
    NVIDIA
};

enum ProtoActive {
    IB = 1,
    ETH = 4
};
enum BAD_SET_STATUS_40_28NM {
    SET_STATUS_INVALID_PARM = 0,
    SET_STATUS_ILLEGAL_OB_BAIS = 0x1,
    SET_STATUS_ILLEGAL_OB_TAPS_POLARITY = 0x2,
    SET_STATUS_UNKNOWN
};

enum BAD_SET_STATUS_16NM {
    SET_STATUS16_INVALID_PARM = 0x1,
    SET_STATUS16_ILLEGAL_M2LP_AMP = 0x800,
    SET_STATUS16_ILLEGAL_M2LP = 0x1000,
    SET_STATUS16_ILLEGAL_AMP = 0x2000,
    SET_STATUS16_ILLEGAL_ALEV_OUT = 0x4000,
    SET_STATUS16_ILLEGAL_TAPS = 0x8000,
    SET_STATUS16_UNKNOWN
};

enum BAD_STAT_7NM {
    BAD_STAT_7NM_INVALID_PRE3 = 0x1,
    BAD_STAT_7NM_INVALID_PRE2 = 0x2,
    BAD_STAT_7NM_INVALID_PRE1 = 0x4,
    BAD_STAT_7NM_INVALID_MAIN = 0x8,
    BAD_STAT_7NM_INVALID_POST = 0x10,
    BAD_STAT_7NM_INVALID_SUM = 0x20,
    BAD_STAT_7NM_TAP_SPEED_MISMATCH = 0x40
};

enum EXT_ETHERNET_COMPLIANCE_CODE {
    EXT_ETHERNET_COMPLIANCE_CODE_Unspecified = 0,
    EXT_ETHERNET_COMPLIANCE_CODE_100G_AOC_FEC = 0x1,
    EXT_ETHERNET_COMPLIANCE_CODE_100GBASE_SR4 = 0x2,
    EXT_ETHERNET_COMPLIANCE_CODE_100GBASE_LR4 = 0x3,
    EXT_ETHERNET_COMPLIANCE_CODE_100GBASE_ER4 = 0x4,
    EXT_ETHERNET_COMPLIANCE_CODE_100GBASE_SR10 = 0x5,
    EXT_ETHERNET_COMPLIANCE_CODE_100G_CWDM4 = 0x6,
    EXT_ETHERNET_COMPLIANCE_CODE_100G_PSM4 = 0x7,
    EXT_ETHERNET_COMPLIANCE_CODE_100G_ACC_FEC = 0x8,
    EXT_ETHERNET_COMPLIANCE_CODE_100GBASE_CR4 = 0xB,
    EXT_ETHERNET_COMPLIANCE_CODE_25GBASE_CR_CA_S = 0xC,
    EXT_ETHERNET_COMPLIANCE_CODE_25GBASE_CR_CA_N = 0xD,
    EXT_ETHERNET_COMPLIANCE_CODE_40GBASE_ER4 = 0x10,
    EXT_ETHERNET_COMPLIANCE_CODE_4_x_10GBASE_SR = 0x11,
    EXT_ETHERNET_COMPLIANCE_CODE_40G_PSM4 = 0x12,
    EXT_ETHERNET_COMPLIANCE_CODE_G959_1_P1I1_2D1 = 0x13,
    EXT_ETHERNET_COMPLIANCE_CODE_G959_1_P1S1_2D2 = 0x14,
    EXT_ETHERNET_COMPLIANCE_CODE_G959_1_P1L1_2D2 = 0x15,
    EXT_ETHERNET_COMPLIANCE_CODE_10GBASE_T = 0x16,
    EXT_ETHERNET_COMPLIANCE_CODE_100G_CLR4 = 0x17,
    EXT_ETHERNET_COMPLIANCE_CODE_100G_AOC = 0x18,
    EXT_ETHERNET_COMPLIANCE_CODE_100G_ACC = 0x19,
    EXT_ETHERNET_COMPLIABCE_CODE_100G_DWDM2 = 0X1A,
    EXT_ETHERNET_COMPLIABCE_CODE_100G_1550NM_WDM = 0X1B,
    EXT_ETHERNET_COMPLIABCE_CODE_10GBASE_T = 0X1C,
    EXT_ETHERNET_COMPLIABCE_CODE_5GBASE_T = 0X1D,
    EXT_ETHERNET_COMPLIABCE_CODE_2_5GBASE_T = 0X1E,
    EXT_ETHERNET_COMPLIABCE_CODE_40G_SWDM4 = 0X1F,
    EXT_ETHERNET_COMPLIABCE_CODE_100G_SWDM4 = 0X20,
    EXT_ETHERNET_COMPLIABCE_CODE_100G_PAM4 = 0X21,
    EXT_ETHERNET_COMPLIABCE_CODE_4WDM10_MSA = 0X22,
    EXT_ETHERNET_COMPLIABCE_CODE_4WDM20_MSA = 0X23,
    EXT_ETHERNET_COMPLIABCE_CODE_4WDM40_MSA = 0X24,
    EXT_ETHERNET_COMPLIABCE_CODE_100GBASE_DR = 0X25,
    EXT_ETHERNET_COMPLIABCE_CODE_100G_FR = 0X26,
    EXT_ETHERNET_COMPLIABCE_CODE_100G_LR = 0X27,
    EXT_ETHERNET_COMPLIABCE_CODE_ACC_10_6 = 0X30,
    EXT_ETHERNET_COMPLIABCE_CODE_AOC_10_6 = 0X31,
    EXT_ETHERNET_COMPLIABCE_CODE_ACC_10_4 = 0X32,
    EXT_ETHERNET_COMPLIABCE_CODE_AOC_10_4 = 0X33,
    EXT_ETHERNET_COMPLIABCE_CODE_50GBASE_CR = 0X40,
    EXT_ETHERNET_COMPLIABCE_CODE_50GBASE_SR = 0X41,
    EXT_ETHERNET_COMPLIABCE_CODE_50GBASE_FR  = 0X42,
    EXT_ETHERNET_COMPLIABCE_CODE_200GBASE_FR4 = 0X43,
    EXT_ETHERNET_COMPLIABCE_CODE_200GBASE_1550NM_PSM4 = 0X44,
    EXT_ETHERNET_COMPLIABCE_CODE_50GBASE_LR = 0X45,
    EXT_ETHERNET_COMPLIABCE_CODE_200GBASE_LR4 = 0X46,
};

enum CMIS_IB_COMPLIANCE_CODE{
    CMIS_IB_COMPLIANCE_CODE_SDR = 0,
    CMIS_IB_COMPLIANCE_CODE_DDR = 0x2,
    CMIS_IB_COMPLIANCE_CODE_QDR = 0x4,
    CMIS_IB_COMPLIANCE_CODE_FDR = 0x8,
    CMIS_IB_COMPLIANCE_CODE_EDR = 0x10,
    CMIS_IB_COMPLIANCE_CODE_HDR = 0x20,
    CMIS_IB_COMPLIANCE_CODE_NDR = 0x40
};

enum QSFP_CABLE_BREAKOUT_NEAR_END{
    QSFP_CABLE_BREAKOUT_CHANNEL_1_STATUS = 0,
    QSFP_CABLE_BREAKOUT_CHANNEL_2_STATUS = 0x2,
    QSFP_CABLE_BREAKOUT_CHANNEL_3_STATUS = 0x4,
    QSFP_CABLE_BREAKOUT_CHANNEL_4_STATUS = 0x8,
};

enum RX_TX_CDR_CAP {
    RX_TX_CDR_CAP_NO_CDR = 0,
    RX_TX_CDR_CAP_BUILD_IN_CDR_WITH_ON_OFF_CONTROL = 0x1,
    RX_TX_CDR_CAP_BUILD_IN_CDR_WITHOUT_ON_OFF_CONTROL = 0x2,
};

enum RX_POWER_TYPE {
    RX_POWER_TYPE_OMA = 0,
    RX_POWER_TYPE_AVERAGE_POWER = 0x1,
};

enum CIMS_MODULE_ST {
    CIMS_MODULE_ST_RESERVED     = 0,
    CIMS_MODULE_ST_LOWPWR_STATE = 0x1,
    CIMS_MODULE_ST_PWRUP_STATE  = 0x2,
    CIMS_MODULE_ST_READY_STATE  = 0x3,
    CIMS_MODULE_ST_PWRDN_STATE  = 0x4,
    CIMS_MODULE_ST_FAULT_STATE  = 0x5,

};

enum TEMP_FLAGS{
    TEMP_FLAGS_NO_ALARM_WARN   = 0,
    TEMP_FLAGS_HI_TEMP_ALARM   = 0x1,
    TEMP_FLAGS_LO_TEMP_ALARM   = 0x2,
    TEMP_FLAGS_HI_TEMP_WARNING = 0x4,
    TEMP_FLAGS_LO_TEMP_WARNING = 0x8,
};

enum VCC_FLAGS{
    VCC_FLAGS_NO_ALARM_WARN  = 0,
    VCC_FLAGS_HI_VCC_ALARM   = 0x1,
    VCC_FLAGS_LO_VCC_ALARM   = 0x2,
    VCC_FLAGS_HI_VCC_WARNING = 0x4,
    VCC_FLAGS_LO_VCC_WARNING = 0x8,
};

enum QSFP_CABLE_BREAKOUT_FAR_END{
    QSFP_CABLE_BREAKOUT_CABLE_FAR_END_IS_UNSPECIFIED                                        = 0,
    QSFP_CABLE_BREAKOUT_CABLE_SINGLE_FAR_END_4_CHANNELS_IMPLEM_OR_SEPAR_MOD_4_CHANNEL_CONN  = 0x1,
    QSFP_CABLE_BREAKOUT_CABLE_SINGLE_FAR_END_2_CHANNELS_IMPLEM_OR_SEPAR_MOD_2_CHANNEL_CONN  = 0x2,
    QSFP_CABLE_BREAKOUT_CABLE_SINGLE_FAR_END_1_CHANNELS_IMPLEM_OR_SEPAR_MOD_1_CHANNEL_CONN  = 0x3,
    QSFP_CABLE_BREAKOUT_4_FAR_ENDS_1_CHANNELS_IMPLEM_IN_EACH                                = 0x4,
    QSFP_CABLE_BREAKOUT_2_FAR_ENDS_2_CHANNELS_IMPLEM_IN_EACH                                = 0x5,
    QSFP_CABLE_BREAKOUT_2_FAR_ENDS_1_CHANNELS_IMPLEM_IN_EACH                                = 0x6,
};

enum CMIS_CABLE_BREAKOUT{
    CMIS_CABLE_BREAKOUT_UNSPECIFIED                 = 0,
    CMIS_CABLE_BREAKOUT_QSFPDD_to_QSFPDD            = 0x1,
    CMIS_CABLE_BREAKOUT_QSFPDD_to_2QSFP_or_2QSFPDD  = 0x2,
    CMIS_CABLE_BREAKOUT_QSFPDD_to_4SFPDD_or_4QSFP   = 0x3,
    CMIS_CABLE_BREAKOUT_QSFPDD_to_8SFP              = 0x4,
    CMIS_CABLE_BREAKOUT_QSFPDD_to_QSFP_or_QSFPDD    = 0x5,
    CMIS_CABLE_BREAKOUT_QSFPDD_to_2QSFP             = 0x6,
    CMIS_CABLE_BREAKOUT_QSFPDD_to_4SFP              = 0x7,
    CMIS_CABLE_BREAKOUT_SFPDD_to_SFPDD              = 0x8,
    CMIS_CABLE_BREAKOUT_SFPDD_to_2SFPDD             = 0x9,
};

enum QSFP_ETHERNET_COMPLIANCE_CODE {
    QSFP_ETHERNET_COMPLIANCE_CODE_Unspecified = 0,
    QSFP_ETHERNET_COMPLIANCE_CODE_40G_ACTIVE_CABLE_XLPPI = 0x1,
    QSFP_ETHERNET_COMPLIANCE_CODE_40GBASE_LR4 = 0x2,
    QSFP_ETHERNET_COMPLIANCE_CODE_40GBASE_SR4 = 0x4,
    QSFP_ETHERNET_COMPLIANCE_CODE_40GBASE_CR4 = 0x8,
    QSFP_ETHERNET_COMPLIANCE_CODE_10GBASE_SR = 0x10,
    QSFP_ETHERNET_COMPLIANCE_CODE_10GBASE_LR = 0x20,
    QSFP_ETHERNET_COMPLIANCE_CODE_10GBASE_LRM= 0x40,
    QSFP_ETHERNET_COMPLIANCE_CODE_EXT = 0x80,
};

enum SFP_ETHERNET_COMPLIANCE_CODE {
    SFP_ETHERNET_COMPLIANCE_CODE_Unspecified = 0,
    SFP_ETHERNET_COMPLIANCE_CODE_10G_BASE_SR = 0x10,
    SFP_ETHERNET_COMPLIANCE_CODE_10G_BASE_LR = 0x20,
    SFP_ETHERNET_COMPLIANCE_CODE_10G_BASE_LRM = 0x40,
    SFP_ETHERNET_COMPLIANCE_CODE_10G_BASE_ER = 0x80,
};

enum CMIS_PASSIVE_COPPER_COMPLIANCE {
    CMIS_COMPLIANCE_UNSPECIFIED = 0x0,
    CMIS_COMPLIANCE_1000_BASE_CX= 0x1,
    CMIS_COMPLIANCE_XAUI = 0x2,
    CMIS_COMPLIANCE_XFI= 0x3,
    CMIS_COMPLIANCE_SFI = 0x4,
    CMIS_COMPLIANCE_25G_AUI = 0x5,
    CMIS_COMPLIANCE_XL_AUI = 0x6,
    CMIS_COMPLIANCE_XL_PPI = 0x7,
    CMIS_COMPLIANCE_L_AUI2= 0x8,
    CMIS_COMPLIANCE_50G_AUI2 = 0x9,
    CMIS_COMPLIANCE_50G_AUI1 = 0xa,
    CMIS_COMPLIANCE_C_AUI4 = 0xb,
    CMIS_COMPLIANCE_100G_AUI4 = 0xc,
    CMIS_COMPLIANCE_100G_AUI2 = 0xd,
    CMIS_COMPLIANCE_200G_AUI8 = 0xe,
    CMIS_COMPLIANCE_200G_AUI4 = 0xf,
    CMIS_COMPLIANCE_400G_AUI16 = 0x10,
    CMIS_COMPLIANCE_400G_AUI8 = 0x11,
    CMIS_COMPLIANCE_10G_BASE_CX4 = 0x13,
    CMIS_COMPLIANCE_25G_CR_L = 0x14,
    CMIS_COMPLIANCE_25G_CR_S = 0x15,
    CMIS_COMPLIANCE_25G_CR_N = 0x16,
    CMIS_COMPLIANCE_40G_BASE_CR4 = 0x17,
    CMIS_COMPLIANCE_50G_BASE_CR = 0x18,
    CMIS_COMPLIANCE_100G_BASE_CR10 = 0x19,
    CMIS_COMPLIANCE_100G_BASE_CR4 = 0x1a,
    CMIS_COMPLIANCE_100G_BASE_CR2 = 0x1b,
    CMIS_COMPLIANCE_200G_BASE_CR4 = 0x1c,
    CMIS_COMPLIANCE_400G_CR8 = 0x1d,
    CMIS_COMPLIANCE_1000_BASE_T = 0x1e,
    CMIS_COMPLIANCE_2_5G_BASE_T = 0x1f,
    CMIS_COMPLIANCE_5G_BASE_T = 0x20,
    CMIS_COMPLIANCE_10G_BASE_T = 0x21,
    CMIS_COMPLIANCE_25_BASE_T = 0x22,
    CMIS_COMPLIANCE_40_BASE_T = 0x23,
    CMIS_COMPLIANCE_50_BASE_T = 0x24,
    CMIS_COMPLIANCE_SDR = 0x2c,
    CMIS_COMPLIANCE_DDR = 0x2d,
    CMIS_COMPLIANCE_QDR = 0x2e,
    CMIS_COMPLIANCE_FDR = 0x2f,
    CMIS_COMPLIANCE_EDR = 0x30,
    CMIS_COMPLIANCE_HDR = 0x31,
    CMIS_COMPLIANCE_NDR = 0x32
};

enum CMIS_MM_COMPLIANCE_CODE {
    CMIS_COMPLIANCE_10G_BASE_SW = 0x1,
    CMIS_COMPLIANCE_10G_BASE_SR = 0x2,
    CMIS_COMPLIANCE_25G_BASE_SR = 0x3,
    CMIS_COMPLIANCE_40G_BASE_SR4 = 0x4,
    CMIS_COMPLIANCE_40G_SWDM4 = 0x5,
    CMIS_COMPLIANCE_40G_BIDI = 0x6,
    CMIS_COMPLIANCE_50G_BASE_SR = 0x7,
    CMIS_COMPLIANCE_100G_BASE_SR10 = 0x8,
    CMIS_COMPLIANCE_100G_BASE_SR4 = 0x9,
    CMIS_COMPLIANCE_100G_SWDM4 = 0xa,
    CMIS_COMPLIANCE_100G_BIDI = 0xb,
    CMIS_COMPLIANCE_100G_SR2 = 0xc,
    CMIS_COMPLIANCE_100G_SR = 0xd,
    CMIS_COMPLIANCE_200G_BASE_SR4 = 0xe,
    CMIS_COMPLIANCE_400G_BASE_SR16 = 0xf,
    CMIS_COMPLIANCE_400G_BASE_SR8 = 0x10,
    CMIS_COMPLIANCE_400G_SR4 = 0x11,
    CMIS_COMPLIANCE_800G_SR8 = 0x12,
    CMIS_COMPLIANCE_400G_BIDI = 0x1a
};

enum CMIS_SM_COMPLIANCE_CODE {
    CMIS_COMPLIANCE_10G_BASE_LW = 0x1,
    CMIS_COMPLIANCE_10G_BASE_EW = 0x2,
    CMIS_COMPLIANCE_10G_ZW = 0x3,
    CMIS_COMPLIANCE_10G_BASE_LR = 0x4,
    CMIS_COMPLIANCE_10G_BASE_ER = 0x5,
    CMIS_COMPLIANCE_10G_BASE_ZR = 0x6,
    CMIS_COMPLIANCE_25G_BASE_LR = 0x7,
    CMIS_COMPLIANCE_25G_BASE_ER = 0x8,
    CMIS_COMPLIANCE_40G_BASE_LR4 = 0x9,
    CMIS_COMPLIANCE_40G_BASE_FR = 0xa,
    CMIS_COMPLIANCE_50G_BASE_FR = 0xb,
    CMIS_COMPLIANCE_50G_BASE_LR = 0xc,
    CMIS_COMPLIANCE_100G_BASE_LR4 = 0xd,
    CMIS_COMPLIANCE_100G_BASE_ER4 = 0xe,
    CMIS_COMPLIANCE_100G_PSM4 = 0xf,
    CMIS_COMPLIANCE_100G_CWDM4_OCP = 0x34,
    CMIS_COMPLIANCE_100G_CWDM4 = 0x10,
    CMIS_COMPLIANCE_100G_4WDM_10 = 0x11,
    CMIS_COMPLIANCE_100G_4WDM_20 = 0x12,
    CMIS_COMPLIANCE_100G_4WDM_40 = 0x13,
    CMIS_COMPLIANCE_100G_BASE_DR = 0x14,
    CMIS_COMPLIANCE_100G_FR = 0x15,
    CMIS_COMPLIANCE_100G_LR = 0x16,
    CMIS_COMPLIANCE_200G_BASE_DR4 = 0x17,
    CMIS_COMPLIANCE_200G_BASE_FR4 = 0x18,
    CMIS_COMPLIANCE_200G_BASE_LR4 = 0x19,
    CMIS_COMPLIANCE_400G_BASE_FR8 = 0x1a,
    CMIS_COMPLIANCE_400G_BASE_LR8 = 0x1b,
    CMIS_COMPLIANCE_400G_BASE_DR4 = 0x1c,
    CMIS_COMPLIANCE_400G_FR4 = 0x1d,
    CMIS_COMPLIANCE_400G_LR4 = 0x1e,
    CMIS_COMPLIANCE_10G_SR = 0x38,
    CMIS_COMPLIANCE_10G_LR = 0x39,
    CMIS_COMPLIANCE_25G_SR = 0x3a,
    CMIS_COMPLIANCE_25G_LR = 0x3b,
    CMIS_COMPLIANCE_10G_LR_BIDI = 0x3c,
    CMIS_COMPLIANCE_25G_LR_BIDI = 0x3d
};

enum PHY_MNGR_FSM_STATE {
    PHY_MNGR_DISABLED = 0,
    PHY_MNGR_OPEN_PORT = 1,
    PHY_MNGR_POLLING = 2,
    PHY_MNGR_ACTIVE_LINKUP = 3,
    PHY_MNGR_CLOSE_PORT = 4,
    PHY_MNGR_PHYSICAL_LINKUP = 5,
    PHY_MNGR_RX_DISABLE = 7
};

enum IB_PHY_FSM_STATE {
    IB_AN_FSM_DISABLED = 0,
    IB_AN_FSM_INITIALY = 1,
    IB_AN_FSM_RCVR_CFG = 2,
    IB_AN_FSM_CFG_TEST = 3,
    IB_AN_FSM_WAIT_RMT_TEST = 4,
    IB_AN_FSM_WAIT_CFG_ENHANCED = 5,
    IB_AN_FSM_CFG_IDLE = 6,
    IB_AN_FSM_LINK_UP = 7
};

enum TECH {
    TECH_NA = 0,
    TECH_40 = 1,
    TECH_28 = 2,
    TECH_16 = 3,
    TECH_7 = 4,
    TECH_5 = 5
};

enum PHY_HST_FSM_HDR_STATE {
   PHY_HST_FSM_HDR_DISABLED               = 0,
   PHY_HST_FSM_HDR_ADAPTATION             = 0x1,
   PHY_HST_FSM_HDR_DESKEW_FIX_REVERSALS   = 0x2,
   PHY_HST_FSM_HDR_WAIT_TS2               = 0x3,
   PHY_HST_FSM_HDR_WAIT_MCB               = 0x4,
   PHY_HST_FSM_HDR_MCB_AN                 = 0x5,
   PHY_HST_FSM_HDR_RECEIVER_READY         = 0x6,
   PHY_HST_FSM_HDR_LINKUP                 = 0x7,
   PHY_HST_FSM_HDR_SUBFSM_FAIL            = 0x8,
   PHY_HST_FSM_HDR_BASIC_DETECT           = 0x9,
   PHY_HST_FSM_HDR_BASIC_STABILITY        = 0xa,
   PHY_HST_FSM_HDR_CONFIG                 = 0xb,
   PHY_HST_HDR_ERROR                      = 0xff,
};

enum MAX_READ_REQUEST_SIZE{
    MAX_READ_REQUEST_SIZE_128B  = 0,
    MAX_READ_REQUEST_SIZE_256B  = 0x1,
    MAX_READ_REQUEST_SIZE_512B  = 0x2,
    MAX_READ_REQUEST_SIZE_1024B = 0x3,
    MAX_READ_REQUEST_SIZE_2048B = 0x4,
    MAX_READ_REQUEST_SIZE_4096B = 0x5,
};

enum PWR_STATUS{
    PWR_STATUS_0 = 0,
    PWR_STATUS_1 = 0x1,
    PWR_STATUS_2 = 0x2,
};

enum PORT_TYPE_MPEIN{
    PORT_TYPE_EP_MPEIN = 0,
    PORT_TYPE_RC_MPEIN = 0x4,
    PORT_TYPE_UP_MPEIN = 0x5,
    PORT_TYPE_DP_MPEIN = 0x6,
};

enum LINK_PEER_MAX_SPEED{
    LINK_PEER_MAX_SPEED_2_5G = 0x1,
    LINK_PEER_MAX_SPEED_5G   = 0x2,
    LINK_PEER_MAX_SPEED_8G   = 0x4,
    LINK_PEER_MAX_SPEED_16G  = 0x16,
    LINK_PEER_MAX_SPEED_32G  = 0x32,
};

enum PORT_STATE{
    PORT_STATE_0 = 0x0,
    PORT_STATE_1 = 0x1,
    PORT_STATE_2 = 0x2,
    PORT_STATE_3 = 0x10,
    PORT_STATE_4 = 0x20,
    PORT_STATE_5 = 0x21,
    PORT_STATE_6 = 0x31,
    PORT_STATE_7 = 0x32,
    PORT_STATE_8 = 0x33,
    PORT_STATE_9 = 0x34,
    PORT_STATE_10 = 0x35,
    PORT_STATE_11 = 0x36,
    PORT_STATE_12 = 0x40,
    PORT_STATE_13 = 0x41,
    PORT_STATE_14 = 0x42,
    PORT_STATE_15 = 0x50,
    PORT_STATE_16 = 0x51,
    PORT_STATE_17 = 0x52,
    PORT_STATE_18 = 0x53,
    PORT_STATE_19 = 0x54,
    PORT_STATE_20 = 0x60,
    PORT_STATE_21 = 0x61,
    PORT_STATE_22 = 0x62,
    PORT_STATE_23 = 0x63,
    PORT_STATE_24 = 0x64,
    PORT_STATE_25 = 0x65,
    PORT_STATE_26 = 0x70,
    PORT_STATE_27 = 0x71,
    PORT_STATE_28 = 0x80,
    PORT_STATE_29 = 0x81,
    PORT_STATE_30 = 0x90,
    PORT_STATE_31 = 0xa0,
    PORT_STATE_32 = 0xa1,
    PORT_STATE_33 = 0xa2,
    PORT_STATE_34 = 0xa5,
    PORT_STATE_35 = 0xa8,
    PORT_STATE_36 = 0xa9,
    PORT_STATE_37 = 0xaa,
    PORT_STATE_38 = 0xab,
    PORT_STATE_39 = 0xac,
    PORT_STATE_40 = 0xb0,
    PORT_STATE_41 = 0xc0,
    PORT_STATE_42 = 0xd0,
    PORT_STATE_43 = 0xe0,
    PORT_STATE_44 = 0xf0,
};

enum LOOPBACK_MODE{
    PHY_NO_LOOPBACK = 0,
    PHY_REMOTE_LOOPBACK = 1,
    PHY_LOCAL_LOOPBACK = 2,
    EXTERNAL_LOCAL_LOOPBACK = 4
};

enum AN_DISABLE {
    AN_DISABLE_NORMAL = 0,
    AN_DISABLE_FORCE  = 1
};

enum ETH_LINK_SPEED {
    ETH_LINK_SPEED_UNKNOWN = 0x0,
    ETH_LINK_SPEED_1000_SGMII = 0x1,
    ETH_LINK_SPEED_1000_KX = 0x2,
    ETH_LINK_SPEED_10G_CX4 = 0x4,
    ETH_LINK_SPEED_10G_KX4 = 0x8,
    ETH_LINK_SPEED_10G_KR = 0x10,
    ETH_LINK_SPEED_20G_KR2 = 0x20,
    ETH_LINK_SPEED_40G_CR4 = 0x40,
    ETH_LINK_SPEED_40G_KR4 = 0x80,
    ETH_LINK_SPEED_56G_KR4 = 0x100,
    ETH_LINK_SPEED_56G_R4 = 0x100,
    ETH_LINK_SPEED_10G_CR = 0x1000,
    ETH_LINK_SPEED_10G_SR = 0x2000,
    ETH_LINK_SPEED_10G_LR = 0x4000,
    ETH_LINK_SPEED_40G_SR4 = 0x8000,
    ETH_LINK_SPEED_40G_LR4 = 0x10000,
    ETH_LINK_SPEED_56G_CR4 = 0x20000,
    ETH_LINK_SPEED_50G_SR2 = 0x40000,
    ETH_LINK_SPEED_50G_KR4 = 0x80000,
    ETH_LINK_SPEED_100G_CR4 = 0x100000,
    ETH_LINK_SPEED_100G_SR4 = 0x200000,
    ETH_LINK_SPEED_100G_KR4 = 0x400000,
    ETH_LINK_SPEED_100G_LR4 = 0x800000,
    ETH_LINK_SPEED_100_BaseTx = 0x01000000,
    ETH_LINK_SPEED_1000_BaseT = 0x02000000,
    ETH_LINK_SPEED_10G_BaseT = 0x04000000,
    ETH_LINK_SPEED_25G_CR = 0x8000000,
    ETH_LINK_SPEED_25G_KR = 0x10000000,
    ETH_LINK_SPEED_25G_SR = 0x20000000,
    ETH_LINK_SPEED_50G_CR2 = 0x40000000,
    ETH_LINK_SPEED_50G_KR2 = 0x80000000,
};

enum ETH_LINK_SPEED_EXT {
    ETH_LINK_SPEED_EXT_UNKNOWN = 0x0,
    ETH_LINK_SPEED_EXT_SGMII_100M = 0x1,
    ETH_LINK_SPEED_EXT_1000BASE_X = 0x2,
    ETH_LINK_SPEED_EXT_2_5GBASE_X = 0x4,
    ETH_LINK_SPEED_EXT_5GBASE_R = 0x8,
    ETH_LINK_SPEED_EXT_XFI = 0x10,
    ETH_LINK_SPEED_EXT_XLAUI_4 = 0x20,
    ETH_LINK_SPEED_EXT_25GAUI_1 = 0x40,
    ETH_LINK_SPEED_EXT_50GAUI_2 = 0x80,
    ETH_LINK_SPEED_EXT_50GAUI_1 = 0x100,
    ETH_LINK_SPEED_EXT_CAUI_4 = 0x200,
    ETH_LINK_SPEED_EXT_100GAUI_2 = 0x400,
    ETH_LINK_SPEED_EXT_100GAUI_1 = 0x800,
    ETH_LINK_SPEED_EXT_200GAUI_4 = 0x1000,
    ETH_LINK_SPEED_EXT_200GAUI_2  = 0x2000,
    ETH_LINK_SPEED_EXT_Reserved_14 = 0x4000,
    ETH_LINK_SPEED_EXT_400GAUI_8 = 0x8000,
    ETH_LINK_SPEED_EXT_400GAUI_4 = 0x10000
};

enum IB_LINK_SPEED {
    IB_LINK_SPEED_SDR   = 0x1,
    IB_LINK_SPEED_DDR   = 0x2,
    IB_LINK_SPEED_QDR   = 0x4,
    IB_LINK_SPEED_FDR10 = 0x8,
    IB_LINK_SPEED_FDR   = 0x10,
    IB_LINK_SPEED_EDR   = 0x20,
    IB_LINK_SPEED_HDR   = 0x40,
    IB_LINK_SPEED_NDR   = 0x80
};

enum PRBS_MODULATION {
    PRBS_NRZ = 0,
    PRBS_PAM4_ENCODING = 1
};

enum PNAT_ACCESS {
    PNAT_LOCAL = 0,
    PNAT_LABEL = 1,
    PNAT_PCIE = 3
};

enum PRODUCT_TECHNOLOGY {
    PRODUCT_40NM = 0,
    PRODUCT_28NM = 1,
    PRODUCT_16NM = 3,
    PRODUCT_7NM = 4
};

enum STATUS_OPCODE {
    CABLE_IS_UNPLUGGED = 1024
};

enum EOM_MEASURMENT {
    SLRG_UPPER_EYE = 0x1,
    SLRG_MIDDLE_EYE = 0x2,
    SLRG_LOWER_EYE = 0x4,
    SLRG_COMPOSITE_EYE = 0x8
};

enum SLRG_FOM_MODE {
    SLRG_FOM_MODE_EYEC,
    SLRG_FOM_MODE_EYEO,
    SLRG_FOM_MODE_EYEM,
    SLRG_FOM_MODE_BER,
    SLRG_FOM_MODE_EYEC_VN,
    SLRG_FOM_MODE_EYEC_VP,
    SLRG_FOM_MODE_EYEM_VN,
    SLRG_FOM_MODE_EYEM_VP
};

#endif /* MLXLINK_ENUMS_H */
