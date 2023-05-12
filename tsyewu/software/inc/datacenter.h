#ifndef   __DATA_CENTER_H_
#define  __DATA_CENTER_H_

#include <stdbool.h>

#define OPT_PATH   "/opt"


#define HISTORY_PATH                              "/opt/record/history"
#define SUPPLY_HISTORY_PATH           "/opt/record/supply"

#define ONE_UPGRADE_PATH                     "/opt/record/upgrade_1"
#define TWO_UPGRADE_PATH                     "/opt/record/upgrade_2"
#define THREE_UPGRADE_PATH                     "/opt/record/upgrade_3"
#define FOUR_UPGRADE_PATH                     "/opt/record/upgrade_4"
#define FIVE_UPGRADE_PATH                     "/opt/record/upgrade_5"
#define SIX_UPGRADE_PATH                     "/opt/record/upgrade_6"
#define SEVEN_UPGRADE_PATH                     "/opt/record/upgrade_7"
#define EIGHT_UPGRADE_PATH                     "/opt/record/upgrade_8"
#define NINE_UPGRADE_PATH                     "/opt/record/upgrade_9"
#define TEN_UPGRADE_PATH                     "/opt/record/upgrade_10"
#define ELEVEN_UPGRADE_PATH                     "/opt/record/upgrade_11"
#define TWELVE_UPGRADE_PATH                     "/opt/record/upgrade_12"
#define THIRTEEN_UPGRADE_PATH                     "/opt/record/upgrade_13"
#define FOURTEEN_UPGRADE_PATH                     "/opt/record/upgrade_14"
#define FIFTEEN_UPGRADE_PATH                     "/opt/record/upgrade_15"
#define SIXTEEN_UPGRADE_PATH                     "/opt/record/upgrade_16"


#define CHARGE_RULES             "/opt/cost/charge_rules"

#define MAX_GUN_NUM                             16


#define FENG_CHONG                                     0x4b48
#define XIAO_JI                                                  0x1f9c

#define FENG_CHONG_STOP                        0x68

#define FENG_CHONG_RESERVE_ID         0x0001

#define ONE_GUN                                              0x00
#define TWO_GUN                                              0x01
#define THREE_GUN                                         0x02
#define FOUR_GUN                                           0x03
#define FIVE_GUN                                              0x04
#define SIX_GUN                                                0x05
#define SEVEN_GUN                                         0x06
#define EIGHT_GUN                                           0x07
#define NINE_GUN                                             0x08
#define TEN_GUN                                               0x09
#define ELEVEN_GUN                                       0x0a
#define TWELVE_GUN                                       0x0b
#define THIRTEEN_GUN                                    0x0c
#define FOURTEEN_GUN                                  0x0d
#define FIFTEEN_GUN                                        0x0e
#define SIXTEEN_GUN                                       0x0f


/********     stop reson from cloud *******/
#define APP_STOP                                 0x01
#define ACHIVE_TIME_STOP              0x02
#define ACHIVE_POWER_STOP        0x03
#define ACHIVE_COST_STOP            0x04
#define ACHIVE_SOC_STOP              0x05
#define COST_LOW_STOP                  0x06
#define MANUAL_STOP                       0x07


#define JIAN_SECTION                          0
#define FENG_SECTION                         1
#define PING_SECTION                          2
#define GU_SECTION                              3


#define GUN_TERMINAL_TEMP                        28


#define GET_LAST_TWO_BIT     0x03
#define SHIFT_LEFT_TWO           0x0c
#define SHIFT_LEFT_FOUR         0x30
#define SHIFT_LEFT_SIX              0xc0


#define IDEL_STATE       0
#define WORK_STATE    1


typedef enum{
	DEVICE_IDEL = 0,                            //idel state
	DEVICE_WORK,                             //work state
	DEVICE_FAULT,                             //fault state
	DEVICE_FREEZEN,                         // lock state 
	DEVICE_OVERHAUL,                          //need repair
	DEVICE_OPERATE_SET,               // operation setting
	RESTORE_FACTORY_SET           // restore factory setting
}deviceStateInfo;


typedef enum{
	ALL_IN_ONE_PROG,                          //integrated machine program,  at there is business program
	POWER_PORT_PROG,                      //power port program
	CHARGE_PORT_PROG,                   // charge port program
	MODULE_PROG,                                           // charge module program
	ENVIRONMENT_DETECT_PROG      // environment detcct program this is not charger's program
}deviceUpgradeType;

typedef struct{
	int powerTime[10];                 //output power timer
	int powerData[10];                // output power data
	int segNum;                           // total segment number
}chargePowerControlInfo;

typedef struct{
	char DCPowerState1_8;
	char DCPowerState9_16;
	char DCPowerState17_24;
	char DCPowerState25_32;
	char gunOutPutState1_8;
	char gunOutPutState9_16;
	char otherFault;
	char DCPowerModeFault_1;
	char DCPowerModeFault_2;
	char DCPowerModeFault_3;
	char DCPowerModeFault_4;
	char DCPowerModeFault_5;
	char DCPowerModeFault_6;
	char DCPowerModeFault_7;
	char DCPowerModeFault_8;
	char DCPowerModeFault_9;
	char DCPowerModeFault_10;
	char DCPowerModeFault_11;
	char DCPowerModeFault_12;
	char DCPowerModeFault_13;
	char DCPowerModeFault_14;
	char DCPowerModeFault_15;
	char DCPowerModeFault_16;
	char DCPowerModeFault_17;
	char DCPowerModeFault_18;
	char DCPowerModeFault_19;
	char DCPowerModeFault_20;
	char DCPowerModeFault_21;
	char DCPowerModeFault_22;
	char DCPowerModeFault_23;
	char DCPowerModeFault_24;
	char DCPowerModeFault_25;
	char DCPowerModeFault_26;
	char DCPowerModeFault_27;
	char DCPowerModeFault_28;
	char DCPowerModeFault_29;
	char DCPowerModeFault_30;
	char DCPowerModeFault_31;
	char DCPowerModeFault_32;
	char accessGunNum;
	char accessDcModeNum;
	short DcModeOutputPower;
}powerSideBaseInfo;

typedef struct{
//	char deviceNum[25];
	char softwareVersion[25];                       //       business side version
	char powerPortVersion[25];                   //        power side version
	char chargePortVersion[25];                 //        charger side version
	char ftpUrl[130];                                        //        ftp url addr
	char userName[25];                                 //        user name
	char passWord[25];                                  //        user pass word
	char md5SumNum[35];                          //         md5 number
	char checkTime[10];                              //         timeSyn
	char cloudDeviceNum[35];                  //         clould issued device number
	
	char upGradeState;                                    // upgrade state
	char isOnLine;                                             // whether or not on line
	char isOpenLog;                                         //whether or net open log function
	
	short portNum;	                                         // terminal port number     note its not the gun number

	powerSideBaseInfo powerBaseInfo;
	chargePowerControlInfo powerControl;   //set power cotrol
	deviceStateInfo deviceState;                       // device state
	int APhaseVol;                                   
	int APhaseCurrent;
	int BPhaseVol;
	int BPhaseCurrent;
	int CPhaseVol;
	int CPhaseCurrent;
	
//	checkTimeInfo checkTime; 
	deviceUpgradeType upGradeType;                  //upgrade type
}whole_device_info;




typedef struct{
	char resultState;                                      //issue result state
	char sectionNum;                                  //total section number
	char costRulesVersion[20];                //electricity billing model version
	char serviceRulesVersion[20];          //service billing model version    
	
	short  costType;                                  // it's definate the free , on line fee, off line fee

	int segmentFlag[50];                 //its at different time's tip peak flat valley 
	
	unsigned int segmentTime[50];   //every segment start time
	
	unsigned int costPrice[50];          // every segment electric price
	unsigned int servicePrice[50];     // every segment service price
	unsigned int DelayPrice[50];       // delay charge price
//	cost_rules costRules[50];
}cost_rules_info;

typedef struct{
	int chargePower;                //charge power
	int chargeCost;                  //electric cost
	int serviceCost;                //service cost
	int delayCost;                    // delay charge cost
}jfpgSetInfo;

typedef struct{
	char accountType;                         //user account type
	char measureUnit;                        //unit of measurement
	char cardState;                              // card state
	char isPay;                                       //pay or not
	char IdentifyResult;                       //authentication results
	char operateType;                        // operate type like start charge stop charge.
//	char isGetIdentifyResult;
	char accountNum[35];                 //user account number
	char uniqueCardId[20];               //user card unique id
	char userPassWd[35];                 //user pass word
	char cloudTradeNum[35];             //cloud charge list number
	
	short stopVerifyCode;                     //stop verification code

	int phyCardNum;                   //physical card number
	int costMoney;                    //electric cost money
	int serviceMoney;                //service cost money
	int delayMoney;                //delay charge coset money
	int  accountMoney;            //account balance
	int phoneNum;                    //the last four digits of the phone number

	
	int section48Power[50];           //every segment charge power
	int section48Cost[50];                //every segment charge cost
	jfpgSetInfo fourSectionInfo[4];          // tip peak flat valley  information
}userAccountInfo;

typedef struct{
	char cardType;
	char setState;
	char setCardNum;
	char isSuccess;
	short totalNum;
}whiteListInfo;

typedef enum{
	NONE_GUN_LOCK,
	GUN_UNLOCK,
	GUN_LOCK,
	SET_LOCK_SUCCESS,
	SET_UNLOCK_SUCCESS,
	SET_GUN_GAULT
}gunLockInfo;


typedef enum{
	NONE_LIMIT,
	COST_LIMIT,
	POWER_LIMIT,
	SOC_LIMIT,
	TIME_LIMIT,
	CURRENT_LIMIT
}chargeLimitType;

typedef struct{
	chargeLimitType limitType;
	int limitData;
}chargeLimitInfo;

typedef struct{
	char startType;          //charging start type like: card, app , manual and so on.
	char isStart;                                //whether or not start charge 
	char isStop;                                 //whether or not stop charge
	gunLockInfo isGunLock;               //gun lock infomation
	chargeLimitInfo chargeLimit;             //gun charging limit
}cloud_ctrl_fun;




typedef enum{
	IDEL,                                                    //gun idel
	PLUG_IN,                               //gun plug in
	HANDSHAKE,                       // gun charge segment of hand shake
	CONFIG,                               //gun charge segment of config
	CHARGING,                      //gun charging segment
	STOP,                                 // gun stop segment
	FINISH_PLUG_IN,     // charge finish but do not plug out the gun
	UPGRADE,                     //upgrade state
	FAULT                             //fault state
}gunStateInfo;


typedef struct{
	char axuPower;                        //set aux power supply
//	char realFrameId;
	char isStartCharge;                //just only have idel or working state and stop state
	char offLineChargeType;             //off line charge type
	char offLineStartControl;             // off line start charge control
	char chargeMode;           // like constant current ,constant voltage.
	char  firstSoc;                   // start charge soc
	char currentSoc;                 //current soc
	char chargingList[35];     // local platform serial num
	char vehicleVin[20];            //vehicle vin code
//	char vehicleLicense[10];
	char BMSVersion[10];            //bms version
	char startChargeTime[20];              //start charge time like 20230327173956
	char stopChargeTime[20];              //stop cahrge time like 20230327173956
	char faultReason;            //falut case
	

	short posTemp;    //gun positive electrode temp
	short negTemp;    // gun negtive electrode temp
	
	gunStateInfo gunState;     //like idel, plug out , plug in , charging , stop , bist ,lock,unlock

	int startUintTime;          //seconds since 1970    like 1614591901
	int stopUintTime;           //seconds since 1970    like 1614591901
	
	int chargingPower;                  //current charge power
	int outputPower;                          //shu chu gong lv
	int BMSConnectVersion;       //BMS  connect version
	int requireVol;                            //demand voltage
	int requireCurrent;                   //demand current
	int chargingVol;                      //charging voltage
	int chargingCurrent;               //charging current
	int chargingTime;                    // charging duration
	int remaindTime;                   //remaining time length
	int firstMeterData;                    //start charge electricity meter data
	int currentMeterData;            // current electricity meter data
	int actPower;                          //active power
	int reactPower;                    //reactive power
	int chargeStopReason;      //reason for end of charging
}chargerBlockInfo;


typedef struct{
	char batteryType;                                       //battery type
	char batteryProduceMonth;                   //battery production month
	char batteryProduceDay;                       // battery production day
	char batteryFlag;                                       //battery property flag bit
//	char batteryReserve;
	char batteryMaxChargeTemp;      //battery max allow charge temperature
	char singleBatteryMaxNum;             //maximum number of single batteries

	char batterySocTooHorL;                  //battery soc too hight or too low
	char batteryOverCurrent;                //charging battery overcurrent
	char batteryOverTemp;                   //charging battery overtemperature
	char batteryInsulationState;           //chaging battery insulation state
	char batteryConnectState;            //battery connect state
	char batteryAllowCharge;              //battery allowed to charge

	short maxBatteryTemp;                      //maximum battery charging temperature
	short minBatteryTemp;                    // minimum battery temperature
	short maxTempCheckNum;            // maximum battery tremperature battery list at the group
	short minTempCheckNum;            // minimum battery tremperature battery list at the group
	short batteryProduceYear;            //battery production year
	short singleBatteryMaxVol;         //single battery  maximum allow charge voltage
	short maxBatteryVol;                  // single battery maximum charging voltage
	short minBatteryVol;                    // single battery minimum charging voltage
	short singleBatteryMaxVolAtNum;       // maximum voltage battery list at the group.
	short batteryState;                                      //battery state
	short singleBatteryVolTooHorL;           //single battery voltage too high or too low

//	int batteryProduceDay;
	int batteryCapacity;                           //battery capacity
	int batteryTotalVol;                         //total battery voltage
	int batteryManufacture;                   //battery manufacturer code
	int batteryCurrentVol;                   //current battery voltage
	int singleBatteryVol;                     //single battery voltage
	int maxChargeVol;                            // total batteries allowed to charging voltage
	int maxChargeCurrent;                  //total batteries allowed to charging current
	int batteryRateCapacity;                //nominal battery capacity
	int batteryList;                                  //serial number of battery pack
	int batteryChargeNum;               //number of battery charges
	int batteryPropertyIdentify;
}batteryBlockInfo;

typedef enum{
	FULL_RECORD,
	RECORD_1,
	RECORD_2,
	RECORD_3,
	RECORD_4,
	RECORD_5
}recordNumInfo;




void lockCloudCtrlFun(cloud_ctrl_fun ctrlFun,int gunNum);     //set  cloud_ctrl_fun

void lockUserAccount(userAccountInfo accountInfo,int gunNum) ;        // set userAccountInfo

void lockWhiteList(whiteListInfo listInfo,int gunNum);                    // set  whiteListInfo

void lockChargerInfo(chargerBlockInfo chargerblock,int gunNum) ;  // set  chargerBlockInfo

void lockBatteryInfo(batteryBlockInfo batteryblock,int gunNum) ;        //set  batteryBlockInfo

void setWholeDeviceInfo(whole_device_info deviceInfo);             //set whole_device_info

void setCostRulesInfo(cost_rules_info rulesInfo);                        // set  cost_rules_info


cloud_ctrl_fun getCloudCtrlFun(int gunNum);                               //get cloud_ctrl_fun

userAccountInfo getUserAccountInfo(int gunNum );                 //get  userAccountInfo

whiteListInfo getWhiteListInfo(int gunNum );                                //get  whiteListInfo

chargerBlockInfo getChargerBlockInfo(int gunNum );           //get chargerBlockInfo

batteryBlockInfo getBatteryBlockInfo(int gunNum );                //get batteryBlockInfo

whole_device_info getDeviceInfo();                                               //get whole_device_info

cost_rules_info getCostRulesInfo();                                    // get cost_rules_info

void IdelDataClearFun(int gunNum);                                //empty data infomation

//unsigned long fileRowValue(char *file);

void printLog(char *buf);                           //write log function      note if   whole_device_info.isOPenLog != 0 ,this function can write data to file

bool isFileExist(char *filePath);                      //judge the file exist

void addSupplyHistory(void *supplyBuf,int dataLen);   //   this the send to iot platform data     

void readFileLastLine(char *filePath,void *buf);   //read file last line

void deleteFileLastLine(char *filePath,char *buf);   //delete file last line

void addDataToHistory(int gunNum);    //   this the local  record data     note : do not need to call

void upGradeHistoryData(int gunNum);    // this is the real time record and the time interval is 10s    note : do not need to call


void addChargeRulesData(cost_rules_info *rulesData);      //this is record cost rules


void initHistoryRecord();

#endif
