//#include "InfoComm_CCM_Serv.h"

#ifndef __INFO_COMM_CCM_SERV__
#define __INFO_COMM_CCM_SERV__

#pragma pack(push, 1)

#define STR_DEF_SERVER_ADDR					_T("192.168.0.3")
#define NUM_ICCS_NET_COMM_BASE_PORT			8010


#define IDX_ICCS_DT_REQ_USM_LGM_STAT		0x01
#define IDX_ICCS_DT_RES_USM_LGM_STAT		0x11

#define IDX_ICCS_DT_REQ_SET_USM_ADDR		0x21
#define IDX_ICCS_DT_REQ_SET_LGM_ADDR		0x22
#define IDX_ICCS_DT_REQ_SET_USM_OP_MODE		0x23
#define IDX_ICCS_DT_REQ_SET_LGM_OP_MODE		0x24
#define IDX_ICCS_DT_REQ_SET_USM_PARAM		0x25
#define IDX_ICCS_DT_REQ_SET_USM_TO_LGM		0x26

#define IDX_ICCS_DT_ACK						0x31

#define IDX_ICCS_DT_NACK					0x41

#define IDX_ICCS_DT_REQ_SENSING_OFF			0x61
#define IDX_ICCS_DT_REQ_SENSING_ON			0x62

#define IDX_ICCS_DT_REQ_SET_EBD_PARAM		0x71

#define SZ_ICCS_PKT_ITEM_STX				4
#define SZ_ICCS_PKT_ITEM_LENGTH				2
#define SZ_ICCS_PKT_ITEM_DATA_TYPE			1
#define SZ_ICCS_PKT_ITEM_DATA_ID			4
#define SZ_ICCS_PKT_ITEM_CRC16				2
#define SZ_ICCS_PKT_ITEM_ETX				4
#define SZ_ICCS_PKT_HDR_ALL					(SZ_ICCS_PKT_ITEM_STX +SZ_ICCS_PKT_ITEM_LENGTH +SZ_ICCS_PKT_ITEM_CRC16 +SZ_ICCS_PKT_ITEM_ETX)

const BYTE GL_ICCS_BUF_STX[SZ_ICCS_PKT_ITEM_STX] = {
	'd', 'j', 'H', 'S'
};
const BYTE GL_ICCS_BUF_ETX[SZ_ICCS_PKT_ITEM_ETX] = {
	's', 'w', 'D', 'J'
};

// SCM status flags.
// These flags are also used in NACK flag.
#define FLAG_ICCS_SCM_INIT					(1 <<7)
#define FLAG_ICCS_SCM_STAT_MISMATCH			(1 <<6)
#define FLAG_ICCS_SCM_SENSING_ON			(1 <<5)
#define FLAG_ICCS_SCM_COMM_ERROR			(1 <<4)
enum {
	IDX_ICCS_NACK_ERR_NO_ERROR,
	IDX_ICCS_NACK_ERR_SCM_NOT_CONNECTED,
	IDX_ICCS_NACK_ERR_SCM_RX_INVALID_DATA,
	IDX_ICCS_NACK_ERR_SCM_RX_TIMEOUT,
	IDX_ICCS_NACK_ERR_SCM_RCV_NACK,
};
#define MASK_FOR_ICCS_SCM_FLAG				0xf8
#define MASK_FOR_ICCS_SCM_ERR_CODE			0x07

#define FLAG_ICCS_USM_USED					(1 <<7)
#define FLAG_ICCS_LGM_USED					(1 <<7)
#define MASK_FOR_ICCS_USM_LGM_STAT			0x0f

// Message[S]
struct ITEM_HDR_REQM {
	BYTE bufSTX[SZ_ICCS_PKT_ITEM_STX];
	BYTE bufLength[SZ_ICCS_PKT_ITEM_LENGTH];
	BYTE nDataType;
	BYTE devID_SCM;
	BYTE numItem;
};

struct ITEM_TRL_REQM {
	BYTE bufCRC[SZ_ICCS_PKT_ITEM_CRC16];
	BYTE bufETX[SZ_ICCS_PKT_ITEM_ETX];
};

struct ITEM_REQM_SET_ADDR {
	BYTE nDevID;
	BYTE bufSN[3];
};
struct ITEM_REQM_SET_OP_MODE {
	BYTE nDevID;
	BYTE idxOpMode;
};
struct ITEM_REQM_SET_PARAM {
	BYTE nDevID;
	BYTE nParam1;
	BYTE nParam2;
	BYTE nParam3;
	BYTE nParam4;
};
struct ITEM_REQM_SET_USM2LGM {
	BYTE nDevID_USM;
	BYTE nDevID_LGM;
};

struct ITEM_RESM_USM_LGM_STAT {
	BYTE statSCM;
	BYTE bufUSM_Stat[MAX_NUM_USM];	// [7]:Used flag, [3:0]:Op mode
	BYTE bufLGM_Stat[MAX_NUM_LGM];	// [7]:Used flag, [3:0]:Op mode
	BYTE bufUSM2LGM[MAX_NUM_USM];
	BYTE bbufUSM_Param[MAX_NUM_USM][NUM_USM_PARAM];
};
// Message[E]

#define DEF_NUM_NCS_RETRY			3
#define DEF_TIME_NCS_RCV_TIMEOUT	3000
struct INFO_NET_COMM_SETTINGS {
	int numRetry;
	DWORD timeRcvTimeout;
};


#pragma pack(pop)

#endif
