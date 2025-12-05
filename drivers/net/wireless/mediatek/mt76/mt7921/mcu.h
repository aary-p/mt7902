/* SPDX-License-Identifier: BSD-3-Clause-Clear */
/* Copyright (C) 2020 MediaTek Inc. */

#ifndef __MT7921_MCU_H
#define __MT7921_MCU_H

#include "../mt76_connac_mcu.h"

struct mt7921_mcu_tx_done_event {
	u8 pid;
	u8 status;
	__le16 seq;

	u8 wlan_idx;
	u8 tx_cnt;
	__le16 tx_rate;

	u8 flag;
	u8 tid;
	u8 rsp_rate;
	u8 mcs;

	u8 bw;
	u8 tx_pwr;
	u8 reason;
	u8 rsv0[1];

	__le32 delay;
	__le32 timestamp;
	__le32 applied_flag;
	u8 txs[28];

	u8 rsv1[32];
} __packed;

/* ext event table */
enum {
	MCU_EXT_EVENT_RATE_REPORT = 0x87,
};

struct mt7921_mcu_eeprom_info {
	__le32 addr;
	__le32 valid;
	u8 data[MT7921_EEPROM_BLOCK_SIZE];
} __packed;

#define MT_RA_RATE_NSS			GENMASK(8, 6)
#define MT_RA_RATE_MCS			GENMASK(3, 0)
#define MT_RA_RATE_TX_MODE		GENMASK(12, 9)
#define MT_RA_RATE_DCM_EN		BIT(4)
#define MT_RA_RATE_BW			GENMASK(14, 13)

enum {
	MT_EBF = BIT(0),	/* explicit beamforming */
	MT_IBF = BIT(1)		/* implicit beamforming */
};

struct mt7921_mcu_ant_id_config {
	u8 ant_id[4];
} __packed;

struct mt7921_txpwr_req {
	u8 ver;
	u8 action;
	__le16 len;
	u8 dbdc_idx;
	u8 rsv[3];
} __packed;

struct mt7921_txpwr_event {
	u8 ver;
	u8 action;
	__le16 len;
	struct mt7921_txpwr txpwr;
} __packed;

struct mt7921_wf_rf_pin_ctrl_event {
	u8 result;
	u8 value;
} __packed;

enum {
	TM_SWITCH_MODE,
	TM_SET_AT_CMD,
	TM_QUERY_AT_CMD,
};

enum {
	MT7921_TM_NORMAL,
	MT7921_TM_TESTMODE,
	MT7921_TM_ICAP,
	MT7921_TM_ICAP_OVERLAP,
	MT7921_TM_WIFISPECTRUM,
};

struct mt7921_rftest_cmd {
	u8 action;
	u8 rsv[3];
	__le32 param0;
	__le32 param1;
} __packed;

struct mt7921_rftest_evt {
	__le32 param0;
	__le32 param1;
} __packed;

int mt7902_mcu_set_channel_domain(struct mt76_phy *phy);

int mt7902_mcu_set_basic_config(struct mt792x_dev *dev);

int mt7902_mcu_send_init_handshake(struct mt792x_dev *dev);

int mt7902_mcu_send_init_handshake_v2(struct mt792x_dev *dev);

struct mt7921_clc_info_tlv {
	__le16 tag;
	__le16 len;

	u8 chan_conf; /* BIT(0) : Enable UNII-4
		       * BIT(1) : Enable UNII-5
		       * BIT(2) : Enable UNII-6
		       * BIT(3) : Enable UNII-7
		       * BIT(4) : Enable UNII-8
		       */
	u8 rsv[63];
} __packed;

struct bss_info_bmc_rate {
	__le16 tag;
	__le16 len;
	__le16 bc_trans;
	__le16 mc_trans;
	u8 short_preamble;
	u8 rsv[7];
} __packed;

struct bss_info_ra {
	__le16 tag;
	__le16 len;
	u8 op_mode;
	u8 adhoc_en;
	u8 short_preamble;
	u8 tx_streams;
	u8 rx_streams;
	u8 algo;
	u8 force_sgi;
	u8 force_gf;
	u8 ht_mode;
	u8 has_20_sta;		/* Check if any sta support GF. */
	u8 bss_width_trigger_events;
	u8 vht_nss_cap;
	u8 vht_bw_signal;	/* not use */
	u8 vht_force_sgi;	/* not use */
	u8 se_off;
	u8 antenna_idx;
	u8 train_up_rule;
	u8 rsv[3];
	unsigned short train_up_high_thres;
	short train_up_rule_rssi;
	unsigned short low_traffic_thres;
	__le16 max_phyrate;
	__le32 phy_cap;
	__le32 interval;
	__le32 fast_interval;
} __packed;

struct bss_info_hw_amsdu {
	__le16 tag;
	__le16 len;
	__le32 cmp_bitmap_0;
	__le32 cmp_bitmap_1;
	__le16 trig_thres;
	u8 enable;
	u8 rsv;
} __packed;

struct bss_info_he {
	__le16 tag;
	__le16 len;
	u8 he_pe_duration;
	u8 vht_op_info_present;
	__le16 he_rts_thres;
	__le16 max_nss_mcs[CMD_HE_MCS_BW_NUM];
	u8 rsv[6];
} __packed;

#define MT7902_MAC_ADDR_LEN 6

/* Derived from gen4m CMD_UPDATE_STA_RECORD */
struct mt7902_cmd_update_sta_record {
    u8 ucStaIndex;
    u8 ucStaType;
    u8 aucMacAddr[MT7902_MAC_ADDR_LEN];
    __le16 u2AssocId;
    __le16 u2ListenInterval;
    u8 ucBssIndex;
    u8 ucDesiredPhyTypeSet;
    __le16 u2DesiredNonHTRateSet;
    __le16 u2BSSBasicRateSet;
    u8 ucIsQoS;
    u8 ucIsUapsdSupported;
    u8 ucStaState;
    u8 ucMcsSet;
    u8 ucSupMcs32;
    u8 ucVersion;
    u8 aucRxMcsBitmask[10];
    __le16 u2RxHighestSupportedRate;
    __le32 u4TxRateInfo;
    __le16 u2HtCapInfo;
    __le16 u2HtExtendedCap;
    __le32 u4TxBeamformingCap;
    u8 ucAmpduParam;
    u8 ucAselCap;
    u8 ucRCPI;
    u8 ucNeedResp;
    u8 ucUapsdAc;
    u8 ucUapsdSp;
    u8 ucWlanIndex;
    u8 ucBMCWlanIndex;
    __le32 u4VhtCapInfo;
    __le16 u2VhtRxMcsMap;
    __le16 u2VhtRxHighestSupportedDataRate;
    __le16 u2VhtTxMcsMap;
    __le16 u2VhtTxHighestSupportedDataRate;
    u8 ucRtsPolicy;
    u8 ucVhtOpMode;
    u8 ucTrafficDataType;
    u8 ucTxGfMode;
    u8 ucTxSgiMode;
    u8 ucTxStbcMode;
    __le16 u2HwDefaultFixedRateCode;
    u8 ucTxAmpdu;
    u8 ucRxAmpdu;
    __le32 u4FixedPhyRate;
    __le16 u2MaxLinkSpeed;
    __le16 u2MinLinkSpeed;
    __le32 u4Flags;
    /* Union BA_SIZE flattened for simplicity */
    __le16 u2RxBaSize;
    __le16 u2TxBaSize; 
    __le16 u2PfmuId;
    u8 fgSU_MU;
    u8 fgETxBfCap;
    u8 ucSoundingPhy;
    u8 ucNdpaRate;
    u8 ucNdpRate;
    u8 ucReptPollRate;
    u8 ucTxMode;
    u8 ucNc;
    u8 ucNr;
    u8 ucCBW;
    u8 ucTotMemRequire;
    u8 ucMemRequire20M;
    u8 ucMemRow0;
    u8 ucMemCol0;
    u8 ucMemRow1;
    u8 ucMemCol1;
    u8 ucMemRow2;
    u8 ucMemCol2;
    u8 ucMemRow3;
    u8 ucMemCol3;
    __le16 u2SmartAnt;
    u8 ucSEIdx;
    u8 uciBfTimeOut;
    u8 uciBfDBW;
    u8 uciBfNcol;
    u8 uciBfNrow;
    /* Padding/Extra fields */
    u8 aucPadding1[3];
    u8 ucTxAmsduInAmpdu;
    u8 ucRxAmsduInAmpdu;
    u8 aucPadding2[2];
    __le32 u4TxMaxAmsduInAmpduLen;
    u8 aucPadding4[32];
} __packed;

/* Derived from gen4m CMD_SET_BSS_INFO (0x12) */
struct mt7902_cmd_set_bss_info {
    u8 ucBssIndex;
    u8 ucConnectionState;
    u8 ucCurrentOPMode;
    u8 ucSSIDLen;
    u8 aucSSID[32];
    u8 aucBSSID[6];
    u8 ucIsQBSS;
    u8 ucVersion;
    __le16 u2OperationalRateSet;
    __le16 u2BSSBasicRateSet;
    u8 ucStaRecIdxOfAP;
    u8 aucPadding0[1];
    __le16 u2HwDefaultFixedRateCode;
    u8 ucNonHTBasicPhyType;
    u8 ucAuthMode;
    u8 ucEncStatus;
    u8 ucPhyTypeSet;
    u8 ucWapiMode;
    u8 ucIsApMode;
    u8 ucBMCWlanIndex;
    u8 ucHiddenSsidMode;
    u8 ucDisconnectDetectThreshold;
    u8 ucIotApAct;
    u8 uc6GPwrRegBitMap;
    u8 aucPadding1[1];
    __le32 u4PrivateData;
    
    /* CMD_SET_BSS_RLM_PARAM flattened (approx 68 bytes in gen4m) */
    /* We break this down to match the 116 byte total size alignment */
    u8 ucPrimaryChannel;
    u8 ucCenterChannel;
    u8 ucCenterChannel2;
    u8 ucBandwidth;
    u8 ucOpRxNss;
    u8 ucOpTxNss;
    u8 ucSCO;
    u8 ucRlmPadding;
    u8 aucRlmPadding[60]; 
    
    /* Remaining CMD_SET_BSS_INFO fields */
    u8 ucDBDCBand;
    u8 ucWmmSet;
    u8 ucDBDCAction;
    u8 ucNss;
    u8 aucPadding2[2];
    u8 ucHeOpParams[6];
    u8 ucBssColorInfo;
    __le16 u2HeBasicMcsSet;
    u8 ucMaxBSSIDIndicator;
    u8 ucMBSSIDIndex;
    u8 aucPadding[12];
} __packed;

#define MT7902_BSS_UPDATE_MAX_SIZE	(sizeof(struct sta_req_hdr) +	\
					 sizeof(struct bss_info_omac) +	\
					 sizeof(struct bss_info_basic) +\
					 sizeof(struct bss_info_rf_ch) +\
					 sizeof(struct bss_info_ra) +	\
					 sizeof(struct bss_info_hw_amsdu) +\
					 sizeof(struct bss_info_he) +	\
					 sizeof(struct bss_info_bmc_rate) +\
					 sizeof(struct bss_info_ext_bss))

#endif
