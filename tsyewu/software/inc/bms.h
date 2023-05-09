#ifndef _BMS_H__
#define _BMS_H__

typedef struct {
	int can_id;      /* 32 bit CAN_ID + EFF/RTR/ERR flags */
    	unsigned char    length; /* data length code: 0 .. 8 */
    	unsigned char    data[8] __attribute__((aligned(8)));
}canFrame;

void bms();

void bmsSendTest();

void initBmsTest();

#endif
