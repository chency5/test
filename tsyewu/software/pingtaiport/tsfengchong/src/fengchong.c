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

#include "fengchong.h"
#include "datacenter.h"
#include "projdebug.h"
#include "utily.h"
#include "proj_timer.h"
#include "systemconfig.h"
#include "crc.h"

#define BAN_KA_PORT_NUM         1895
#define MAX_LIST_NUM                    65536
#define FRAME_HEAD_LEN             37
#define ENCRYPT_STATE                 0
#define DEVICE_ID_NUM                   1
#define NORMAL_UP_DATA_LEN    2
#define ERROR_UP_DATA_LEN      4
#define CHARGE_UP_DATA_LEN   13
#define REQUEST_OURPUT_POWER      0
#define SOCKET_DATA_LEN                500
#define IF_TEST							1
#define REAL_FRAME_ITEM    25

#define DEVICE_NUM_START_ADDR          9
#define GUN_NUM_ADDR                               33
#define CMD_ADDR                                          30


#define GUN_CONNECT           1
#define GUN_UNCONNECT     2
#define GUN_UNUSUAL           3
#define GUN_CHARGING         4


#define FC_NONE_LIMIT                0
#define FC_TIME_LIMIT                  1
#define FC_COST_LIMIT                2
#define FC_POWER_LIMIT            3
#define FC_CURRENT_LIMIT       4

#define ONE_SEGMENT               1
#define FENG_CHARGE_SEGMENT             4

#define FENGCHONG_START               1
#define FENGCHONG_STOP                  2


static unsigned long 		initFengChongTimerList = 0;
static unsigned long 		initFengChongTimerId = 0;
// static int count = 0;
static int fengchongClick = 0;

static feng_chong_data fengChongData[MAX_GUN_NUM];

static pthread_mutex_t fengChongLock = PTHREAD_MUTEX_INITIALIZER;

static int fcFd = 0;

static bool isConnect = false;

static int isSign = false;

static int  listNum = 0;
static int heartBeatNum = 0;


static int checkTimeResult = 1;

static char gunWorkBuf[20] = {0};


void connectFengChong(){
	if(fcFd){
		close(fcFd);
		fcFd = 0;
	}
	struct sockaddr_in  servaddr;
	 if((fcFd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
	 	TRACE_PROJ_SOCKET_INFO("creat socket error : %s(errno: %d)\n",strerror(errno),errno);
		return;
	 }

	 memset(&servaddr, 0, sizeof(servaddr));
          servaddr.sin_family = AF_INET;
         servaddr.sin_port = htons(BAN_KA_PORT_NUM);
	if(IF_TEST){
		if(inet_pton(AF_INET, "120.24.38.57", &servaddr.sin_addr) <= 0){   //  controlConfigInfo()->serviceIp
			TRACE_PROJ_SOCKET_INFO("inet_pton error for\n");
			isConnect = false;
				return;
		}
	}
	else{
		if(inet_pton(AF_INET, "120.25.135.57", &servaddr.sin_addr) <= 0){   //  controlConfigInfo()->serviceIp
			TRACE_PROJ_SOCKET_INFO("inet_pton error for\n");
			isConnect = false;
				return;
		}
	}

	if(connect(fcFd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
		TRACE_PROJ_SOCKET_INFO("connect error: %s(errno: %d)\n",strerror(errno),errno);
		isConnect = false;
		return;
	}
	isConnect = true;
	return;
} 

static void  judgeConnected() {
	if (fcFd < 0)
		return ;
	
	struct tcp_info info;
	int len = sizeof(info);
	getsockopt(fcFd,IPPROTO_TCP,TCP_INFO,&info,(socklen_t *)&len);
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

static int getFengChongStopReason(int sourceData){
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

static int getFengChongAlarmData(int sourceData){
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

int  getFCerrorCode(int gunNum){
	int errorCode = 0;
	
	switch(getChargerBlockInfo(gunNum).chargeStopReason){
		case 0x07: errorCode = 0x3003; break;
		case 0x08: errorCode = 0x3002; break;
		case 0x13: errorCode = 0x3008; break;
		case 0x14: errorCode = 0x3007; break;
		case 0x12: errorCode = 0x300a; break;
		case 0x1a: errorCode = 0x300e; break;
		case 0x10: errorCode = 0x3014; break;
		case 0x0e: errorCode = 0x3016; break;
		case 0x0f:  errorCode = 0x3017; break;
		case 0x18: errorCode = 0x3018; break;
		case 0x0d: errorCode = 0x301b; break;
		case 0x1b:
		case 0x1c: errorCode = 0x4000;  break;
		case 0x0c: errorCode = 0x4001; break;
		case 0x0b: errorCode = 0x4002; break;
		case 0x20: errorCode = 0x5001; break;
		case 0x21: errorCode = 0x5002; break;
		case 0x25: errorCode = 0x5003; break;
		case 0x24: errorCode = 0x5004; break;
		case 0x22: errorCode = 0x5008; break;
		case 0x3a: errorCode = 0x5009; break;
		case 0x1f:  errorCode = 0x500a; break;
		case 0x50: errorCode = 0x500b; break;
		case 0x2b: errorCode = 0x5012; break;
		case 0x2c: errorCode = 0x5013; break;
		case 0x2d: errorCode = 0x5014; break;
		case 0x2e: errorCode = 0x5015; break;
		case 0x2f:  errorCode = 0x5016; break;
		case 0x31: errorCode = 0x5017; break;
		case 0x33: errorCode = 0x5018; break;
		case 0x35: errorCode = 0x5019; break;
		case 0x0a: errorCode = 0x501a; break;

		default: break;
		
	}
	return errorCode;
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


static bool fengChongSend(char *sendBuf,int sendLen){
	if(!isConnect || !sendBuf)
		return false;

	int i = 0;
	for(i = 0 ; i < sendLen ; i ++){
		printf("_0x%x",sendBuf[i]);
	}
	printf("\n");
	
	int ret = 0;
	ret = send(fcFd,sendBuf,sendLen,0);
	if(ret == -1){
		isConnect = false;
		return false;
	}
	listNum ++;
	if(listNum >= MAX_LIST_NUM)
		listNum = 0;
	return true;
}

static bool framingSendData(int gunNum,char cmd,char *dataBuf,int bufLen){
	TRACE_PROJ_SOCKET_INFO(" feng chong   framingSendData :cmd = %x\n",cmd);
	int i = 0;
	int k = 0;
	int totalLen = 0;
	unsigned short crc = 0;
	bool isSuccess = false;
	char sendBuf[SOCKET_DATA_LEN] = {0};
	totalLen =  bufLen + FRAME_HEAD_LEN;

	sendBuf[i ++] = FRAME_HEAD_H;
	sendBuf[i ++] = FRAME_HEAD_L;
	
	sendBuf[i ++] = totalLen >> 8 & 0xff;
	sendBuf[i ++] = totalLen & 0xff;

	int version = 501;
	
	sendBuf[i ++] = version >> 8 & 0xff;                                           //controlConfigInfo()->softwareVersion >> 8 & 0xff;
	sendBuf[i ++] = version & 0xff;                                              //controlConfigInfo()->softwareVersion & 0xff;
	
	sendBuf[i ++] = listNum >> 8 & 0xff;
	sendBuf[i ++] = listNum & 0xff;
	
	sendBuf[i ++] = 5;   //(char)controlConfigInfo()->deviceType;

	char deviceCode[25] = {0};
	strcpy(deviceCode,"00000000000005805023");   //00000000000005805023   00000000000005805021

	for(k = 0 ; k < 20 ; k ++){
		sendBuf[i ++] = deviceCode[k]; //controlConfigInfo()->serialNum[k];
	}
	
	sendBuf[i ++] = ENCRYPT_STATE;
	
	sendBuf[i ++] = cmd;

	sendBuf[i ++] = 0;
	sendBuf[i ++] = DEVICE_ID_NUM;

	sendBuf[i ++] = (char)gunNum;

	for(k = 0 ; k < bufLen ; k ++){
		sendBuf[i ++] = dataBuf[k];
	}

	crc = CRC16((unsigned char*)sendBuf,(totalLen - 3));
	sendBuf[i ++] = crc >> 8 & 0xff;
	sendBuf[i ++]  = crc & 0xff;
	
	sendBuf[i ++] = FRAME_TAIL;
	
	isSuccess = fengChongSend(sendBuf,totalLen);
	memset(sendBuf,0,sizeof(sendBuf));
	
	return isSuccess;
}

void clientUpLoad(){
	int i = 0;
	int k =0;
	char buf[50] = {0};
	buf[i ++] = 2;    //controlConfigInfo()->gunTotalNum;
	for(k = 0 ; k < 20 ; k ++){
		buf[i ++]  = 0;
	}
	
	pthread_mutex_lock(&fengChongLock);
	framingSendData(0,SIGN_ON_UP,buf,i);
	pthread_mutex_unlock(&fengChongLock);
	return;
}

void historyUpFrame(void){
	char buf[500] = {0};
	readFileLastPart(SUPPLY_HISTORY_PATH,buf,FC_HISTORY_MESSAGE_LEN);
	if(buf[0] == 0x4b && buf[1] == 0x48){
		pthread_mutex_lock(&fengChongLock);
		fengChongSend(buf,FC_HISTORY_MESSAGE_LEN);
		pthread_mutex_unlock(&fengChongLock);
	}
}

void heartBeat(){
	char buf[5] = {0};
	int i = 0;
	buf[i ++] = heartBeatNum >> 8 & 0xff;
	buf[i ++] = heartBeatNum & 0xff;
	buf[i ++] = 0;

	if(heartBeatNum > MAX_LIST_NUM)
		heartBeatNum = 0;

	pthread_mutex_lock(&fengChongLock);
	framingSendData(0,HEART_BEAT_UP,buf,i);
	pthread_mutex_unlock(&fengChongLock);

	return;
}

void isStartChargeConfirm(int gunNum){
	int i = 0;
	int k = 0;
	char buf[100] = {0};
	
	for(k = 0 ; k < 20 ; k ++){
		buf[i ++] = getUserAccountInfo(gunNum).accountNum[k];
	}
	buf[i ++] = fengChongData[gunNum].controlType;
	for(k = 0 ; k < 32 ; k ++){
		buf[i ++] = getUserAccountInfo(gunNum).cloudTradeNum[k];
	}
	
	if(getChargerBlockInfo(gunNum).gunState == PLUG_IN ||getChargerBlockInfo(gunNum).gunState == FINISH_PLUG_IN)
		buf[i ++] = GUN_CONNECT;
	
	if(getChargerBlockInfo(gunNum).gunState == IDEL)
		buf[i ++] = GUN_UNCONNECT;

	if(getChargerBlockInfo(gunNum).gunState == HANDSHAKE || getChargerBlockInfo(gunNum).gunState == CONFIG || getChargerBlockInfo(gunNum).gunState == CHARGING)
		buf[i ++] = GUN_CHARGING;        

	if(getChargerBlockInfo(gunNum).gunState == UPGRADE || getChargerBlockInfo(gunNum).gunState == FAULT)
		buf[i ++] = GUN_UNUSUAL;

	pthread_mutex_lock(&fengChongLock);
	framingSendData(gunNum,START_CHARGE_CONFIRM_UP,buf,i);
	pthread_mutex_unlock(&fengChongLock);

	return;
}

void startChargeResultUp(int gunNum){
	int i = 0;
	int k = 0;
	char buf[100] = {0};
	

	buf[i ++] = fengChongData[gunNum].controlType;
	for(k = 0 ; k < 20 ; k ++){
		buf[i ++] = getUserAccountInfo(gunNum).accountNum[k];
	}

	for(k = 0 ; k < 32 ; k ++){
		buf[i ++] = getUserAccountInfo(gunNum).cloudTradeNum[k];
	}
	
	if(fengChongData[gunNum].controlType == FENGCHONG_START){
		if(getChargerBlockInfo(gunNum).isStartCharge)
			buf[i ++] = 0;
		else
			buf[i ++] = 1;
	}else{
		if(!getChargerBlockInfo(gunNum).isStartCharge)
			buf[i ++] = 0;
		else
			buf[i ++] = 1;
	}


	for(k = 0 ; k < 32 ; k ++){
		buf[i ++] = getChargerBlockInfo(gunNum).chargingList[k];
	}
	

	pthread_mutex_lock(&fengChongLock);
	framingSendData(gunNum,START_CHARGE_RESULT_UP,buf,i);
	pthread_mutex_unlock(&fengChongLock);
	return;
}

void cardRequestFrame(int gunNum,char operate){
	int i  = 0;
	int k = 0;
	char buf[100] = {0};
	
	buf[i ++] = getUserAccountInfo(gunNum).accountType;
	for(k = 0 ; k < 20 ; k ++){
		buf[i ++] = getUserAccountInfo(gunNum).accountNum[k];
	}
	for(k = 0 ; k < 32 ; k ++){
		buf[i ++] = getUserAccountInfo(gunNum).userPassWd[k];
	}
	for(k = 0 ; k < 16 ; k ++){
		buf[i ++] = getUserAccountInfo(gunNum).uniqueCardId[k];
	}
	if(getUserAccountInfo(gunNum).operateType)
		buf[i ++] = FENGCHONG_START;
	else
		buf[i ++] = FENGCHONG_STOP;	

	pthread_mutex_lock(&fengChongLock);
	framingSendData(gunNum,CARD_REQUEST_UP,buf,i);
	pthread_mutex_unlock(&fengChongLock);
	
	return;
}

void chargeRealDataFrame(int gunNum){
	char buf[200] = {0};
	int i = 0;
	buf[i ++] = 17;
//	buf[i ++] = 0x10;
//	buf[i ++] = 0x01;
//	buf[i ++] = 1;
//	buf[i ++] = getUserAccountInfo(gunNum).measureUnit;
//	buf[i ++] = 0x10;
//	buf[i ++] = 0x03;
//	buf[i ++] = 4;
//	buf[i ++] = getChargerBlockInfo(gunNum).chargingList[0];
//	buf[i ++] = getChargerBlockInfo(gunNum).chargingList[1];
//	buf[i ++] = getChargerBlockInfo(gunNum).chargingList[2];
//	buf[i ++] = getChargerBlockInfo(gunNum).chargingList[3];
	buf[i ++] = 0x10;
	buf[i ++] = 0x04;
	buf[i ++] = 4;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingVol >> 24 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingVol >> 16 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingVol >> 8 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingVol & 0xff;
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
	buf[i ++] = getChargerBlockInfo(gunNum).chargingPower >> 24 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingPower >> 16 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingPower >> 8 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingPower & 0xff;
	buf[i ++] = 0x10;
	buf[i ++] = 0x08;
	buf[i ++] = 4;
	buf[i ++] = getUserAccountInfo(gunNum).costMoney >> 24 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).costMoney >> 16 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).costMoney >> 8 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).costMoney & 0xff;
	buf[i ++] = 0x10;
	buf[i ++] = 0x09;
	buf[i ++] = 4;
	buf[i ++] =  getUserAccountInfo(gunNum).serviceMoney >> 24 & 0xff;
	buf[i ++] =  getUserAccountInfo(gunNum).serviceMoney >> 16 & 0xff;
	buf[i ++] =  getUserAccountInfo(gunNum).serviceMoney >> 8 & 0xff;
	buf[i ++] =  getUserAccountInfo(gunNum).serviceMoney & 0xff;
	buf[i ++] = 0x10;
	buf[i ++] = 0x0A;
	buf[i ++] = 4;
	buf[i ++] =  getChargerBlockInfo(gunNum).remaindTime >> 24 & 0xff;
	buf[i ++] =  getChargerBlockInfo(gunNum).remaindTime >> 16 & 0xff;
	buf[i ++] =  getChargerBlockInfo(gunNum).remaindTime >> 8 & 0xff;
	buf[i ++] =  getChargerBlockInfo(gunNum).remaindTime & 0xff;
	buf[i ++] = 0x10;
	buf[i ++] = 0x0B;
	buf[i ++] = 4;
	buf[i ++] =  getChargerBlockInfo(gunNum).currentMeterData >> 24 & 0xff;
	buf[i ++] =  getChargerBlockInfo(gunNum).currentMeterData >> 16 & 0xff;
	buf[i ++] =  getChargerBlockInfo(gunNum).currentMeterData >> 8 & 0xff;
	buf[i ++] =  getChargerBlockInfo(gunNum).currentMeterData & 0xff;
	buf[i ++] = 0x10;
	buf[i ++] = 0x0c;
	buf[i ++] = 1;
	buf[i ++] = getChargerBlockInfo(gunNum).currentSoc;
	buf[i ++] = 0x10;
	buf[i ++] = 0x0D;
	buf[i ++] = 2;
	buf[i ++] =  getChargerBlockInfo(gunNum).requireVol >> 8 & 0xff;
	buf[i ++] =  getChargerBlockInfo(gunNum).requireVol& 0xff;
	buf[i ++] = 0x10;
	buf[i ++] = 0x0E;
	buf[i ++] = 2;
	buf[i ++] =  getChargerBlockInfo(gunNum).requireCurrent >> 8 & 0xff;
	buf[i ++] =  getChargerBlockInfo(gunNum).requireCurrent & 0xff;
	buf[i ++] = 0x10;
	buf[i ++] = 0x0F;
	buf[i ++] = 4;
	buf[i ++] = getDeviceInfo().APhaseVol >> 24 & 0xff;
	buf[i ++] = getDeviceInfo().APhaseVol >> 16 & 0xff;
	buf[i ++] = getDeviceInfo().APhaseVol >> 8 & 0xff;
	buf[i ++] = getDeviceInfo().APhaseVol  & 0xff;
	buf[i ++] = 0x10;
	buf[i ++] = 0x10;
	buf[i ++] = 4;
	buf[i ++] = getDeviceInfo().BPhaseVol >> 24 & 0xff;
	buf[i ++] = getDeviceInfo().BPhaseVol >> 16 & 0xff;
	buf[i ++] = getDeviceInfo().BPhaseVol >> 8 & 0xff;
	buf[i ++] = getDeviceInfo().BPhaseVol & 0xff;
	buf[i ++] = 0x10;
	buf[i ++] = 0x11;
	buf[i ++] = 4;
	buf[i ++] = getDeviceInfo().CPhaseVol >> 24 & 0xff;
	buf[i ++] = getDeviceInfo().CPhaseVol >> 16 & 0xff;
	buf[i ++] = getDeviceInfo().CPhaseVol >> 8 & 0xff;
	buf[i ++] = getDeviceInfo().CPhaseVol & 0xff;
	buf[i ++] = 0x10;
	buf[i ++] = 0x12;
	buf[i ++] = 4;
	buf[i ++] = getDeviceInfo().APhaseCurrent >> 24 & 0xff;
	buf[i ++] = getDeviceInfo().APhaseCurrent >> 16 & 0xff;
	buf[i ++] = getDeviceInfo().APhaseCurrent >> 8 & 0xff;
	buf[i ++] = getDeviceInfo().APhaseCurrent & 0xff;
	buf[i ++] = 0x10;
	buf[i ++] = 0x13;
	buf[i ++] = 4;
	buf[i ++] = getDeviceInfo().BPhaseCurrent >> 24 & 0xff;
	buf[i ++] = getDeviceInfo().BPhaseCurrent >> 16 & 0xff;
	buf[i ++] = getDeviceInfo().BPhaseCurrent >> 8 & 0xff;
	buf[i ++] = getDeviceInfo().BPhaseCurrent & 0xff;
	buf[i ++] = 0x10;
	buf[i ++] = 0x14;
	buf[i ++] = 4;
	buf[i ++] = getDeviceInfo().CPhaseCurrent >> 24 & 0xff;
	buf[i ++] = getDeviceInfo().CPhaseCurrent >> 16 & 0xff;
	buf[i ++] = getDeviceInfo().CPhaseCurrent >> 8 & 0xff;
	buf[i ++] = getDeviceInfo().CPhaseCurrent & 0xff;
#if 0
	buf[i ++] = 0x10;
	buf[i ++] = 0x15;
	buf[i ++] = 4;
	buf[i ++] = getChargerBlockInfo(gunNum).actPower >> 24 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).actPower >> 16 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).actPower >> 8 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).actPower & 0xff;
	buf[i ++] = 0x10;
	buf[i ++] = 0x16;
	buf[i ++] = 4;
	buf[i ++] = getChargerBlockInfo(gunNum).reactPower >> 24 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).reactPower >> 16 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).reactPower >> 8 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).reactPower & 0xff;

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
	buf[i ++] = 0x10;
	buf[i ++] = 0x19;
	buf[i ++] = 2;
	buf[i ++] = getBatteryBlockInfo(gunNum).maxBatteryTemp >> 8 & 0xff;
	buf[i ++] = getBatteryBlockInfo(gunNum).maxBatteryTemp & 0xff;	
	buf[i ++] = 0x10;
	buf[i ++] = 0x1A;
	buf[i ++] = 2;
	buf[i ++] = getBatteryBlockInfo(gunNum).minBatteryTemp >> 8 & 0xff;
	buf[i ++] = getBatteryBlockInfo(gunNum).minBatteryTemp & 0xff;
	
#endif

	pthread_mutex_lock(&fengChongLock);
	framingSendData((gunNum + 1),REAL_DATA_UP,buf,i);
	pthread_mutex_unlock(&fengChongLock);

	return;
}

void historyFrame(int gunNum){
	int i = 0;
	int k = 0;
	short stopReason = 0;
	char bcdBuf[10] = {0};
	char buf[450] = {0};

	buf[i ++] = getCloudCtrlFun(gunNum).startType;
	buf[i ++] = getCloudCtrlFun(gunNum).chargeLimit.limitType;
	buf[i ++] = 5; //getUserAccountInfo(gunNum).accountType;
	for(k = 0 ; k < 20 ; k ++){
		buf[i ++] = getUserAccountInfo(gunNum).accountNum[k];
	}
	for(k = 0 ; k < 17 ; k ++){
		buf[i ++]= getChargerBlockInfo(gunNum).vehicleVin[k];
	}
	buf[i ++] = getUserAccountInfo(gunNum).accountMoney >> 24 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).accountMoney >> 16 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).accountMoney >> 8 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).accountMoney & 0xff;
	
	for(k = 0 ; k < 4 ; k ++){
		buf[i ++] = 0;
	}
	
	buf[i ++] = getChargerBlockInfo(gunNum).chargingTime >> 24 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingTime >> 16 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingTime >> 8 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingTime & 0xff;
	
	buf[i ++] = getUserAccountInfo(gunNum).costMoney >> 24 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).costMoney >> 16 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).costMoney >> 8 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).costMoney & 0xff;
	
	buf[i ++] = getChargerBlockInfo(gunNum).chargingPower >> 24 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingPower >> 16 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingPower >> 8 & 0xff;
	buf[i ++] = getChargerBlockInfo(gunNum).chargingPower & 0xff;

	for(k = 0 ; k < 8 ; k ++){
		buf[i ++] = 0;
	}
	
//	buf[i ++] = getChargerBlockInfo(gunNum).firstMeterData >> 24 & 0xff;
//	buf[i ++] = getChargerBlockInfo(gunNum).firstMeterData >> 16 & 0xff;
//	buf[i ++] = getChargerBlockInfo(gunNum).firstMeterData >> 8 & 0xff;
//	buf[i ++] = getChargerBlockInfo(gunNum).firstMeterData & 0xff;
//	buf[i ++] = getChargerBlockInfo(gunNum).currentMeterData >> 24 & 0xff;
//	buf[i ++] = getChargerBlockInfo(gunNum).currentMeterData >> 16 & 0xff;
//	buf[i ++] = getChargerBlockInfo(gunNum).currentMeterData >> 8 & 0xff;
//	buf[i ++] = getChargerBlockInfo(gunNum).currentMeterData & 0xff;
	
	buf[i ++] = getChargerBlockInfo(gunNum).firstSoc;
	buf[i ++] = getChargerBlockInfo(gunNum).currentSoc;
	buf[i ++] = 1;//getUserAccountInfo(gunNum).isPay;
//	transformStopReason(gunNum,buf,i);
	
	stopReason = getFengChongStopReason(getChargerBlockInfo(gunNum).chargeStopReason);
	buf[i ++] = stopReason >> 8 & 0xff;
	buf[i ++] = stopReason & 0xff;;

	
	convertTimeToBcd(getChargerBlockInfo(gunNum).startChargeTime,bcdBuf);
	for(k = 0 ; k < 7 ; k ++){
		buf[i ++] = bcdBuf[k];
	}
	memset(bcdBuf,0,sizeof(bcdBuf));
	convertTimeToBcd(getChargerBlockInfo(gunNum).stopChargeTime,bcdBuf);
	for(i = 0 ; i < 7 ; i ++){
		buf[i ++] = bcdBuf[k];
	}

	for(k = 0 ; k < 4 ; k ++){
		buf[i ++] = 0;
	} 
	
//	buf[i ++] = getBatteryBlockInfo(gunNum).maxBatteryVol >> 8 & 0xff;
//	buf[i ++] = getBatteryBlockInfo(gunNum).maxBatteryVol & 0xff;
//	buf[i ++] = getBatteryBlockInfo(gunNum).maxBatteryTemp >> 8 & 0xff;
//	buf[i ++] = getBatteryBlockInfo(gunNum).maxBatteryTemp & 0xff;


	for(k = 0 ; k < 32 ; k ++){
		buf[i ++] = getUserAccountInfo(gunNum).cloudTradeNum[k];
	}
	
	for(k = 0; k < 32 ; k ++){
		buf[i ++] = getChargerBlockInfo(gunNum).chargingList[k];
	}

	
	
	buf[i ++] = getUserAccountInfo(gunNum).serviceMoney >> 24 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).serviceMoney >> 16 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).serviceMoney >> 8 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).serviceMoney & 0xff;

	for(k = 0 ; k < 10 ; k ++){
		buf[i ++] = 0;
	}
	for(k = 0 ; k <48 ; k++){
		buf[i++] = getUserAccountInfo(gunNum).section48Power[k]  >> 24 & 0xff;
		buf[i++] = getUserAccountInfo(gunNum).section48Power[k]  >> 16 & 0xff;
		buf[i++] = getUserAccountInfo(gunNum).section48Power[k]  >> 8 & 0xff;
		buf[i++] = getUserAccountInfo(gunNum).section48Power[k]  >> 0 & 0xff;
	}
#if 0
	buf[i ++] = getUserAccountInfo(gunNum).costMoney >> 24 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).costMoney >> 16 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).costMoney >> 8 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).costMoney & 0xff;
	for(k = 0 ; k < 10 ; k ++){
		buf[i ++] = getCostRulesInfo().costRulesVersion[k];
	}
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[JIAN_SECTION].chargePower >> 24 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[JIAN_SECTION].chargePower >> 16 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[JIAN_SECTION].chargePower >> 8 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[JIAN_SECTION].chargePower & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[FENG_SECTION].chargePower >> 24 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[FENG_SECTION].chargePower >> 16 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[FENG_SECTION].chargePower >> 8 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[FENG_SECTION].chargePower & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[PING_SECTION].chargePower >> 24 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[PING_SECTION].chargePower >> 16 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[PING_SECTION].chargePower >> 8 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[PING_SECTION].chargePower & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[GU_SECTION].chargePower >> 24 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[GU_SECTION].chargePower >> 16 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[GU_SECTION].chargePower >> 8 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[GU_SECTION].chargePower & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[JIAN_SECTION].chargeCost >> 24 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[JIAN_SECTION].chargeCost >> 16 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[JIAN_SECTION].chargeCost >> 8 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[JIAN_SECTION].chargeCost & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[FENG_SECTION].chargeCost >> 24 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[FENG_SECTION].chargeCost >> 16 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[FENG_SECTION].chargeCost >> 8 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[FENG_SECTION].chargeCost & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[PING_SECTION].chargeCost >> 24 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[PING_SECTION].chargeCost >> 16 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[PING_SECTION].chargeCost >> 8 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[PING_SECTION].chargeCost & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[GU_SECTION].chargeCost >> 24 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[GU_SECTION].chargeCost >> 16 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[GU_SECTION].chargeCost >> 8 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[GU_SECTION].chargeCost & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[JIAN_SECTION].serviceCost >> 24 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[JIAN_SECTION].serviceCost >> 16 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[JIAN_SECTION].serviceCost >> 8 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[JIAN_SECTION].serviceCost & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[FENG_SECTION].serviceCost >> 24 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[FENG_SECTION].serviceCost >> 16 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[FENG_SECTION].serviceCost >> 8 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[FENG_SECTION].serviceCost & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[PING_SECTION].serviceCost >> 24 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[PING_SECTION].serviceCost >> 16 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[PING_SECTION].serviceCost >> 8 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[PING_SECTION].serviceCost & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[GU_SECTION].serviceCost >> 24 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[GU_SECTION].serviceCost >> 16 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[GU_SECTION].serviceCost >> 8 & 0xff;
	buf[i ++] = getUserAccountInfo(gunNum).fourSectionInfo[GU_SECTION].serviceCost & 0xff;
#endif
	
	// pthread_mutex_lock(&fengChongLock);
	// framingSendData((gunNum + 1),HISTORY_UP,buf,i);
	// pthread_mutex_unlock(&fengChongLock);
	
	addSupplyHistory(buf,i);
	
	
	return;
}

#if 0
void upGradeAnswerFrame(){
	int i = 0;
	int k =0;
	char buf[30] = {0};
	
	buf[i ++] = getDeviceInfo().deviceState;
	buf[i ++] = getDeviceInfo().upGradeType;
	switch(getDeviceInfo().upGradeType){
		case ALL_IN_ONE_PROG:{
			for(k = 0 ; k < 20 ; k ++){
				buf[i ++] = getDeviceInfo().softwareVersion[k];
			}
		}
		break;
		
		case POWER_PORT_PROG:{
			for(k = 0 ; k < 20 ; k ++){
				buf[i ++] = getDeviceInfo().powerPortVersion[k];
			}
		}
		break;
		
		case CHARGE_PORT_PROG:{
			for(k = 0 ; k < 20 ; k ++){
				buf[i ++] = getDeviceInfo().chargePortVersion[k];
			}
		}
		break;

		default:break;
	}

	pthread_mutex_lock(&fengChongLock);
	framingSendData(0,UP_GRADE_CONFIRM_UP,buf,i);
	pthread_mutex_unlock(&fengChongLock);
	return;
}

void upGradeResultFrame(){
	int i = 0;
	int k = 0;
	char buf[30] = {0};

	buf[i ++] = getDeviceInfo().upGradeState;
	switch(getDeviceInfo().upGradeType){
		case ALL_IN_ONE_PROG:{
			for(k = 0 ; k < 20 ; k ++){
				buf[i ++] = getDeviceInfo().softwareVersion[k];
			}
		}
		break;
		
		case POWER_PORT_PROG:{
			for(k = 0 ; k < 20 ; k ++){
				buf[i ++] = getDeviceInfo().powerPortVersion[k];
			}
		}
		break;
		
		case CHARGE_PORT_PROG:{
			for(k = 0 ; k < 20 ; k ++){
				buf[i ++] = getDeviceInfo().chargePortVersion[k];
			}
		}
		break;

		default:break;
	}
	
	pthread_mutex_lock(&fengChongLock);
	framingSendData(0,UP_GRADE_RESULT_UP,buf,i);
	pthread_mutex_unlock(&fengChongLock);
	
	return;
}

#endif

void activeUpLoadFrame(int gunNum){
	char buf[150] = {0};
	int i = 0;
	
	int alarmData = 0;
	
	
	buf[i ++]= 1; //getChargerBlockInfo(gunNum).realFrameId;
	
	if(getChargerBlockInfo(gunNum).gunState == FAULT)
		buf[i ++] = 4;
	else
		buf[i ++] = 3;
	
	buf[i ++] = 0x10;
	buf[i ++] = 0;
	buf[i ++] = 1;
	if(getChargerBlockInfo(gunNum).gunState == IDEL ||getChargerBlockInfo(gunNum).gunState == PLUG_IN ||
		getChargerBlockInfo(gunNum).gunState == HANDSHAKE ||getChargerBlockInfo(gunNum).gunState == CHARGING)
		buf[i ++] = getChargerBlockInfo(gunNum).gunState;

	if(getChargerBlockInfo(gunNum).gunState == FINISH_PLUG_IN)
		buf[i ++] = 1;

	if(getChargerBlockInfo(gunNum).gunState == FAULT)
		buf[i ++] = 9;
	
	buf[i ++] = 0x10;
	buf[i ++] = 0x01;
	buf[i ++] = 1;
	if(getChargerBlockInfo(gunNum).gunState == PLUG_IN || getChargerBlockInfo(gunNum).gunState == FINISH_PLUG_IN)
		buf[i ++] = GUN_CONNECT;
	else{
		if(getChargerBlockInfo(gunNum).gunState == IDEL)
			buf[i ++] = GUN_UNCONNECT;
	}

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
		alarmData = getFengChongAlarmData(getChargerBlockInfo(gunNum).faultReason);
		buf[i ++] = alarmData >> 8 & 0xff;
		buf[i ++] = alarmData & 0xff;
	}
	
	

	pthread_mutex_lock(&fengChongLock);
	framingSendData((gunNum + 1),POS_SEND_DATA_UP,buf,i);
	pthread_mutex_unlock(&fengChongLock);
	
	return;
}

void checkTimeFrame(int gunNum,char resultState){
	char buf[5] = {0};
	int i = 0;
	buf[i ++] = resultState;
	pthread_mutex_lock(&fengChongLock);
	framingSendData(gunNum,CHECK_TIME_UP,buf,i);
	pthread_mutex_unlock(&fengChongLock);

	return;
}

void vehicleVinChargeFrame(int gunNum){
	int i = 0;
	int k = 0;
	char buf[20] = {0};
	for(k = 0 ; k < 17 ; k ++){
		buf[i ++] = getChargerBlockInfo(gunNum).vehicleVin[k];
	}

	pthread_mutex_lock(&fengChongLock);
	framingSendData(gunNum,VIN_CHARGE_UP,buf,i);
	pthread_mutex_unlock(&fengChongLock);

	return;
}

void costRulesConfirmFrame(){
	int i = 0;
	int k = 0;
	char buf[15] = {0};
	
	buf[i ++] = getCostRulesInfo().resultState;
	for(k = 0 ; k < 10 ; k ++){
		buf[i ++] = getCostRulesInfo().costRulesVersion[k];
	}

	pthread_mutex_lock(&fengChongLock);
	framingSendData(0,COST_RULES_UP,buf,i);
	pthread_mutex_unlock(&fengChongLock);
	
	return;
}
 

void offLineControlConfirmFrame(int gunNum,int resultState){
	char buf[5] = {0};
	int i = 0;

	buf[i ++] = resultState;
	buf[i ++] = getChargerBlockInfo(gunNum).offLineChargeType;
	buf[i ++] = getChargerBlockInfo(gunNum).offLineStartControl;

	pthread_mutex_lock(&fengChongLock);
	framingSendData(gunNum,OFF_LINE_CONTROL_UP,buf,i);
	pthread_mutex_unlock(&fengChongLock);

	return;
}

void outputControlConfirmFrame(int gunNum,char resultState){
	char buf[5] = {0};
	int i = 0;
	
	buf[i ++] = resultState;

	pthread_mutex_lock(&fengChongLock);
	framingSendData(gunNum,OUTPUT_CONTROL_UP,buf,i);
	pthread_mutex_unlock(&fengChongLock);
	
	return;
}

int moniterStartChargerFun(int gunNum){
	return getChargerBlockInfo(gunNum).isStartCharge;
}

int moniterStopChargerFun(int gunNum){
	if(getChargerBlockInfo(gunNum).isStartCharge == 0)
		return 1;
	else
		return 0;
}


void isStartChargeControl(int gunNum,char *buf){   // the can protocol lack relevant data so it is not complete.
	int i = 0;
	int k = 0;
//	chargerBlockInfo blockInfo;
	userAccountInfo accountInfo;
	cloud_ctrl_fun ctrlFun;
	
//	blockInfo = getChargerBlockInfo(gunNum);
	ctrlFun = getCloudCtrlFun(gunNum);
	fengChongData[gunNum].controlType = buf[i ++];
//	blockInfo.axuPower = buf[1];
	i ++;
	switch( buf[i ++]){
		case FC_NONE_LIMIT: ctrlFun.chargeLimit.limitType= NONE_LIMIT; break;
		case FC_TIME_LIMIT: ctrlFun.chargeLimit.limitType = TIME_LIMIT; break;
		case FC_COST_LIMIT: ctrlFun.chargeLimit.limitType = COST_LIMIT; break;
		case FC_POWER_LIMIT: ctrlFun.chargeLimit.limitType = POWER_LIMIT; break;
		case FC_CURRENT_LIMIT: ctrlFun.chargeLimit.limitType = CURRENT_LIMIT; break;
		default: break;
	}
	ctrlFun.chargeLimit.limitData = buf[i ++];
	ctrlFun.chargeLimit.limitData = ctrlFun.chargeLimit.limitData << 8 | buf[i ++];
	ctrlFun.chargeLimit.limitData = ctrlFun.chargeLimit.limitData << 8 | buf[i ++];
	ctrlFun.chargeLimit.limitData = ctrlFun.chargeLimit.limitData << 8 | buf[i ++];
	lockCloudCtrlFun(ctrlFun,gunNum);

	accountInfo = getUserAccountInfo(gunNum);
	for(k = 0 ; k < 20 ; k ++){
		accountInfo.accountNum[k] = buf[i ++];
	}
	

	for(k = 0 ; k < 32 ; k ++){
		accountInfo.cloudTradeNum[k] = buf[i ++]; 
	}

	accountInfo.accountMoney = buf[i ++];
	accountInfo.accountMoney = accountInfo.accountMoney << 8 | buf[i ++];
	accountInfo.accountMoney = accountInfo.accountMoney << 8 | buf[i ++];
	accountInfo.accountMoney = accountInfo.accountMoney << 8 | buf[i ++];
	accountInfo.stopVerifyCode = buf[i ++];
	accountInfo.stopVerifyCode = accountInfo.stopVerifyCode << 8 | buf[i ++];
	lockUserAccount(accountInfo,gunNum);

	ctrlFun = getCloudCtrlFun(gunNum);
	if(fengChongData[gunNum].controlType == FENGCHONG_START)
		ctrlFun.isStart = 1;
	else
		ctrlFun.isStop = 1;

	lockCloudCtrlFun(ctrlFun,gunNum);
	
	isStartChargeConfirm(gunNum);

	if(fengChongData[gunNum].controlType == FENGCHONG_START)
		startDelayTimer(startChargeResultUp,gunNum,200,1000 * 5,moniterStartChargerFun,NULL);
	else
		startDelayTimer(startChargeResultUp,gunNum,200,1000 * 5,moniterStopChargerFun,NULL);
	return;
}

void cardResultConfirm(int gunNum,char *buf){
	userAccountInfo accountInfo;
	int i = 0;
	int k = 0;
	i = 21;
	accountInfo = getUserAccountInfo(gunNum);
	accountInfo.accountMoney = buf[i ++];
	accountInfo.accountMoney = accountInfo.accountMoney  << 8 |buf[i ++];
	accountInfo.accountMoney = accountInfo.accountMoney  << 8 |buf[i ++];
	accountInfo.accountMoney = accountInfo.accountMoney  << 8 |buf[i ++];
	accountInfo.cardState = buf[i ++];
	
	for(k = 0 ; k < 32 ; k ++){
		accountInfo.cloudTradeNum[k] = buf[i ++];
	}
	
	accountInfo.stopVerifyCode = buf[i ++];
	accountInfo.stopVerifyCode = accountInfo.stopVerifyCode << 8 | buf[i ++];
	lockUserAccount(accountInfo,gunNum);
	return;
}

void historyConfiurm(int gunNum,char *buf){
	printf("recv  history  confiurm gunNum = %d \n",gunNum);
	if(*buf == 0)
		historyFrame(gunNum);
	if(*buf == 1)
		deleteFileLastPart(SUPPLY_HISTORY_PATH,FC_HISTORY_MESSAGE_LEN);
	return;
}

void readFileLastPart(char *filePath,void *buf,int len){
	char ch = 0;
	FILE *fp = NULL;
	int i = 0;
	fp = fopen(filePath,"r");
	if (!fp)
	 	return ;
	fseek(fp,0,SEEK_END);
	i = ftell(fp);
	if(i < len + 2){
		fclose(fp);
		return;
	}
	fseek(fp,i-2-len,SEEK_SET);
	fread(buf,len,1,fp);
	fclose(fp);
}

void deleteFileLastPart(char *filePath,int len){
	char ch = 0;
	FILE *fp1 = NULL;
	int i = 0;
	fp1 = fopen(filePath,"a");
	if (!fp1)
	 	return ;
	fseek(fp1, 0, SEEK_END);
	i = ftell(fp1);
	int a=fileno(fp1);
	if(i >= 2+len)
		ftruncate(a,i-2-len);
	fclose(fp1);
}

#if 0

void upGradeProg(char *buf){
	whole_device_info deviceInfo;
	int i = 0;
	deviceInfo = getDeviceInfo();
	deviceInfo.upGradeType = buf[0];
	for(i = 0 ; i < 128 ; i ++){
		deviceInfo.ftpUrl[i] = buf[1 +i];
	}

	deviceInfo.portNum = buf[129];
	deviceInfo.portNum = deviceInfo.portNum << 8 | buf[130];

	for(i = 0 ; i < 20 ; i ++){
		deviceInfo.userName[i] = buf[131 + i];
	}

	for(i = 0 ; i < 20 ; i ++){
		deviceInfo.passWord[i] = buf[151 + i];
	}

	for(i = 0 ; i < 32 ; i ++){
		deviceInfo.md5SumNum[i] = buf[171 + i];
	}
	
	switch(deviceInfo.upGradeType){
		case ALL_IN_ONE_PROG:{
			for(i = 0 ; i < 20 ; i ++)
				deviceInfo.softwareVersion[i] = buf[103 + i];
		}break;

		case POWER_PORT_PROG:{
			for(i = 0 ; i < 20 ; i ++)
				deviceInfo.powerPortVersion[i] = buf[103 + i];
		}break;

		case CHARGE_PORT_PROG:{
			for(i = 0 ; i < 20 ; i ++)
				deviceInfo.chargePortVersion[i] = buf[103 + i];
		}break;

		default:break;
	}

	setWholeDeviceInfo(deviceInfo);
	return;
}




void activeonfirm(int gunNum,char *buf){
	if(buf[1] == 0)
		activeUpLoadFrame(gunNum);
	return;
}

#endif

void checkTimeData(char *buf){
	int i = 0;
	whole_device_info deviceInfo;

	deviceInfo = getDeviceInfo();
	for(i = 0 ; i < 7 ; i ++){
		deviceInfo.checkTime[i] = buf[i];
	}
	setWholeDeviceInfo(deviceInfo);
	
	checkTimeFrame(0,checkTimeResult);
	
	return;
}

void vinChargeData(int gunNum,char *buf){
	int i = 0;
	int k = 0;
	if(buf[i ++] != 0)
		return;
	
	userAccountInfo accountInfo;

	accountInfo = getUserAccountInfo(gunNum);
	for(k = 0 ; k < 20 ; k ++){
		accountInfo.accountNum[k] = buf[i ++];
	}
	accountInfo.accountMoney = buf[i ++];
	accountInfo.accountMoney = accountInfo.accountMoney << 8 |buf[i ++];
	accountInfo.accountMoney = accountInfo.accountMoney << 8 |buf[i ++];
	accountInfo.accountMoney = accountInfo.accountMoney << 8 |buf[i ++];

	for(k = 0; k < 32 ; k ++){
		accountInfo.cloudTradeNum[k] = buf[i ++];
	}

	accountInfo.stopVerifyCode = buf[i ++];
	accountInfo.stopVerifyCode = accountInfo.stopVerifyCode << 8 | buf[i ++];
	lockUserAccount(accountInfo,gunNum);
	
	return;
}

#if 0
void manualChargeData(int gunNum,char *buf){
	if(buf[0] != 0)
		return;

//	int i = 0;
	userAccountInfo accountInfo;
	chargerBlockInfo chargerInfo;

	accountInfo = getUserAccountInfo(gunNum);
	accountInfo.accountMoney = buf[1];
	accountInfo.accountMoney = accountInfo.accountMoney << 8 |buf[2];
	accountInfo.accountMoney = accountInfo.accountMoney << 8 |buf[3];
	accountInfo.accountMoney = accountInfo.accountMoney << 8 |buf[4];
	lockUserAccount(accountInfo,gunNum);

	chargerInfo = getChargerBlockInfo(gunNum);
	chargerInfo.chargingList[0] = buf[5];
	chargerInfo.chargingList[1] = buf[6];
	chargerInfo.chargingList[2] = buf[7];
	chargerInfo.chargingList[3] = buf[8];
	lockChargerInfo(chargerInfo,gunNum);

	accountInfo = getUserAccountInfo(gunNum);
	accountInfo.stopVerifyCode = buf[9];
	accountInfo.stopVerifyCode = accountInfo.stopVerifyCode << 8 | buf[10];
	lockUserAccount(accountInfo,gunNum);
	
	return;
}
#endif

void costRateRulesData(unsigned char *buf){
	int i = 0;
	int k = 0;
	int startNum = 0;
	int timeSpan = 0;
//	int continueNum = 0;
	cost_rules_info costRulesInfo;

	costRulesInfo = getCostRulesInfo();
	for(k = 0 ; k < 10 ; k ++){
		costRulesInfo.costRulesVersion[k] = buf[i ++];
	}
//	costRulesInfo.sectionNum = buf[i ++];

	startNum =  buf[i ++];
	timeSpan = buf[i ++];

	for(k = 0 ; k < timeSpan ; k ++){
		costRulesInfo.costPrice[startNum + k] = buf[i ++];
		costRulesInfo.costPrice[startNum + k] <<= 8;
		costRulesInfo.costPrice[startNum + k] |= buf[i ++];
		costRulesInfo.costPrice[startNum + k] <<= 8;
		costRulesInfo.costPrice[startNum + k] |= buf[i ++];
		costRulesInfo.costPrice[startNum + k] <<= 8;
		costRulesInfo.costPrice[startNum + k] |= buf[i ++];

		costRulesInfo.servicePrice[startNum + k] = buf[i ++];
		costRulesInfo.servicePrice[startNum + k] <<= 8;
		costRulesInfo.servicePrice[startNum + k] |= buf[i ++];
		costRulesInfo.servicePrice[startNum + k] <<= 8;
		costRulesInfo.servicePrice[startNum + k] |= buf[i ++];
		costRulesInfo.servicePrice[startNum + k] <<= 8;
		costRulesInfo.servicePrice[startNum + k] |= buf[i ++];
		
	}

	addChargeRulesData(&costRulesInfo);
#if 0 

	for(i = 0 ; i <48 ; i ++){
		costRulesInfo.segmentTime[i] = buf[11 + i * 3];
		costRulesInfo.segmentTime[i] = costRulesInfo.segmentTime[i] << 8 | buf[12 + i * 3];
		costRulesInfo.segmentFlag[i]  = buf[13 + i * 3];
	}

//	continueNum = 14 + i * 3;
    //set charge price 

	for(i = 0 ; i < FENG_CHARGE_SEGMENT ; i ++){
		costRulesInfo.costPrice[i] = buf[continueNum + i * FENG_CHARGE_SEGMENT];
		costRulesInfo.costPrice[i] = costRulesInfo.costPrice[i] << 8 | buf[continueNum + 1 + i * FENG_CHARGE_SEGMENT];
		costRulesInfo.costPrice[i] = costRulesInfo.costPrice[i] << 8 | buf[continueNum + 2 + i * FENG_CHARGE_SEGMENT];
		costRulesInfo.costPrice[i] = costRulesInfo.costPrice[i] << 8 | buf[continueNum + 3 + i * FENG_CHARGE_SEGMENT];
	}

	continueNum = continueNum + 4 + i * FENG_CHARGE_SEGMENT;

	for(i = 0 ; i < FENG_CHARGE_SEGMENT ; i ++){
		costRulesInfo.servicePrice[i] = buf[continueNum + i * FENG_CHARGE_SEGMENT];
		costRulesInfo.servicePrice[i] = costRulesInfo.servicePrice[i] << 8 | buf[continueNum + 1 + i * FENG_CHARGE_SEGMENT];
		costRulesInfo.servicePrice[i] = costRulesInfo.servicePrice[i] << 8 | buf[continueNum + 2 + i * FENG_CHARGE_SEGMENT];
		costRulesInfo.servicePrice[i] = costRulesInfo.servicePrice[i] << 8 | buf[continueNum + 3 + i * FENG_CHARGE_SEGMENT];
	}
#endif
	
	
#if 0
	costRulesInfo.sectionNum  = buf[13];
	costRulesInfo.costRules[buf[13]].startTime= buf[11];
	costRulesInfo.costRules[buf[13]].startTime = costRulesInfo.costRules[buf[13]].startTime << 8 |buf[12];

	costRulesInfo.costRules[buf[16]].startTime = buf[14];
	costRulesInfo.costRules[buf[16]].startTime = costRulesInfo.costRules[buf[16]].startTime << 8 |  buf[15];

	costRulesInfo.costRules[buf[19]].startTime = buf[17];
	costRulesInfo.costRules[buf[19]].startTime = costRulesInfo.costRules[buf[19]].startTime << 8 | buf[18];

	costRulesInfo.costRules[buf[22]].startTime = buf[20];
	costRulesInfo.costRules[buf[22]].startTime=costRulesInfo.costRules[buf[22]].startTime << 8 |  buf[21];
	
	costRulesInfo.costRules[0].electricPrice = buf[23];
	costRulesInfo.costRules[0].electricPrice = costRulesInfo.costRules[0].electricPrice << 8 |buf[24];
	costRulesInfo.costRules[0].electricPrice = costRulesInfo.costRules[0].electricPrice << 8 |buf[25];
	costRulesInfo.costRules[0].electricPrice = costRulesInfo.costRules[0].electricPrice << 8 |buf[26];

	costRulesInfo.costRules[1].electricPrice = buf[27];
	costRulesInfo.costRules[1].electricPrice = costRulesInfo.costRules[1].electricPrice << 8 |buf[28];
	costRulesInfo.costRules[1].electricPrice = costRulesInfo.costRules[1].electricPrice << 8 |buf[29];
	costRulesInfo.costRules[1].electricPrice = costRulesInfo.costRules[1].electricPrice << 8 |buf[30];

	costRulesInfo.costRules[2].electricPrice = buf[31];
	costRulesInfo.costRules[2].electricPrice = costRulesInfo.costRules[2].electricPrice << 8 |buf[32];
	costRulesInfo.costRules[2].electricPrice = costRulesInfo.costRules[2].electricPrice << 8 |buf[33];
	costRulesInfo.costRules[2].electricPrice = costRulesInfo.costRules[2].electricPrice << 8 |buf[34];

	costRulesInfo.costRules[3].electricPrice = buf[35];
	costRulesInfo.costRules[3].electricPrice = costRulesInfo.costRules[3].electricPrice << 8 |buf[36];
	costRulesInfo.costRules[3].electricPrice = costRulesInfo.costRules[3].electricPrice << 8 |buf[37];
	costRulesInfo.costRules[3].electricPrice = costRulesInfo.costRules[3].electricPrice << 8 |buf[38];

	costRulesInfo.costRules[0].servicePrice = buf[39];
	costRulesInfo.costRules[0].servicePrice = costRulesInfo.costRules[0].servicePrice << 8 |buf[40];
	costRulesInfo.costRules[0].servicePrice = costRulesInfo.costRules[0].servicePrice << 8 |buf[41];
	costRulesInfo.costRules[0].servicePrice = costRulesInfo.costRules[0].servicePrice << 8 |buf[42];

	costRulesInfo.costRules[1].servicePrice = buf[43];
	costRulesInfo.costRules[1].servicePrice = costRulesInfo.costRules[1].servicePrice << 8 |buf[44];
	costRulesInfo.costRules[1].servicePrice = costRulesInfo.costRules[1].servicePrice << 8 |buf[45];
	costRulesInfo.costRules[1].servicePrice = costRulesInfo.costRules[1].servicePrice << 8 |buf[46];

	costRulesInfo.costRules[2].servicePrice = buf[47];
	costRulesInfo.costRules[2].servicePrice = costRulesInfo.costRules[2].servicePrice << 8 |buf[48];
	costRulesInfo.costRules[2].servicePrice = costRulesInfo.costRules[2].servicePrice << 8 |buf[49];
	costRulesInfo.costRules[2].servicePrice = costRulesInfo.costRules[2].servicePrice << 8 |buf[50];

	costRulesInfo.costRules[3].servicePrice = buf[51];
	costRulesInfo.costRules[3].servicePrice = costRulesInfo.costRules[3].servicePrice << 8 |buf[52];
	costRulesInfo.costRules[3].servicePrice = costRulesInfo.costRules[3].servicePrice << 8 |buf[53];
	costRulesInfo.costRules[3].servicePrice = costRulesInfo.costRules[3].servicePrice << 8 |buf[54];
	
#endif
	setCostRulesInfo(costRulesInfo);
	return;
}


#if 0
void answerPowerOutPut(int gunNum,char *buf){
	
	if(buf[0] == 0xff && buf[1] == 0xff && buf[2] == 0xff && buf[3] == 0xff)
		return;

	chargerBlockInfo chargerInfo;
	
	chargerInfo = getChargerBlockInfo(gunNum);
	chargerInfo.outputPower = buf[0];
	chargerInfo.outputPower = chargerInfo.outputPower << 8 |buf[1];
	chargerInfo.outputPower = chargerInfo.outputPower << 8 |buf[2];
	chargerInfo.outputPower = chargerInfo.outputPower << 8 |buf[3];
	lockChargerInfo(chargerInfo,gunNum);
	
	return;
}


void setPowerOutPut(int gunNum,char *buf){
	if(buf[0] == 0)
		return;

	chargerBlockInfo chargerInfo;
	
	chargerInfo = getChargerBlockInfo(gunNum);
	chargerInfo.outputPower = buf[1];
	chargerInfo.outputPower = chargerInfo.outputPower  <<  8 |buf[2];
	chargerInfo.outputPower = chargerInfo.outputPower <<  8 |buf[3];
	chargerInfo.outputPower = chargerInfo.outputPower << 8 |buf[4];
	lockChargerInfo(chargerInfo,gunNum);
	
	return;
}
#endif

void parseFengChongRecvData(char cmdNum,int gunNum,char *getBuf){
	TRACE_PROJ_SOCKET_INFO("##########   parseFengChongRecvData   ########### \n");
//	int i = 0;
	switch(cmdNum){
		case SIGN_ON_DOWN:{
			isSign = getBuf[0];
			printf("  isSign = %d\n",isSign);
		}break;

		case HEART_BEAT_DOWN:{
			printf("recv heart beat\n");
	//		heartBeatConfiirm(getBuf);
		}break;

		case START_CHARGE_DOWN:{
			isStartChargeControl(gunNum,getBuf);
		}break;

		case ST_RESULT_CONFIRM:{

		}break;

		case CARD_REQUEST_DOWN:{
			cardResultConfirm(gunNum,getBuf);
		}break;

		case REAL_DATA_DOWN:{

		}break;

		case HISTORY_DOWN:{
			historyConfiurm(gunNum,getBuf);
		}break;

		case UP_GRADE_DOWN:{
//			upGradeProg(getBuf);
		}break;

		case UP_RESULT_CONFIRM_DOWN:{

		}break;
		
		case POS_SEND_DATA_DOWN:{
			printf(" recv pos data  gunNum = %d\n",gunNum);
		}break;

		case CHECK_TIME_DOWN:{
			checkTimeData(getBuf);
		}break;

		case VIN_CHARGE_DOWN:{
			vinChargeData(gunNum,getBuf);
		}break;


//		case MANUAL_CHARGE_DOWN:{
//			manualChargeData(gunNum,getBuf);
//		}break;

		case COST_RULES_DOWN:{
			costRateRulesData((unsigned char*)getBuf);
		}break;

//		case POWER_OUTPUT_LIMIT_DOWN:{
//			answerPowerOutPut(gunNum,getBuf);
//		}break;

//		case POS_POWER_LIMIT_DOWN:{
//			setPowerOutPut(gunNum,getBuf);
//		}break;

		case OFF_LINE_CHECK_DOWN:{   

		}break;

		case OFF_LINE_RULES_DOWN:{

		}break;

		case OFF_LINE_DELETE_DOWN:{

		}break;

		case OFF_LINE_CONTROL_DOWN:{

		}break;

		case OUTPUT_CONTROL_DOWN:{

		}break;

		default:break;
	}
	
	return;
}

void judgeFrameIntegrity(char *getBuf ,int recvLen){
	// TRACE_PROJ_SOCKET_INFO("#######  judgeFrameIntegrity  #########\n");
	TRACE_PROJ_SOCKET_INFO("%d\n",recvLen);
	int len = 0;
	int i = 0;
	int k = 0;
	char databuf[500] = {0};
	char dealBuf[500] = {0};
	short recvCrc = 0;
	for(i = 0 ; i < recvLen ; i ++){
		if(getBuf[i] == FRAME_HEAD_H && getBuf[i + 1] == FRAME_HEAD_L){
			for(k = 0 ; k < (recvLen - i) ; k ++){
				databuf[k] = getBuf[i + k];
				if(databuf[k] == FRAME_TAIL){
					len = databuf[2];
					len <<= 8;
					len |= databuf[3];
					if(k + 1 >= len)
						break;
				}
			}
			
			recvCrc = CRC16((unsigned char*)databuf,(len - 3));
			if(databuf[len - 3] != (recvCrc >> 8 & 0xff)  ||databuf[len - 2] != (recvCrc & 0xff) ){
				continue;
			}
			for(k = 0 ; k < (len - FRAME_HEAD_LEN) ; k ++){
				dealBuf[k] = databuf[k + 34];
				// printf("############  dealBuf[%d] = 0x%x\n",k,dealBuf[k]);
				printf("0x%x ",dealBuf[k]);
			}
			parseFengChongRecvData( databuf[CMD_ADDR],databuf[GUN_NUM_ADDR],dealBuf);
		}
	}
	
	return;
}

void *fengChongRecv(){
	TRACE_PROJ_SOCKET_INFO("#########    fengChongRecv    ########## \n");
	int ret = 0;
	fd_set rset;
	int recvLength = 0;
	char recvBuf[SOCKET_DATA_LEN] = {0};
	while(1){
		if(!isConnect){
			mSleep(10);
			printf(" fengChongRecv connect error \n");
			isSign = 0;
		
			connectFengChong();
			continue;
		}
		memset(recvBuf,0,SOCKET_DATA_LEN);
		FD_ZERO(&rset);
	         FD_SET(fcFd, &rset);
		ret = select(fcFd+1, &rset, NULL, NULL, NULL);

		  if ((ret == EBADF) || (ret == EINTR)) {
	//	   	   printLogToFile("ret == EBADF");
			   TRACE_PROJ_SOCKET_INFO("ret == EBADF \n");
		   	   isConnect = false;
		   }
		  recvLength = recv(fcFd, recvBuf, SOCKET_DATA_LEN,0);
		  if(recvLength == -1){
			 mSleep(10); 
			 printf("######  recv error  ######\n");
			 continue;
		  }
		  judgeFrameIntegrity(recvBuf,recvLength);
		  mSleep(50);
	}
	return NULL;
}

void fengChongTimer(){
	int i = 0;
	static int fengchongClick = 0;
	fengchongClick++;								//++per100ms
	judgeConnected();
	
	if(!isConnect){
		isSign = 0;
		if(!(fengchongClick%10))
			connectFengChong();
	}
	else{
		if(!isSign ){
			if(!(fengchongClick%100))
			clientUpLoad();
		}
		else{
			if(!(fengchongClick%300))
				heartBeat();	
			for(i = 0 ; i < MAX_GUN_NUM ; i ++){
				if(getChargerBlockInfo(i).isStartCharge == WORK_STATE){
					if(!(fengchongClick%300-10)){
						chargeRealDataFrame(i);
					}
					if(gunWorkBuf[i] == 0){
						gunWorkBuf[i] = 1;
					}
				}else{
					if(gunWorkBuf[i] == 1){
						gunWorkBuf[i] = 0;
						historyFrame(i);
						mSleep(5);
						historyUpFrame();
					}
					// historyFrame(i);
			//		activeUpLoadFrame(i);
					// mSleep(1000);
				}
			}
			if(!(fengchongClick%100-20))
				historyUpFrame();

		}
	}
	mSleep(100);
}

void initFengChong(){
	TRACE_PROJ_SOCKET_INFO("#########  initFengChong  #############\n");
//	pthread_mutex_init(&fengChongLock,NULL);

	

#if	1
	connectFengChong();

	mSleep(300);
	clientUpLoad();
	create_thread(NULL,fengChongRecv,15);
	create_thread(NULL,fengChongTimer,15);
	// initFengChongTimerList = proj_Timer_Init("fengChongTimer");
	// initFengChongTimerId = proj_Timer_Add(initFengChongTimerList,"fengChongTimer",fengChongTimer,NULL,1000,1);
#endif	
	return;
}
