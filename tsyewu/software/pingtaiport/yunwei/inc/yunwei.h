#ifndef _YUN_WEI_H__
#define _YUN_WEI_H__

#define   YEWU_UPGRADE_ADDR                "/opt/firmware/xxx.txt"
#define   POWER_UPGRADE_ADDR             "/opt/firmware/xxx.txt"
#define   TERMINAL_UPGRADE_ADDR       "/opt/firmware/xxx.txt"


#define YUNWEI_BUF_LEN            900 



#define YEWU_BIN                       6
#define POWER_BIN                    7
#define TERMINAL_BIN              8


#define YUNWEI_HEAD_H             0x54
#define YUNWEI_HEAD_L              0x53
#define YUNWEI_TAIL_ID               0x68

#define DEVICE_ID                           0x0001
#define FINISH_BYTE                      0x68
#define MESSAGE_HEAD_LEN       12

#define SEND_SIGN_ID                       0x01
#define RECV_SIGN_ID                       0x81

#define SEND_HEART_BEAT_ID                   0x02
#define RECV_HEART_BEAT_ID                   0x82

#define SEND_CHARGE_DATA_ID               0x0d
#define RECV_CHARGE_DATA_ID               0x8d

#define SEND_HISTORY_DATA_ID              0x0e
#define RECV_HISTORY_DATA_ID              0x8e

#define SEND_CHARGE_COUNT_ID            0x0f
#define RECV_CHARGE_COUNT_ID            0x8f

#define SEND_ACTIVE_DATA_ID                0x13
#define RECV_ACTIVE_DATA_ID                0x93

#define SEND_MODULE_STATE_ID            0x16
#define RECV_MODULE_STATE_ID            0x96

#define SEND_RELAY_WORK_STATE_ID               0x17
#define RECV_RELAY_WORK_STATE_ID               0x97


#define SEND_RELAY_STATE_ID               0x18
#define RECV_RELAY_STATE_ID               0x98

#define SEND_FIRMWARE_INFO_ID            0x19
#define RECV_FIRMWARE_INFO_ID            0x99

#define RECV_UPGRADE_ID                               0x11
#define SEND_CONFIRM_UPGRADE_ID          0x91

#define SEND_UPGRADE_RESULT_ID            0x12
#define RECV_UPGRADE_RESULT_ID            0x92

#define RECV_CLOULD_WRITE_ID                   0x04
#define SEND_CLOULD_WRITE_ID                   0x84

#define SEND_LOG_FILE_INFO                     0x14
#define RECV_LOG_FILE_INFO                     0x94

#define RECV_UP_LOG_FILE_RESULT           0x15
#define SEND_UP_LOG_FILR_CONFIRM        0x95

#define RECV_CLOUD_READ_ID                  0x1a
#define SEND_CLOUD_READ_ID                  0x9a



typedef struct{
	char upgradeType;
	char upgradeResult;
	char ftpCurl[130];
	char userName[25];
	char ftpIp[20];
	char password[25];
	char md5[35];
	char softwareVersion[25];
	short hostPort;
	int port;
}ungrade_info;


#define CLOUD_TYPE             0x01
#define DEVICE_SERIAL_NUM             0x02
#define CLOUD_IP              0x03
#define CLOUD_PORT            0x04
#define LOG_FLAG                  0x05
#define DEVICE_CONTROL  0x06

#define LOCAL_LOG              1
#define GUN_LOG           2

#define LOCAL_LOG_NAME         "loggle"
#define GUN_LOG_NAME              "bmsloggle"


#define GUN_LOG_FILE  "/opt/.record/bmsloggle" 


typedef struct{	
	char logFlag;
	char deviceSerialNum[25];
	char cloudIp[35];
	short cloudType;
	short cloudPort;
}clould_write_info;



typedef struct{
	char hostBuf[200];
	char postBuf[200];
	char urlAddr[200];
	char clientId[50];
	char usrUniqueFlag[50];
	char certData[50];
	char httpIp[30];
	int httpPort;
}http_connect_info;

#if 0
#define HTTP_HEAD "POST %s HTTP/1.1\r\n"\
					"Host: %s\r\n"\
					"User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux i686; rv:59.0) Gecko/20100101 Firefox/59.0\r\n"\
					"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"\
					"Accept-Language: en-US,en;q=0.5\r\n"\
					"Accept-Encoding: gzip, deflate\r\n"\
					"Content-Type: multipart/form-data; boundary=%s\r\n"\
					"Content-Length: %ld\r\n"\
					"Connection: close\r\n"\
					"Upgrade-Insecure-Requests: 1\r\n"\
					"DNT: 1\r\n\r\n"\

#endif

#define UPLOAD_REQUEST  "--%s\r\n"\
						"Content-Disposition: form-data; name=\"file\"; filename=\"%s\'\r\n"\
						"Content-Type: application/octet-stream\r\n\r\n"




#define HTTP_HEAD "POST %s HTTP/1.1\r\n"\
  					  "accept: */*\r\n"\
  					  "accept-encoding: gzip, deflate, br\r\n"\
					  "accept-language: zh-CN\r\n"\
  					  "user-agent: ApiPOST Runtime +https://www.apipost.cn\r\n"\
  					  "connection: keep-alive\r\n"\
    					  "Host: %s\r\n"\
  					  "Content-Type: multipart/form-data; boundary=%s\r\n"\
 					  "Content-Length: %ld\r\n\r\n"





#define EXAMPLE_HEADER  "POST  %s HTTP/1.1\r\n"\
 						 "accept: */*\r\n"\
  						 "accept-encoding: gzip, deflate, br\r\n"\
						 "accept-language: zh-CN\r\n"\
   						 "user-agent: ApiPOST Runtime +https://www.apipost.cn\r\n"\
  						  "connection: keep-alive\r\n"\
  						  "Host: %s\r\n"\
 						   "Content-Type: multipart/form-data; boundary=--------------------------886907744690010664062520\r\n"\
 						   "Content-Length:  213\r\n\r\n"\
 						   "----------------------------886907744690010664062520\r\n"\
						  "Content-Disposition: form-data; name=\"file\"; filename=\"%s\"\r\n"\
						  "Content-Type: text/plain\r\n\r\n"\
						  "%s\r\n"\
						  "----------------------------886907744690010664062520--\r\n"



void yunWeiSendLogUpLoad(int logType);


void httpConnectInit(http_connect_info httpInfo);

void yunWeiInit();

#endif
