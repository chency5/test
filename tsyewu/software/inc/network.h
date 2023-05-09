#ifndef _NET_WORK_H__
#define _NET_WORK_H__


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


typedef struct{
	int socket;
	int remote_port;
	char remoteIp[20];
	struct sockaddr_in addr;
	bool isConnect;
}netWorkClient;


#endif
