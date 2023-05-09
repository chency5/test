#ifndef __SLX__CAN_DEVICE__
#define __SLX__CAN_DEVICE__
#include <stdio.h>



/**
*   @ingroup 	
*   @fn		int configCanDevice(char* deviceName);	
*   @brief 		config can device
*   @param[in]	deviceName
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
int configCanDevice(char* deviceName);

/**
*   @ingroup 	
*   @fn		int openCanDevice()	
*   @brief 		open can device
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
int openCanDevice(char* deviceName);



/**
*   @ingroup 	
*   @fn		int setFilerType()	
*   @brief 		open can device
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
int setFilerType(int fd, int level, int optname,const void *optval, int optlen);



/**
*   @ingroup 	
*   @fn		int sendData()	
*   @brief 		open can device
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
int sendData(int fd, void* buf,int len);



/**
*   @ingroup 	
*   @fn		int receiveData()	
*   @brief 		open can device
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
int receiveData(int fd, void* buf,int len);



/**
*   @ingroup 	
*   @fn		int customerSlxFiler()	
*   @brief 		open can device
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
int customerSlxFiler(int bms_fd, int module_fd );


#endif

