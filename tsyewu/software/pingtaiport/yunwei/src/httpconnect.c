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


#include "socket_cJSON.h"
#include "yunwei.h"
#include "datacenter.h"
#include "projdebug.h"
#include "utily.h"
#include "proj_timer.h"
#include "systemconfig.h"
#include "crc.h"
#include "modbus_protocol.h"

#include "curl.h"


static int httpFd = 0;
//static bool isHttpConnect = false;
#if 0
static void connectHttpConnect(http_connect_info httpInfo){
	TRACE_PROJ_SOCKET_INFO("################   connectYunWei   #################\n");
	if(httpFd){
		close(httpFd);
		httpFd = 0;
	}
	
	struct sockaddr_in  servaddr;
	 if((httpFd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
	 	TRACE_PROJ_SOCKET_INFO("yunwei creat socket error : %s(errno: %d)\n",strerror(errno),errno);
		return;
	 }

	 memset(&servaddr, 0, sizeof(servaddr));
          servaddr.sin_family = AF_INET;
         servaddr.sin_port = htons(httpInfo.httpPort);

	if(inet_pton(AF_INET,httpInfo.httpIp, &servaddr.sin_addr) <= 0){                                                        /* 120.24.38.57 controlConfigInfo()->yunWeiIp          "192.168.8.136"*/
		TRACE_PROJ_SOCKET_INFO("yunwei inet_pton error for\n");
		isHttpConnect = false;
	    	return;
           }

	if(connect(httpFd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
		TRACE_PROJ_SOCKET_INFO("yunwei connect error: %s(errno: %d)\n",strerror(errno),errno);
		isHttpConnect = false;
		return;
	}
	isHttpConnect = true;
	return;
} 

#if 0

static void  httpConnectJudgeConnected() {
	if (httpFd < 0)
		return ;
	
	struct tcp_info info;
	int len = sizeof(info);
	getsockopt(httpFd,IPPROTO_TCP,TCP_INFO,&info,(socklen_t *)&len);
	if (info.tcpi_state == TCP_ESTABLISHED){
		isHttpConnect = true;
		return ;
	}else{
	         TRACE_PROJ_SOCKET_INFO("socket disconnected \n");
		//printLogToFile("socket disconnected");
		isHttpConnect = false;
		return ;
         }
	return ;
}

#endif

static bool   httpConnectSend(char *sendBuf,int bufLen){
	printf("this is yunWeiSend bufLen = %d \n",bufLen);
	if(!isHttpConnect || !sendBuf)
		return false;


	int ret = 0;
	ret = send(httpFd,sendBuf,bufLen,0);
	if(ret == -1){
		printf("@@@    send error!  @@@@\n");
		isHttpConnect = false;
		return false;
	}
	
	return true;
}

void sendHttpPostFile(http_connect_info httpInfo,char* filePath){
//	printf(" #####  this is sendHttpPostFile  #####\n");
	if(!isHttpConnect)
		return;
	
	long int totalsize = 0;
	long int retLen = 0;
	long long int timeStamp = 0;
	unsigned long int fileSize = 0;
	char httpBoundary[100] = {0};
	char sendRequest[500] = {0};
	char headerBuf[1500] = {0};
	char endBuf[200] = {0};
	char *httpRequest = NULL;
	char *fileBuf = NULL;
	struct timeval tv;
	gettimeofday(&tv,NULL);
	timeStamp = (long long int)tv.tv_sec * 1000000 + tv.tv_usec;
	fileSize = get_file_size(filePath);
	sprintf(httpBoundary,"--------------------------%lld",timeStamp);
	retLen = sprintf(sendRequest,UPLOAD_REQUEST,httpBoundary,LOCAL_LOG_NAME);
	totalsize += retLen;
//	printf("requestLen = %d\n",strlen());
	retLen = sprintf(endBuf,"\r\n--%s--\r\n",httpBoundary);
	totalsize += retLen;
	totalsize += fileSize;
	
	retLen = sprintf(headerBuf,HTTP_HEAD,httpInfo.hostBuf,httpInfo.postBuf,httpBoundary,totalsize);
	
	totalsize += retLen;
	httpRequest = (char *)malloc(totalsize + 200);
	if(httpRequest == NULL)
		return;

	fileBuf =  (char *)malloc(fileSize + 100);
	if(fileBuf == NULL)
		return;
	
	httpRequest[0] = '\0';
	strcat(httpRequest,headerBuf);
	strcat(httpRequest,sendRequest);
	
	FILE *p = NULL;
	p = fopen(filePath,"r");
	if(p == NULL){
		fclose(p);
		return;
	}
	fread(fileBuf,fileSize,1,p);
	strcat(httpRequest,fileBuf);
	strcat(httpRequest,endBuf);
	

//	printf("  \n  totalsize = %d---%d \n",totalsize,strlen(httpRequest));
	
//	char sBuf[2000] = {0};
//	int len = sprintf(sBuf,EXAMPLE_HEADER,httpInfo.hostBuf,httpInfo.postBuf,"xxx.txt",fileBuf);
//	printf("##########  sBuf    =   %s\n",sBuf);
	
//	httpConnectSend(sBuf,len);
	
	
	httpConnectSend(httpRequest,totalsize);

	free(httpRequest);
	free(fileBuf);
	fclose(p);
	p = NULL;
	return;
}

#endif

/*****   use libcurl  ****/


#if 0
static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *stream){
	 size_t retcode;
	 curl_off_t nread;

	    /* in real-world cases, this would probably get this data differently as this fread() stuff is exactly what the library already would do by default internally */

	retcode = fread(ptr, size, nmemb, stream);

   	 nread = (curl_off_t)retcode;

    	printf( "*** We read %lld CURL_FORMAT_CURL_OFF_Tbytes from file\n", nread);
   	 return retcode;

}


int curlSendFun(http_connect_info httpInfo){
    	CURL *curl;
    	CURLcode res;
    	FILE * fstream;
   	 struct stat file_info;
	struct curl_slist  *headers = NULL;
    /* get the file size of the local file */

   	 stat(HISTORY_PATH, &file_info);
   	 fstream = fopen(HISTORY_PATH, "rb");
	 
    	 curl_global_init(CURL_GLOBAL_ALL);
   
    /* get a curl handle */

    	curl = curl_easy_init();
    	if (!curl)
       		 return -1;


    /* specify URL */

   	 curl_easy_setopt(curl, CURLOPT_URL, httpInfo.urlAddr);

	headers = curl_slist_append(headers,httpInfo.clientId);

	headers = curl_slist_append(headers,httpInfo.usrUniqueFlag);

	headers = curl_slist_append(headers,httpInfo.certData);

	curl_easy_setopt(curl,CURLOPT_HTTPHEADER,headers);

	curl_easy_setopt(curl,CURLOPT_POST,1);

    /* we want to use our own read function */

    	curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);

    /* which file to upload */

   	 curl_easy_setopt(curl, CURLOPT_READDATA, (void *) fstream);

    /* enable "uploading" */

    	curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

    /* Set the size of the file to upload (optional) */

   	 curl_easy_setopt(curl,CURLOPT_INFILESIZE_LARGE, (curl_off_t)file_info.st_size);

    /* set commom option */

   	 curl_easy_setopt (curl,CURLOPT_SSL_VERIFYPEER, 0L);

    	curl_easy_setopt (curl,CURLOPT_SSL_VERIFYHOST, 0L);

    	curl_easy_setopt (curl,CURLOPT_SSLCERT,"client.crt");

    	curl_easy_setopt (curl, CURLOPT_SSLCERTTYPE, "PEM");

    	curl_easy_setopt (curl, CURLOPT_SSLKEY,"client.key");

    	curl_easy_setopt (curl, CURLOPT_SSLKEYTYPE,"PEM");

    	curl_easy_setopt (curl,CURLOPT_TIMEOUT, 60L);
		
    	curl_easy_setopt (curl,CURLOPT_CONNECTTIMEOUT, 10L);
		
   	res = curl_easy_perform(curl);
    	if (res !=CURLE_OK)
        		printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));


    	if(fstream)
       	fclose(fstream);
    	curl_easy_cleanup(curl);
	curl_slist_free_all(headers);
    	curl_global_cleanup();

   	 return 0;

}
#endif

int curlSendFun(http_connect_info httpInfo){

	  CURL *curl;

	  CURLcode res;  

	  struct curl_httppost *formpost=NULL;

	  struct curl_httppost *lastptr=NULL;

	  struct curl_slist *headerlist=NULL;

//	  static const char buf[] = "Expect:";  

	char headBuf[100] = {0};

	  curl_global_init(CURL_GLOBAL_ALL);  

	  /* Fill in the file upload field */

	  curl_formadd(&formpost,
	               &lastptr,
	               CURLFORM_COPYNAME, "file",
	               CURLFORM_FILE, HISTORY_PATH,
	               CURLFORM_CONTENTTYPE,"application/octet-stream",
	               CURLFORM_END);  

	  /* Fill in the filename field */

	  curl_formadd(&formpost,
	               &lastptr,
	               CURLFORM_COPYNAME, "filename",
	               CURLFORM_COPYCONTENTS, "history",
	               CURLFORM_CONTENTTYPE,"application/octet-stream",
	               CURLFORM_END);   

	  /* Fill in the submit field too, even if this is rarely needed */

	  curl_formadd(&formpost,
	               &lastptr,
	               CURLFORM_COPYNAME, "submit",
	               CURLFORM_COPYCONTENTS, "Submit",
	               CURLFORM_END);  

	 
	  curl = curl_easy_init();

	  /* initalize custom header list (stating that Expect: 100-continue is not

	     wanted */

//	  headerlist = curl_slist_append(headerlist, buf);

	  strcpy(headBuf,"Client-Id: ");
	  strcat(headBuf,httpInfo.clientId);
	  printf("@@@@@ httpInfo.clientId  headBuf= %s\n",headBuf);
	  headerlist = curl_slist_append(headerlist,headBuf);
	  
	
//	  headerlist = curl_slist_append(headerlist,httpInfo.clientId);
	 memset(headBuf,0,sizeof(headBuf));
	  strcpy(headBuf,"User-Key: ");
	  strcat(headBuf,httpInfo.usrUniqueFlag);
	  printf("@@@@@ httpInfo.usrUniqueFlag  headBuf= %s\n",headBuf);

	  headerlist = curl_slist_append(headerlist,headBuf);

	   memset(headBuf,0,sizeof(headBuf));
	  strcpy(headBuf,"File-Token: ");
	  strcat(headBuf,httpInfo.certData);
	  printf("@@@@@ httpInfo.certData  headBuf= %s\n",headBuf);

	  headerlist = curl_slist_append(headerlist,headBuf);

	

	  if(curl) {

	    /* what URL that receives this POST */  
		
		    curl_easy_setopt(curl, CURLOPT_URL,  httpInfo.urlAddr);

	//	    if ( (argc == 2) && (!strcmp(argv[1], "noexpectheader")) )

		      /* only disable 100-continue header if explicitly requested */

		     curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);

		     curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);  

		    /* Perform the request, res will get the return code */

		    res = curl_easy_perform(curl);

		    /* Check for errors */

		    if(res != CURLE_OK)

			     printf( "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));  

			    /* always cleanup */

			    curl_easy_cleanup(curl);  

			    /* then cleanup the formpost chain */

			    curl_formfree(formpost);

			    /* free slist */

			    curl_slist_free_all (headerlist);

	  }

	  return 0;

}  



/*****   end libcurl *****/


#if 0
void parseHttpJsonData(char *jsonData){
	if(NULL == jsonData)
		return;
	
     	cJSON * root = cJSON_Parse(jsonData);
		
	if(root == NULL)
		return;

	cJSON *itemRoot = NULL;
	cJSON *item = NULL;
	int codeData = 0;
	
	itemRoot = cJSON_GetObjectItem(root,"data");
	if(item == NULL)
		return;
	
	item = cJSON_GetObjectItem(itemRoot,"code");
	if(item == NULL)
		return;
	codeData = item->valueint;

	if(codeData == 3){
		sleep(3);
		yunWeiSendLogUpLoad(LOCAL_LOG,0);
	}
		
	
	return;
}

void httpConnectRecv(){
	TRACE_PROJ_SOCKET_INFO("#########    httpConnectRecv    ########## \n");
	int ret = 0;
//	int i = 0;
	fd_set rset;
	int recvLength = 0;
	char recvBuf[YUNWEI_BUF_LEN] = {0};
	
	if(!isHttpConnect){
		mSleep(10);
		printf("   connect error  \n");
//		connectHttpConnect();
		return;
	}
	memset(recvBuf,0,YUNWEI_BUF_LEN);
	 recvLength = 0;
	FD_ZERO(&rset);
         FD_SET(httpFd, &rset);		 
	ret = select(httpFd+1, &rset, NULL, NULL, NULL);
	if(ret == 0){
		 TRACE_PROJ_SOCKET_INFO("select time out  \n");
		 mSleep(300);
		 return;
	}
	  if ((ret == EBADF) || (ret == EINTR)) {
		   printf("   judge connect error  \n");
		   TRACE_PROJ_SOCKET_INFO("ret == EBADF \n");
	   	   isHttpConnect = false;
		   return;
	   }

	  recvLength = recv(httpFd, recvBuf, YUNWEI_BUF_LEN,0);
	  if(recvLength == -1){
		 mSleep(10); 
		 printf("   recv error  \n");
	  }
	  parseHttpJsonData(recvBuf);
//	  printf("   httpConnectRecv     recvLength = %d\n",recvLength);

//	  printf("recvBuf = %s",recvBuf);
	
	return ;
}

#endif

void httpConnectInit(http_connect_info httpInfo){
//	connectHttpConnect(httpInfo);
//	mSleep(500);
//	sendHttpPostFile(httpInfo,LOG_FILE);
	curlSendFun(httpInfo);
	mSleep(500);
//	startDelayTimer(httpConnectRecv,0,20,1500,NULL,NULL);
	close(httpFd);
	httpFd = 0;
	return;
}

