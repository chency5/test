#include <stdio.h>
#include "uart.h"
#include "projdebug.h"

void uart(){
        printf("\n");
        printf("this is uart file");
	TRACE_PROJ_HISTORY_INFO("new log print####################");
        printf("\n");
        return;
}

