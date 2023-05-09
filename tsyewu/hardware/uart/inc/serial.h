#ifndef __SLX_SERIAL__
#define __SLX_SERIAL__
#include <stdbool.h>
typedef struct {
   char port[128];
   char settings[128];
   int timeout;
   int handle;
   int baudrate;
   int debug;
   int portid;
}serialNativeData;

#define MAX_SERIAL_COUNT 8
#define DW_HANDLE        0
#define ICARD_HANDLE     1
#define AMMETER_HANDLE   2
#define GPIO_EXTEND   3
#define GPRD_EXTEND  4


/**
*   @ingroup 	
*   @fn			int init(const char* _port, const char* _settings, int _debug, int _timeout);
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
int initSerial(int type, const char* _port, const char* _settings, int _debug, int _timeout);


/**
*   @ingroup 	
*   @fn			int openSerial();
*   @brief 		open serial
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
int openSerial(int type);


/**
*   @ingroup 	
*   @fn			bool change(const char* _settings, int _debug = -1, int _timeout = 1000);
*   @brief 		change serial config param
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
bool change(int type, const char* _settings, int _debug, int _timeout);


/**
*   @ingroup 	
*   @fn			int send(char* buffer, int length)
*   @brief 		send serial data
*   @param[in]	buffer
*   @param[in]	length
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
int sendSerial(int type, char* buffer, int length);


/**
*   @ingroup 	
*   @fn			int recv(char* buffer, int length)
*   @brief 		receive data
*   @param[in]	buffer
*   @param[in]	length
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
int recvSerial(int type,char* buffer, int length);


/**
*   @ingroup 	
*   @fn			void close()
*   @brief 		close dev
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
void closeSerial(int type);


/**
*   @ingroup 	
*   @fn			void setInternal
*   @brief 		
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
bool setInternal(int type);


/**
*   @ingroup 	
*   @fn			int waitReadable(int millis);
*   @brief 		
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
int waitReadable(int type, int millis);



/**
*   @ingroup 	
*   @fn			int waitWritable(int millis)
*   @brief 		
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
int waitWritable(int type, int millis);




/**
*   @ingroup 	
*   @fn			int getBaudrate();
*   @brief 		
*   @param[in]	
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
int getBaudrate(int type);


/**
*   @ingroup 	
*   @fn			void setDebugMode(int val)
*   @brief 		
*   @param[in]	val
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
void setDebugMode(int type, int val);
#endif
