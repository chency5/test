#ifndef __PROJ_UTILY__
#define __PROJ_UTILY__
#include <stdio.h>
#include "projdebug.h"
#define true 1
#define false 0
#define SLX_DEBUG 0
#define LOG_FILE   "/opt/.record/loggle" 


typedef struct {
        int begin;
        int end;
}swapSpace;

typedef struct {
	unsigned char array0;
	unsigned char array1;
	unsigned char array2;
	unsigned char array3;
}swapContainer;

typedef struct{
	short year;
	char month;
	char day;
	char hour;
	char minute;
	char sec;
}localTimeInfo;

typedef struct{
	int param;
	int times;
	int timeOut;
	int (*startFun)(int param);
	int (*stopFun)(int param);
	void (*fun)(int param);
}delay_timer_info;


void Message( const char*  fmt, ... );

/**
*   @ingroup 	
*   @fn			int create_thread(void *param,void *(*callback) (void *));
*   @brief 		create_pthread
*   @param[in]	param
*   @param[in]	callback
*	@return int
* 
*  Description
*  
* @if bug_display
*  	Bug1.
*  	...
* @endif
*  
* @if warning_display
*  	Warning1. 
*  	...
* @endif
*/
void create_thread(void *param,void *(*callback)(void *),int Priority);

/**
*   @ingroup 	
*   @fn			int gettimesec();
*   @brief 		 //获取时间->sec
*   @param[in]	param
*	@return int
* 
*  Description
*  
* @if bug_display
*  	Bug1.
*  	...
* @endif
*  
* @if warning_display
*  	Warning1. 
*  	...
* @endif
*/


int gettimesec();





/**
*   @ingroup 	
*   @fn			int gettimemin();
*   @brief 		 //获取时间->sec
*   @param[in]	param
*	@return int
* 
*  Description
*  
* @if bug_display
*  	Bug1.
*  	...
* @endif
*  
* @if warning_display
*  	Warning1. 
*  	...
* @endif
*/
int gettimemin();


/**
*   @ingroup 	
*   @fn			int gettimehour();
*   @brief 		 //获取时间->sec
*   @param[in]	param
*	@return int
* 
*  Description
*  
* @if bug_display
*  	Bug1.
*  	...
* @endif
*  
* @if warning_display
*  	Warning1. 
*  	...
* @endif
*/
int gettimehour() ;

localTimeInfo getTimeInfo();


char * getCurrentTime();




/**
*   @ingroup 	
*   @fn			void mSleep(int ms) 
*   @brief 		 // 毫秒级延时
*   @param[in]	param
*	@return void
* 
*  Description
*  
* @if bug_display
*  	Bug1.
*  	...
* @endif
*  
* @if warning_display
*  	Warning1. 
*  	...
* @endif

*/
void mSleep(int ms);

int mySystem(char * strCmd,char *saveBuf,int len);

void TimeSyncInstruction(char *timeBuf);

void timestempToTimeDate(int timestamp,char *timeDate);

unsigned int stringToHex(char* buf);

unsigned int stringToDec(char* buf);

int hexToInt(unsigned char temp1,unsigned char temp2,unsigned char temp3,unsigned char temp4);

short hexToShort(unsigned char temp1, unsigned char temp2);

void hexToStr(const char *sSrc,  char *sDest, int nSrcLen);

int bcdToDec(int bcd);

int decToBcd(int dec);

void strIpToNumIp(char *srcIp,int *distIp);


void printLogToFile(char * buffer);

unsigned long get_file_size(const char *path);

unsigned long fileRowValue(char *file);

void startDelayTimer(void(*fun)(int param),int param,int times,int timeInterval,int (*startFun)(),int (*stopFun)());

void shieldSig();

char * getLocalIp(char *ipName);

long long getCurrentTimeMs();
long long getCurrentTimeSingleMs();

swapSpace packageFrameData(int input);

#define getLowByte(value)   ((value) & 0xff) //提取一个变量的低位（最右边）字节
#define getHighByte(value)   ((value) >> 8)  //提取一个字节的高位（最左边的），或一个更长的字节的第2低位
#define getBitValue(value, pos)   (((value) >> (pos)) & 0x01)  //读取一个数的位
#define bitSet(value, pos)   ((value) |= (1UL << (pos)))   //置pos位的值，即pos位置1
#define bitClear(value, pos)  ((value) &= ~(1UL << (pos))) //清除bit位，即bit位置0
#define bitWrite(value, pos, bitvalue) (bitvalue ? bitSet(value, pos) : bitClear(value, pos)) //写bit位的值，1或者0
#define myerr(str)	fprintf(stderr, "%s, %s, %d: %s\n", __FILE__, __func__, __LINE__, str)

#endif
