#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>


#include "control.h"
#include "public.h"
#include "type.h"
#include "projdebug.h"
#include "proj_timer.h"
#include "init.h"
#include "bms.h"
#include "can_device.h"
#include "utily.h"


static int canFd = 0;
static canFrame controlFrame;

static unsigned long 		initModuleTimerList = 0;
static unsigned long 		initModuleTimerId = 0;

static void print(){
	TRACE_SOFT_INFO("control timer test\n");
	publicUsed();
	return;
}

void control(){
	printf("\n");
	printf("this is control file");
	printf("\n");
	public_test();
	typeTest(666);
	TRACE_SOFT_INFO("blue control ********\n");
	initModuleTimerList =  proj_Timer_Init("query");
        initModuleTimerId = proj_Timer_Add(initModuleTimerList,"query",print,NULL,1000,1);
	return;
}

void controlSendTest(){
	canFrame framedata;
	framedata.can_id = 0x18608f7f;
        framedata.length = 8;
        framedata.data[0] = 0x0a;
        framedata.data[1] = 0x0a;
        framedata.data[2] = 0x0a;
        framedata.data[3] = 0x0a;
        framedata.data[4] = 0x0a;
        framedata.data[5] = 0x0a;
        framedata.data[6] = 0x0a;
        framedata.data[7] = 0x0a;
        sendData(canFd,&framedata,sizeof(framedata));
	return;
}

void *controlRecvTest(){
	int moduleRet;
        fd_set rset;
        int ret;
        int i = 0;
        while(1){
//		printf("RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR\n");
//		usleep(500*1000);
#if 1
                FD_ZERO(&rset);
                FD_SET(canFd, &rset);
                ret = select(canFd+1, &rset, NULL, NULL, NULL);
                if (ret == 0) {
                       printf("select module callback time out \n");
                       continue;
                }
                moduleRet = receiveData(canFd, &controlFrame,sizeof(canFrame));
                printf("end receiver module data $$$$$$$$$$$$$$ canFd=%d\n",canFd);
                if(moduleRet < sizeof(controlFrame)) {
                        printf("receiveData module failed $$$$$$$$$$$$$$\n");
                        continue;
               }
               printf("controlFrame.can_id = 0x%x\n",controlFrame.can_id);
               printf("controlFrame.length = %d\n",controlFrame.length);
               for(i = 0 ; i < 8 ; i ++){
                        printf("--0x%x",controlFrame.data[i]);
               }
               printf("\n");
	       sleep(1);
#endif
        }
        return NULL;
}

void initControlTest(){
        canFd = openCanDevice("can1");
        printf("$$$$$$   canFd = %d\n",canFd);
        create_thread(NULL, controlRecvTest, 10);
        return;
}
