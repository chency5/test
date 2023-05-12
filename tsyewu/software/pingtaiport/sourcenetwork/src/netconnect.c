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

#include "netconnect.h"
#include "projdebug.h"
#include "utily.h"
#include "proj_timer.h"
#include "systemconfig.h"
#include "crc.h"


#define MAX_COUNT_NUM                    65536
#define TCP_NET_BUF_LEN                  900 


static unsigned long 		initNetConnectTimerList = 0;
static unsigned long 		initNetConnectTimerId = 0;


net_connect_info *connectInfo;


static void tcpNetWorkConnect(){
	TRACE_PROJ_SOCKET_INFO("################   tcpNetWorkConnect   #################\n");
	if(connectInfo->netFd){
		close(connectInfo->netFd);
		connectInfo->netFd = 0;
	}
	// printf("01010101010101010101010\n");
	struct sockaddr_in  servaddr;
	 if((connectInfo->netFd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
	 	TRACE_PROJ_SOCKET_INFO("tcpNetWork creat socket error : %s(errno: %d)\n",strerror(errno),errno);
		return;
	 }
	 memset(&servaddr, 0, sizeof(servaddr));
          servaddr.sin_family = AF_INET;
         servaddr.sin_port = htons(1895);   //connectInfo->servicePort
	//if(inet_pton(AF_INET, controlConfigInfo()->serviceIp, &servaddr.sin_addr) <= 0){                                                        /*connectInfo->serviceIp   120.24.38.57 controlConfigInfo()->yunWeiIp tan gong test  192.168.8.136*/ 
	// printf("0000000000000000000000\n");
	if(inet_pton(AF_INET, "120.24.38.57", &servaddr.sin_addr) <= 0){ 
		TRACE_PROJ_SOCKET_INFO("tcpNetWork inet_pton error for\n");
		connectInfo->isConnect = false;
	    	return;
    }
	// printf("11111111111111111111111111111\n");
	if(connect(connectInfo->netFd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
		TRACE_PROJ_SOCKET_INFO("tcpNetWork connect error: %s(errno: %d)\n",strerror(errno),errno);
		connectInfo->isConnect = false;
		return;
	}
	printf("connectInfo->netFd = %d\n",connectInfo->netFd);
	printf("connectInfo->isConnect = true\n");
	connectInfo->isConnect = true;
	return;
} 

static void  tcpNetWorkJudgeConnected() {
	if (connectInfo->netFd < 0)
		return ;
	
	struct tcp_info info;
	int len = sizeof(info);
	getsockopt(connectInfo->netFd,IPPROTO_TCP,TCP_INFO,&info,(socklen_t *)&len);
	if (info.tcpi_state == TCP_ESTABLISHED){
		connectInfo->isConnect = true;
		return ;
	}else{
	         TRACE_PROJ_SOCKET_INFO("socket disconnected \n");
		//printLogToFile("socket disconnected");
		connectInfo->isConnect = false;
		return ;
         }
	return ;
}

int tcpNetWorkSend(char *sendBuf,int bufLen){
	if(!connectInfo->isConnect || !sendBuf)
		return false;

	int ret = 0;
	ret = send(connectInfo->netFd,sendBuf,bufLen,0);
	if(ret == -1){
		printf("@@@    send error!  @@@@\n");
		connectInfo->isConnect = false;
		connectInfo->sendCount = 0;
		return 1;
	}
	connectInfo->sendCount ++;
	if(connectInfo->sendCount >= MAX_COUNT_NUM)
		connectInfo->sendCount = 0;
	return 0;
}


void *tcpNetWorkRecv(){
	TRACE_PROJ_SOCKET_INFO("#########    tcpNetWorkRecv    ########## \n");
	int ret = 0;
	fd_set rset;
	int recvLength = 0;
	char recvBuf[TCP_NET_BUF_LEN] = {0};
	while(1){
		if(!connectInfo->isConnect ){
			mSleep(10);
			printf("   connect error  \n");
			tcpNetWorkConnect();
			if(connectInfo->isLogOn)
				connectInfo->isLogOn = false;
			continue;
		}
		memset(recvBuf,0,TCP_NET_BUF_LEN);
		 recvLength = 0;
		FD_ZERO(&rset);
	         FD_SET(connectInfo->netFd, &rset);		
		ret = select(connectInfo->netFd+1, &rset, NULL, NULL, NULL);
		if(ret == 0){
			 TRACE_PROJ_SOCKET_INFO("select time out  \n");
			 mSleep(300);
			 continue;
		}
		if ((ret == EBADF) || (ret == EINTR)) {
			 printf("   judge connect error  \n");
			 TRACE_PROJ_SOCKET_INFO("ret == EBADF \n");
		   	 connectInfo->isConnect = false;
		 }

		recvLength = recv(connectInfo->netFd, recvBuf, TCP_NET_BUF_LEN,0);
		if(recvLength == -1){
			mSleep(10); 
			printf("   recv error  \n");
			continue;
		}
		printf("test3\n");
		connectInfo->dealfun(recvBuf,recvLength);
		mSleep(100);
	}
	
	return NULL;
}


net_connect_info *ctrlNetConnectInfo(){
	return connectInfo;
}

void netConnectMalloc(){
 connectInfo = (net_connect_info*)malloc(sizeof(net_connect_info));
 if(connectInfo == NULL){
  TRACE_PROJ_ERROR("connectInfo malloc error");
  return;
 }
}

void netConnectInit(){
	
	printf("netConnectInit\n");
	tcpNetWorkConnect();
	mSleep(50);
	create_thread(NULL,tcpNetWorkRecv,15);


	initNetConnectTimerList = proj_Timer_Init("netConnectTimer");
	initNetConnectTimerId = proj_Timer_Add(initNetConnectTimerList,"netConnectTimer",tcpNetWorkJudgeConnected,NULL,1000,1);
	
	return;
}

