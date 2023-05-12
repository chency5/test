#ifndef   __FENG_CHONG_H_
#define   __FENG_CHONG_H_



#define START_CHARGE       1
#define STOP_CHARGE          0


#define FRAME_HEAD_H              0x4b
#define FRAME_HEAD_L              0x48
#define FRAME_TAIL                     0x68

#define DEVICE_ID                         0x0001

#define SIGN_ON_UP                                  0x01
#define SIGN_ON_DOWN                           0x81

#define HEART_BEAT_UP                           0x02
#define HEART_BEAT_DOWN                    0x82

#define START_CHARGE_DOWN                           0x0A
#define START_CHARGE_CONFIRM_UP             0x8A
#define START_CHARGE_RESULT_UP                0x0B
#define ST_RESULT_CONFIRM                                0x8B

#define CARD_REQUEST_UP                                  0x0C
#define CARD_REQUEST_DOWN                           0x8C

#define REAL_DATA_UP                                           0x0D
#define REAL_DATA_DOWN                                    0x8D

#define HISTORY_UP                       0x0E
#define HISTORY_DOWN                0x8E

#define UP_GRADE_DOWN                                    0x11
#define UP_GRADE_CONFIRM_UP                      0x91
#define UP_GRADE_RESULT_UP                         0x12
#define UP_RESULT_CONFIRM_DOWN              0x92


#define POS_SEND_DATA_UP                   0x13
#define POS_SEND_DATA_DOWN            0x93

#define CHECK_TIME_DOWN                        0x1B
#define CHECK_TIME_UP                               0x9B

#define VIN_CHARGE_UP                          0x1D
#define VIN_CHARGE_DOWN                   0x9D

#define MANUAL_CHARGE_UP                   0x1E
#define MANUAL_CHARGE_DOWN            0x9E


#define COST_RULES_DOWN                             0x1F
#define COST_RULES_UP                                    0x9F

#define POWER_OUTPUT_LIMIT_UP                            0x21
#define POWER_OUTPUT_LIMIT_DOWN                     0xA1

#define POS_POWER_LIMIT_DOWN                                    0x22
#define POS_POWER_LIMIT_UP                                           0xA2

#define OFF_LINE_CHECK_DOWN                         0x23
#define OFF_LINE_CHECK_UP                                0xA3

#define OFF_LINE_RULES_DOWN                          0x24
#define OFF_LINE_RULES_UP                                 0xA4

#define OFF_LINE_DELETE_DOWN                               0x25
#define OFF_LINE_DELETE_UP                                      0xA5

#define OFF_LINE_CONTROL_DOWN          0x3E
#define OFF_LINE_CONTROL_UP                 0xBE

#define OUTPUT_CONTROL_DOWN       0x3F
#define OUTPUT_CONTROL_UP              0xBF

#define BMS_MES_UP									0x40
#define BMS_MES_DOWN							0xC0

#define FC_HISTORY_MESSAGE_LEN				402

typedef struct{
	char controlType;
	char orderNum[35];
}feng_chong_data;

//void judgeFrameIntegrity();
void readFileLastPart(char *filePath,void *buf,int len);
void deleteFileLastPart(char *filePath,int len);
void initFengChong();

#endif