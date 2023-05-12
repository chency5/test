#ifndef _NET_CONNECT_H__
#define _NET_CONNECT_H__

typedef struct{
	int netFd;
	int servicePort;
	int sendCount;
	bool isLogOn;
	bool isConnect;
	char serviceIp[20];
	void (*dealfun)(char *buf,int length);
}net_connect_info;

void netConnectMalloc();
int tcpNetWorkSend(char *sendBuf,int bufLen);

net_connect_info *ctrlNetConnectInfo();

void netConnectInit();


#endif
