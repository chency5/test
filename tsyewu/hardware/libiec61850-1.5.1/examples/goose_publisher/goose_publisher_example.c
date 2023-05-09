/*
 * goose_publisher_example.c
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include "mms_value.h"
#include "goose_publisher.h"
#include "hal_thread.h"

/* has to be executed as root! */
int
main(int argc, char **argv)
{
    char *interface;

    if (argc > 1)
        interface = argv[1];
    else
        interface = "eth0";

    int sendNum = 100;

    printf("Using interface %s        sendNum =  %d  \n", interface,sendNum);

    LinkedList dataSetValues = LinkedList_create();

    LinkedList_add(dataSetValues, MmsValue_newIntegerFromInt32(1234));

	LinkedList_add(dataSetValues, MmsValue_newIntegerFromInt32(4321));

	LinkedList_add(dataSetValues, MmsValue_newIntegerFromInt32(5678));

	LinkedList_add(dataSetValues, MmsValue_newIntegerFromInt32(6789));

//    printf("1111111  dataSetValues->data = %s\n",(char*)MmsValue_newIntegerFromInt32(1234));

  //  LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
	
    LinkedList_add(dataSetValues, MmsValue_newVisibleString("abcdefg"));
    
 //   LinkedList_add(dataSetValues, MmsValue_newIntegerFromInt32(sendNum));

    CommParameters gooseCommParameters;

    gooseCommParameters.appId = 1000;
    gooseCommParameters.dstAddress[0] = 0x01;
    gooseCommParameters.dstAddress[1] = 0x0c;
    gooseCommParameters.dstAddress[2] = 0xcd;
    gooseCommParameters.dstAddress[3] = 0x01;
    gooseCommParameters.dstAddress[4] = 0x00;
    gooseCommParameters.dstAddress[5] = 0x01;
    gooseCommParameters.vlanId = 0;
    gooseCommParameters.vlanPriority = 4;

    /*
     * Create a new GOOSE publisher instance. As the second parameter the interface
     * name can be provided (e.g. "eth0" on a Linux system). If the second parameter
     * is NULL the interface name as defined with CONFIG_ETHERNET_INTERFACE_ID in
     * stack_config.h is used.
     */
    GoosePublisher publisher = GoosePublisher_create(&gooseCommParameters, interface);

    if (publisher) {
        GoosePublisher_setGoCbRef(publisher, "simpleIOGenericIO/LLN0$GO$gcbAnalogValues");
        GoosePublisher_setConfRev(publisher, 1);
        GoosePublisher_setDataSetRef(publisher, "simpleIOGenericIO/LLN0$AnalogValues");
        GoosePublisher_setTimeAllowedToLive(publisher, 500);

        int i = 0;

        for (i = 0; i < 4; i++) {
            Thread_sleep(1000);
	  LinkedList_add(dataSetValues, MmsValue_newIntegerFromInt32(sendNum));
	   sendNum ++;
	   printf("111111111111111   sendNum = %d   \n",sendNum);
            if (i == 3) {
                /* now change dataset to send an invalid GOOSE message */
                LinkedList_add(dataSetValues, MmsValue_newBoolean(true));
 //               GoosePublisher_publish(publisher, dataSetValues);
            }
    //        else {
   //             if (GoosePublisher_publish(publisher, dataSetValues) == -1) {
    //               printf("Error sending message!\n");
      //          }
  //          }
        }

	if (GoosePublisher_publish(publisher, dataSetValues) == -1) {
                   printf("Error sending message!\n");
                }

        GoosePublisher_destroy(publisher);
    }
    else {
        printf("Failed to create GOOSE publisher. Reason can be that the Ethernet interface doesn't exist or root permission are required.\n");
    }

    LinkedList_destroyDeep(dataSetValues, (LinkedListValueDeleteFunction) MmsValue_delete);

    return 0;
}




