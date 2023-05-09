#include <pthread.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include<signal.h>


#include "utily.h"


static FILE* logFd;
static struct timeval curtime;
static struct timeval curMsTime;
localTimeInfo timeInfo;

static char  timeBuf[10];

delay_timer_info delayTimerInfo;

static pthread_mutex_t timerInfoLock = PTHREAD_MUTEX_INITIALIZER;

void Message( const char*  fmt, ... )
{
	va_list  ap;
	va_start( ap, fmt );
	vprintf( fmt, ap );
	va_end( ap );
}

void create_thread(void *param,void *(*callback)(void *),int Priority)
{
    pthread_t id;
    int stacksize = 5*1024*1024; /*thread 堆栈设置为1024K，stacksize以字节为单位。*/
    pthread_attr_t attr;  
     					    		
    pthread_attr_init(&attr); /*初始化线程属性*/
    pthread_attr_setstacksize(&attr, stacksize);

#if 1
	if (Priority > 0) {
        struct sched_param sparam;

        if (Priority < sched_get_priority_min(SCHED_RR))
            Priority = sched_get_priority_min(SCHED_RR);

        if (Priority > sched_get_priority_max(SCHED_RR))
            Priority = sched_get_priority_max(SCHED_RR);

            sparam.sched_priority = Priority;
            pthread_attr_setschedpolicy(&attr, SCHED_RR);
            pthread_attr_setschedparam(&attr, &sparam);
    }
#endif	    
    if (pthread_create(&id, &attr, callback, (void*)param) == 0){
    	    pthread_detach(id);
    }	   
	return;	    
}


int gettimesec()   //获取时间->sec
{
     struct tm *t;
     time_t tt;
     time(&tt);
     t=localtime(&tt);
     return t->tm_sec;
}

int gettimemin()   //获取时间->sec
{
     struct tm *t;
     time_t tt;
     time(&tt);
     t=localtime(&tt);
     return t->tm_min;
}

int gettimehour()   //获取时间->sec
{
     struct tm *t;
     time_t tt;
     time(&tt);
     t=localtime(&tt);
     return t->tm_hour;
}

char *getCurrentTime(){
	 struct tm *t;
    	 time_t tt;
    	 time(&tt);
    	 t=localtime(&tt);
	memset(timeBuf,0,sizeof(timeBuf));
	sprintf(timeBuf,"%d%02d%02d%02d%02d%02d",t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
	return timeBuf;
}


localTimeInfo getTimeInfo(){
	struct tm *t;
	time_t tt;
	time(&tt);
	t=localtime(&tt);
	timeInfo.year = t->tm_year+1900;
	timeInfo.month = t->tm_mon+1;
	timeInfo.day = t->tm_mday;
	timeInfo.hour = t->tm_hour;
	timeInfo.minute = t->tm_min;
	timeInfo.sec = t->tm_sec;
	return timeInfo;
}

void mSleep(int ms) // 毫秒级延时
{
   struct timeval delay;
   delay.tv_sec = 0;
   delay.tv_usec = ms * 1000;
   select(0, NULL, NULL, NULL, &delay);
   return;
}

int mySystem(char * strCmd,char *saveBuf,int len){
	FILE *p = NULL;
//	char saveBuf[200];
	int ret = 0;
	p = popen(strCmd,"r");
	if(p == NULL){
		perror("popen");
		return 1;
	}
	fgets(saveBuf,len,p);
	if(saveBuf[strlen(saveBuf) - 1] == '\n')
		saveBuf[strlen(saveBuf) - 1] = '\0';

	ret = pclose(p);
	if(WIFEXITED(ret))
		return 0;
	return 1;
}

void TimeSyncInstruction(char *timeBuf){  // timeBuf = date -s "20220607 10:52:00"
	char buf[30];
	sprintf(buf,"%s %s","date -s",timeBuf);
	system(buf);
	system("hwclock -w");
	return;
}

void timestempToTimeDate(int timestamp,char *timeDate){   // transform time format is 20220607 10:52:00
	char timeCmd[100] = {0};
	sprintf(timeCmd,"date -d@%d +%c%s%c",timestamp,'"',"%Y%m%d %H:%M:%S",'"');
	mySystem(timeCmd,timeDate,50);
	return;
}


unsigned int stringToHex(char* buf)
{
       return (unsigned int)strtol(buf, NULL, 16);//十六进制 
}


unsigned int stringToDec(char* buf)
{
       return (unsigned int)strtol(buf, NULL, 10);//十六进制 
}

int hexToInt(unsigned char temp1,unsigned char temp2,unsigned char temp3,unsigned char temp4){
       int data=0;
       data=temp1;
       data<<=8;
       data|=temp2;
       data<<=8;
       data|=temp3;
       data<<=8;
       data|=temp4;   
       return data;
} 



short hexToShort(unsigned char temp1, unsigned char temp2) {
	    short data=0;
        data=temp1;
        data<<=8;
        data|=temp2;
        return data;
}


swapSpace packageFrameData(int input) {
	char array[5] = {0};
	char swap[3] = {0};
	swapSpace swap_space;
	memset(&swap_space,0,sizeof(swapSpace));
         sprintf(array,"%04x",input);	
	swap[0] = array[2];
	swap[1] = array[3];
	swap_space.end = stringToHex(swap);	
	memset(&swap,0,3);
	swap[0] = array[0];
	swap[1] = array[1];
	swap_space.begin = stringToHex(swap);
	return swap_space;
}

#if 1

swapContainer DecToHexChar(int swap) {
//	int temp;
	swapContainer container;
         memset(&container,0,sizeof(container));
	container.array0 = swap & 0xff;
	container.array1 = (swap >> 8) & 0xff;
	container.array2 = (swap >> 16) & 0xff;
	container.array3 = (swap >> 24) & 0xff;
	
	char ch[35] = {0};
	unsigned int c;
	sprintf(ch,"%d",container.array0);
	sscanf(ch,"%2x",&c);
	container.array0 = c;
	
         c = 0;
	memset(ch,0,32);
	sprintf(ch,"%d",container.array1);
	sscanf(ch,"%2x",&c);
	container.array1 = c;

	c = 0;
	memset(ch,0,32);
	sprintf(ch,"%d",container.array2);
	sscanf(ch,"%2x",&c);
	container.array2 = c;

	c = 0;
	memset(ch,0,32);
	sprintf(ch,"%d",container.array3);
	sscanf(ch,"%2x",&c);
	container.array3 = c;

	return container;
}

#endif
void hexToStr(const char *sSrc,  char *sDest, int nSrcLen){
    int  i;
    char szTmp[3] = {0};

    for( i = 0; i < nSrcLen; i++ )
    {
        sprintf( szTmp, "%02X", (unsigned char) sSrc[i] );
        memcpy( &sDest[i * 2], szTmp, 2 );
    }
    return;
}

int bcdToDec(int bcd){
	return (bcd - (bcd>>4)*6);
}

int decToBcd(int dec){
	return (dec + (dec/10)*6);
}

void strIpToNumIp(char *srcIp,int *distIp){
	int n = 0;
	char *p = NULL;
	p = strtok(srcIp,".");
	while(p != NULL){
		distIp[n] = atoi(p);
		n ++;
		p = strtok(NULL,".");
	}
	return;
}

void printLogToFile(char * buffer) {
	logFd = fopen(LOG_FILE,"a+");
	if (logFd) {
		fprintf(logFd, "%s  %s \n",getCurrentTime(),buffer);
		fclose(logFd);
	}	
	return;
}

unsigned long get_file_size(const char *path)  //??????
{    
    unsigned long filesize = -1;        
    struct stat statbuff;    
    if(stat(path, &statbuff) < 0){    
        return filesize;    
    }else{    
        filesize = statbuff.st_size;    
    }    
    return filesize;    
}  


unsigned long fileRowValue(char *file){
     int c, lc=0;                    //c\u4e3a\u6587\u4ef6\u5f53\u524d\u5b57\u7b26\uff0clc\u4e3a\u4e0a\u4e00\u4e2a\u5b57\u7b26\uff0c\u4f9b\u7ed3\u5c3e\u5224\u65ad\u7528\u3002
     short line = 0;                 //\u884c\u6570\u7edf\u8ba1
     FILE *fpRow = NULL; 
	 
     fpRow = fopen(file, "r");       //\u4ee5\u53ea\u8bfb\u65b9\u5f0f\u6253\u5f00\u6587\u4ef6\u3002
     if (!fpRow)
	 	return 0;
    while((c = fgetc(fpRow)) != EOF)    //\u9010\u4e2a\u8bfb\u5165\u5b57\u7b26\u76f4\u5230\u6587\u4ef6\u7ed3\u5c3e
    {
        if(c == '\n') line ++;       //\u7edf\u8ba1\u884c\u6570\u3002
        lc = c;                     //\u4fdd\u5b58\u4e0a\u4e00\u5b57\u7b26\u3002
    }
    fclose(fpRow);                      //\u5173\u95ed\u6587\u4ef6
    fpRow = NULL;
    if((lc !=0)  &&  (lc != '\n'))   ++line;        //\u5904\u7406\u672b\u884c
    return line;
}


void *delayTimerFun(){
	if(delayTimerInfo.times == 0)
		return NULL;
//	int i = 0;
	int cnt = 0;
	int num = delayTimerInfo.times;
	while(num --){	
		if(delayTimerInfo.startFun){
			if(delayTimerInfo.startFun(delayTimerInfo.param) == 1)
				delayTimerInfo.fun(delayTimerInfo.param);
		}else{
			delayTimerInfo.fun(delayTimerInfo.param);
		}

		if(delayTimerInfo.stopFun)
			if(delayTimerInfo.stopFun(delayTimerInfo.param) == 1)
				return NULL;

		cnt ++;
		if(cnt * 200 >= delayTimerInfo.timeOut)
			return NULL;
		
	}
	return NULL;
}

void timerThread(){
	pthread_t id;
	if(pthread_create(&id,NULL,delayTimerFun,NULL) != 0){
		perror("creat error");
		exit(1);
	}
	pthread_join(id,NULL);
	return;
}

void startDelayTimer(void(*fun)(int param),int param,int times,int timeOut,int (*startFun)(int param),int (*stopFun)(int param)){
	pthread_mutex_lock(&timerInfoLock);
	delayTimerInfo.param = param;
	delayTimerInfo.times = times;
	delayTimerInfo.timeOut = timeOut;
	delayTimerInfo.fun = fun;
	delayTimerInfo.startFun = startFun;
	delayTimerInfo.stopFun = stopFun;
	timerThread();
	pthread_mutex_unlock(&timerInfoLock);
	return;
}

void shieldSig(){
	sigset_t signal_mask;
	sigemptyset(&signal_mask);
	sigaddset(&signal_mask,SIGPIPE);
	sigprocmask(SIG_BLOCK,&signal_mask,NULL);
#if 0
	int rc = pthread_sigmask(SIG_BLOCK,&signal_mask,NULL);
	if(rc!= 0)
		printf("block sigpipe error\n");
#endif
	return;
}


char * getLocalIp(char *ipName) {
	int inet_sock;
	struct ifreq ifr;
	inet_sock = socket(AF_INET, SOCK_DGRAM, 0);
	strcpy(ifr.ifr_name, ipName);
			 //SIOCGIFADDR\u6807\u5fd7\u4ee3\u8868\u83b7\u53d6\u63a5\u53e3\u5730\u5740
	if (ioctl(inet_sock, SIOCGIFADDR, &ifr) <	0)
		perror("ioctl");
	printf("%s\n", inet_ntoa(((struct sockaddr_in*)&(ifr.ifr_addr))->sin_addr));
	return inet_ntoa(((struct sockaddr_in*)&(ifr.ifr_addr))->sin_addr);
}

long long getCurrentTimeMs(){
	gettimeofday(&curtime,NULL);
	return 1000*curtime.tv_sec+curtime.tv_usec/1000;
}

long long getCurrentTimeSingleMs(){
	gettimeofday(&curMsTime,NULL);
	return curMsTime.tv_usec/1000;
}


//#define TEST
#ifdef TEST
int main(){
int value = 10;
printf("value=%d\n",value>>2&1);
printf("value=%d\n",value);

#endif
