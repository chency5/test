#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>


#include "socket.h"
#include "uart.h"
#include "timer.h"
#include "type.h"
#include "init.h"
#include "projdebug.h"
#include "utily.h"
#include "proj_timer.h"
#include "systemconfig.h"
#include "datacenter.h"
#include "yunwei.h"
#include "fengchong.h"
#include "xiaoju_app.h"
//#include "gooseport.h"


void init(){
	int i = 0;
        printf("\n");
		TRACE_PROJ_SOCKET_INFO("this is init###################\n");
        printf("##################\n");
		
	shieldSig();
	
	initHistoryRecord();
	sleep(2);
	tsConfigInit();
//	sleep(1);
//	setDeviceIp("169.254.99.100");
	sleep(1);
	printf("### %s \n",getLocalIp("eth0"));

	 initFengChong();
//	gooseInitFunction();
//	xiaoJuInit();
	// yunWeiInit();
#if 0
	for(i = 0 ; i < 20 ; i ++){
		sendTestData();
		sleep(1);
	}
#endif
        return;
}

