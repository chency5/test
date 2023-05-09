#ifndef  __XIAOJU_APP_H__
#define __XIAOJU_APP_H__

#define XIAOJU_BILL_PATH   "/opt/record/xiajubill"


#define CHARGER_READY      1
#define NORMAL_DATA            2



void doPlugIn(int gunNum);

void doPlugOut(int gunNum);

void doWarningLoad();

void xiaoJuInit();
#endif