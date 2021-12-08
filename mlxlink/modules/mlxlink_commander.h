/*
 * Copyright (c) 2019-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 */

#ifndef MLXLINK_COMMANDER_H
#define MLXLINK_COMMANDER_H

#include <common/tools_utils.h>
#include <common/tools_version.h>
#include <mft_utils/mft_sig_handler.h>
#ifndef MST_UL
#include <cmdif/cib_cif.h>
#else
#include <cmdif/icmd_cif_open.h>
#endif
#include <cmdparser/cmdparser.h>
#include "mlxlink_cables_commander.h"
#include "mlxlink_eye_opener.h"
#include "mlxlink_err_inj_commander.h"
#include "mlxlink_port_info.h"
#include "mlxlink_amBER_collector.h"

#ifdef MST_UL
#define MLXLINK_EXEC "mstlink"
#else
#define MLXLINK_EXEC "mlxlink"
#endif

//------------------------------------------------------------
//        Mlxlink OPTIONS Flags

#define HELP_FLAG                    "help"
#define HELP_FLAG_SHORT              'h'
#define VERSION_FLAG                 "version"
#define VERSION_FLAG_SHORT           'v'
#define DEVICE_FLAG                  "device"
#define DEVICE_FLAG_SHORT            'd'
#define LABEL_PORT_FLAG              "port"
#define LABEL_PORT_FLAG_SHORT        'p'
#define PORT_TYPE_FLAG               "port_type"
#define PORT_TYPE_FLAG_SHORT         ' '
#define DEPTH_FLAG                   "depth"
#define DEPTH_FLAG_SHORT             ' '
#define PCIE_INDEX_FLAG              "pcie_index"
#define PCIE_INDEX_FLAG_SHORT        ' '
#define NODE_FLAG                    "node"
#define NODE_FLAG_SHORT              ' '
#define PRINT_JSON_OUTPUT_FLAG       "json"
#define PRINT_JSON_OUTPUT_FLAG_SHORT ' '
//------------------------------------------------------------
//        Mlxlink QUERIES Flags

#define PCIE_LINKS_FLAG                 "show_links"
#define PCIE_LINKS_FLAG_SHORT            ' '
#define MODULE_INFO_FLAG                "show_module"
#define MODULE_INFO_FLAG_SHORT          'm'
#define BER_FLAG                        "show_counters"
#define BER_FLAG_SHORT                  'c'
#define EYE_OPENING_FLAG                "show_eye"
#define EYE_OPENING_FLAG_SHORT          'e'
#define FEC_DATA_FLAG                   "show_fec"
#define FEC_DATA_FLAG_SHORT             ' '
#define SLTP_SHOW_FLAG                  "show_serdes_tx"
#define SLTP_SHOW_FLAG_SHORT            ' '
#define DEVICE_DATA_FLAG                "show_device"
#define DEVICE_DATA_FLAG_SHORT          ' '
#define BER_MONITOR_INFO_FLAG           "show_ber_monitor"
#define BER_MONITOR_INFO_FLAG_SHORT     ' '
#define PEPC_SHOW_FLAG                  "show_external_phy"
#define PEPC_SHOW_FLAG_SHORT            ' '

//------------------------------------------------------------
//        Mlxlink COMMANDS Flags

#define PAOS_FLAG                          "port_state"
#define PAOS_FLAG_SHORT                    'a'
#define PTYS_FLAG                          "speeds"
#define PTYS_FLAG_SHORT                    's'
#define PPLR_FLAG                          "loopback"
#define PPLR_FLAG_SHORT                    'l'
#define PPLM_FLAG                          "fec"
#define PPLM_FLAG_SHORT                    'k'
#define FEC_SPEED_FLAG                     "fec_speed"
#define FEC_SPEED_FLAG_SHORT               ' '
#define SLTP_SET_FLAG                      "serdes_tx"
#define SLTP_SET_FLAG_SHORT                ' '
#define LANE_FLAG                          "serdes_tx_lane"
#define LANE_FLAG_SHORT                    ' '
#define SLTP_TX_POLICY_FLAG                "tx_params_override"
#define SLTP_TX_POLICY_FLAG_SHORT          ' '
#define DATABASE_FLAG                      "database"
#define DATABASE_FLAG_SHORT                ' '
#define PRBS_MODE_FLAG                     "test_mode"
#define PRBS_MODE_FLAG_SHORT               ' '
#define PPRT_PRBS_FLAG                     "rx_prbs"
#define PPRT_PRBS_FLAG_SHORT               ' '
#define PPTT_PRBS_FLAG                     "tx_prbs"
#define PPTT_PRBS_FLAG_SHORT               ' '
#define PPRT_RATE_FLAG                     "rx_rate"
#define PPRT_RATE_FLAG_SHORT               ' '
#define PPTT_RATE_FLAG                     "tx_rate"
#define PPTT_RATE_FLAG_SHORT               ' '
#define PRBS_LANES_FLAG                    "lanes"
#define PRBS_LANES_FLAG_SHORT              ' '
#define PRBS_INVERT_TX_POL_FLAG            "invert_tx_polarity"
#define PRBS_INVERT_TX_POL_FLAG_SHORT      ' '
#define PRBS_INVERT_RX_POL_FLAG            "invert_rx_polarity"
#define PRBS_INVERT_RX_POL_FLAG_SHORT      ' '
#define PPRT_TUNING_TYPE_FLAG              "tuning_type"
#define PPRT_TUNING_TYPE_FLAG_SHORT        ' '
#define BER_COLLECT_FLAG                   "ber_collect"
#define BER_COLLECT_FLAG_SHORT             'b'
#define BER_LIMIT_FLAG                     "ber_limit"
#define BER_LIMIT_FLAG_SHORT               ' '
#define ITERATION_FLAG                     "iteration"
#define ITERATION_FLAG_SHORT               ' '
#define AMBER_COLLECT_FLAG                 "amber_collect"
#define AMBER_COLLECT_FLAG_SHORT           ' '
#define PPCNT_CLEAR_FLAG                   "pc"
#define PPCNT_CLEAR_FLAG_SHORT             ' '
#define PEPC_SET_FLAG                      "set_external_phy"
#define PEPC_SET_FLAG_SHORT                ' '
#define PEPC_FORCE_MODE_FLAG               "twisted_pair_force_mode"
#define PEPC_FORCE_MODE_FLAG_SHORT         ' '
#define PEPC_AN_MODE_FLAG                  "twisted_pair_an_mode"
#define PEPC_AN_MODE_FLAG_SHORT            ' '
#define PTYS_LINK_MODE_FORCE_FLAG          "link_mode_force"
#define PTYS_LINK_MODE_FORCE_FLAG_SHORT    ' '

//------------------------------------------------------------
//        Mlxlink Cable info flags
#define CABLE_FLAG                          "cable"
#define CABLE_FLAG_SHORT                    ' '
#define CABLE_DUMP_FLAG                     "dump"
#define CABLE_DUMP_FLAG_SHORT               ' '
#define CABLE_DDM_FLAG                      "ddm"
#define CABLE_DDM_FLAG_SHORT                ' '
#define CABLE_WRITE_FLAG                    "write"
#define CABLE_WRITE_FLAG_SHORT              ' '
#define CABLE_READ_FLAG                     "read"
#define CABLE_READ_FLAG_SHORT               ' '
#define WRITE_PAGE_FLAG                     "page"
#define WRITE_PAGE_FLAG_SHORT               ' '
#define WRITE_OFFSET_FLAG                   "offset"
#define WRITE_OFFSET_FLAG_SHORT             ' '
#define READ_LEN_FLAG                       "length"
#define READ_LEN_FLAG_SHORT                 ' '
#define SHOW_TX_GROUP_MAP_FLAG              "show_tx_group_map"
#define SHOW_TX_GROUP_MAP_FLAG_SHORT        ' '
#define SET_TX_GROUP_MAP_FLAG               "tx_group_map"
#define SET_TX_GROUP_MAP_FLAG_SHORT         ' '
#define TX_GROUP_PORTS_FLAG                 "ports"
#define TX_GROUP_PORTS_FLAG_SHORT           ' '
//------------------------------------------------------------
//        Mlxlink Eye Opener Flags
#define MARGIN_SCAN_FLAG                    "margin"
#define MARGIN_SCAN_FLAG_SHORT              ' '
#define EYE_SEL_FLAG                        "eye_select"
#define EYE_SEL_FLAG_SHORT                  ' '
#define EYE_MEASURE_TIME_FLAG               "measure_time"
#define EYE_MEASURE_TIME_FLAG_SHORT         ' '
#define LANE_INDEX_FLAG                     "lane"
#define LANE_INDEX_FLAG_SHORT               ' '
#define FORCE_YES_FLAG                      "yes"
#define FORCE_YES_FLAG_SHORT                ' '

//------------------------------------------------------------
//        Mlxlink Error Injection Flags
#define PREI_RX_ERR_INJ_FLAG                "rx_error_injection"
#define PREI_RX_ERR_INJ_FLAG_SHORT          ' '
#define PREI_MIXER_OFFSET_0                 "mixer_offset0"
#define PREI_MIXER_OFFSET_0_SHORT           ' '
#define PREI_MIXER_OFFSET_1                 "mixer_offset1"
#define PREI_MIXER_OFFSET_1_SHORT           ' '
#define PREI_SHOW_MIXERS_FLAG               "show_mixers_offset"
#define PREI_SHOW_MIXERS_FLAG_SHORT         ' '

//------------------------------------------------------------
//        Histogram Counters Flags
#define PPHCR_FEC_HIST_FLAG                 "rx_fec_histogram"
#define PPHCR_FEC_HIST_FLAG_SHORT           ' '
#define PPHCR_SHOW_FEC_HIST_FLAG            "show_histogram"
#define PPHCR_SHOW_FEC_HIST_FLAG_SHORT      ' '
#define PPHCR_CLEAR_HISTOGRAM_FLAG          "clear_histogram"
#define PPHCR_CLEAR_HISTOGRAM_FLAG_SHORT    ' '

//------------------------------------------------------------
//        Mlxlink HIDDEN Flags

#define SLTP_SET_ADVANCED_FLAG              "advanced"
#define SLTP_SET_ADVANCED_FLAG_SHORT        ' '
#define GVMI_ADDRESS_FLAG                   "gvmi_address"
#define GVMI_ADDRESS_FLAG_SHORT             ' '
#define LOG_FLAG                            "log"
#define LOG_FLAG_SHORT                      ' '

//------------------------------------------------------------

#define REG_ACCESS_UNION_NODE "access_reg_summary"

//------------------------------------------------------------
//        Mlxlink commands enumerations
enum OPTION_TYPE {
    SHOW_PDDR = 1,
    SHOW_PCIE,
    SHOW_BER,
    SHOW_EYE,
    SHOW_FEC,
    SHOW_SLTP,
    SHOW_SLRP,
    SHOW_MODULE,
    SHOW_DEVICE,
    SHOW_BER_MONITOR,
    SHOW_EXTERNAL_PHY,
    SHOW_LINK_DOWN_BLAME,
    SHOW_TX_GROUP_MAP,
    CABLE_EEPROM_INI,
    CABLE_SHOW_DUMP,
    CABLE_SHOW_DDM,
    CABLE_EEPROM_WRITE,
    CABLE_EEPROM_READ,
    SEND_BER_COLLECT,
    SEND_AMBER_COLLECT,
    SEND_PAOS,
    SEND_PTYS,
    SEND_PPLM,
    SEND_PPLR,
    SEND_PRBS,
    SEND_SLTP,
    SEND_CLEAR_COUNTERS,
    SEND_PEPC,
    SHOW_PCIE_LINKS,
    SET_TX_GROUP_MAP,
    GRADE_SCAN_ENABLE,
    ERR_INJ_ENABLE,
    RS_FEC_HISTOGRAM = 33,
    SLRG_TEST,
    // Any new function's index should be added before FUNCTION_LAST in this enum
    FUNCTION_LAST
};


///////////
struct DPN {
    DPN()
    {
        depth =0;
        pcieIndex=0;
        node=0;
    }

    DPN(u_int32_t d, u_int32_t p, u_int32_t n)
    {
        depth = d;
        pcieIndex = p;
        node = n;
    }

    bool operator==(DPN dpn) {
       return (dpn.depth == depth && dpn.pcieIndex == pcieIndex &&
               dpn.node == node);
    }

    u_int32_t depth;
    u_int32_t pcieIndex;
    u_int32_t node;
};

using namespace std;

class MlxlinkCommander: public MlxlinkRegParser {

public:
    MlxlinkCommander();
    virtual ~MlxlinkCommander();

    void checkRegCmd();
    void validatePortToLC();
    void validatePortType(const string &portTypeStr);
    void updatePortType();
    void gearboxBlock(const string &option);
    void checkLocalPortDPNMapping(u_int32_t localPort);
    int getLocalPortFromMPIR(DPN& dpn);
    void checkValidFW();
    void getProductTechnology();
    bool checkPortStatus(u_int32_t localPort);
    void checkAllPortsStatus();
    void handlePortStr(const string &portStr);
    void labelToLocalPort();
    void labelToHCALocalPort();
    void labeltoDSlocalPort();
    bool isDSdevice();
    void labelToSpectLocalPort();
    void labelToIBLocalPort();
    bool isIBSplitReady();
    u_int32_t calculatePanelPort(bool ibSplitReady);
    void checkWidthSplit(u_int32_t localPort);
    void checkUnSplit(u_int32_t localPort);
    u_int32_t maxLocalPort();
    void checkStrLength(const string &str);
    void getActualNumOfLanes(u_int32_t linkSpeedActive, bool extended);
    u_int32_t activeSpeed2gNum(u_int32_t mask, bool extended);
    string activeSpeed2Str(u_int32_t mask, bool extended);
    void getCableParams();
    bool inPrbsTestMode();
    bool checkGBPpaosDown();
    bool checkPaosDown();
    bool checkPpaosTestMode();
    void getSltpParamsFromVector(std::vector<string> sltpParams);
    void getprbsLanesFromParams(std::vector<string> prbsLanesParams);
    std::vector<string> parseParamsFromLine(const string & ParamsLine);
    bool isSpect2WithGb();
    bool isIbLocalPortValid(u_int32_t localPort);
    void fillIbPortGroupMap(u_int32_t localPort,u_int32_t labelPort, u_int32_t group,
            bool splitReady);
    void fillEthPortGroupMap(u_int32_t localPort,u_int32_t labelPort, u_int32_t group,
            u_int32_t width, bool spect2WithGb);
    int handleIBLocalPort(u_int32_t labelPort, bool ibSplitReady);
    int handleEthLocalPort(u_int32_t labelPort, bool spect2WithGb);
    void handleLabelPorts(std::vector<string> labelPortsStr, bool skipException = false);
    vector<string> localToPortsPerGroup(vector<u_int32_t> localPorts);
    u_int32_t getPortGroup(u_int32_t localPort);

    //Mlxlink query functions
    virtual void showModuleInfo();
    void prepareBerModuleInfoNdr(bool valid);
    virtual void runningVersion();
    void operatingInfoPage();
    void supportedInfoPage();
    virtual void troubInfoPage();
    void showPddr();
    void getPtys();
    virtual void showBer();
    void prepare40_28_16nmEyeInfo(u_int32_t numOfLanesToUse);
    void prepare7nmEyeInfo(u_int32_t numOfLanesToUse);
    virtual void showEye();
    void showFEC();
    virtual void showSltp();
    virtual void showDeviceData();
    void showBerMonitorInfo();
    void showExternalPhy();
    void showPcie();
    void showPcieLinks();
    void collectAMBER();
    void collectBER();
    void showTxGroupMapping();

    // Query helper functions
    string getCableTechnologyStr(u_int32_t cableTechnology);
    string getCompliaceLabelForCIMIS(u_int32_t hostCompliance, u_int32_t mediaCompliance);
    string getComplianceLabel(u_int32_t compliance,  u_int32_t extCompliance, bool ignoreExtBitChk = false);
    string getCableTypeStr(u_int32_t cableType);
    void prepareStaticInfoSection(bool valid);
    void prepareAttenuationAndFwSection(bool valid);
    void preparePowerAndCdrSection(bool valid);
    void prepareDDMSection(bool valid);
    void strToInt32(char *str, u_int32_t &value);
    template<typename T, typename Q> string getValueAndThresholdsStr(T value, Q lowTH, Q highTH);
    void prepareSltp28_40nm(std::vector<std::vector<string> > &sltpLanes,
            u_int32_t laneNumber);
    void prepareSltp16nm(std::vector<std::vector<string> > &sltpLanes,
            u_int32_t laneNumber);
    void prepareSltp7nm(std::vector<std::vector<string> > &sltpLanes,
            u_int32_t laneNumber);
    void initValidDPNList();
    u_int32_t readBitFromField(const string &fieldName, u_int32_t bitIndex);
    string getSupportedFecForSpeed(const string &speed);
    string fecMaskToUserInputStr(u_int32_t fecCapMask);
    string fecMaskToStr(u_int32_t mask);

    void showTestMode();
    void showTestModeBer();
    void showMpcntPerformance(DPN& dpn);
    void showMpcntTimers(DPN& dpn);
    void showMpcntLane();
    void showPcieState(DPN& dpn);
    void checkPCIeValidity();
    virtual void prepareBerInfo();
    virtual void prepareBerInfoEDR();
    virtual void getPcieNdrCounters();

    std::map<std::string, std::string>  getPprt();
    std::map<std::string, std::string>  getPptt();

    std::map<std::string, float>  getRawEffectiveErrors();
    std::map<std::string, float>  getRawEffectiveErrorsinTestMode();
    int prbsModeToMask(const string &mode);
    string prbsMaskToMode(u_int32_t mask, u_int32_t modeSelector);
    string getPrbsModeRX();
    u_int32_t getPrbsRateRX();
    string getSupportedPrbsRates(u_int32_t modeSelector);
    string getSupportedPrbsModes(u_int32_t modeSelector);
    u_int32_t getLoopbackMode(const string &lb);
    string getLoopbackStr(u_int32_t loopbackCapMask);
    int getLinkDown();
    float getRawBERLimit();
    bool getResult(std::map<std::string, float>  errors_vector,
                   float raw_ber_limit, int link_down);
    string getDevicePN(bool queryMSGI = false);
    string getDeviceSN(bool queryMSGI = false);
    string getDeviceProductName(bool queryMSGI = false);
    string getDeviceRev(bool queryMSGI = false);
    string getDeviceFW();
    void printOuptputVector(vector<MlxlinkCmdPrint> &cmdOut);
    virtual void prepareJsonOut();

    // Cable operation
    bool isPassiveQSFP();
    bool isSFP51Paging();
    void initCablesCommander();
    void initEyeOpener();
    void initErrInj();
    void initPortInfo();
    void setAmBerCollectorFields();
    virtual void initAmBerCollector();
    void showCableDump();
    void showCableDDM();
    vector<u_int8_t> validateBytes(const vector<string> &strBytes);
    void writeCableEEPROM();
    void readCableEEPROM();

    MlxlinkCmdPrint _toolInfoCmd;
    MlxlinkCmdPrint _operatingInfoCmd;
    MlxlinkCmdPrint _supportedInfoCmd;
    MlxlinkCmdPrint _troubInfoCmd;
    MlxlinkCmdPrint _testModeInfoCmd;
    MlxlinkCmdPrint _pcieInfoCmd;
    MlxlinkCmdPrint _moduleInfoCmd;
    MlxlinkCmdPrint _berInfoCmd;
    MlxlinkCmdPrint _testModeBerInfoCmd;
    MlxlinkCmdPrint _mpcntPerfInfCmd;
    MlxlinkCmdPrint _mpcntTimerInfCmd;
    MlxlinkCmdPrint _eyeOpeningInfoCmd;
    MlxlinkCmdPrint _fecCapInfoCmd;
    MlxlinkCmdPrint _sltpInfoCmd;
    MlxlinkCmdPrint _showDeviceInfoCmd;
    MlxlinkCmdPrint _showBerMonitorInfo;
    MlxlinkCmdPrint _extPhyInfoCmd;
    MlxlinkCmdPrint _linkBlameInfoCmd;
    MlxlinkCmdPrint _validPcieLinks;
    MlxlinkCmdPrint _cableDumpRawCmd;
    MlxlinkCmdPrint _cableDDMCmd;
    MlxlinkCmdPrint _portGroupMapping;

    // Mlxlink config functions
    void clearCounters();
    void sendPaos();
    void handlePrbs();
    void sendPtys();
    virtual void sendPplm();
    void sendSltp();
    void sendPplr();
    void sendPepc();
    void setTxGroupMapping();

    // Config helper functions
    bool isForceDownSupported();
    bool isPPHCRSupported();
    void sendGBPaosCmd(PAOS_ADMIN adminStatus, bool forceDown);
    void sendPaosCmd(PAOS_ADMIN adminStatus, bool forceDown = false);
    void sendPaosDown(bool toggleCommand = false);
    void sendPaosUP();
    void sendPaosToggle();
    void checkPRBSModeCap(u_int32_t modeSelector, u_int32_t capMask);
    void checkPrbsRegsCap(const string &prbsReg, const string &laneRate);
    void checkPrbsPolCap(const string &prbsReg);
    void checkPprtPptt();
    void checkPplrCap();
    void sendPrbsPpaos(bool);
    void startTuning();
    void prbsConfiguration(const string &prbsReg, bool enable, u_int32_t laneRate,
            u_int32_t prbsMode, bool perLaneConfig, bool prbsPolInv);
    void sendPprtPptt();
    void resetPprtPptt();
    u_int32_t ptysSpeedToMask(const string & speed);
    void validateSpeedStr();
    void checkSupportedSpeed(const string & speed, u_int32_t cap, bool extSpeed = false);
    string speedToFecSpeedStr(const string &speed, u_int32_t numOfLanes);
    u_int32_t fecToBit(const string &fec, const string &speedStrG);
    u_int32_t getFecCapForCheck(const string &speedStr);
    void checkPplmCap();
    void updateSltp28_40nmFields();
    void updateSltp16nmFields();
    void updateSltp7nmFields();
    string getSltpStatus();
    void getSltpAlevOut(u_int32_t lane);
    void getSltpRegAndLeva(u_int32_t lane);
    u_int32_t getLaneSpeed(u_int32_t lane);
    void validateNumOfParamsForNDRGen();
    void checkSltpParamsSize();

    // Mlxlink params
    UserInput _userInput;
    dm_dev_id_t _devID;
    u_int32_t _localPort;
    u_int32_t _portType;
    DPN _dpn;
    u_int32_t _numOfLanes;
    u_int32_t _numOfLanesPcie;
    u_int32_t _cableMediaType;
    u_int32_t _fecActive;
    u_int32_t _protoActive;
    u_int32_t _uniqueCmds;
    u_int32_t _uniqueCableCmds;
    u_int32_t _networkCmds;
    u_int32_t _anDisable;
    u_int32_t _speedBerCsv;
    u_int32_t _cableIdentifier;
    u_int32_t _cableTechnology;
    u_int32_t _cableAtten12G;
    u_int32_t _cableLen;
    u_int32_t _activeSpeed;
    u_int32_t _activeSpeedEx;
    u_int32_t _protoCapability;
    u_int32_t _deviceCapability;
    u_int32_t _protoAdmin;
    u_int32_t _protoAdminEx;
    u_int32_t _productTechnology;
    u_int32_t _moduleNumber;
    u_int32_t _linkSpeed;
    string _extAdbFile;
    string _device;
    string _fwVersion;
    string _speedStrG;
    string _speedForce;
    string _cablePN;
    string _cableSN;
    string _moduleTemp;
    bool _protoCapabilityEx;
    bool _linkUP;
    bool _prbsTestMode;
    bool _plugged;
    bool _linkModeForce;
    bool _useExtAdb;
    bool _isHCA;
    bool _ddmSupported;
    bool _cmisCable;
    bool _qsfpCable;
    bool _portPolling;
    bool _mngCableUnplugged;
    bool _isPam4Speed;
    bool _ignorePortType;
    bool _ignorePortStatus;
    bool _isGboxPort;
    bool _ignoreIbFECCheck;
    std::vector<std::string> _ptysSpeeds;
    std::vector<PortGroup> _localPortsPerGroup;
    std::vector<DPN> _validDpns;
    string _allUnhandledErrors;
    Json::Value _jsonRoot;
    MlxlinkMaps* _mlxlinkMaps;
    MlxlinkCablesCommander* _cablesCommander;
    MlxlinkEyeOpener* _eyeOpener;
    MlxlinkErrInjCommander* _errInjector;
    MlxlinkPortInfo* _portInfo;
    MlxlinkAmBerCollector* _amberCollector;

protected:
    vector<AmberField> _ppcntFields;
    string loopAllLanesStr(vector<AmberField> &fields, string str);
};

#endif /* MLXLINK_COMMANDER_H */
