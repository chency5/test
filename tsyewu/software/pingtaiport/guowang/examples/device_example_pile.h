#ifndef __DEVICE_EXAMPLE_PILE_H__
#define __DEVICE_EXAMPLE_PILE_H__


#define GW_METER_DATA           "/opt/gw/meter"
#define GW_ERROR_CODE          "/opt/gw/error_code"
#define GW_BMS_DATA                "/opt/gw/bms_data"
#define GW_LOG_DATA                "/opt/gw/log_data"
#define GW_CONFIG_DATA         "/opt/gw/config_data"


void addGwMeterData(void *materBuf,int dataLen);

void addGwErrorCode(void *errorCode,int dataLen);

void addGwBmsData(void *bmsInfo,int dataLen);

void addGwLogData(void *logInfo,int dataLen);

int addGwConfigData(void *configInfo,int dataLen);


#endif