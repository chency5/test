#include <stdio.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <linux/socket.h>
#include <linux/can.h>
#include <linux/can/error.h>
#include <linux/can/raw.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include "can_device.h"
#include "projdebug.h"

#ifndef AF_CAN
#define AF_CAN 29
#endif
#ifndef PF_CAN
#define PF_CAN AF_CAN
#endif


#define myerr(str)	fprintf(stderr, "%s, %s, %d: %s\n", __FILE__, __func__, __LINE__, str)
#define errout(_s)	fprintf(stderr, "error class: %s\n", (_s))
#define errcode(_d) fprintf(stderr, "error code: %02x\n", (_d))

static void handle_err_frame(const struct can_frame *fr)
{
	if (fr->can_id & CAN_ERR_TX_TIMEOUT) 
	{
		errout("CAN_ERR_TX_TIMEOUT");
	}
	if (fr->can_id & CAN_ERR_LOSTARB)
	 {
		errout("CAN_ERR_LOSTARB");
		errcode(fr->data[0]);
	}
	if (fr->can_id & CAN_ERR_CRTL) 
	{
		errout("CAN_ERR_CRTL");
		errcode(fr->data[1]);
	}
	if (fr->can_id & CAN_ERR_PROT) 
	{
		errout("CAN_ERR_PROT");
		errcode(fr->data[2]);
		errcode(fr->data[3]);
	}
	if (fr->can_id & CAN_ERR_TRX)
	 {
		errout("CAN_ERR_TRX");
		errcode(fr->data[4]);
	}
	if (fr->can_id & CAN_ERR_ACK)
	 {
		errout("CAN_ERR_ACK");
	}
	if (fr->can_id & CAN_ERR_BUSOFF)
	 {
		errout("CAN_ERR_BUSOFF");
	}
	if (fr->can_id & CAN_ERR_BUSERROR) 
	{
		errout("CAN_ERR_BUSERROR");
	}
	if (fr->can_id & CAN_ERR_RESTARTED)
	 {
		errout("CAN_ERR_RESTARTED");
	}
}


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
int configCanDevice(char* deviceName) {
    TRACE_CAN_INFO("config can device  250kps or 125kps\n");
	//system();
    return 0;
}


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
int openCanDevice(char* deviceName){
	TRACE_CAN_INFO("open can device\n");
	int s;
    int ret;
    struct sockaddr_can addr;
    struct ifreq ifr;
    s = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (s < 0) {
        perror("socket PF_CAN failed");
        return -1;
    }
    strcpy(ifr.ifr_name, deviceName);
    ret = ioctl(s, SIOCGIFINDEX, &ifr);
    if (ret < 0) {
        perror("ioctl failed");
        return -1;
    }

    addr.can_family = PF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    ret = bind(s, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) {
        perror("bind failed");
        return -1;
    }
    return s;
}



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
int setFilerType(int fd, int level, int optname,const void *optval, int  optlen){
	TRACE_CAN_INFO("set can filter rules \n");
	int ret;
    ret = setsockopt(fd, level, optname, optval, optlen);
    if (ret < 0){
	    perror("setsockopt failed");
        return -1;
	}
	return ret;
}	

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
int customerSlxFiler(int bms_fd, int module_fd ){
	TRACE_CAN_INFO("customerSlxFiler \n");
	int ret;
    struct can_filter filterBms[2];
	filterBms[0].can_id = 0x56f4 | CAN_EFF_FLAG;
	filterBms[0].can_mask = 0xFFFF;
    filterBms[1].can_id = 0x20F | CAN_EFF_FLAG;
	filterBms[1].can_mask = 0xFFF;
    ret = setsockopt(bms_fd, SOL_CAN_RAW, CAN_RAW_FILTER, &filterBms, sizeof(filterBms));

#if 0
    struct can_filter filterModule[2];
	filterModule[0].can_id = 0x18000000 | CAN_EFF_FLAG;
	filterModule[0].can_mask = 0xFFF00000;
    filterModule[1].can_id = 0x20F | CAN_EFF_FLAG;
	filterModule[1].can_mask = 0xFFF;	
	ret = setsockopt(module_fd, SOL_CAN_RAW, CAN_RAW_FILTER, &filterModule, sizeof(filterModule));
#endif

	if (ret < 0) {
		perror("customerSlxFiler failed");
		return -1;
	}
	return ret;
}




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
int sendData(int fd, void* buf,int len) {
    TRACE_CAN_INFO("send data fd=%d\n",fd);
    int ret; 
	struct can_frame* fr = buf;
	fr->can_id |= CAN_EFF_FLAG;

    ret = write(fd,fr,len);
    if (ret < 0){
       myerr("write failed");
       return -1;
    }
    return ret;
}


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
int receiveData(int fd, void* buf,int len) {
    TRACE_CAN_INFO("[can module] revice data 001 fd=%d\n",fd);
    int ret;
    struct can_frame *frdup;
	
    ret = read(fd,buf,len);
	TRACE_CAN_INFO("[can module] revice data  002 fd=%d\n",fd);
    if (ret < len){
	    myerr("read failed");
	    return -1;
    }
	frdup = buf;
	frdup->can_id = frdup->can_id & CAN_EFF_MASK;
	TRACE_CAN_INFO("[can module] revice data  003 fd=%d\n",fd);
    if (frdup->can_id & CAN_ERR_FLAG) {
	    handle_err_frame(frdup);
	    myerr("CAN device error");
    }
    return ret;
}

