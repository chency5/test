#include "interface.h"
#include "protocol.h"
#include "wrappers.h"

#include "datacenter.h"
#include "systemconfig.h"
//#include "chargerdata.h"
#include "utily.h"
#include "device_example_pile.h"

#include <string.h>



#define SINGLE_PHASE_AC         10
#define THREE_PHASE_AC          11
#define THREE_PHASE_DC          12

#define NONE_FUNCTION       10

#define DC_POWER_METER      10
#define AC_POWER_METER      11
#define DC_METER_MODE         12
#define AC_METER_MODE         13

#define SCAN_CODE_START                 10
#define PLUG_AND_CHARGE_FAST    11

#define START_SUCCESS                                 10
#define START_FAULT                                        11
#define START_TIMEOUT                                   12
#define VEHICLE_CONNECT_FAULT              13
#define VEHICLE_CHARGING                            14

#define STOP_SUCCESS                               10
#define STOP_FAULT                                      11

#define CALCULATE_COST                                             10
#define CALCULATE_QUANTITY                                    11
#define NONE_COST                                                          12

#define GW_PLUG_IN                 10
#define GW_PLUG_OUT             11

#define SCREEN_REGISTE                        10
#define SDK_VERSION                      "EVS_v1.1.7"

#define NONE_NET_CONNECT                                      10

#define NET_WORK_2G                                         11
#define NET_WORK_3G                                         12
#define NET_WORK_4G                                         13
#define NET_WORK_5G                                         14




#define NB_IOT                                                                    15
#define WIFI_NET                                                                 16
#define WIRD_NET                                                              17

#define NET_SIGNAL_LEVEL                                          25


#define CAN_NOT_OBAIN_SIGNAL                             10
#define UNICOM                                                                 11
#define MOBILE                                                                  12
#define TELECOM                                                              13
#define OTHER_VENDER                                                14

//#define 2011_BMS_VERSION               10
//#define 2015_BMS_VERSION               11

#define BMS_VERSION_2011               10
#define BMS_VERSION_2015               11



#define GUN_CHARGING        13


#define GW_GET_OPEN_STATE           10
#define GW_GET_CLOSE_STATE        11

#define METER_ADDR_LEN     6

#define QUERY_TRANSCATION        10
#define QUERY_METER_VALUE        11
#define QUERY_DAILY_LOG               12
#define QUERY_FAULT_RECORD     13
#define QUERY_BMS_RECORD         14

#define MESSAGE_FORMATE          10
#define FILE_FORMATE                      11

#define NONE_DATA_REPLY          10
#define EXIST_DATA_REPLY           11
#define NOT_ALLOW_REPLY          12

#define MAINTAIN_SUCCESS           10
#define MAINTAIN_CHARGING         11

#define GW_GUN_LOCK               10
#define GW_GUN_UNLOCK         11

#define SET_SUCCESS                         10
#define UNALLOW_UNLOCK                11
#define UNALLOW_LOCK                      12
#define UNEXIST_FUNCTION               13

#define SET_FAULT                               11

#define GW_SHARP_SEGMENT               10
#define GW_PEAK_SEGMENT                  11
#define GW_FLAT_SEGMENT                    12
#define GW_GALLEY_SEGMENT              13

#define NONE_THE_FUNCTIONS          12



typedef enum{
	REBOOT = 11,
	VOERHAUL,
	FREEZE,
	OPERATE,
	INOPERATE,
	EXIT_OPERATE,
	SET_RESTORE_FACTORY
}maintainStateInfo;


static int  isSameFault[EVS_MAX_PORT_NUM];

char gunMaterAddr[MAX_GUN_NUM][METER_ADDR_LEN];


char _product_key[IOTX_PRODUCT_KEY_LEN + 1] = "a1X3BP5v0vn";
char _device_name[IOTX_DEVICE_NAME_LEN + 1] = "EvseSdkTestDevice";
char _device_secret[IOTX_DEVICE_SECRET_LEN + 1] = "38be4ad34bd079b4f765f71a3a30fc4e";
char _device_reg_code[IOTX_DEVICE_REG_CODE_LEN + 1] = "";
char _device_uid[IOTX_DEVICE_UID_LEN + 1] = "1587416872968745";

int online_flag = 0;

#define DEVICE_EXAMPLE_TRACE(...)                               \
	do                                                          \
	{                                                           \
		HAL_Printf("\033[1;32;40m%s.%d: ", __func__, __LINE__); \
		HAL_Printf(__VA_ARGS__);                                \
		HAL_Printf("\033[0m\r\n");                              \
	} while (0)

unsigned long  encapsulationTimeData(char * timebuf){
	unsigned long timeValue = 0;
	int year = 0;
	int month = 0;
	int day = 0;
	int hour = 0;
	int minute = 0;
	int sec = 0;
	char buf[5] ;
	buf[0] = timebuf[0];
	buf[1] = timebuf[1];
	year = atoi(buf);
	buf[0] = timebuf[2];
	buf[1] =0;
	month = atoi(buf);
	buf[0] = timebuf[3];
	day = atoi(buf);
	buf[0] = timebuf[4];
	hour = atoi(buf);
	buf[0] = timebuf[5];
	minute = atoi(buf);
	buf[0] = timebuf[6];
	sec = atoi(buf);
	if(0 >= (int)(month -= 2)){
		month += 12;
		year -= 1;
	}
	timeValue =((( (unsigned long)(year / 4 - year / 100 + year / 400 + 367 * month / 12 + day) + year * 365 - 719499
		)*24 + hour
		)*60 + minute
		)*60 + sec;
	return timeValue;
}


void addGwMeterData(void *materBuf,int dataLen){
	FILE *meterFp = NULL;
	meterFp = fopen(GW_METER_DATA,"a+");
	if(meterFp == NULL){
		fclose(meterFp);
		return;
	}

	fwrite(materBuf,dataLen,1,meterFp);
//	fwrite("\r\n",1,2,meterFp);
	
	fclose(meterFp);
	meterFp = NULL;
	
	return;
	
}

void addGwErrorCode(void *errorCode,int dataLen){
	FILE *errFp = NULL;
	errFp = fopen(GW_ERROR_CODE,"a+");
	if(errFp == NULL){
		fclose(errFp);
		return;
	}

	fwrite(errorCode,dataLen,1,errFp);
//	fwrite("\r\n",1,2,errFp);

	fclose(errFp);
	errFp = NULL;

	return;
}

void addGwBmsData(void *bmsInfo,int dataLen){
	FILE *bmsFp = NULL;
	bmsFp = fopen(GW_BMS_DATA,"a+");
	if(bmsFp == NULL){
		fclose(bmsFp);
		return;
	}

	fwrite(getCurrentTime(),strlen(getCurrentTime()),1,bmsFp);
//	fwrite("\r\n",1,2,bmsFp);
	
	fwrite(bmsInfo,dataLen,1,bmsFp);
//	fwrite("\r\n",1,2,bmsFp);

	fclose(bmsFp);
	bmsFp = NULL;
	return;
}

void addGwLogData(void *logInfo,int dataLen){
	FILE *logFp = NULL;
	logFp = fopen(GW_LOG_DATA,"a+");
	if(logFp == NULL){
		fclose(logFp);
		return;
	}

	fwrite(logInfo,dataLen,1,logFp);
//	fwrite("\r\n",1,2,logInfo);

	fclose(logInfo);
	logInfo = NULL;
	return;
}   

int addGwConfigData(void *configInfo,int dataLen){
	FILE *configFp = NULL;
	configFp = fopen(GW_CONFIG_DATA,"w");
	if(configFp == NULL){
		fclose(configFp);
		return -1;
	}
	
	fwrite(configInfo,dataLen,1,configFp);
//	fwrite("\r\n",1,2,configFp);

	fclose(configFp);
	configFp = NULL;
	
	return 0;
}


int getStopCode(int gunNum){
	 int stopCode = 0;
	switch(getChargerBlockInfo(gunNum).chargeStopReason){ 
		case 0x3f:
		case 0x40:
		case 0x41:  stopCode = 1000; break;
		case 0x09: stopCode = 1001;  break;
	//	case 0x01: stopCode = 1002;  break;
		case 0x02: stopCode = 1003;  break;
		case 0x03: stopCode = 1004;  break;
		case 0x04: stopCode = 1005;  break;
		case 0x05: stopCode = 1007;  break;
		case 0x0d: stopCode = 1008;  break;
		case 0x01: stopCode = 1009;  break;
		case 0x35: stopCode = 1010;  break;
		case 0x39: stopCode = 1011;  break;
			
		default:break;
	}
	return stopCode;
}

int getErrorCode(int gunNum,bool isSave){
	int errorCode = 0;
	
	if(getChargerBlockInfo(gunNum).faultReason & SHIFT_LEFT_FOUR)
		errorCode = 5003;
	if(getChargerBlockInfo(gunNum).faultReason & SHIFT_LEFT_SIX)
		errorCode = 5004;
	if(getChargerBlockInfo(gunNum).faultReason & GET_LAST_TWO_BIT)
		errorCode = 5005;
	if(getChargerBlockInfo(gunNum).faultReason & SHIFT_LEFT_TWO)
		errorCode = 5006;
	if(getChargerBlockInfo(gunNum).faultReason & SHIFT_LEFT_FOUR)
		errorCode = 5007;
	if(getChargerBlockInfo(gunNum).faultReason & SHIFT_LEFT_SIX)
		errorCode = 5008;

	switch(getChargerBlockInfo(gunNum).chargeStopReason){
		case 0x07: errorCode = 3033;  break;
		case 0x0f:  errorCode = 3010;  break;
		case 0x0c: errorCode = 4009;  break;
		case 0x0b: errorCode = 4010;  break;
		case 0x10: errorCode = 3050;  break;
		case 0x16:
		case 0x17: errorCode = 3046;  break;
		case 0x15: errorCode = 3044;  break;
		case 0x13: errorCode = 3038;  break;
		case 0x12: errorCode = 3040;  break;
		case 0x1b:
		case 0x1c: errorCode = 4000;  break;
		case 0x39: errorCode = 5001;  break;
		case 0x20: errorCode = 5002;  break;
		case 0x49: errorCode = 5006;  break;
		case 0x3a: errorCode = 5010;  break;
		case 0x4e:
		case 0x4f:
		case 0x50:
		case 0x51:
		case 0x52:
		case 0x53:
		case 0x54: errorCode = 5012;  break;
		case 0x26: errorCode = 5006;  break;
		case 0x27: errorCode = 5007;  break;
		case 0x1f:  errorCode = 5011;  break;
		case 0x2b: errorCode = 5019;  break;
		case 0x2c: errorCode = 5020;  break;
		case 0x2d: errorCode = 5021;  break;
		case 0x2e: errorCode = 5022;  break;
		case 0x31: errorCode = 5024;  break;
		case 0x35:
		case 0x36: errorCode = 5026;  break;
	
		default:break;
	}
	
	if(isSave && errorCode != 0 && isSameFault[gunNum] != errorCode){
		char errBuf[20];
		sprintf(errBuf,"%s - %d",getCurrentTime(),errorCode);
		addGwErrorCode(errBuf,sizeof(errBuf));
		memset(errBuf,0,20);
		isSameFault[gunNum] = errorCode;
	}
	if(errorCode == 0)
		isSameFault[gunNum] = errorCode;
	
	return errorCode;
}




/** 断开连接事件回调 */
static int evs_disconnected_event_handler(void)
{
	online_flag = 0;
	DEVICE_EXAMPLE_TRACE("EVS--- Cloud Disconnected\n");
	return 0;
}

/** 事件回调：接收到云端回复属性上报应答 **/
static int evs_report_reply_event_handler(const int msgid, const int code, const char *reply,
										  const int reply_len)
{
	DEVICE_EXAMPLE_TRACE("EVS--- Message Post Reply Received, Message ID: %d, Code: %d, Reply: %.*s", msgid, code,
						 reply_len,
						 (reply == NULL) ? ("NULL") : (reply));
	return 0;
}

/** 事件回调：接收到云端回复的事件上报应答 **/
static int evs_trigger_event_reply_event_handler(const int msgid, const int code, const char *eventid,
												 const int eventid_len, const char *message, const int message_len)
{
	DEVICE_EXAMPLE_TRACE("EVS--- Trigger Event Reply Received, Message ID: %d, Code: %d, EventID: %.*s, Message: %.*s",
						 msgid, code,
						 eventid_len,
						 eventid, message_len, message);

	return 0;
}

/** 事件回调: SDK内部运行状态打印 **/
static int evs_sdk_state_dump(int ev, const char *msg)
{
	DEVICE_EXAMPLE_TRACE("EVS--- received state event, -0x%04x(%s)\n", -ev, msg);
	return 0;
}

/** 事件回调: 证书设置 **/
static int evs_device_cert_set(const evs_device_meta meta)
{
	//在这里实现证书三元组的存储,下面代码只是示例，设置成功返回0，设置失败返回-1
#if 0	

	int len = strlen(meta.product_key);
	memset(_product_key, 0x0, sizeof(_product_key));
	strncpy(_product_key, meta.product_key, IOTX_PRODUCT_KEY_LEN);
	_product_key[len] = '\0';

	len = strlen(meta.device_name);
	memset(_device_name, 0x0, sizeof(_device_name));
	strncpy(_device_name, meta.device_name, IOTX_DEVICE_NAME_LEN);
	_device_name[len] = '\0';

	len = strlen(meta.device_secret);
	memset(_device_secret, 0x0, sizeof(_device_secret));
	strncpy(_device_secret, meta.device_secret, IOTX_DEVICE_SECRET_LEN);
	_device_secret[len] = '\0';

	DEVICE_EXAMPLE_TRACE("EVS--- evs_device_cert_set\n");
	DEVICE_EXAMPLE_TRACE("evs_device_cert_set :meta.product_key is %s\n", meta.product_key);
	DEVICE_EXAMPLE_TRACE("evs_device_cert_set :meta.device_name is %s\n", meta.device_name);
	DEVICE_EXAMPLE_TRACE("evs_device_cert_set :meta.device_secret is %s\n", meta.device_secret);
#endif
	if(getDeviceInfo().deviceState == DEVICE_IDEL){
		memset(getgwConfig()->productKey,0,sizeof(getgwConfig()->productKey));
		memcpy(getgwConfig()->productKey,meta.product_key,strlen(meta.product_key));

		memset(getgwConfig()->deviceName,0,sizeof(getgwConfig()->deviceName));
		memcpy(getgwConfig()->deviceName,meta.device_name,strlen(meta.device_name));

		memset(getgwConfig()->deviceSecret,0,sizeof(getgwConfig()->deviceSecret));
		memcpy(getgwConfig()->deviceSecret,meta.device_secret,strlen(meta.device_secret));
		writeGwConfig();
	}
	
	return 0;
}
/** 事件回调: 证书读取 **/
static int evs_device_cert_get(evs_device_meta *meta)
{
	//在这里实现证书三元组的读取,下面为示例获取成功返回0，如果证书为空返回-1
#if 0
	int len = strlen(_product_key);
	if (len < 5)
	{
		DEVICE_EXAMPLE_TRACE("_product_key length is %d", len);
		return -1;
	}

	memset(meta->product_key, 0x0, sizeof(meta->product_key));
	strncpy(meta->product_key, _product_key, IOTX_PRODUCT_KEY_LEN);
	meta->product_key[len] = '\0';

	len = strlen(_device_name);
	if (len < 2)
	{
		DEVICE_EXAMPLE_TRACE("_device_name length is %d", len);
		return -1;
	}
	memset(meta->device_name, 0x0, sizeof(meta->device_name));
	strncpy(meta->device_name, _device_name, IOTX_DEVICE_NAME_LEN);
	meta->device_name[len] = '\0';

	len = strlen(_device_secret);
	if (len < 5)
	{
		DEVICE_EXAMPLE_TRACE("_device_secret length is %d", len);
		return -1;
	}
	memset(meta->device_secret, 0x0, sizeof(meta->device_secret));
	strncpy(meta->device_secret, _device_secret, IOTX_DEVICE_SECRET_LEN);
	meta->device_secret[len] = '\0';

	DEVICE_EXAMPLE_TRACE("EVS--- evs_device_cert_get\n");
	DEVICE_EXAMPLE_TRACE("evs_device_cert_get :meta->product_key is %s\n", meta->product_key);
	DEVICE_EXAMPLE_TRACE("evs_device_cert_get :meta->device_name is %s\n", meta->device_name);
	DEVICE_EXAMPLE_TRACE("evs_device_cert_get :meta->device_secret is %s\n", meta->device_secret);
#endif
	memset(meta->product_key, 0x0, sizeof(meta->product_key));
	memcpy(meta->product_key,getgwConfig()->productKey,strlen(getgwConfig()->productKey));

	memset(meta->device_name, 0x0, sizeof(meta->device_name));
	memcpy(meta->device_name,getgwConfig()->deviceName,strlen(getgwConfig()->deviceName));

	memset(meta->device_secret, 0x0, sizeof(meta->device_secret));
	memcpy(meta->device_secret,getgwConfig()->deviceSecret,strlen(getgwConfig()->deviceSecret));
	
	return 0;
}
/** 事件回调: 设备注册码获取 **/
static int evs_device_reg_code_get(char *device_reg_code)     // do not know where the value come from
{
	//在这里实现注册码的读取操作，读取成功返回注册码长度，如果注册码为NULL或读取失败返回-1

	int len = strlen(_device_reg_code);
	memset(device_reg_code, 0x0, IOTX_DEVICE_REG_CODE_LEN);
	strncpy(device_reg_code, _device_reg_code, IOTX_DEVICE_REG_CODE_LEN);
	device_reg_code[len] = '\0';
	DEVICE_EXAMPLE_TRACE("EVS--- evs_device_reg_code_get\n");
	DEVICE_EXAMPLE_TRACE("EVS--- device_reg_code is %s\n", device_reg_code);
	return strlen(_device_reg_code);
}
/** 事件回调: 设备唯一编码获取 **/
static int evs_device_uid_get(char *device_uid)    // do not know where the value come from
{
	//在这里实现注册码的读取操作，读取成功返回注册码长度，如果注册码为NULL或读取失败返回-1

	int len = strlen(_device_uid);
	memset(device_uid, 0x0, IOTX_DEVICE_UID_LEN);
	strncpy(device_uid, _device_uid, IOTX_DEVICE_UID_LEN);
	device_uid[len] = '\0';
	return strlen(_device_uid);
}

/******************************************SDK提供的接口供用户调用*************************************************/

/**
 *
 * 函数 evs_send_event() SDK内部实现的事件发送接口, 供使用者调用。
 * ---
 * Interface of evs_send_event() implemented by SDK， provide for user of SDK.
 *
 * 
 */
/**
 * @brief Send pile event data to SDK.
 *---
 * @param [in] event_type: @n the event you want to send.
 * @param [in] param: @n the event data will be written.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
//int  evs_send_event(evs_cmd_event_enum event_type, void *param);

/**
 *
 * 函数 evs_send_property() SDK内部实现的事件发送接口, 供使用者调用。
 * ---
 * Interface of evs_send_property() implemented by SDK， provide for user of SDK.
 *
 * 
 */
/**
 * @brief Send pile porperty data to SDK.
 *---
 * @param [in] event_type: @n the property you want to send.
 * @param [in] param: @n the property data will be written.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
//int  evs_send_property(evs_cmd_property_enum property_type, void *param);

/******************************************需用户实现的回调函数*************************************************/

/**
 *
 * 函数 callback_service_query_log() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_query_log() requires to be implemented by user of SDK.
 *
 * 
 */
/**
 * @brief Reply IOT platform log query service by param through SDK.
 *---
 * @param [in] param: @n the param received from IOT platform.
 * @param [out] result: @n the result data will be written by user of SDK.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */



void replyIotQueryTransction(evs_event_logQuery_Result queryTransction){
	if(queryTransction.askType != QUERY_TRANSCATION)
		return;
	
	evs_event_tradeInfo *tradeInfo;
	char buf[300];
	int dataLine = 0;
	int i = 0;
	FILE *historyP = NULL;

	queryTransction.logQueryEvtSum = 0;
	queryTransction.logQueryEvtNo = 0;
	dataLine = fileRowValue(HISTORY_PATH);
	tradeInfo = (evs_event_tradeInfo *)malloc(sizeof(evs_event_tradeInfo) + 5);
	historyP = fopen(HISTORY_PATH,"r");
	if(historyP == NULL){
		fclose(historyP);
		return;
	}
	
	for(i = 0 ; i < dataLine ; i ++){
		fscanf(historyP,"%[^\n]%*c",buf);
		tradeInfo = (evs_event_tradeInfo*)buf;
		if(tradeInfo->chargeEndTime < queryTransction.stopDate && tradeInfo->chargeStartTime > queryTransction.startDate){
			queryTransction.logQueryEvtSum ++;
		}
		memset(buf,0,sizeof(buf));
	}

	for(i = 0 ; i < dataLine ; i ++){
		fscanf(historyP,"%[^\n]%*c",buf);
		tradeInfo = (evs_event_tradeInfo*)buf;
		if(tradeInfo->chargeEndTime < queryTransction.stopDate && tradeInfo->chargeStartTime > queryTransction.startDate){
			queryTransction.dataArea.tradeInfo = *tradeInfo;
			queryTransction.logQueryEvtNo ++;
			queryTransction.retType = MESSAGE_FORMATE;
			evs_send_event(EVS_CMD_EVENT_LOGQUERY_RESULT,&queryTransction);
		}
		memset(buf,0,sizeof(buf));
	}
	fclose(historyP);
	historyP = NULL;
	return;
}

void replyIotQueryMeterValue(evs_event_logQuery_Result queryMeter){
	if(queryMeter.askType != QUERY_METER_VALUE)
		return;

	int lineNum = 0;
	unsigned long  timeData = 0;
	int i = 0;
	evs_property_meter *meterInfo;
	char meterBuf[200];
	FILE *meterFp = NULL;
	
	queryMeter.logQueryEvtSum = 0;
	queryMeter.logQueryEvtNo = 0;
	lineNum = fileRowValue(GW_METER_DATA);
	meterFp = fopen(GW_METER_DATA,"r");
	if(meterFp == NULL){
		fclose(meterFp);
		return;
	}

	for(i = 0 ; i < lineNum ; i ++){
		fscanf(meterFp,"%[^\n]%*c",meterBuf);
		meterInfo = (evs_property_meter*)meterBuf;
		timeData = encapsulationTimeData(meterInfo->acqTime);
		if(timeData > queryMeter.startDate && timeData < queryMeter.stopDate)
			queryMeter.logQueryEvtSum ++;
		
		memset(meterBuf,0,sizeof(meterBuf));
	}

	for(i = 0 ; i < lineNum ; i ++){
		fscanf(meterFp,"%[^\n]%*c",meterBuf);
		meterInfo = (evs_property_meter*)meterBuf;
		timeData = encapsulationTimeData(meterInfo->acqTime);
		if(timeData > queryMeter.startDate && timeData < queryMeter.stopDate){
			queryMeter.dataArea.meterData =  *meterInfo;
			queryMeter.logQueryEvtNo ++;
			queryMeter.retType = MESSAGE_FORMATE;
			evs_send_event(EVS_CMD_EVENT_LOGQUERY_RESULT,&queryMeter);
		}
		memset(meterBuf,0,sizeof(meterBuf));
	}
	fclose(meterFp);
	meterFp = NULL;
	return;
}

void replyIotLogData(evs_event_logQuery_Result quarylog){
	if(quarylog.askType != QUERY_DAILY_LOG)
		return;

	int lineNum = 0;
	unsigned long timeData = 0;
	int i = 0;
	FILE *logFp = NULL;
	char logBuf[20];
	char timeBuf[10];
	lineNum = fileRowValue(GW_LOG_DATA);
	logFp = fopen(GW_LOG_DATA,"r");
	if(logFp == NULL){
		fclose(logFp);
		return;
	}
	for(i = 0 ; i < lineNum ; i ++){
		fscanf(logFp,"%[^\n]%*c",logBuf);
		strncat(timeBuf,logBuf,7);
		timeData = encapsulationTimeData(timeBuf);
		if(timeData > quarylog.startDate && timeData < quarylog.stopDate){
			quarylog.logQueryEvtSum ++;
		}
		memset(logBuf,0,20);
		memset(timeBuf,0,10);
	}

	for(i = 0 ; i < lineNum ; i ++){
		fscanf(logFp,"%[^\n]%*c",logBuf);
		strncat(timeBuf,logBuf,7);
		timeData = encapsulationTimeData(timeBuf);
		if(timeData > quarylog.startDate && timeData < quarylog.stopDate){
			memcpy(quarylog.dataArea.rawData,logBuf,strlen(logBuf));
			quarylog.logQueryEvtSum ++;
			quarylog.retType = MESSAGE_FORMATE;
			evs_send_event(EVS_CMD_EVENT_LOGQUERY_RESULT,&quarylog);
		}
		memset(logBuf,0,20);
		memset(timeBuf,0,10);
	}

	fclose(logFp);
	logFp = NULL;
	return;
}


void replyIotErrorCode(evs_event_logQuery_Result queryErrCode){
	if(queryErrCode.askType != QUERY_FAULT_RECORD)
		return;
	
	int lineNum = 0;
	unsigned long  timeData = 0;
	FILE *errFp = NULL;
	char errBuf[20];
	char timeBuf[10];
	int i = 0;

	queryErrCode.logQueryEvtSum = 0;
	queryErrCode.logQueryEvtSum = 0;
	lineNum = fileRowValue(GW_ERROR_CODE);
	errFp = fopen(GW_ERROR_CODE,"r");
	if(errFp == NULL){
		fclose(errFp);
		return;
	}

	for(i = 0 ; i < lineNum ; i ++){
		fscanf(errFp,"%[^\n]%*c",errBuf);
		strncat(timeBuf,errBuf,7);
		timeData = encapsulationTimeData(timeBuf);
		if(timeData > queryErrCode.startDate && timeData < queryErrCode.stopDate){
			queryErrCode.logQueryEvtSum ++;
		}
		memset(errBuf,0,20);
		memset(timeBuf,0,10);
	}

	for(i = 0 ; i < lineNum ; i ++){
		fscanf(errFp,"%[^\n]%*c",errBuf);
		strncat(timeBuf,errBuf,7);
		timeData = encapsulationTimeData(timeBuf);
		if(timeData > queryErrCode.startDate && timeData < queryErrCode.stopDate){
			memcpy(queryErrCode.dataArea.rawData,errBuf,strlen(errBuf));
			queryErrCode.logQueryEvtSum ++;
			queryErrCode.retType = MESSAGE_FORMATE;
			evs_send_event(EVS_CMD_EVENT_LOGQUERY_RESULT,&queryErrCode);
		}
		memset(errBuf,0,20);
		memset(timeBuf,0,10);
	}
	fclose(errFp);
	errFp = NULL;
	return;
}

void replyIotBmsData(evs_event_logQuery_Result quaryBms){
	if(quaryBms.askType != QUERY_BMS_RECORD)
		return;

	evs_property_BMS *bmsInfo;
	FILE *bmsFp = NULL;
	int lineNum = 0;
	int i = 0;
	unsigned long  timeData = 0;
	char bmsBuf[200];
	char timeBuf[10];

	lineNum = fileRowValue(GW_BMS_DATA);
	quaryBms.logQueryEvtSum = 0;
	quaryBms.logQueryEvtNo = 0;
	bmsFp = fopen(GW_BMS_DATA,"r");
	if(bmsFp == NULL){
		fclose(bmsFp);
		return;
	}
	for(i = 0 ; i < (lineNum / 2); i ++){
		fscanf(bmsFp,"%[^\n]%*c",timeBuf);
		fscanf(bmsFp,"%[^\n]%*c",bmsBuf);
		timeData = encapsulationTimeData(timeBuf);
		if(timeData > quaryBms.startDate && timeData < quaryBms.stopDate)
			quaryBms.logQueryEvtSum ++;

		memset(bmsBuf,0,20);
		memset(timeBuf,0,10);
	}

	for(i = 0 ; i < (lineNum / 2) ; i ++){
		fscanf(bmsFp,"%[^\n]%*c",timeBuf);
		fscanf(bmsFp,"%[^\n]%*c",bmsBuf);
		timeData = encapsulationTimeData(timeBuf);
		if(timeData > quaryBms.startDate && timeData < quaryBms.stopDate){
			bmsInfo = (evs_property_BMS *)bmsBuf;
			quaryBms.dataArea.BMSData =  *bmsInfo;
			quaryBms.logQueryEvtNo ++;
			quaryBms.retType = MESSAGE_FORMATE;
			evs_send_event(EVS_CMD_EVENT_LOGQUERY_RESULT,&quaryBms);
		}
		memset(bmsBuf,0,20);
		memset(timeBuf,0,10);
	}

	fclose(bmsFp);
	bmsFp = NULL;
	return;
}

int callback_service_query_log(evs_service_query_log *param, evs_service_feedback_query_log *result){
	evs_event_logQuery_Result resultInfo;
	resultInfo.gunNo = result->gunNo = param->gunNo;
	resultInfo.startDate = result->startDate = param->startDate;
	resultInfo.stopDate = result->stopDate = param->stopDate;
	memcpy(result->logQueryNo,param->logQueryNo,strlen(param->logQueryNo));
	memcpy(resultInfo.logQueryNo,param->logQueryNo,strlen(param->logQueryNo));
	resultInfo.askType = result->askType = param->askType;
	resultInfo.result = result->result = EXIST_DATA_REPLY;
	
	switch(resultInfo.askType){
		case QUERY_TRANSCATION:{
			replyIotQueryTransction(resultInfo);
		}break;

		case QUERY_METER_VALUE:{
			replyIotQueryMeterValue(resultInfo);
		}break;

		case QUERY_DAILY_LOG:{
			replyIotLogData(resultInfo);
		}break;

		case QUERY_FAULT_RECORD:{
			replyIotErrorCode(resultInfo);
		}break;

		case QUERY_BMS_RECORD:{
			replyIotBmsData(resultInfo);
		}break;

		default: break;
	}
	
	return 0;
}

/**
 *
 * 函数 callback_service_dev_maintain() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_dev_maintain() requires to be implemented by user of SDK.
 *
 * 
 */
/**
 * @brief Reply IOT platform device control service by param through SDK.
 *---
 * @param [in] param: @n the param received from IOT platform.
 * @param [out] result: @n the result data will be written by user of SDK.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */

int callback_service_dev_maintain(evs_service_dev_maintain *param, evs_service_feedback_dev_maintain *result){
	maintainStateInfo maintainInfo;
	whole_device_info deviceInfo;
	maintainInfo = param->ctrlType;
	if(getDeviceInfo().deviceState != DEVICE_WORK){
		switch(maintainInfo){
			case REBOOT:{
				if(getDeviceInfo().deviceState != DEVICE_WORK)
					system("reboot");
			}break;

			case VOERHAUL:{
				deviceInfo = getDeviceInfo();
				deviceInfo.deviceState = DEVICE_OVERHAUL;
				setWholeDeviceInfo(deviceInfo);
			}break;

			case FREEZE:{
				deviceInfo = getDeviceInfo();
				deviceInfo.deviceState = DEVICE_FREEZEN;
				setWholeDeviceInfo(deviceInfo);
			}break;

			case OPERATE:{
				deviceInfo = getDeviceInfo();
				deviceInfo.deviceState = DEVICE_IDEL;
				setWholeDeviceInfo(deviceInfo);
			}break;

			case INOPERATE:{
				deviceInfo = getDeviceInfo();
				deviceInfo.deviceState = DEVICE_FREEZEN;
				setWholeDeviceInfo(deviceInfo);
			}break;

			case EXIT_OPERATE:{
				deviceInfo = getDeviceInfo();
				deviceInfo.deviceState = DEVICE_FREEZEN;
				setWholeDeviceInfo(deviceInfo);
			}break;
			
			case SET_RESTORE_FACTORY:{
				deviceInfo = getDeviceInfo();
				deviceInfo.deviceState = RESTORE_FACTORY_SET;
				setWholeDeviceInfo(deviceInfo);
			}break;

			default: break;
		}
	
		if(maintainInfo != REBOOT){
			char operateBuf[100];
			sprintf(operateBuf,"%s%d",getCurrentTime(),maintainInfo);
			addGwLogData(operateBuf,sizeof(operateBuf));
		}
		result->ctrlType = param->ctrlType;
		result->reason = MAINTAIN_SUCCESS;
	}else{
		result->ctrlType = param->ctrlType;
		result->reason = MAINTAIN_CHARGING;
	}
	
	return 0;
}

/**
 *
 * 函数 callback_service_lockCtrl() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_lockCtrl() requires to be implemented by user of SDK.
 *
 * 
 */
/**
 * @brief Reply IOT platform chargeGun e-lock control service by param through SDK.
 *---
 * @param [in] param: @n the param received from IOT platform.
 * @param [out] result: @n the result data will be written by user of SDK.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
int callback_service_lockCtrl(evs_service_lockCtrl *param, evs_service_feedback_lockCtrl *result)
{
#if 0
	result->gunNo = 0;
	result->lockStatus = 10;
	DEVICE_EXAMPLE_TRACE("callback_service_lockCtrl:param is gunNo: %d, result is lockStatus；%d \n", param->gunNo, result->lockStatus);
#endif

//	chargerBlockInfo chargeInfo;
	cloud_ctrl_fun ctrlFun;

	int gunNum = 0;

	gunNum = param->gunNo - 1;
	
	if(param->lockParam == GW_GUN_LOCK){
		ctrlFun = getCloudCtrlFun(gunNum);
		ctrlFun.isGunLock = GUN_LOCK;
		lockCloudCtrlFun(ctrlFun,gunNum);
	}

	if(param->lockParam == GW_GUN_UNLOCK){
		ctrlFun = getCloudCtrlFun(gunNum);
		ctrlFun.isGunLock = GUN_UNLOCK;
		lockCloudCtrlFun(ctrlFun,gunNum);
	}

	if(getCloudCtrlFun(gunNum).isGunLock == NONE_GUN_LOCK){
		result->resCode = UNEXIST_FUNCTION;
		return 0;
	}
	
	if(getCloudCtrlFun(gunNum).isGunLock == SET_LOCK_SUCCESS ||getCloudCtrlFun(gunNum).isGunLock == SET_UNLOCK_SUCCESS)
		result->resCode = SET_SUCCESS;
	
	if(getCloudCtrlFun(gunNum).isGunLock == SET_GUN_GAULT && param->lockParam == GW_GUN_LOCK)
		result->resCode = UNALLOW_LOCK;

	if(getCloudCtrlFun(gunNum).isGunLock == SET_GUN_GAULT && param->lockParam == GW_GUN_UNLOCK)
		result->resCode = UNALLOW_UNLOCK;
	
	return 0;
}

/**
 *
 * 函数 callback_service_issue_feeModel() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_issue_feeModel() requires to be implemented by user of SDK.
 *
 * 
 */
/**
 * @brief Reply IOT platform feemodel issue service by param through SDK.
 *---
 * @param [in] param: @n the param received from IOT platform.
 * @param [out] result: @n the result data will be written by user of SDK.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */

int callback_service_issue_feeModel(evs_service_issue_feeModel *param, evs_service_feedback_feeModel *result){
	if(getDeviceInfo().deviceState == DEVICE_IDEL){
		cost_rules_info costRulesInfo;
		int i = 0;
		costRulesInfo = getCostRulesInfo();
		memset(&costRulesInfo,0,sizeof(cost_rules_info));
		memcpy(costRulesInfo.costRulesVersion,param->eleModelId,strlen(param->eleModelId));
		memcpy(costRulesInfo.serviceRulesVersion,param->serModelId,strlen(param->serModelId));	
		costRulesInfo.sectionNum = param->TimeNum;
		for(i = 0 ; i < costRulesInfo.sectionNum ; i ++){
			costRulesInfo.segmentTime[i] = atoi(param->TimeSeg[i]);
			switch(param->SegFlag[i]){
				case GW_SHARP_SEGMENT:{
					costRulesInfo.segmentFlag[i] = JIAN_SECTION;
				}break;

				case GW_PEAK_SEGMENT:{
					costRulesInfo.segmentFlag[i] = FENG_SECTION;
				}break;

				case GW_FLAT_SEGMENT:{
					costRulesInfo.segmentFlag[i] = PING_SECTION;
				}break;

				case GW_GALLEY_SEGMENT:{
					costRulesInfo.segmentFlag[i] = GU_SECTION;
				}break;
			}
		}

		memcpy(costRulesInfo.costPrice,param->chargeFee,sizeof(param->chargeFee));
		memcpy(costRulesInfo.servicePrice,param->chargeFee,sizeof(param->serviceFee));

		memcpy(result->eleModelId,param->eleModelId,strlen(param->eleModelId));
		memcpy(result->serModelId,param->serModelId,strlen(param->serModelId));
		result->result = SET_SUCCESS;
	}else{
		memcpy(result->eleModelId,param->eleModelId,strlen(param->eleModelId));
		memcpy(result->serModelId,param->serModelId,strlen(param->serModelId));
		result->result = SET_FAULT;
	}
	
	return 0;
}

/**
 *
 * 函数 callback_service_startCharge() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_startCharge() requires to be implemented by user of SDK.
 *
 * 
 */
/**
 * @brief Reply IOT platform remote start-charge service by param through SDK.
 *---
 * @param [in] param: @n the param received from IOT platform.
 * @param [out] result: @n the result data will be written by user of SDK.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
int callback_service_startCharge(evs_service_startCharge *param, evs_service_feedback_startCharge *result)  // the can protocol lack relevant data so it is not complete.
{
	int gunNum = 0;
	
	gunNum = param->gunNo;
	if(getChargerBlockInfo(gunNum).gunState == PLUG_IN){
		cloud_ctrl_fun ctrlFun;
		userAccountInfo accountInfo;
		ctrlFun = getCloudCtrlFun(gunNum);
		accountInfo = getUserAccountInfo(gunNum);
			
		memset(accountInfo.cloudTradeNum,0,sizeof(accountInfo.cloudTradeNum));
		memcpy(accountInfo.cloudTradeNum,param->preTradeNo,strlen(param->preTradeNo));
		ctrlFun.startType = param->startType;
		ctrlFun.chargeLimit.limitType = param->chargeMode;
		ctrlFun.chargeLimit.limitData = param->limitData;
		lockCloudCtrlFun(ctrlFun,gunNum);
		lockUserAccount(accountInfo,gunNum);
	      // stop code  , srart mode and insert gun time this three parameter do not use now.
	      
		// lack the start charging function.

		  
		memcpy(result->preTradeNo, param->preTradeNo, sizeof(result->preTradeNo));
		memcpy(result->tradeNo, param->preTradeNo, sizeof(result->tradeNo));
		result->gunNo = param->gunNo;
		DEVICE_EXAMPLE_TRACE("callback_service_startCharge:param is gunNo:%d,result is tradeNo:%s \n", param->gunNo, result->tradeNo);
		return 0;
	}else{
		memcpy(result->preTradeNo, param->preTradeNo, sizeof(result->preTradeNo));
		memcpy(result->tradeNo, param->preTradeNo, sizeof(result->tradeNo));
		result->gunNo = param->gunNo;
		DEVICE_EXAMPLE_TRACE("callback_service_startCharge:param is gunNo:%d,result is tradeNo:%s \n", param->gunNo, result->tradeNo);
		return -1;
	}
}

/**
 *
 * 函数 callback_service_authCharge() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_authCharge() requires to be implemented by user of SDK.
 *
 * 
 */
/**
 * @brief Reply IOT platform authorization charge service by param through SDK.
 *---
 * @param [in] param: @n the param received from IOT platform.
 * @param [out] result: @n the result data will be written by user of SDK.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */

char judgeAuthResult(int authType){
	char authResult = 0;
	switch(authType){
		case 10: authResult = 0; break;
		case 11: authResult = 0x13; break;
		case 12: authResult = 0x02; break;
		case 13: authResult = 0x01; break;
		case 14: authResult = 0x1e; break;
		case 15: authResult = 0x15; break;
		case 16: authResult = 0x04; break;
		case 17: authResult = 0x03; break;
		case 18: authResult = 0x16; break;
		case 19: authResult = 0x17; break;
		case 20: authResult = 0x18; break;
		case 21: authResult = 0x0d; break;
		case 22: authResult = 0x20; break;
		case 23: authResult = 0x29; break;
		case 24: authResult = 0x2a; break;
		case 25: authResult = 0x2b; break;
		case 26: authResult = 0x2f;  break;
		case 27: authResult = 0x13; break;

		default: break;
	}

	return authResult;
}

int callback_service_authCharge(evs_service_authCharge *param, evs_service_feedback_authCharge *result){   
	char gunNum = 0;
	gunNum = param->gunNo;
	if(getChargerBlockInfo(gunNum).gunState == PLUG_IN){
		
		userAccountInfo accountInfo;
		cloud_ctrl_fun ctrlFun;
		
		accountInfo = getUserAccountInfo(gunNum);
		ctrlFun = getCloudCtrlFun(gunNum);
		memset(accountInfo.cloudTradeNum,0,sizeof(accountInfo.cloudTradeNum));
		memcpy(accountInfo.cloudTradeNum,param->preTradeNo,strlen(param->preTradeNo));
		ctrlFun.chargeLimit.limitType = param->chargeMode;
		ctrlFun.chargeLimit.limitData = param->limitData;
		accountInfo.IdentifyResult = judgeAuthResult(param->result);
		
		lockCloudCtrlFun(ctrlFun,gunNum);
		lockUserAccount(accountInfo,gunNum);

	//	cardIdentifyData(gunNum);
		memcpy(result->preTradeNo, param->preTradeNo, sizeof(result->preTradeNo));
		memcpy(result->tradeNo, param->preTradeNo, sizeof(result->tradeNo));
		result->gunNo = param->gunNo;
		return 0;
	}else{
		memcpy(result->preTradeNo, param->preTradeNo, sizeof(result->preTradeNo));
		memcpy(result->tradeNo, param->preTradeNo, sizeof(result->tradeNo));
		result->gunNo = param->gunNo;
		return -1;
	}
		
	
}

/**
 *
 * 函数 callback_service_stopCharge() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_stopCharge() requires to be implemented by user of SDK.
 *
 * 
 */
/**
 * @brief Reply IOT platform remote stop-charge service by param through SDK.
 *---
 * @param [in] param: @n the param received from IOT platform.
 * @param [out] result: @n the result data will be written by user of SDK.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
int callback_service_stopCharge(evs_service_stopCharge *param, evs_service_feedback_stopCharge *result){
	int gunNum = 0;
	gunNum = param->gunNo;

	if(getChargerBlockInfo(gunNum).gunState == CHARGING){
		chargerBlockInfo chargerInfo;
		chargerInfo.chargeStopReason = param->stopReason;
		lockChargerInfo(chargerInfo,gunNum);

		// lack the stop charging function.

		memcpy(result->preTradeNo, param->preTradeNo, sizeof(result->preTradeNo));
		memcpy(result->tradeNo, param->preTradeNo, sizeof(result->tradeNo));
		result->gunNo = param->gunNo;
		return 0;
	}else{
		memcpy(result->preTradeNo, param->preTradeNo, sizeof(result->preTradeNo));
		memcpy(result->tradeNo, param->preTradeNo, sizeof(result->tradeNo));
		result->gunNo = param->gunNo;
		return -1;
	}
	
	
}

/**
 *
 * 函数 callback_service_rsvCharge() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_rsvCharge() requires to be implemented by user of SDK.
 *
 * 
 */
/**
 * @brief Reply IOT platform reservation charge service by param through SDK.
 *---
 * @param [in] param: @n the param received from IOT platform.
 * @param [out] result: @n the result data will be written by user of SDK.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */


int callback_service_rsvCharge(evs_service_rsvCharge *param, evs_service_feedback_rsvCharge *result){

	result->gunNo = param->gunNo;
	result->appomathod = param->appomathod;
	result->ret = NONE_THE_FUNCTIONS;
	return 0;
}

/**
 *
 * 函数 callback_service_confirmTrade() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_confirmTrade() requires to be implemented by user of SDK.
 *
 * 
 */
/**
 * @brief Reply IOT platform transaction confirm service by param through SDK.
 *---
 * @param [in] param: @n the param received from IOT platform.
 * @param [out] result: @n the result data will be written by user of SDK.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
int callback_service_confirmTrade(evs_service_confirmTrade *param, void *result){
	if(param->errcode == SET_SUCCESS)    // trade recodrd upload success.
		return 0;        

	return -1;
}

/**
 *
 * 函数 callback_service_grounLock_ctrl() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_grounLock_ctrl() requires to be implemented by user of SDK.
 *
 * 
 */
/**
 * @brief Reply IOT platform smart ground locker service by param through SDK.
 *---
 * @param [in] param: @n the param received from IOT platform.
 * @param [out] result: @n the result data will be written by user of SDK.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
int callback_service_grounLock_ctrl(evs_service_groundLock_ctrl *param, evs_service_feedback_groundLock_ctrl *result){
	result->gunNo = param->gunNo;
	result->result = param->ctrlFlag;
	result->reason = 10;
	return 0;
}

/**
 *
 * 函数 callback_service_gateLock_ctrl() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_gateLock_ctrl() requires to be implemented by user of SDK.
 *
 * 
 */
/**
 * @brief Reply IOT platform smart gate locker service by param through SDK.
 *---
 * @param [in] param: @n the param received from IOT platform.
 * @param [out] result: @n the result data will be written by user of SDK.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
int callback_service_gateLock_ctrl(evs_service_gateLock_ctrl *param, evs_service_feedback_gateLock_ctrl *result)
{
	result->lockNo = param->lockNo;
	result->result = 10;
	DEVICE_EXAMPLE_TRACE("evs_gate_lock_service:param is ctrlFlag: %d, result is lockNo: %d \n", param->ctrlFlag, param->lockNo);
	return 0;
}

/**
 *
 * 函数 callback_service_orderCharge() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_orderCharge() requires to be implemented by user of SDK.
 *
 * 
 */
/**
 * @brief Reply IOT platform order-charge strategy service by param through SDK.
 *---
 * @param [in] param: @n the param received from IOT platform.
 * @param [out] result: @n the result data will be written by user of SDK.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
/************直流功率调节控制与交流有序充电共用回调****************/
int callback_service_orderCharge(evs_service_orderCharge *param, evs_service_feedback_orderCharge *result){
	whole_device_info deviceInfo;
	deviceInfo = getDeviceInfo();
	memset(&deviceInfo.powerControl,0,sizeof(deviceInfo.powerControl));
	memcpy(deviceInfo.powerControl.powerTime,param->validTime,strlen((char *)param->validTime));
	memcpy(deviceInfo.powerControl.powerData,param->kw,sizeof(param->kw) /sizeof(param->kw[0]));
	deviceInfo.powerControl.segNum = param->num;

	strcpy(result->preTradeNo,param->preTradeNo);
	result->result = SET_SUCCESS;
	result->reason = SET_SUCCESS;

	return 0;
}

/**
 *
 * 函数 callback_service_get_config() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_get_config() requires to be implemented by user of SDK.
 *
 * 
 */
/**
 * @brief Reply IOT platform device configuration get service by result through SDK.
 *---
 * @param [out] result: @n the result data will be written by user of SDK.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
int callback_service_get_config(evs_data_dev_config *result){
	FILE *conFp = NULL;
	char buf[300] = {0};
	conFp = fopen(GW_CONFIG_DATA,"r");
	if(conFp == NULL){
		fclose(conFp);
		return -1;
	}
	fscanf(conFp,"%[^\n]%*c",buf);
	result = (evs_data_dev_config*)buf;
//	fread(result,sizeof(result),1,conFp);
	
	return 0;
}
/**
 *
 * 函数 callback_service_get_maintain_status() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_get_maintain_status() requires to be implemented by user of SDK.
 *
 * 
 */
/**
 * @brief Reply IOT platform device configuration get service by result through SDK.
 *---
 * @param [out] result: @n the result data will be written by user of SDK.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
int callback_service_get_maintain_status(evs_service_feedback_maintain_query *result)
{
	FILE *logFp = NULL;
	int lineNum = 0;
	int i = 0;
	int len = 0;
	char logBuf[10];
	lineNum = fileRowValue(GW_LOG_DATA);
	logFp = fopen(GW_LOG_DATA,"r");
	if(logFp == NULL){
		fclose(logFp);
		return -1;
	}

	for(i = 0 ; i < lineNum ; i ++){
		memset(logBuf,0,10);
		fgets(logBuf,10,logFp);
	}
	len = strlen(logBuf);
	result->ctrlType = logBuf[len -1];
	result->result = SET_SUCCESS;
	return 0;
}
/**
 *
 * 函数 callback_service_update_config() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_update_config() requires to be implemented by user of SDK.
 *
 * 
 */
/**
 * @brief Reply IOT platform update devicce configuration service by param through SDK.
 *---
 * @param [in] param: @n the param received from IOT platform.
 * @param [out] result: @n the result data will be written by user of SDK.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
int callback_service_update_config(evs_data_dev_config *param, int *result){
	if(addGwConfigData(param,sizeof(evs_data_dev_config)) == 0)
		*result = SET_SUCCESS;
	else
		*result = SET_FAULT;
	
	return 0;
}

/**
 *ota升级 需要动态申请内存，根据设备当前状态通过返回值确定是否升级
 * 函数 callback_service_ota_update() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_ota_update() requires to be implemented by user of SDK.
 *
 * 
 */
/**
 * @brief perform the ota order  from IOT platform .
 *---
 * @param [in] version: @n the new firmware version received from IOT platform.
 * 
 * @param [out] buffer: @n the ota buffer that need you to apply by malloc.

 * @param [out] buffer_length: @n the buffer length of ota.
 * @return do not update device -1 update device 0.
 * @see None.
 * @note None.
 */

static bool isUpGrade = false;

int callback_service_ota_update(const char *version)
{
	if(!isUpGrade){
//		setSoftwareVersion(atoi(version));
		controlConfigInfo()->softwareVersion = atoi(version);

		unsigned char buf[1024] = {};
//		DEVICE_EXAMPLE_TRACE("version is %s\n", version);
		evs_linkkit_fota(buf, 1024);
		isUpGrade = true;

		return 0;
	}

#if 0
	unsigned char buf[1024] = {};
	DEVICE_EXAMPLE_TRACE("version is %s\n", version);
	evs_linkkit_fota(buf, 1024);
#endif
	return -1; //升级
}

/**
 *
 * 函数 callback_service_time_sync() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of callback_service_time_sync() requires to be implemented by user of SDK.
 *
 * 
 */
/**
 * @brief send timestamp that Recived from IOT platform to user by timestamp through SDK.
 *---
 * @param [in] param: @n the param received from IOT platform.
 * @param [out] result: @n the result data will be written by user of SDK.
 * @return failed -1 success 0.
 * @see None.
 * @note None.
 */
int callback_service_time_sync(const unsigned int timestamp)
{
	char retBuf[100] = {0};
	timestempToTimeDate(timestamp,retBuf);
	TimeSyncInstruction(retBuf);
	return 0;
}


void assignedFirmwareEvt(){
	evs_event_fireware_info firewareInfo;
	int i = 0;
	memset(&firewareInfo,0,sizeof(firewareInfo));
	memcpy(firewareInfo.simNo,getSimNum(),strlen(getSimNum()) + 1);
	memcpy(firewareInfo.eleModelId,getCostRulesInfo().costRulesVersion , strlen(getCostRulesInfo().costRulesVersion) + 1);
	memcpy(firewareInfo.serModelId,getCostRulesInfo().serviceRulesVersion,strlen(getCostRulesInfo().serviceRulesVersion) + 1);
//	memcpy(firewareInfo.stakeModel,controlConfigInfo()->serialNum,strlen(controlConfigInfo()->serialNum) + 1);   
	firewareInfo.stakeModel[0] = controlConfigInfo()->deviceType & 0xff;
	firewareInfo.stakeModel[1] = controlConfigInfo()->deviceType >> 8 & 0xff;
	firewareInfo.stakeModel[2] = controlConfigInfo()->deviceType >> 16 & 0xff;
	firewareInfo.stakeModel[3] = controlConfigInfo()->deviceType >> 24 & 0xff;
	firewareInfo.vendorCode = controlConfigInfo()->manufactureCode;
	memcpy(firewareInfo.devSn,controlConfigInfo()->serialNum,strlen(controlConfigInfo()->serialNum) + 1);  
	firewareInfo.devType = THREE_PHASE_DC;
	firewareInfo.portNum = controlConfigInfo()->gunTotalNum;   
	memcpy(firewareInfo.simMac,getMacAddr(),strlen( getMacAddr()) + 1);
	firewareInfo.longitude = 0;
	firewareInfo.latitude = 0;
	firewareInfo.height = 0;  
	firewareInfo.gridType = NONE_FUNCTION;
	memcpy(firewareInfo.btMac," ",strlen(" "));
	firewareInfo.meaType = DC_POWER_METER;
	firewareInfo.otRate = controlConfigInfo()->maxOutPutPower;
	firewareInfo.otMinVol = controlConfigInfo()->minOutputVol;
	firewareInfo.otMaxVol = controlConfigInfo()->maxOutputVol;
	firewareInfo.otCur = controlConfigInfo()->maxOutputCurrent;
	memset(firewareInfo.inMeter,0,sizeof(firewareInfo.inMeter));
	for(i = 0 ; i < MAX_GUN_NUM ; i ++){
		memcpy(firewareInfo.outMeter[i],gunMaterAddr[i],METER_ADDR_LEN);
	}
	firewareInfo.CT = 0;
	firewareInfo.isGateLock = NONE_FUNCTION;
	firewareInfo.isGroundLock = NONE_FUNCTION;

	evs_send_event(EVS_CMD_EVENT_FIREWARE_INFO,&firewareInfo);
	return;
}

void assignedAskFeedModelEvt(int gunNum){
	evs_event_ask_feeModel feeModelInfo;
	memset(&feeModelInfo,0,sizeof(feeModelInfo));
	feeModelInfo.gunNo = gunNum;
	memcpy(feeModelInfo.eleModelId,getCostRulesInfo().costRulesVersion,strlen(getCostRulesInfo().costRulesVersion) + 1);
	memcpy(feeModelInfo.serModeId,getCostRulesInfo().serviceRulesVersion,strlen(getCostRulesInfo().costRulesVersion) + 1);

	evs_send_event(EVS_CMD_EVENT_ASK_FEEMODEL,&feeModelInfo);
	return;
}

void assignedStartChargeAuthEvt(int gunNum){
	evs_event_startCharge startChargeInfo;
	int i = 0;
	memset(&startChargeInfo,0,sizeof(startChargeInfo));
	startChargeInfo.gunNo = gunNum;
	memcpy(startChargeInfo.preTradeNo,getUserAccountInfo(gunNum).cloudTradeNum,strlen(getUserAccountInfo(gunNum).cloudTradeNum));
	for(i = 0 ; i < 32 ; i ++){
		startChargeInfo.tradeNo[i] = getChargerBlockInfo(gunNum).chargingList[i]; 
	}
//	startChargeInfo.tradeNo[0] = getChargerBlockInfo(gunNum).localChargeNum & 0xff;
//	startChargeInfo.tradeNo[1] = getChargerBlockInfo(gunNum).localChargeNum >> 8 & 0xff;
//	startChargeInfo.tradeNo[2] = getChargerBlockInfo(gunNum).localChargeNum >> 16 & 0xff;
//	startChargeInfo.tradeNo[3] = getChargerBlockInfo(gunNum).localChargeNum >> 24 & 0xff;
	startChargeInfo.startType = PLUG_AND_CHARGE_FAST;
	if(startChargeInfo.startType == SCAN_CODE_START){

	}else{
		memcpy(startChargeInfo.authCode,getChargerBlockInfo(gunNum).vehicleVin,strlen(getChargerBlockInfo(gunNum).vehicleVin));
	}
	startChargeInfo.batterySOC = getChargerBlockInfo(gunNum).currentSoc;
	startChargeInfo.batteryCap = getBatteryBlockInfo(gunNum).batteryCapacity;
	startChargeInfo.chargeTimes = getBatteryBlockInfo(gunNum).batteryChargeNum;
	startChargeInfo.batteryVol = getBatteryBlockInfo(gunNum).batteryCurrentVol;
	evs_send_event(EVS_CMD_EVENT_STARTCHARGE,&startChargeInfo);
	return;
}

void assignedStartChaResEvt(int gunNum){
	evs_event_startResult startResultInfo;
	int i = 0;
	memset(&startResultInfo,0,sizeof(startResultInfo));
	startResultInfo.gunNo = gunNum;
	memcpy(startResultInfo.preTradeNo,getUserAccountInfo(gunNum).cloudTradeNum,strlen(getUserAccountInfo(gunNum).cloudTradeNum));
	for(i = 0 ; i < 32 ; i ++){
		startResultInfo.tradeNo[i] = getChargerBlockInfo(gunNum).chargingList[i]; 
	}
//	startResultInfo.tradeNo[0] = getChargerBlockInfo(gunNum).localChargeNum & 0xff;
//	startResultInfo.tradeNo[1] = getChargerBlockInfo(gunNum).localChargeNum >> 8 & 0xff;
//	startResultInfo.tradeNo[2] = getChargerBlockInfo(gunNum).localChargeNum >> 16 & 0xff;
//	startResultInfo.tradeNo[3] = getChargerBlockInfo(gunNum).localChargeNum >> 24 & 0xff;
	if(getChargerBlockInfo(gunNum).gunState == CONFIG || getChargerBlockInfo(gunNum).gunState == HANDSHAKE)
		startResultInfo.startResult = START_SUCCESS;
	if(getChargerBlockInfo(gunNum).gunState == STOP)
		startResultInfo.startResult = START_TIMEOUT;
	if(getChargerBlockInfo(gunNum).gunState == FAULT)
		startResultInfo.startResult = START_FAULT;
	if(getChargerBlockInfo(gunNum).gunState == CHARGING)
		startResultInfo.startResult = VEHICLE_CHARGING;

	if(startResultInfo.startResult == START_SUCCESS || startResultInfo.startResult == VEHICLE_CHARGING )
		startResultInfo.faultCode = 0;
	else
		startResultInfo.faultCode = getErrorCode(gunNum,false);

	memcpy(startResultInfo.vinCode,getChargerBlockInfo(gunNum).vehicleVin,strlen(getChargerBlockInfo(gunNum).vehicleVin));

	evs_send_event(EVS_CMD_EVENT_STARTRESULT,&startResultInfo);
	return;
}

void assignedStopChaResEvt(int gunNum){
	evs_event_stopCharge stopChargeInfo;
	int i = 0;
	memset(&stopChargeInfo,0,sizeof(stopChargeInfo));
	stopChargeInfo.gunNo = gunNum;
	memcpy(stopChargeInfo.preTradeNo,getUserAccountInfo(gunNum).cloudTradeNum,strlen(getUserAccountInfo(gunNum).cloudTradeNum));
	for(i = 0 ; i < 32 ; i ++){
		stopChargeInfo.tradeNo[i] = getChargerBlockInfo(gunNum).chargingList[i]; 
	}
//	stopChargeInfo.tradeNo[0] = getChargerBlockInfo(gunNum).localChargeNum & 0xff;
//	stopChargeInfo.tradeNo[1] = getChargerBlockInfo(gunNum).localChargeNum >> 8 & 0xff;
//	stopChargeInfo.tradeNo[2] = getChargerBlockInfo(gunNum).localChargeNum >> 16 & 0xff;
//	stopChargeInfo.tradeNo[3] = getChargerBlockInfo(gunNum).localChargeNum >> 24 & 0xff;
	if(getChargerBlockInfo(gunNum).gunState == IDEL ||getChargerBlockInfo(gunNum).gunState == STOP )
		stopChargeInfo.stopResult = STOP_SUCCESS;
	if(getChargerBlockInfo(gunNum).gunState == FAULT)
		stopChargeInfo.stopResult = STOP_FAULT;  
	stopChargeInfo.resultCode = getStopCode(gunNum);
	stopChargeInfo.stopFailReson = STOP_FAULT;    // already stoped

	evs_send_event(EVS_CMD_EVENT_STOPCHARGE,&stopChargeInfo);
	return;
}

static bool isConnectNet = false;

void assignedOrderUpdateEvt(int gunNum){
	evs_event_tradeInfo tradeInfo;
	int i = 0;
	memset(&tradeInfo,0,sizeof(tradeInfo));
	tradeInfo.gunNo = gunNum;
	memcpy(tradeInfo.preTradeNo,getUserAccountInfo(gunNum).cloudTradeNum,strlen(getUserAccountInfo(gunNum).cloudTradeNum));
	for(i = 0 ; i < 32 ; i ++){
		tradeInfo.tradeNo[i] = getChargerBlockInfo(gunNum).chargingList[i]; 
	}
//	tradeInfo.tradeNo[0] = getChargerBlockInfo(gunNum).localChargeNum & 0xff;
//	tradeInfo.tradeNo[1] = getChargerBlockInfo(gunNum).localChargeNum >> 8 & 0xff;
//	tradeInfo.tradeNo[2] = getChargerBlockInfo(gunNum).localChargeNum >> 16 & 0xff;
//	tradeInfo.tradeNo[3] = getChargerBlockInfo(gunNum).localChargeNum >> 24 & 0xff;
	memcpy(tradeInfo.vinCode,getChargerBlockInfo(gunNum).vehicleVin,strlen(getChargerBlockInfo(gunNum).vehicleVin));
	tradeInfo.timeDivType = CALCULATE_COST;
	tradeInfo.chargeStartTime = encapsulationTimeData(getChargerBlockInfo(gunNum).startChargeTime);
	tradeInfo.chargeEndTime = encapsulationTimeData(getChargerBlockInfo(gunNum).stopChargeTime);
	tradeInfo.startSoc = getChargerBlockInfo(gunNum).firstSoc;
	tradeInfo.endSoc = getChargerBlockInfo(gunNum).currentSoc;
	tradeInfo.reason= getStopCode(gunNum);
	memcpy(tradeInfo.eleModelId,getCostRulesInfo().costRulesVersion,strlen(getCostRulesInfo().costRulesVersion));
	memcpy(tradeInfo.serModelId,getCostRulesInfo().serviceRulesVersion,strlen(getCostRulesInfo().serviceRulesVersion));
	tradeInfo.sumStart = getChargerBlockInfo(gunNum).firstMeterData;
	tradeInfo.sumEnd = getChargerBlockInfo(gunNum).currentMeterData;
	tradeInfo.totalElect = getChargerBlockInfo(gunNum).chargingPower;
	tradeInfo.sharpElect = getUserAccountInfo(gunNum).fourSectionInfo[JIAN_SECTION].chargePower;
	tradeInfo.peakElect = getUserAccountInfo(gunNum).fourSectionInfo[FENG_SECTION].chargePower;
	tradeInfo.flatElect = getUserAccountInfo(gunNum).fourSectionInfo[PING_SECTION].chargePower;
	tradeInfo.valleyElect = getUserAccountInfo(gunNum).fourSectionInfo[GU_SECTION].chargePower;
	tradeInfo.totalPowerCost = getUserAccountInfo(gunNum).costMoney;
	tradeInfo.totalServCost = getUserAccountInfo(gunNum).serviceMoney;
	tradeInfo.sharpPowerCost = getUserAccountInfo(gunNum).fourSectionInfo[JIAN_SECTION].chargeCost;
	tradeInfo.peakPowerCost = getUserAccountInfo(gunNum).fourSectionInfo[FENG_SECTION].chargeCost;
	tradeInfo.flatPowerCost = getUserAccountInfo(gunNum).fourSectionInfo[PING_SECTION].chargeCost;
	tradeInfo.valleyPowerCost = getUserAccountInfo(gunNum).fourSectionInfo[GU_SECTION].chargeCost;
	tradeInfo.sharpServCost = getUserAccountInfo(gunNum).fourSectionInfo[JIAN_SECTION].serviceCost;
	tradeInfo.peakServCost = getUserAccountInfo(gunNum).fourSectionInfo[FENG_SECTION].serviceCost;
	tradeInfo.flatServCost = getUserAccountInfo(gunNum).fourSectionInfo[PING_SECTION].serviceCost;
	tradeInfo.valleyServCost = getUserAccountInfo(gunNum).fourSectionInfo[GU_SECTION].serviceCost;	
	
	if(getChargerBlockInfo(gunNum).isStartCharge != WORK_STATE){
		if(isConnectNet){
			evs_send_event(EVS_CMD_EVENT_TRADEINFO,&tradeInfo);
			addSupplyHistory(&tradeInfo,sizeof(evs_event_tradeInfo));
		}
	}
	
		
	return;
}

void assignedTotalFaultEvt(int gunNum){
	int i = 0;
	int errCode = 0;
	evs_event_alarm alarmInfo;
	memset(&alarmInfo,0,sizeof(alarmInfo));
	errCode = getErrorCode(gunNum,true);
	alarmInfo.gunNo = gunNum;
	if(errCode)
		alarmInfo.faultSum = 1;
	else
		alarmInfo.faultSum = 0;
	alarmInfo.warnSum = 0;
	if(alarmInfo.faultSum != 0){
		for(i = 0 ; i < alarmInfo.faultSum ; i ++)
			alarmInfo.faultValue[i] =  errCode;
	}

//	if(alarmInfo.warnSum != 0){
//		for(i = 0 ; i < alarmInfo.faultSum ; i ++)
//			alarmInfo.warnValue[i] =  0;
//	}

	evs_send_event(EVS_CMD_EVENT_ALARM,&alarmInfo);
	
	return;
}

void assignedDcStChEvt(int gunNum){
	
	evs_event_pile_stutus_change pileStateInfo;
	memset(&pileStateInfo,0,sizeof(pileStateInfo));
	pileStateInfo.gunNo = gunNum;
	memcpy((int *)pileStateInfo.yxOccurTime,getCurrentTime(),strlen(getCurrentTime()));
	if(getChargerBlockInfo(gunNum).gunState == PLUG_IN)
		pileStateInfo.connCheckStatus = GW_PLUG_IN;
	if(getChargerBlockInfo(gunNum).gunState == IDEL)
		pileStateInfo.connCheckStatus = GW_PLUG_OUT;

	evs_send_event(EVS_CMD_EVENT_DCPILE_CHANGE,&pileStateInfo);
	return;
}

void assignedAskConfigEvt(){
	evs_send_event(EVS_CMD_EVENT_ASK_DEV_CONFIG,NULL);
	return;
}

void assignedVerInfoEvt(){
	evs_event_ver_info versionInfo;
	int gwSoftVersion = 0;
	int gwHardVersion = 0;
	memset(&versionInfo,0,sizeof(versionInfo));
	gwSoftVersion = controlConfigInfo() ->softwareVersion;
	gwHardVersion = controlConfigInfo() ->hardwareVersion;
	
	versionInfo.devRegMethod = SCREEN_REGISTE;
	versionInfo.pileSoftwareVer[0] = gwSoftVersion & 0xff;
	versionInfo.pileSoftwareVer[1] = gwSoftVersion >> 8 & 0xff;
	versionInfo.pileSoftwareVer[2] = gwSoftVersion >> 16 & 0xff;
	versionInfo.pileSoftwareVer[3] = gwSoftVersion >> 24 & 0xff;    

	versionInfo.pileHardwareVer[0] = gwHardVersion & 0xff;
	versionInfo.pileHardwareVer[1] = gwHardVersion >> 8 & 0xff;
	versionInfo.pileHardwareVer[2] = gwHardVersion >> 16 & 0xff;
	versionInfo.pileHardwareVer[3] = gwHardVersion >> 24 & 0xff;  

	memcpy(versionInfo.sdkVer,SDK_VERSION,255);
	
	evs_send_event(EVS_CMD_EVENT_VER_INFO,&versionInfo);
	return;
}

void assignedDcDeRealTty(){
	evs_property_dcPile dcPileInfo;
	memset(&dcPileInfo,0,sizeof(dcPileInfo));
	dcPileInfo.netType = NET_WORK_4G;
	dcPileInfo.sigVal = NET_SIGNAL_LEVEL;
	dcPileInfo.netId = MOBILE;
	dcPileInfo.acVolA = getDeviceInfo().APhaseVol;
	dcPileInfo.acCurA = getDeviceInfo().APhaseCurrent;
	dcPileInfo.acVolB = getDeviceInfo().BPhaseVol;
	dcPileInfo.acCurB = getDeviceInfo().BPhaseCurrent;
	dcPileInfo.acVolC = getDeviceInfo().CPhaseVol;
	dcPileInfo.acCurC = getDeviceInfo().CPhaseCurrent;
	dcPileInfo.caseTemp = 0;
	dcPileInfo.inletTemp = 0;
	dcPileInfo.outletTemp = 0;
	memcpy(dcPileInfo.eleModelId,getCostRulesInfo().costRulesVersion,strlen(getCostRulesInfo().costRulesVersion));
	memcpy(dcPileInfo.eleModelId,getCostRulesInfo().serviceRulesVersion,strlen(getCostRulesInfo().serviceRulesVersion));
	evs_send_event(EVS_CMD_PROPERTY_DCPILE,&dcPileInfo);
	return;
}

void assignedDcBmsRunIty(int gunNum){
	evs_property_BMS bmsInfo;
	int i = 0;
	memset(&bmsInfo,0,sizeof(bmsInfo));
	bmsInfo.gunNo = gunNum;
	memcpy(bmsInfo.preTradeNo,getUserAccountInfo(gunNum).cloudTradeNum,strlen(getUserAccountInfo(gunNum).cloudTradeNum));
	for(i = 0 ; i < 32 ; i ++){
		bmsInfo.tradeNo[i] = getChargerBlockInfo(gunNum).chargingList[i]; 
	}
//	bmsInfo.tradeNo[0] = getChargerBlockInfo(gunNum).localChargeNum & 0xff;
//	bmsInfo.tradeNo[1] = getChargerBlockInfo(gunNum).localChargeNum >> 8 & 0xff;
//	bmsInfo.tradeNo[2] = getChargerBlockInfo(gunNum).localChargeNum >> 16 & 0xff;
//	bmsInfo.tradeNo[3] = getChargerBlockInfo(gunNum).localChargeNum >> 24 & 0xff;
	bmsInfo.socVal = getChargerBlockInfo(gunNum).currentSoc;
	bmsInfo.BMSVer = BMS_VERSION_2015;
	bmsInfo.BMSMaxVol = getBatteryBlockInfo(gunNum).maxBatteryVol;
	
	bmsInfo.batType = getBatteryBlockInfo(gunNum).batteryType;      //need to convert values;
	
	bmsInfo.batRatedCap = getBatteryBlockInfo(gunNum).batteryRateCapacity;
	bmsInfo.batRatedTotalVol = getBatteryBlockInfo(gunNum).batteryTotalVol;
	bmsInfo.singlBatMaxAllowVol = getBatteryBlockInfo(gunNum).singleBatteryMaxVol;
	bmsInfo.maxAllowCur = getBatteryBlockInfo(gunNum).maxChargeCurrent;
	bmsInfo.battotalEnergy = getBatteryBlockInfo(gunNum).batteryCapacity;
	bmsInfo.maxVol = getBatteryBlockInfo(gunNum).maxChargeVol;
	bmsInfo.maxTemp = getBatteryBlockInfo(gunNum).batteryMaxChargeTemp;
	bmsInfo.batCurVol = getBatteryBlockInfo(gunNum).batteryCurrentVol;
	
	evs_send_event(EVS_CMD_PROPERTY_BMS,&bmsInfo);

	return;
}

void assignedDcSysMeterIty(int gunNum){
	evs_property_dc_input_meter inputMeterInfo;
	inputMeterInfo.gunNo = gunNum;
	memcpy(inputMeterInfo.acqTime,getCurrentTime(),strlen(getCurrentTime()));
	
	evs_send_event(EVS_CMD_PROPERTY_DC_INPUT_METER,&inputMeterInfo);
	
	return;
}

void assignedDcOutMeterIty(int gunNum){
	evs_property_meter propertyMeterInfo; 
	int i = 0;
	memset(&propertyMeterInfo,0,sizeof(propertyMeterInfo));
	propertyMeterInfo.gunNo = gunNum;
	memcpy(propertyMeterInfo.acqTime,getCurrentTime(),strlen(getCurrentTime()));
	memcpy(propertyMeterInfo.mailAddr," ",strlen(" "));
	memcpy(propertyMeterInfo.meterNo," ",strlen(" "));
	memcpy(propertyMeterInfo.assetId," ",strlen(" "));
	propertyMeterInfo.sumMeter = getChargerBlockInfo(gunNum).currentMeterData;
	for(i = 0 ; i < 32 ; i ++){
		propertyMeterInfo.lastTrade[i] = getChargerBlockInfo(gunNum).chargingList[i]; 
	}
//	propertyMeterInfo.lastTrade[0] = getChargerBlockInfo(gunNum).localChargeNum & 0xff;
//	propertyMeterInfo.lastTrade[1] = getChargerBlockInfo(gunNum).localChargeNum >> 8 & 0xff;
//	propertyMeterInfo.lastTrade[2] = getChargerBlockInfo(gunNum).localChargeNum >> 16 & 0xff;
//	propertyMeterInfo.lastTrade[3] = getChargerBlockInfo(gunNum).localChargeNum >> 24 & 0xff;
	propertyMeterInfo.elec = getChargerBlockInfo(gunNum).chargingPower;

	evs_send_event(EVS_CMD_PROPERTY_DC_OUTMETER,&propertyMeterInfo);
	addGwMeterData(&propertyMeterInfo,sizeof(evs_property_meter));
	return;
}


void assignedDcGunRunIty(int gunNum){
	evs_property_dc_work dcWorkInfo;
	int i = 0;
	memset(&dcWorkInfo,0,sizeof(dcWorkInfo));

	dcWorkInfo.gunNo = gunNum;
	dcWorkInfo.workStatus = GUN_CHARGING;
	dcWorkInfo.gunStatus = GW_PLUG_IN;
	dcWorkInfo.eLockStatus = GW_GET_CLOSE_STATE;
	dcWorkInfo.DCK1Status = GW_GET_CLOSE_STATE;
	dcWorkInfo.DCK2Status = GW_GET_CLOSE_STATE;
	dcWorkInfo.DCPlusFuseStatus = GW_GET_CLOSE_STATE;
	dcWorkInfo.DCMinusFuseStatus = GW_GET_CLOSE_STATE;   
	dcWorkInfo.conTemp1 = GUN_TERMINAL_TEMP;
	dcWorkInfo.conTemp2 = GUN_TERMINAL_TEMP;
	dcWorkInfo.dcVol = getChargerBlockInfo(gunNum).chargingVol;
	dcWorkInfo.dcCur = getChargerBlockInfo(gunNum).chargingCurrent;
	memcpy(dcWorkInfo.preTradeNo,getUserAccountInfo(gunNum).cloudTradeNum,strlen(getUserAccountInfo(gunNum).cloudTradeNum));
	for(i = 0 ; i < 32 ; i ++){
		dcWorkInfo.tradeNo[i] = getChargerBlockInfo(gunNum).chargingList[i]; 
	}
//	dcWorkInfo.tradeNo[0] = getChargerBlockInfo(gunNum).localChargeNum & 0xff;
//	dcWorkInfo.tradeNo[1] = getChargerBlockInfo(gunNum).localChargeNum >> 8 & 0xff;
//	dcWorkInfo.tradeNo[2] = getChargerBlockInfo(gunNum).localChargeNum >> 16 & 0xff;
//	dcWorkInfo.tradeNo[3] = getChargerBlockInfo(gunNum).localChargeNum >> 24 & 0xff;   
	
	dcWorkInfo.chgType = getCloudCtrlFun(gunNum).startType;   // need to add in the can protocol  now this value is none.

	dcWorkInfo.realPower =controlConfigInfo()->maxOutPutPower;    //getMaxOutPutPower();

	dcWorkInfo.chgTime = getChargerBlockInfo(gunNum).chargingTime;
	dcWorkInfo.socVal = getChargerBlockInfo(gunNum).currentSoc;
	dcWorkInfo.needVol = getChargerBlockInfo(gunNum).requireVol;
	dcWorkInfo.needCur = getChargerBlockInfo(gunNum).requireCurrent;
	dcWorkInfo.chargeMode = getChargerBlockInfo(gunNum).chargeMode;
	dcWorkInfo.bmsVol = getChargerBlockInfo(gunNum).chargingVol;
	dcWorkInfo.bmsCur = getChargerBlockInfo(gunNum).chargingCurrent;
	dcWorkInfo.SingleMHV = getBatteryBlockInfo(gunNum).maxBatteryVol;
	dcWorkInfo.remainT = getChargerBlockInfo(gunNum).remaindTime;
	dcWorkInfo.MHTemp = getBatteryBlockInfo(gunNum).maxBatteryTemp;
	dcWorkInfo.MLTemp = getBatteryBlockInfo(gunNum).minBatteryTemp;
	dcWorkInfo.totalElect = getChargerBlockInfo(gunNum).chargingPower;
	dcWorkInfo.sharpElect = getUserAccountInfo(gunNum).fourSectionInfo[JIAN_SECTION].chargePower;
	dcWorkInfo.peakElect = getUserAccountInfo(gunNum).fourSectionInfo[FENG_SECTION].chargePower;
	dcWorkInfo.flatElect = getUserAccountInfo(gunNum).fourSectionInfo[PING_SECTION].chargePower;
	dcWorkInfo.valleyElect = getUserAccountInfo(gunNum).fourSectionInfo[GU_SECTION].chargePower;
	dcWorkInfo.totalCost = getUserAccountInfo(gunNum).costMoney + getUserAccountInfo(gunNum).serviceMoney;
	dcWorkInfo.totalPowerCost = getUserAccountInfo(gunNum).costMoney;
	dcWorkInfo.totalServCost = getUserAccountInfo(gunNum).serviceMoney;

	evs_send_event(EVS_CMD_PROPERTY_DC_WORK,&dcWorkInfo);
	
	return;
}

void assignedDcGunIdleIty(int gunNum){
	evs_property_dc_nonWork nonWorkInfo;
	memset(&nonWorkInfo,0,sizeof(nonWorkInfo));
	nonWorkInfo.gunNo = gunNum;
	if(getChargerBlockInfo(gunNum).gunState == PLUG_IN)
		nonWorkInfo.gunStatus = GW_PLUG_IN;
	if(getChargerBlockInfo(gunNum).gunState == IDEL)
		nonWorkInfo.gunStatus = GW_PLUG_OUT;

	nonWorkInfo.eLockStatus = GW_GET_OPEN_STATE;
	nonWorkInfo.DCK1Status = GW_GET_OPEN_STATE;
	nonWorkInfo.DCK2Status = GW_GET_OPEN_STATE;
	nonWorkInfo.DCPlusFuseStatus = GW_GET_OPEN_STATE;
	nonWorkInfo.DCMinusFuseStatus = GW_GET_OPEN_STATE;
	nonWorkInfo.conTemp1 = GUN_TERMINAL_TEMP;
	nonWorkInfo.conTemp2 = GUN_TERMINAL_TEMP;
	nonWorkInfo.dcVol = 0;
	nonWorkInfo.dcCur = 0;

	evs_send_event(EVS_CMD_PROPERTY_DC_NONWORK,&nonWorkInfo);
	
	return;
}


/** 建连成功事件回调 */
static int evs_connected_event_handler(void)
{
	evs_linkkit_time_sync();
	mSleep(150);
	assignedVerInfoEvt();
	mSleep(150);
	assignedAskFeedModelEvt(0);
	mSleep(150);
	assignedDcDeRealTty();
	mSleep(150);
	assignedAskConfigEvt();
	mSleep(150);
	assignedFirmwareEvt();
	online_flag = 1;
	DEVICE_EXAMPLE_TRACE(" EVS--- Cloud Connected\n");
	return 0;
}


int guoWangInit(){
	int res = 0;
	int i = 0;
	bool isStartCharging[EVS_MAX_PORT_NUM];
	bool isGunPlugIn[EVS_MAX_PORT_NUM];
	bool isGunPlugOut[EVS_MAX_PORT_NUM];
	char charge60s[EVS_MAX_PORT_NUM];
	int faultFlagCode[EVS_MAX_PORT_NUM];
	unsigned int gunCount[EVS_MAX_PORT_NUM];
	unsigned long deviceCnt = 0;
	
       	EVS_RegisterCallback(EVS_CONF_GET_SRV, callback_service_get_config);                //���û�ȡ����
       
         	EVS_RegisterCallback(EVS_CONF_UPDATE_SRV, callback_service_update_config);          //���Þ��·���
       
       	EVS_RegisterCallback(EVS_QUE_DATA_SRV,callback_service_query_log);                  //�豞��֟��ѯ
       
         	EVS_RegisterCallback(EVS_DEV_MAINTAIN_SRV,callback_service_dev_maintain);           //�豞ά������
       
       	EVS_RegisterCallback(EVS_CTRL_LOCK_SRV, callback_service_lockCtrl);                 //���������Ʒ���
       
        	EVS_RegisterCallback(EVS_FEE_MODEL_UPDATA_SRV,callback_service_issue_feeModel);     //�����Ʒ�ģ�͞��·���

	EVS_RegisterCallback(EVS_START_CHARGE_SRV, callback_service_startCharge);           //Ɯ̚Զ����������

	EVS_RegisterCallback(EVS_AUTH_RESULT_SRV, callback_service_authCharge);            //��������Ț���

	EVS_RegisterCallback(EVS_STOP_CHARGE_SRV,callback_service_stopCharge);             //Ɯֹͣ̚���

	EVS_RegisterCallback(EVS_ORDER_CHECK_SRV,callback_service_confirmTrade);           //���׌�ȷ�Ϸ���

	EVS_RegisterCallback(EVS_RSV_CHARGE_SRV,callback_service_rsvCharge);               //ԀԌ������

	EVS_RegisterCallback(EVS_GROUND_LOCK_SRV,callback_service_grounLock_ctrl);          //�������Ʒ���

	EVS_RegisterCallback(EVS_GATE_LOCK_SRV, callback_service_gateLock_ctrl);             //�����������Ʒ���

	EVS_RegisterCallback(EVS_ORDERLY_CHARGE_SRV, callback_service_orderCharge);          //���ʿ���

	EVS_RegisterCallback(EVS_MAINTAIN_RESULT_SRV, callback_service_get_maintain_status); //ά��׎̬��ѯ���

  

  //ϵͳ�ص�
	EVS_RegisterCallback(EVS_STATE_EVERYTHING, evs_sdk_state_dump);                      //sdk׎̬�仯�ص�

	EVS_RegisterCallback(EVS_CONNECT_SUCC, evs_connected_event_handler);                 //���ӻص�

	EVS_RegisterCallback(EVS_DISCONNECTED, evs_disconnected_event_handler);              //�Ͽ����ӻص�

	EVS_RegisterCallback(EVS_REPORT_REPLY, evs_report_reply_event_handler);              //�����ϱ��؞��ص�

	EVS_RegisterCallback(EVS_TRIGGER_EVENT_REPLY, evs_trigger_event_reply_event_handler);//���ϱ��؞��ص�

	EVS_RegisterCallback(EVS_CERT_GET, evs_device_cert_get);                             //ր���ȡ�ص�

	EVS_RegisterCallback(EVS_CERT_SET, evs_device_cert_set);                             //ր�����ûص�

	EVS_RegisterCallback(EVS_DEVICE_REG_CODE_GET, evs_device_reg_code_get);              //ע�����ȡ�ص�

	EVS_RegisterCallback(EVS_DEVICE_UID_GET, evs_device_uid_get);                        //�豞Κһ�����ȡ�ص�

	EVS_RegisterCallback(EVS_TIME_SYNC, callback_service_time_sync);                     //ʱ��ͬ��

	EVS_RegisterCallback(EVS_OTA_UPDATE, callback_service_ota_update); 
	


	res = evs_linkkit_new(0, 0);
	if (res < 0)
	{
		return -1;
	}

	char gunBmsCnt[EVS_MAX_PORT_NUM];

	while (1)
	{
		evs_mainloop();

		for(i = 0 ; i < EVS_MAX_PORT_NUM ; i ++){
			faultFlagCode[i] = isSameFault[i];
			if(getChargerBlockInfo(i).isStartCharge == WORK_STATE){
				if(!isStartCharging[i]){
					assignedStartChaResEvt(i);
					isStartCharging[i] = true;
					charge60s[i] = 0;
				}
				if(charge60s[i] <= 600){
					charge60s[i] ++;
					if(charge60s[i] % 50 == 0)
						assignedDcGunRunIty(i);
				}
				
				if(gunCount[i] % 300){
					if(charge60s[i]  > 600)
						assignedDcGunRunIty(i);
					if(gunBmsCnt[i] <= 6){
						assignedDcBmsRunIty(i);
						gunBmsCnt[i] ++;
					}
				}
				
				
			}else{
				if(isStartCharging[i]){
					assignedStopChaResEvt(i);
					assignedOrderUpdateEvt(i);
			//		assignedOrderUpdateEvt(i);
					isStartCharging[i] = false;
				}
				
				if(gunCount[i] % 1800 && getChargerBlockInfo(i).gunState != FAULT)
					assignedDcGunIdleIty(i);
			}

			if(getChargerBlockInfo(i).gunState == PLUG_IN && !isGunPlugIn[i]){
				assignedDcStChEvt(i);
				isGunPlugIn[i] = true;
				isGunPlugOut[i] = false; 
			}

			if(getChargerBlockInfo(i).gunState == IDEL && !isGunPlugOut[i]){
				assignedDcStChEvt(i);
				isGunPlugOut[i] = true;
				isGunPlugIn[i] = false; 
			}

			if(getChargerBlockInfo(i).gunState == FAULT && faultFlagCode[i] != getErrorCode(i,false)){
				assignedTotalFaultEvt(i);
			}

			if( faultFlagCode[i] != 0 &&  getErrorCode(i,false) == 0){
				assignedTotalFaultEvt(i);
			}

			if(gunCount[i] % 3600)
				assignedDcOutMeterIty(i);

			if(getChargerBlockInfo(i).gunState == HANDSHAKE && getCloudCtrlFun(i).startType == PLUG_AND_CHARGE_FAST)
				assignedStartChargeAuthEvt(i);

		

			
	//		if(getChargerBlockInfo(i).gunState == FAULT && getChargerBlockInfo(i).isStartCharge == WORK )    will up load the fault messagr immediately

		}

		if(deviceCnt % 6000)
				assignedDcDeRealTty();

		if(deviceCnt % 288000 && getDeviceInfo().deviceState == DEVICE_IDEL)
			evs_linkkit_time_sync();

		for(i = 0 ; i < EVS_MAX_PORT_NUM ; i ++){
			gunCount[i]++;
			if(gunCount[i] >= 10801)
				gunCount[i] = 0;
		}
		deviceCnt ++;
		if(deviceCnt > 288000)
			deviceCnt = 0;
		
		HAL_SleepMs(100);
	}

	return 0;
}
