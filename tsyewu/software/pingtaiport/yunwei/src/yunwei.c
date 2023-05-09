#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<errno.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/signal.h>
#include <linux/types.h>
#include <asm/byteorder.h>
#include <linux/ip.h>
#include <netinet/tcp.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include <sys/time.h>


#include "yunwei.h"
#include "datacenter.h"
#include "projdebug.h"
#include "utily.h"
#include "proj_timer.h"
#include "systemconfig.h"
#include "crc.h"
#include "modbus_protocol.h"



#if 1

#define YUN_WEI_PORT          8800

#define MAX_LIST_NUM                    65536

#define LOCAL_VERSION       "v6.2.30"
#define POWER_VERSION      "v7.2.30"
#define GUN_VERSION            "v8.2.30"


#define YUNWEI_ENCRYPTION                    0

static bool isFault = false;
static bool isLogSend = false;

static bool isSendVersion = false;

static unsigned long 		initYunWeiTimerList = 0;
static unsigned long 		initYunWeiTimerId = 0;

static unsigned long 		initFaultMonitorList = 0;
static unsigned long 		initFaultMonitorTimerId = 0;


static char gunChargeBuf[20] = {0};

static int ywFd = 0;

static bool isConnect = false;

static clould_write_info clouldWriteInfo;

static char uplogRunAccount[35] = {0};
//static char saveSourceAccount[35];

//static  char sendBuf[SOCKET_DATA_LEN] = {0};
//static char recvBuf[SOCKET_DATA_LEN] = {0};




static int  listNum = 0;

static int heartBeatNum = 0;

static int isSign = 0;

static int islogUp = 0;


static void connectYunWei(){
	TRACE_PROJ_SOCKET_INFO("################   connectYunWei   #################\n");
	if(ywFd){
		close(ywFd);
		ywFd = 0;
	}
	
	struct sockaddr_in  servaddr;
	 if((ywFd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
	 	TRACE_PROJ_SOCKET_INFO("yunwei creat socket error : %s(errno: %d)\n",strerror(errno),errno);
		return;
	 }

	 memset(&servaddr, 0, sizeof(servaddr));
          servaddr.sin_family = AF_INET;
         servaddr.sin_port = htons(2884);

	if(inet_pton(AF_INET, "192.168.8.136", &servaddr.sin_addr) <= 0){                                                        /* 120.24.38.57 controlConfigInfo()->yunWeiIp tan gong test  192.168.8.136*/ 
		TRACE_PROJ_SOCKET_INFO("yunwei inet_pton error for\n");
		isConnect = false;
	    	return;
           }

	if(connect(ywFd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
		TRACE_PROJ_SOCKET_INFO("yunwei connect error: %s(errno: %d)\n",strerror(errno),errno);
		isConnect = false;
		return;
	}
	isConnect = true;
	return;
} 

static void  yunWeiJudgeConnected() {
	if (ywFd < 0)
		return ;
	
	struct tcp_info info;
	int len = sizeof(info);
	getsockopt(ywFd,IPPROTO_TCP,TCP_INFO,&info,(socklen_t *)&len);
	if (info.tcpi_state == TCP_ESTABLISHED){
		isConnect = true;
		return ;
	}else{
	         TRACE_PROJ_SOCKET_INFO("socket disconnected \n");
		//printLogToFile("socket disconnected");
		isConnect = false;
		return ;
         }
	return ;
}

static bool yunWeiSend(char *sendBuf,int bufLen){
//	printf("this is yunWeiSend \n");
	if(!isConnect || !sendBuf)
		return false;
//	int i = 0;
//	for(i = 0 ; i < bufLen ; i ++){
//		printf("_0x%x",sendBuf[i]);
//	}
//	printf("\n");
	int ret = 0;
	ret = send(ywFd,sendBuf,bufLen,0);
	if(ret == -1){
		printf("@@@    send error!  @@@@\n");
		isConnect = false;
		listNum = 0;
		return false;
	}
	listNum ++;
	if(listNum >= MAX_LIST_NUM)
		listNum = 0;
	return true;
}

static int getMd5Num(char *addrBuf,char *md5Buf){
	
	char cmdBuf[100] = {0};
	char readBuf[200] = {0};
	int ret = 0;

	sprintf(cmdBuf,"md5sum %s",addrBuf);
	ret = mySystem(cmdBuf,readBuf,200);
	if(ret)
		TRACE_PROJ_SOCKET_INFO("get md5 error");
	strcpy(md5Buf,strtok(readBuf," "));
	
	return 0;
}

void getRunAccount(){
//	int i = 0;
	char *p = NULL;
	p = getCurrentTime();
//	printf("getCurrentTime() = %s\n",p);
	memset(uplogRunAccount,0,sizeof(uplogRunAccount));
	strcpy(uplogRunAccount,p);
	return;
}

static int getInternalStopReason(int sourceData){
	int convertId = 0;
	switch(sourceData){
		case 0x00: convertId = 0x1000; break;
		case 0x01: convertId = 0x1001; break;
		case 0x09: convertId = 0x1002; break;
		case 0x05: convertId = 0x1003; break;
		case 0x02: convertId = 0x1005; break;
		case 0x03: convertId = 0x1006; break;
		case 0x04: convertId = 0x1007; break;
		case 0x3f:  convertId = 0x100b; break;
		case 0x0d: convertId = 0x100d; break;
		default:
			convertId = 0x100a; break;
	}	
	
	return convertId;
}

static int getInternalAlarmData(int sourceData){
	int convertId = 0;
	switch(sourceData){
		case 0x01: convertId = 0x3003; break;
		case 0x04: convertId = 0x3013; break;
		case 0x05: convertId = 0x3015; break;
		case 0x10: convertId = 0x3014; break;
		case 0x0b: convertId = 0x4002; break;
		case 0x0c: convertId = 0x4001; break;
		case 0x15: convertId = 0x300d; break;
		case 0x0d: convertId = 0x301b; break;
		case 0x39: convertId = 0x5000; break;
		case 0x20: convertId = 0x5001; break;
		case 0x21: convertId = 0x5002; break;
		case 0x26: convertId = 0x5005; break;
		case 0x27: convertId = 0x5006; break;
		case 0x3a: convertId = 0x5009; break;
		case 0x3d:
		case 0x3e: convertId = 0x500c; break;
		case 0x45: convertId = 0x5032; break;
		case 0x46: convertId = 0x5033; break;
		case 0x47: convertId = 0x5035; break;
		case 0x44: convertId = 0x5034; break;
		case 0x4b: convertId = 0x5039; break;
		case 0x4c: convertId = 0x503a; break;
		default: break;
	}
	return convertId;
}

#if 0
static int getAuthenticationData(int sourceData){
	int convertId = 0;
	switch(sourceData){
		case 0x04: convertId = 0x2000; break;
		case 0x12: convertId = 0x2001; break;
		case 0x05: convertId = 0x2002; break;
		case 0x13: convertId = 0x2003; break;
		case 0x09: convertId = 0x200b; break;
		default: break;
	}
	return convertId;
}
#endif

static void convertTimeToBcd(char *timeSrc,char *dest){
	char buf[3] = {0};
	int i = 0;
	int len = 0;
	len = sizeof(dest);
	memset(dest,0,len);
	for(i = 0 ; i < 7 ; i ++){
		buf[0] = timeSrc[i *2];
		buf[1] = timeSrc[i *2 +1];
		dest[i] = decToBcd(atoi(buf));
		memset(buf,0,3);
	}
	return;
}

static bool frameSendData(int gunNum,char cmd,char *dataBuf,int bufLen){
//	TRACE_PROJ_SOCKET_INFO(" yunwei   frameSendData \n");
	
	int i = 0;
	int k = 0;
	int totalLen = 0;
//	int dataLen = 0;
	unsigned short crc = 0;
	bool isSuccess = false;
	char sendBuf[YUNWEI_BUF_LEN] = {0};
//	dataLen =  strlen(dataBuf);
	totalLen =  bufLen + MESSAGE_HEAD_LEN;

	printf("  frameSendData   totalLen = %d   bufLen = %d\n",totalLen,bufLen);
	
	sendBuf[i ++] = YUNWEI_HEAD_H;
	sendBuf[i ++] = YUNWEI_HEAD_L;
	
	sendBuf[i ++]  = totalLen >> 8 & 0xff;
	sendBuf[i ++]  = totalLen & 0xff;
	
	sendBuf[i ++] = listNum >> 8 & 0xff;
	sendBuf[i ++] = listNum & 0xff;
	
	sendBuf[i ++] = YUNWEI_ENCRYPTION;
	
	sendBuf[i ++] = cmd;

//	sendBuf[i ++] = 0;
//	sendBuf[i ++] = DEVICE_ID_NUM;

	sendBuf[i ++] = (char)gunNum;

	for(k = 0 ; k < bufLen ; k ++){
		sendBuf[i ++] = dataBuf[k];
	}

	crc = CRC16((unsigned char*)sendBuf,(totalLen - 3));
	sendBuf[i ++]  = crc >> 8 & 0xff;
	sendBuf[i ++]   = crc & 0xff;
	
	sendBuf[i ++]  = YUNWEI_TAIL_ID;
	
	
	
	isSuccess = yunWeiSend(sendBuf,totalLen);
	
	memset(sendBuf,0,sizeof(sendBuf));
	
	return isSuccess;
}


static void signInYunWei(){
	TRACE_PROJ_SOCKET_INFO("signInYunWei\n");
	char buf[100] = {0};
//	char *p = NULL;
	int i = 0;
	int k = 0;
	int version = 103;
	char testSerialNum[] = "yfd20200403149";
//	p = buf;
	buf[i ++] = controlConfigInfo()->gunTotalNum;
	for(k = 0 ; k < 20 ; k ++){
		buf[i ++] = 0;
	}
	buf[i ++] = version >> 8 & 0xff;                                                 /*controlConfigInfo()->protocolVersion >> 8 & 0xff;   */
	buf[i ++] = version & 0xff;                                                                  /*controlConfigInfo()->protocolVersion & 0xff;*/
	buf[i ++] = controlConfigInfo()->deviceType;
	

	for(k = 0; k < 14 ; k ++){
//		buf[i ++] = controlConfigInfo()->serialNum[k];
		buf[i ++] = testSerialNum[k];
	}
	for(k = 0 ; k < 18 ; k ++){
		buf[i ++] = 0;
	}

	for(k = 0; k < 20 ; k ++){
		buf[i ++] = controlConfigInfo()->propertyCode[k];
	}
	
//	printf("@@@@@@@@@@@@@@@    buf size = %d \n",strlen(buf));
	frameSendData(0,SEND_SIGN_ID,buf,i);
//	p  = NULL;
	return;
}

static void yunWeiheartBeat(){
//	TRACE_PROJ_SOCKET_INFO("yunWeiheartBeat\n");
	char buf[5] = {0};
	buf[0] = heartBeatNum >> 8 & 0xff;
	buf[1] = heartBeatNum & 0xff;
	buf[2] = 0;
	
	heartBeatNum ++;
	if(heartBeatNum > 50000)
		heartBeatNum = 0;

	frameSendData(0,SEND_HEART_BEAT_ID,buf,3);
	return;
}


static void yunWeiChargeData(int gunNum){
	printf("#####   yunWeiChargeData #####\n");
	char buf[300] = {0};
	int i = 0;
//	int k = 0;
	buf[i ++] = 19;
	
	buf[i ++] = 0x10;
	buf[i ++] = 0x04;
	buf[i ++] = 4;

	buf[i ++] = getChargerBlockInfo(gunNum).chargingVol >> 24 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingVol >> 16 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingVol >> 8 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingVol & 0xff;
#if 1
	buf[i ++] = 0x10;
	buf[i ++] = 0x05;
	buf[i ++] = 4;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingCurrent >> 24 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingCurrent >> 16 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingCurrent >> 8 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingCurrent & 0xff;
	buf[i ++] = 0x10;
	buf[i ++] = 0x06;
	buf[i ++] = 4;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingTime >> 24 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingTime >> 16 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingTime >> 8 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingTime & 0xff;
	buf[i ++] = 0x10;
	buf[i ++] = 0x07;
	buf[i ++] = 4;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingPower>> 24 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingPower >> 16 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingPower >> 8 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingPower & 0xff;
	buf[i ++] = 0x10;
	buf[i ++] = 0x08;
	buf[i ++] = 4;
	buf[i ++] = getUserAccountInfo(gunNum).costMoney>> 24 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).costMoney >> 16 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).costMoney >> 8 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).costMoney & 0xff;
	buf[i ++] = 0x10;
	buf[i ++] = 0x09;
	buf[i ++] = 4;
	buf[i ++] = getUserAccountInfo(gunNum).serviceMoney>> 24 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).serviceMoney >> 16 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).serviceMoney >> 8 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).serviceMoney & 0xff;
	buf[i ++] = 0x10;
	buf[i ++] = 0x0a;
	buf[i ++] = 4;
	buf[i ++] = getChargerBlockInfo(gunNum).remaindTime>> 24 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).remaindTime >> 16 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).remaindTime >> 8 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).remaindTime & 0xff;
	buf[i ++] = 0x10;
	buf[i ++] = 0x0b;
	buf[i ++] = 8;
	buf[i ++] = getChargerBlockInfo(gunNum).currentMeterData>> 24 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).currentMeterData >> 16 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).currentMeterData >> 8 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).currentMeterData & 0xff;
	buf[i ++] = 0;
	buf[i ++] = 0;
	buf[i ++] = 0;
	buf[i ++] = 0;
	buf[i ++] = 0x10;
	buf[i ++] = 0x0c;
	buf[i ++] = 1;
	buf[i ++] = getChargerBlockInfo(gunNum).currentSoc;
	buf[i ++] = 0x10;
	buf[i ++] = 0x0d;
	buf[i ++] = 4;
	buf[i ++] = getChargerBlockInfo(gunNum).requireVol>> 24 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).requireVol >> 16 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).requireVol >> 8 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).requireVol & 0xff;
	buf[i ++] = 0x10;
	buf[i ++] = 0x0e;
	buf[i ++] = 4;
	buf[i ++] = getChargerBlockInfo(gunNum).requireCurrent>> 24 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).requireCurrent >> 16 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).requireCurrent >> 8 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).requireCurrent & 0xff;
	buf[i ++] = 0x10;
	buf[i ++] = 0x0f;
	buf[i ++] = 4;
	buf[i ++] = getDeviceInfo().APhaseVol>> 24 & 0xff;
	buf[i ++] = getDeviceInfo().APhaseVol >> 16 & 0xff;
	buf[i ++] = getDeviceInfo().APhaseVol >> 8 & 0xff;
	buf[i ++] = getDeviceInfo().APhaseVol & 0xff;
	buf[i ++] = 0x10;
	buf[i ++] = 0x10;
	buf[i ++] = 4;
	buf[i ++] = getDeviceInfo().BPhaseVol>> 24 & 0xff;
	buf[i ++] = getDeviceInfo().BPhaseVol >> 16 & 0xff;
	buf[i ++] = getDeviceInfo().BPhaseVol >> 8 & 0xff;
	buf[i ++] = getDeviceInfo().BPhaseVol & 0xff;
	buf[i ++] = 0x10;
	buf[i ++] = 0x11;
	buf[i ++] = 4;
	buf[i ++] = getDeviceInfo().CPhaseVol>> 24 & 0xff;
	buf[i ++] = getDeviceInfo().CPhaseVol >> 16 & 0xff;
	buf[i ++] = getDeviceInfo().CPhaseVol >> 8 & 0xff;
	buf[i ++] = getDeviceInfo().CPhaseVol & 0xff;
	buf[i ++] = 0x10;
	buf[i ++] = 0x12;
	buf[i ++] = 4;
	buf[i ++] = getDeviceInfo().APhaseCurrent>> 24 & 0xff;
	buf[i ++] = getDeviceInfo().APhaseCurrent >> 16 & 0xff;
	buf[i ++] = getDeviceInfo().APhaseCurrent >> 8 & 0xff;
	buf[i ++] = getDeviceInfo().APhaseCurrent & 0xff;
	buf[i ++] = 0x10;
	buf[i ++] = 0x13;
	buf[i ++] = 4;
	buf[i ++] = getDeviceInfo().BPhaseCurrent>> 24 & 0xff;
	buf[i ++] = getDeviceInfo().BPhaseCurrent >> 16 & 0xff;
	buf[i ++] = getDeviceInfo().BPhaseCurrent >> 8 & 0xff;
	buf[i ++] = getDeviceInfo().BPhaseCurrent & 0xff;
	buf[i ++] = 0x10;
	buf[i ++] = 0x14;
	buf[i ++] = 4;
	buf[i ++] = getDeviceInfo().CPhaseCurrent>> 24 & 0xff;
	buf[i ++] = getDeviceInfo().CPhaseCurrent >> 16 & 0xff;
	buf[i ++] = getDeviceInfo().CPhaseCurrent >> 8 & 0xff;
	buf[i ++] = getDeviceInfo().CPhaseCurrent & 0xff;
	buf[i ++] = 0x10;
	buf[i ++] = 0x17;
	buf[i ++] = 2;
	buf[i ++] = getChargerBlockInfo(gunNum).posTemp >> 8 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).posTemp & 0xff;
	buf[i ++] = 0x10;
	buf[i ++] = 0x18;
	buf[i ++] = 2;
	buf[i ++] = getChargerBlockInfo(gunNum).negTemp >> 8 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).negTemp & 0xff;
//	buf[i ++] = 0x10;
//	buf[i ++] = 0x1b;
//	for(k = 0 ; k < 32 ; k ++){
//		buf[i ++] = getChargerBlockInfo(gunNum).chargingList[k];
//	}
#endif
	frameSendData((gunNum + 1),SEND_CHARGE_DATA_ID,buf,i);
	memset(buf,0,300);
	return;
}


static void yunWeiHistoryData(int gunNum){
	char buf[450] = {0};
	int i = 0;
	int k = 0;
	char bcdBuf[10] = {0};
	short stopReason = 0;
	buf[i ++] = getCloudCtrlFun(gunNum).startType;
	buf[i ++] = 0;
	buf[i ++] = 5;
	for(k = 0 ; k < 20 ; k ++){
		buf[i ++] = getUserAccountInfo(gunNum).accountNum[k];
	}
	
	for(k = 0; k < 17 ; k ++){
		buf[i ++] = getChargerBlockInfo(gunNum).vehicleVin[k];
	}

	buf[i ++] = getUserAccountInfo(gunNum).accountMoney >> 24 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).accountMoney >> 16 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).accountMoney >> 8 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).accountMoney & 0xff;

	for(k = 0 ; k < 8 ; k ++){
		buf[i ++] = 0;                                   //max vol & current
	}

	buf[i ++] = getChargerBlockInfo(gunNum).chargingTime >> 24 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingTime >> 16 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingTime >> 8 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingTime & 0xff;

	buf[i ++]  = getUserAccountInfo(gunNum).costMoney >> 24 & 0xff;
	buf[i ++]  = getUserAccountInfo(gunNum).costMoney >> 16 & 0xff;
	buf[i ++]  = getUserAccountInfo(gunNum).costMoney >> 8 & 0xff;
	buf[i ++]  = getUserAccountInfo(gunNum).costMoney & 0xff;

	buf[i ++] = getChargerBlockInfo(gunNum).chargingPower >> 24 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingPower >> 16 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingPower >> 8 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingPower & 0xff;

	buf[i ++] = getChargerBlockInfo(gunNum).firstMeterData >> 24 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).firstMeterData >> 16 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).firstMeterData >> 8 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).firstMeterData & 0xff;
	for(k = 0 ; k < 4 ; k ++){
		buf[i ++] = 0;                                  
	}

	buf[i ++] = getChargerBlockInfo(gunNum).currentMeterData >> 24 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).currentMeterData >> 16 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).currentMeterData >> 8 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).currentMeterData & 0xff;
	for(k = 0 ; k < 4 ; k ++){
		buf[i ++] = 0;                                   
	}

	buf[i ++] = getChargerBlockInfo(gunNum).firstSoc;
	buf[i ++] = getChargerBlockInfo(gunNum).currentSoc;

	buf[i ++] = 1;
	
	stopReason = getInternalStopReason(getChargerBlockInfo(gunNum).chargeStopReason);
	buf[i ++] = stopReason >> 8 & 0xff;
	buf[i ++] = stopReason & 0xff;

//	buf[i ++] = 1;

	for(k = 0 ; k < 14 ; k ++)
		buf[i ++] = 0;
	
	convertTimeToBcd(getChargerBlockInfo(gunNum).startChargeTime,bcdBuf);
	for(k = 0 ; k < 7 ; k ++){
		buf[i ++] = bcdBuf[k];
	}

	convertTimeToBcd(getChargerBlockInfo(gunNum).stopChargeTime,bcdBuf);
	for(k = 0 ; k < 7 ; k ++){
		buf[i ++] = bcdBuf[k];
	}

	for(k = 0 ; k < 6 ; k ++)
		buf[i ++] = 0;

	for(k = 0 ; k < 32 ; k ++){
		buf[i ++] = 0;
	}
	

	for(k = 0 ; k < 32 ; k ++){
		buf[i ++] = getChargerBlockInfo(gunNum).chargingList[k];
	}
	
	buf[i ++]  = getUserAccountInfo(gunNum).serviceMoney >> 24 & 0xff;
	buf[i ++]  = getUserAccountInfo(gunNum).serviceMoney >> 16 & 0xff;
	buf[i ++]  = getUserAccountInfo(gunNum).serviceMoney >> 8 & 0xff;
	buf[i ++]  = getUserAccountInfo(gunNum).serviceMoney & 0xff;

	for(k = 0 ; k < 14 ; k ++){
		buf[i ++] = 0;                                  //total fee and fee version
	}

	for(k = 0 ; k < 192 ; k ++){
		buf[i ++] = 0;      
	}
	
	frameSendData((gunNum + 1),SEND_HISTORY_DATA_ID,buf,i);
	return;
}

#if 0
static void chargeCountMode(int gunNum){
	char buf[500];
	int i = 0;
	int k = 0;
	for(k = 0 ; k < 32 ; k ++){
		buf[i ++] =  getChargerBlockInfo(gunNum).chargingList[k];
	}
	for(k = 0 ; k < 7 ; k ++){
		buf[i ++] = getChargerBlockInfo(gunNum).startChargeTime[k];
	}
	for(k = 0 ; k < 25 ; k ++)
		buf[i ++] = 0;
	
	for(k = 0 ; k < 48 ; k ++){
		buf[i ++] = getCostRulesInfo().costPrice[k] >> 24 & 0xff;
		buf[i ++] = getCostRulesInfo().costPrice[k] >> 16 & 0xff;
		buf[i ++] = getCostRulesInfo().costPrice[k] >> 8 & 0xff;
		buf[i ++] = getCostRulesInfo().costPrice[k] & 0xff;

		buf[i ++] = getCostRulesInfo().servicePrice[k] >> 24 & 0xff;
		buf[i ++] = getCostRulesInfo().servicePrice[k] >> 16 & 0xff;
		buf[i ++] = getCostRulesInfo().servicePrice[k] >> 8 & 0xff;
		buf[i ++] = getCostRulesInfo().servicePrice[k] & 0xff;
	}
	
	frameSendData(gunNum,SEND_CHARGE_COUNT_ID,buf,i);
	return;
}
#endif

static void yunWeiActiveData(int gunNum){
	char buf[200] = {0};
	int alarmData = 0;
	int i  = 0;
	buf[i ++] = 0;
	if(getChargerBlockInfo(gunNum).gunState == FAULT)
		buf[i ++] = 3;
	else
		buf[i ++] = 2;
		
	buf[i ++] = 0x10;
	buf[i ++] = 0x00;
	buf[i ++] = 1;
	if(getChargerBlockInfo(gunNum).gunState == IDEL ||getChargerBlockInfo(gunNum).gunState == PLUG_IN ||
		getChargerBlockInfo(gunNum).gunState == HANDSHAKE ||getChargerBlockInfo(gunNum).gunState == CHARGING)
		buf[i ++] = getChargerBlockInfo(gunNum).gunState;

	if(getChargerBlockInfo(gunNum).gunState == FINISH_PLUG_IN)
		buf[i ++] = 1;

	if(getChargerBlockInfo(gunNum).gunState == FAULT)
		buf[i ++] = 9;

	buf[i ++] = 0x10;
	buf[i ++] = 0x03;
	buf[i ++] = 1;
	if(getChargerBlockInfo(gunNum).gunState == FAULT)
		buf[i ++] = 0;
	else
		buf[i ++] = 1;

	if(getChargerBlockInfo(gunNum).gunState == FAULT){
		buf[i ++] = 0x10;
		buf[i ++] = 0x3c;
		buf[i ++] = 2;
		alarmData = getInternalAlarmData(getChargerBlockInfo(gunNum).faultReason);
		buf[i ++] = alarmData >> 8 & 0xff;
		buf[i ++] = alarmData & 0xff;
	}

#if 0
	buf[i ++] = 0x10;
	buf[i ++] = 0x40;
	buf[i ++] = getDeviceInfo().APhaseVol >> 24 & 0xff;
	buf[i ++] = getDeviceInfo().APhaseVol >> 16 & 0xff;
	buf[i ++] = getDeviceInfo().APhaseVol >> 8 & 0xff;
	buf[i ++] = getDeviceInfo().APhaseVol & 0xff;

	buf[i ++] = 0x10;
	buf[i ++] = 0x41;
	buf[i ++] = getDeviceInfo().BPhaseVol >> 24 & 0xff;
	buf[i ++] = getDeviceInfo().BPhaseVol >> 16 & 0xff;
	buf[i ++] = getDeviceInfo().BPhaseVol >> 8 & 0xff;
	buf[i ++] = getDeviceInfo().BPhaseVol & 0xff;

	buf[i ++] = 0x10;
	buf[i ++] = 0x42;
	buf[i ++] = getDeviceInfo().CPhaseVol >> 24 & 0xff;
	buf[i ++] = getDeviceInfo().CPhaseVol >> 16 & 0xff;
	buf[i ++] = getDeviceInfo().CPhaseVol >> 8 & 0xff;
	buf[i ++] = getDeviceInfo().CPhaseVol & 0xff;

	buf[i ++] = 0x10;
	buf[i ++] = 0x43;
	buf[i ++] = getDeviceInfo().APhaseCurrent >> 24 & 0xff;
	buf[i ++] = getDeviceInfo().APhaseCurrent >> 16 & 0xff;
	buf[i ++] = getDeviceInfo().APhaseCurrent >> 8 & 0xff;
	buf[i ++] = getDeviceInfo().APhaseCurrent & 0xff;

	buf[i ++] = 0x10;
	buf[i ++] = 0x44;
	buf[i ++] = getDeviceInfo().BPhaseCurrent >> 24 & 0xff;
	buf[i ++] = getDeviceInfo().BPhaseCurrent >> 16 & 0xff;
	buf[i ++] = getDeviceInfo().BPhaseCurrent >> 8 & 0xff;
	buf[i ++] = getDeviceInfo().BPhaseCurrent & 0xff;

	buf[i ++] = 0x10;
	buf[i ++] = 0x45;
	buf[i ++] = getDeviceInfo().CPhaseCurrent >> 24 & 0xff;
	buf[i ++] = getDeviceInfo().CPhaseCurrent >> 16 & 0xff;
	buf[i ++] = getDeviceInfo().CPhaseCurrent >> 8 & 0xff;
	buf[i ++] = getDeviceInfo().CPhaseCurrent & 0xff;
#endif
	
	frameSendData((gunNum + 1),SEND_ACTIVE_DATA_ID,buf,i);
	return;
}

static void yunWeiModuleState(){
	printf("#########    yunWeiModuleState  ########## \n");
	char buf[650] = {0};
	int i = 0;
	int k = 0;
	bool isSend = false;
	buf[i ++] = SEND_MODULE_STATE_ID;
	buf[i ++] =  48;//getModuleStateInfo().moduleNum;
	buf[i ++] = 1;
	for(k = 0; k <  48; k ++){               /*getModuleStateInfo().moduleNum*/
		buf[i ++] = k + 1;	
		if(k == 9)
			buf[i ++] = 0;
		else
			buf[i ++] = getModuleStateInfo().faultType[k];
		
		buf[i ++] = getModuleWorkInfo(k).outputState & 0xff;
		buf[i ++] = getModuleWorkInfo(k).outputVol >> 8 & 0xff;
		buf[i ++] = getModuleWorkInfo(k).outputVol & 0xff;
		buf[i ++] = getModuleWorkInfo(k).outputCurrent >> 8 & 0xff;
		buf[i ++] = getModuleWorkInfo(k).outputCurrent & 0xff;
		buf[i ++] = getModuleWorkInfo(k).setVol >> 8 & 0xff;
		buf[i ++] = getModuleWorkInfo(k).setVol & 0xff;
		buf[i ++] = getModuleWorkInfo(k).setCurrent >> 8 & 0xff;
		buf[i ++] = getModuleWorkInfo(k).setCurrent & 0xff;
		buf[i ++] = getModuleWorkInfo(k).moduleTemp >> 8 & 0xff;
		buf[i ++] = getModuleWorkInfo(k).moduleTemp & 0xff;
		if(getModuleStateInfo().faultType[k])
			isSend = true;
		printf("@@@@@@@@@@@@@@    i = %d\n",i);
	}
	if(isSend)
		frameSendData(0,SEND_MODULE_STATE_ID,buf,i);
	
	return;
}


static void yunWeiRelayWorkSatae(){
	TRACE_PROJ_SOCKET_INFO(" yunWeiRelayWorkSatae \n");
	char buf[100] = {0};
	int i = 0;
	int k = 0;
	int relayTotalNum = 512;
	char *p = NULL;
	p = getRelayWorkState();
	buf[i ++] = SEND_RELAY_WORK_STATE_ID;
	buf[i ++] = relayTotalNum >> 8 & 0xff;
	buf[i ++] = relayTotalNum & 0xff;
	for(k = 0 ;  k < 64 ; k ++){
		buf[i ++] = p[k];
	}
	frameSendData(0,SEND_RELAY_WORK_STATE_ID,buf,i);
	return;
}

static void yunWeiRelayState(){
	TRACE_PROJ_SOCKET_INFO(" yunWeiRelayState \n");
	char buf[200] = {0};
	int i = 0;
	int k = 0;
	char *p = NULL;
	p = getRelayFaultState();
	
	for(k = 0 ; k < 64 ; k ++){
		if(p[k * 2] == 0 && p[k * 2 + 1] == 0){
			continue;
		}else{
			buf[i ++] = SEND_RELAY_STATE_ID;
			buf[i ++] = k +1;
			buf[i ++] = p[k * 2];
			buf[i ++] = p[k * 2 + 1];

			frameSendData(0,SEND_RELAY_STATE_ID,buf,i);
			i = 0;
			mSleep(300);
			
		}
		mSleep(300);

		yunWeiRelayWorkSatae();
	}
	
	
	return;
}

static void yunWeiFirmwareInfo(){
	TRACE_PROJ_SOCKET_INFO(" yunWeiFirmwareInfo \n");
	char buf[200] = {0};
	int i = 0;
	int k = 0;
//	int version = 0;
	char version[55] = {0};
	buf[i ++] = 3;
	buf[i ++] = 6;
	strcpy(version,LOCAL_VERSION);
	for(k = 0 ;  k < 50 ; k ++){
		buf[i ++] = version[k];
	}
#if 0	
	buf[i ++] = version >> 24 & 0xff;//controlConfigInfo()->softwareVersion >> 24 & 0xff;
	buf[i ++] = version >> 16 & 0xff;//controlConfigInfo()->softwareVersion >> 16 & 0xff;
	buf[i ++] = version >> 8 & 0xff;//controlConfigInfo()->softwareVersion >> 8 & 0xff;
	buf[i ++] = version & 0xff;//controlConfigInfo()->softwareVersion & 0xff;

	for(k = 0 ; k < 46 ; k ++)
		buf[i ++] = 0;
#endif	
	memset(version,0,55);
	strcpy(version,POWER_VERSION);
	buf[i ++] = 7;
	for(k = 0 ; k < 50 ; k ++){
		buf[i ++] = version[k];
	}
#if 0	
	buf[i ++] =  version >> 24 & 0xff;//controlConfigInfo()->powerTermSoftVersion >> 24 & 0xff;
	buf[i ++] =  version >> 16 & 0xff;//controlConfigInfo()->powerTermSoftVersion >> 16 & 0xff;
	buf[i ++] =  version >> 8 & 0xff;//controlConfigInfo()->powerTermSoftVersion >> 8 & 0xff;
	buf[i ++] =  version & 0xff;//controlConfigInfo()->powerTermSoftVersion & 0xff;

	for(k = 0 ; k < 46 ; k ++)
		buf[i ++] = 0;
#endif	

	memset(version,0,55);
	strcpy(version,GUN_VERSION);
	buf[i ++] = 8;
	for(k = 0 ; k < 50 ; k ++){
		buf[i ++] = version[k];
	}
#if 0	
	buf[i ++] =  version >> 24 & 0xff;//controlConfigInfo()->gunTermSoftVersion >> 24 & 0xff;
	buf[i ++] =  version >> 16 & 0xff;//controlConfigInfo()->gunTermSoftVersion >> 16 & 0xff;
	buf[i ++] =  version >> 8 & 0xff;//controlConfigInfo()->gunTermSoftVersion >> 8 & 0xff;
	buf[i ++] =  version & 0xff;//controlConfigInfo()->gunTermSoftVersion & 0xff;

	for(k = 0 ; k < 46 ; k ++)
		buf[i ++] = 0;
#endif	
	frameSendData(0,SEND_FIRMWARE_INFO_ID,buf,i);
	return;
}


#if 0
static void yunWeiConfirmLogUpResult(int result){
	TRACE_PROJ_SOCKET_INFO(" yunWeiConfirmLogUpResult \n");
	char buf[50] = {0};
	int i = 0;
	int k = 0;
	for(k = 0 ; k < 32 ; k ++){
		buf[i ++] = 0;
	}
	buf[i ++] = result;
	frameSendData(0,SEND_UP_LOG_FILR_CONFIRM,buf,i);
	return;
}
#endif

static void yunWeiUpgradeReply(ungrade_info upInfo){
	TRACE_PROJ_SOCKET_INFO(" yunWeiUpgradeReply \n");
	char buf[50] = {0};
	int i = 0;
	int k = 0;
	
	buf[i ++] = 1;
	buf[i ++] = 1;
	buf[i ++] = upInfo.softwareVersion[0];
	buf[i ++] =  upInfo.softwareVersion[1];
	buf[i ++] =  upInfo.softwareVersion[2];
	buf[i ++] =  upInfo.softwareVersion[3];

	for(k = 0 ; k < 16 ; k ++){
		buf[i ++] = 0;
	}
	
	frameSendData(0,SEND_CONFIRM_UPGRADE_ID,buf,i);
	return;
}

static void yunWeiConfirmUpgrade(ungrade_info upInfo){
	TRACE_PROJ_SOCKET_INFO(" yunWeiConfirmUpgrade \n");
	char buf[30] = {0};
	int i = 0;
	int k = 0;
	buf[i ++] = upInfo.upgradeResult;
	buf[i ++] = upInfo.softwareVersion[0];
	buf[i ++] =  upInfo.softwareVersion[1];
	buf[i ++] =  upInfo.softwareVersion[2];
	buf[i ++] =  upInfo.softwareVersion[3];

	for(k = 0 ; k < 16 ; k ++){
		buf[i ++] = 0;
	}

	frameSendData(0,SEND_UPGRADE_RESULT_ID,buf,i);
	return;
}

static void yunWeiUpgrade(ungrade_info upInfo){
	TRACE_PROJ_SOCKET_INFO(" yunWeiUpgrade \n");
	char upBuf[200] = {0};
	char addrBuf[50] = {0};
//	char md5Buf[200] = {0};
	char saveBuf[500] = {0};
	int ret = 0;
	switch(upInfo.upgradeType){
		case YEWU_BIN:{
			strcat(addrBuf,YEWU_UPGRADE_ADDR);
		}break;

		case POWER_BIN:{
			strcat(addrBuf,POWER_UPGRADE_ADDR);
		}break;

		case TERMINAL_BIN:{
			strcat(addrBuf,TERMINAL_UPGRADE_ADDR);
		}break;
	}
	
	sprintf(upBuf,"ftpget -u %s -p %s -P %d %s %s %s",upInfo.userName,upInfo.password,upInfo.port,"192.168.8.136",addrBuf,upInfo.ftpCurl);

	printf("upBuf = %s\n",upBuf);
	
	ret = mySystem(upBuf,saveBuf,500);
	mSleep(30);
	if(0 != ret){
		upInfo.upgradeResult = 2;
		yunWeiConfirmUpgrade(upInfo);
		return;
	}
#if 0
	getMd5Num(addrBuf,md5Buf);
	if(strcmp(md5Buf,upInfo.md5) != 0){
		upInfo.upgradeResult = 3;
		yunWeiConfirmUpgrade(upInfo);
		return;
	}
#endif
	upInfo.upgradeResult = 1;
	yunWeiConfirmUpgrade(upInfo);
	return;
}


static void dealRecvUpgradeInfo(char *dataBuf){
	TRACE_PROJ_SOCKET_INFO(" dealRecvUpgradeInfo \n");
	int i = 0;
	int k = 0;
	char urlBuf[130] = {0};
	char *p = NULL;
	char *p1 = NULL;
	ungrade_info   ungradeInfo;
	char portBuf[5] = {0};
	ungradeInfo.upgradeType = dataBuf[i ++];
	for(k = 0 ; k < 128 ; k ++){
		urlBuf[k] = dataBuf[i ++];
	}   //  ftp://
//	printf("urlBuf = %s\n",urlBuf);
//	printf("\n");
//	p = strstr(urlBuf,"6:");
//	for(k = 0 ; k < 4 ; k ++){
//		portBuf[k] = p[k + 2];
//	}

//	printf("portBuf = %s\n",portBuf);
//	ungradeInfo.port = atoi(portBuf);


	p = strstr(urlBuf,"//");
	for(k = 0 ; k < 20 ; k ++){
		if(p[k + 2] == ':')
			break;
		ungradeInfo.ftpCurl[k] = p[k + 2];
		ungradeInfo.ftpIp[k] = p[k + 2];
	}

	p1 = strstr(p,":");
	for(k = 0 ; k < 6 ; k ++){
		if(p1[k + 1] == '/')
			break;
		portBuf[k] = p1[k + 1];
	}
	ungradeInfo.port = atoi(portBuf);
	
//	printf("ungradeInfo.port = %d\n",ungradeInfo.port);
//	strcpy(ungradeInfo.ftpCurl,"192.168.8.136 ");
	p = strstr(urlBuf,"/ftp");
	strcat(ungradeInfo.ftpCurl,p);
	
	
//	printf("ungradeInfo.ftpCurl = %s\n",ungradeInfo.ftpCurl);
	
	ungradeInfo.hostPort = dataBuf[i ++];
	ungradeInfo.hostPort <<= 8;
	ungradeInfo.hostPort |= dataBuf[i ++];
//	printf("ungradeInfo.hostPort = %d\n",ungradeInfo.hostPort);
	for(k = 0 ; k < 20 ; k ++){
		ungradeInfo.userName[k] = dataBuf[i ++];
	}
//	printf("ungradeInfo.userName = %s\n",ungradeInfo.userName);
	for(k = 0 ; k < 20 ; k ++){
		ungradeInfo.password[k] = dataBuf[i ++];
	}
	for(k = 0 ; k < 32 ; k ++){
		ungradeInfo.md5[k] = dataBuf[i ++];
	}
//	printf("ungradeInfo.md5 = %s\n",ungradeInfo.md5);
	for(k = 0 ; k < 20 ; k ++){
		ungradeInfo.softwareVersion[k] = dataBuf[i ++];
	}
//	printf("ungradeInfo.softwareVersion = %s\n",ungradeInfo.softwareVersion);
	
	yunWeiUpgradeReply(ungradeInfo);

	yunWeiUpgrade(ungradeInfo);
	return;
}

static void replyCloudWriteData(int flagNum,char *flagBuf){
	TRACE_PROJ_SOCKET_INFO(" replyCloudWriteData \n");
	int i = 0;
	int k = 0;
	char buf[100] = {0};
	buf[i ++] = flagNum;
	for(k = 0 ; k < flagNum ; k ++){
		buf[i ++] = flagBuf[k * 2];
		buf[i ++] = flagBuf[k * 2 + 1];
		buf[i ++] = 1;
	}

	frameSendData(0,SEND_CLOULD_WRITE_ID,buf,i);
	return;
}

static void dealClouldWriteData(char *dataBuf){
	TRACE_PROJ_SOCKET_INFO(" dealClouldWriteData \n");
	int i = 0;
	int len = 0;
	int k = 0;
	int m = 0;
	int totalNum = 0;
	char replyBuf[50] = {0};
	totalNum = dataBuf[i ++];
	len = strlen(dataBuf);
//	printf("######## totalNum = %d    len = %d \n",totalNum,totalNum);
	for(k = 0 ; k < totalNum ; k ++){
		if(dataBuf[i++] == 0){
			switch(dataBuf[i ++]){
				case CLOUD_TYPE:{
					len = dataBuf[i ++];
					clouldWriteInfo.cloudType = dataBuf[i ++];
					clouldWriteInfo.cloudType <<=  8;
					clouldWriteInfo.cloudType |= dataBuf[i ++];
					replyBuf[m ++] = 0;
					replyBuf[m ++] = CLOUD_TYPE;
//					printf("this is cloud type  clouldWriteInfo.cloudType = %d    len = %d",clouldWriteInfo.cloudType,len);
				}break;

				case DEVICE_SERIAL_NUM:{
					len = dataBuf[i ++];
//					printf(" this is device serial num len = %d\n",len);
					for(k = 0 ; k < len ; k ++){
						clouldWriteInfo.deviceSerialNum[k] = dataBuf[i ++];
						printf("0x%x_",clouldWriteInfo.deviceSerialNum[k]);
					}
					printf("\n");
					replyBuf[m ++] = 0;
					replyBuf[m ++] = DEVICE_SERIAL_NUM;
				}break;

				case CLOUD_IP:{
					len = dataBuf[i ++];
//					printf("this is cloud ip\n");
					for(k = 0 ; k < len ; k ++){
						clouldWriteInfo.cloudIp[k] = dataBuf[i ++];
//						printf("0x%x_",clouldWriteInfo.cloudIp[k]);
					}
//					printf("\n");
					replyBuf[m ++] = 0;
					replyBuf[m ++] = CLOUD_IP;
				}break;

				case CLOUD_PORT:{
					i ++;
					clouldWriteInfo.cloudPort = dataBuf[i ++];
					clouldWriteInfo.cloudPort <<= 8;
					clouldWriteInfo.cloudPort |= dataBuf[i ++];
					replyBuf[m ++] = 0;
					replyBuf[m ++] = CLOUD_PORT;
//					printf("this is cloud port  clouldWriteInfo.cloudPort = %d \n",clouldWriteInfo.cloudPort);
				}break;

				case LOG_FLAG:{
					i ++;
					whole_device_info deviceInfo;
					deviceInfo = getDeviceInfo();
					deviceInfo.isOpenLog =  dataBuf[i ++];
					setWholeDeviceInfo(deviceInfo);
					replyBuf[m ++] = 0;
					replyBuf[m ++] = LOG_FLAG;
//					printf("this is log flag getDeviceInfo().isOpenLog = %d\n",getDeviceInfo().isOpenLog);
				}break;

				case DEVICE_CONTROL:{
					i ++;
					printf("device control data is %d\n",dataBuf[i ++]);
					replyBuf[m ++] = 0;
					replyBuf[m ++] = DEVICE_CONTROL;
				}break;
				
			}
		}
	}
	replyCloudWriteData(totalNum,replyBuf);
	return;
}

static void dealClouldReadData(char *dataBuf){
	printf("this is dealClouldReadData \n");
	int i = 0;
	int k = 0;
	int m = 0;
	int n = 0;
	int readTotalNum = 0;
	char replyBuf[300] = {0};
	readTotalNum = dataBuf[i ++];
	replyBuf[m ++] = readTotalNum;
	printf("@@@@@ readTotalNum = %d \n",readTotalNum);
	for(k = 0 ; k < readTotalNum ; k++){
		if(dataBuf[i ++] == 0){
			switch(dataBuf[i ++]){
				case CLOUD_TYPE:{
					replyBuf[m ++] = 0;
					replyBuf[m ++] = CLOUD_TYPE;
					replyBuf[m ++] = 2;
					replyBuf[m ++] = clouldWriteInfo.cloudType >> 8 & 0xff;
					replyBuf[m ++] = clouldWriteInfo.cloudType & 0xff;
				}break;

				case DEVICE_SERIAL_NUM:{
					replyBuf[m ++] = 0;
					replyBuf[m ++] = DEVICE_SERIAL_NUM;
					replyBuf[m ++] = 20;
					for(n = 0 ; n < 20 ; n ++){
						replyBuf[m ++] = clouldWriteInfo.deviceSerialNum[n];
					}
				}break;

				case CLOUD_IP:{
					replyBuf[m ++] = 0;
					replyBuf[m ++] = CLOUD_IP;
					replyBuf[m ++] = 20;
					for(n = 0 ; n < 30 ; n ++){
						replyBuf[m ++] = clouldWriteInfo.cloudIp[n];
					}
				}break;

				case CLOUD_PORT:{
					replyBuf[m ++] = 0;
					replyBuf[m ++] = CLOUD_PORT;
					replyBuf[m ++] = 2;
					replyBuf[m ++] = clouldWriteInfo.cloudPort >> 8 & 0xff;
					replyBuf[m ++] = clouldWriteInfo.cloudPort & 0xff;
				}break;

				case LOG_FLAG:{
					replyBuf[m ++] = 0;
					replyBuf[m ++] = LOG_FLAG;
					replyBuf[m ++] = 1;
					replyBuf[m ++] = clouldWriteInfo.logFlag;
				}break;
			}
		}
	}
	
	frameSendData(0,SEND_CLOUD_READ_ID,replyBuf,m);
	return;
}

void yunWeiSendLogUpLoad(int logType){
	TRACE_PROJ_SOCKET_INFO(" yunWeiSendLogUpLoad \n");
	char buf[230] = {0};
	char md5Buf[100] = {0};
	int i = 0;
	int k = 0;
//	int len = 0;
	char fileNameBuf[128] = {0};
	
	getRunAccount();
	for(k = 0 ; k < 32 ; k ++){
		buf[i ++] = uplogRunAccount[k];
	}
	buf[i ++] = logType;
	if(logType == LOCAL_LOG){
		strcpy(fileNameBuf,LOCAL_LOG_NAME);
		for(k = 0 ; k < 128 ; k ++){
			buf[i ++] = fileNameBuf[k];
		}
		getMd5Num(LOG_FILE,md5Buf);
	}else{
		strcpy(fileNameBuf,GUN_LOG_NAME);
		for(k = 0 ; k < 128 ; k ++){
			buf[i ++] = fileNameBuf[k];
		}
		getMd5Num(GUN_LOG_FILE,md5Buf);
	}
	for(k = 0 ; k < 32 ; k ++){
		buf[i ++]  = md5Buf[k];
	}
	
	frameSendData(0,SEND_LOG_FILE_INFO,buf,i);
	
	return;
}


static void dealUpLogApplyReault(char *dealBuf){
	TRACE_PROJ_SOCKET_INFO(" dealUpLogApplyReault \n");
	int i = 0; 
	int k = 0;
//	char *p = NULL;
//	char port[10] = {0};
//	char buf[35] = {0};
//	char urlBuf[200] = {0};
	char postAddr[210] = {0};

	http_connect_info httpConnectInfo;
	
	for(k = 0 ; k < 32 ; k ++){
//		buf[k] = dealBuf[i ++];
		i ++;
	}
//	if(strcmp(buf,uplogRunAccount) != 0)
//		return;
	islogUp = dealBuf[i ++];
	if(islogUp == 0){
		printf("#####  upload refused reason is %d\n",dealBuf[i ++]);
		return;
	}
	i ++;
	
	for(k = 0 ; k < 150 ; k ++){
		postAddr[k] = dealBuf[i ++];
	}
	for(k = 0 ; k < 40 ; k ++){
		httpConnectInfo.clientId[k] = dealBuf[i ++];
	}
	for(k = 0 ; k < 40 ; k ++){
		httpConnectInfo.usrUniqueFlag[k] = dealBuf[i ++];
	}
	for(k = 0 ; k < 40 ; k ++){
		httpConnectInfo.certData[k] = dealBuf[i ++];
	}

	
#if 0
	for(k = 0 ; k < 200 ; k ++)
		postAddr[k] = dealBuf[i ++];
#endif	
	for(k = 0 ; k < 150 ; k ++){
		httpConnectInfo.urlAddr[k] = postAddr[k];
	}

//	printf("httpConnectInfo.urlAddr = %s\n",httpConnectInfo.urlAddr);
//	printf("httpConnectInfo.clientId = %s\n",httpConnectInfo.clientId);
//	printf("httpConnectInfo.usrUniqueFlag = %s\n",httpConnectInfo.usrUniqueFlag);
//	printf("httpConnectInfo.certData = %s\n",httpConnectInfo.certData);

#if 0
	p = strstr(postAddr,"//");
	strcpy(urlBuf,p);
	for(k = 0 ; k < 200 ; k ++){
		if(urlBuf[k + 2] == '/')
			break;
		httpConnectInfo.postBuf[k] = urlBuf[k + 2];
	}

	p = strstr(&urlBuf[2],"/");
	strcpy(httpConnectInfo.hostBuf,p);
	
	p = strstr(httpConnectInfo.postBuf ,":");
	strcpy(port,(p + 1));
	httpConnectInfo.httpPort = atoi(port);

	for(k = 0; k < 20 ; k ++){
		if(httpConnectInfo.postBuf [k] == ':')
			break;

		httpConnectInfo.httpIp[k] = httpConnectInfo.postBuf[k];
	}
#endif
	httpConnectInit(httpConnectInfo);
	return;
}

void dealYunWeiRecvBuf(char *buf,int len){
	printf("##################   this is dealYunWeiRecvBuf  len = %d \n",len);
	int revLen = 0;
	int i = 0;
	int k = 0;
	int m = 0;
//	int num = 0;
//	int gunNum = 0;
	int crcData = 0;
	char extractBuf[YUNWEI_BUF_LEN];
	char dataBuf[500] = {0};
	for(i = 0 ; i < len ; i ++){
		if(buf[i] == YUNWEI_HEAD_H && buf[i + 1] == YUNWEI_HEAD_L){
			for(m = 0; m < (len - i) ; m ++){
				extractBuf[m] = buf[i + m];
		//		printf("0x%x_",extractBuf[m]);
				if(extractBuf[m] == YUNWEI_TAIL_ID){
					revLen = extractBuf[2];
					revLen <<= 8;
					revLen |= extractBuf[3];
//					printf("########### revLen = %d  m = %d \n",revLen,m);
					if(m + 1 >=  revLen)
						break;
				}		
			}
			printf("\n");

			crcData = CRC16((unsigned char*)extractBuf,(revLen - 3));
			
			if(extractBuf[revLen - 3] != (crcData >> 8 & 0xff)  ||extractBuf[revLen - 2] != (crcData & 0xff) ){
				TRACE_PROJ_SOCKET_INFO("recv crc data error\n");
				continue;
			}
	//		TRACE_PROJ_SOCKET_INFO("check success\n");
		//	gunNum = extractBuf[8];
			
			for(k = 0 ; k < revLen - 12 ; k ++){
				dataBuf[k] = extractBuf[9 + k];
//				printf("_0x%x",dataBuf[k]);
			}
//			printf("\n");
			switch(extractBuf[7]){
				case RECV_SIGN_ID:{
					isSign = dataBuf[0];
					TRACE_PROJ_SOCKET_INFO("####### isSign = %d \n",isSign);
				}break;

				case RECV_HEART_BEAT_ID:{
					TRACE_PROJ_SOCKET_INFO("  recv heart beat reply\n");
				}break;

				case RECV_CHARGE_DATA_ID:{
					TRACE_PROJ_SOCKET_INFO("  recv charge data reply\n");
				}break;

				case RECV_HISTORY_DATA_ID:{
					TRACE_PROJ_SOCKET_INFO("  recv history reply\n");
				}break;

				case RECV_ACTIVE_DATA_ID:{
					printf("  recv active data reply\n");
				}break;

				case RECV_MODULE_STATE_ID:{
					TRACE_PROJ_SOCKET_INFO("  recv module state data reply\n");
				}break;

				case RECV_RELAY_STATE_ID:{
					TRACE_PROJ_SOCKET_INFO("  recv relay data reply\n");
				}break;

				case RECV_FIRMWARE_INFO_ID:{
					TRACE_PROJ_SOCKET_INFO("  recv firmware data reply\n");
					isSendVersion = true;
				}break;

				case RECV_UPGRADE_ID:{
					dealRecvUpgradeInfo(dataBuf);
				}break;

				case RECV_CLOULD_WRITE_ID:{
					dealClouldWriteData(dataBuf);
				}break;  

				case RECV_CLOUD_READ_ID:{
					dealClouldReadData(dataBuf);
				}break;

				case RECV_LOG_FILE_INFO:{
					dealUpLogApplyReault(dataBuf); 
				}break;

		//		case RECV_UP_LOG_FILE_RESULT:{
		//			yunWeiConfirmLogUpResult(islogUp);
		//		}break;

				default: break;
			}
		}
	}
	return;
}

void *yunWeiRecv(){
	TRACE_PROJ_SOCKET_INFO("#########    yunweiRecv    ########## \n");
	int ret = 0;
//	int i = 0;
	fd_set rset;
	int recvLength = 0;
	char recvBuf[YUNWEI_BUF_LEN] = {0};
	while(1){
//		printf("############################  while(1)  #############\n");
		if(!isConnect){
			mSleep(10);
			printf("   connect error  \n");
			connectYunWei();
			isSign = false;
			continue;
		}
		memset(recvBuf,0,YUNWEI_BUF_LEN);
		 recvLength = 0;
		FD_ZERO(&rset);
	         FD_SET(ywFd, &rset);		 
		ret = select(ywFd+1, &rset, NULL, NULL, NULL);
		if(ret == 0){
			 TRACE_PROJ_SOCKET_INFO("select time out  \n");
			 mSleep(300);
			 continue;
		}
		  if ((ret == EBADF) || (ret == EINTR)) {
			   printf("   judge connect error  \n");
			   TRACE_PROJ_SOCKET_INFO("ret == EBADF \n");
		   	   isConnect = false;
		   }

		  recvLength = recv(ywFd, recvBuf, YUNWEI_BUF_LEN,0);
		  if(recvLength == -1){
			 mSleep(10); 
			 printf("   recv error  \n");
			 continue;
		  }
//		  printf("recvLength = %d\n",recvLength);
//		  for(i = 0 ; i < recvLength ; i ++){
//			printf("0x%x_",recvBuf[i]);
//		  }
//		  printf("\n");
		  dealYunWeiRecvBuf(recvBuf,recvLength);
		  mSleep(100);
	}
	
	return NULL;
}

void yunWeiTimer(){
	int i = 0;
	int gunSum = 0;
	yunWeiJudgeConnected();
	gunSum = controlConfigInfo()->gunTotalNum;
	if(!isConnect){
		connectYunWei();
		isSign = false;
		return;
	}
	
	if(isSign){
		yunWeiheartBeat();
		mSleep(500);

	//	yunWeiSendLogUpLoad(LOCAL_LOG,sendCount);
	
		mSleep(1000);
#if 1
		if(!isSendVersion){
			yunWeiFirmwareInfo();
			mSleep(500);
		}
#endif	

#if 1
		for(i = 0 ; i < gunSum; i++){
			if(getChargerBlockInfo(i).isStartCharge != IDEL_STATE){
				yunWeiChargeData(i);
				if(gunChargeBuf[i] == 0)
					gunChargeBuf[i] = 1;
				mSleep(1000);
			}else{
				if(gunChargeBuf[i] == 1){
					gunChargeBuf[i] = 0;
					 yunWeiHistoryData(i);
					 mSleep(1000);
				}
				yunWeiActiveData(i);
				mSleep(1000);
			}
			if(getChargerBlockInfo(i).gunState == FAULT)
				isFault = true;
			mSleep(1000);
		}
#endif
		
	}else{
		signInYunWei();
		mSleep(500);	
	}
	return;
}

#if 1
void yunWeiFaultMonitor(){
	if(!isConnect)
		return;

	if(!isSign)
		return;

	yunWeiRelayState();
	mSleep(500);	
	yunWeiModuleState();
	mSleep(500);	
	if(getDeviceInfo().isOpenLog && isFault && (!isLogSend)){
		yunWeiSendLogUpLoad(LOCAL_LOG);
		isLogSend = true;
	}	
	
	return;
}

#endif


void yunWeiInit(){
	TRACE_PROJ_SOCKET_INFO("#########  yunWeiInit   #############\n");
//	pthread_mutex_init(&fengChongLock,NULL);

	connectYunWei();
	mSleep(20);
	create_thread(NULL,yunWeiRecv,15);

	mSleep(200);
	signInYunWei();
	mSleep(500);
//	yunWeiFirmwareInfo();
	
	initYunWeiTimerList = proj_Timer_Init("yunweiTimer");
	initYunWeiTimerId = proj_Timer_Add(initYunWeiTimerList,"yunweiTimer",yunWeiTimer,NULL,3000,1);

	initFaultMonitorList = proj_Timer_Init("faultMonitor");
	initFaultMonitorTimerId = proj_Timer_Add(initFaultMonitorList,"faultMonitor",yunWeiFaultMonitor,NULL,500,1);
	
	return;
}

#endif

