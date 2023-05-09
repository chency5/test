#include <stdio.h>
#include "socket.h"
#include "log.h"
#include "timer.h"
#include "public.h"
#include "type.h"

void socket_test(){
        printf("\n");
	int b = 0;
	b = getA();
	printf("*******  b = %d *******\n",b);
        printf("this is socket file");
        printf("\n");

	public_test();
	typeTest(888);
        return;
}

