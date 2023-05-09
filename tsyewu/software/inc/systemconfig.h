#ifndef __SYSTEM_CONFIG_H_
#define __SYSTEM_CONFIG_H_


#define TS_CONFIG_PATH            "/opt/config/tsconfig.json"

#define DEVICE_SET_PATH            "/opt/config/setdevice.json"



#define TERM_ONE                         0
#define TERM_TWO                         1
#define TERM_THREE                    2
#define TERM_FOUR                      3
#define TERM_FIVE                         4
#define TERM_SIX                           5
#define TERM_SEVEN                    6
#define TERM_EIGHT                     7
#define TERM_NINE                        8
#define TERM_TEN                         9
#define TERM_ELEVEN                 10
#define TERM_TWELVE                 11
#define TERM_THIRTEEN             12
#define TERM_FOURTEEN           13
#define TERM_FIFTEEN                 14
#define TERM_SIXTEEN                15
#define TERM_POWER                  16



#define TERM_GUN_NUM       0
#define TERM_IP                        1
#define TERM_MAC                  2




typedef enum{
	FENGCHONG = 1,
	XIAOJU,
	GUOWANG
}pingTaiTypeInfo;


typedef struct{
	int deviceType;                           //device type
	int gunTotalNum;                              //total number of guns
	int softwareVersion;                         //business software version
	int hardwareVersion;                      //business hardware version
	int gunTermSoftVersion;                  //gun terminal software version
	int gunTermHardVersion;                //gun terminal hardware version
	int powerTermSoftVersion;            //power terminal software version
	int powerTermHardVersion;           //power terminal hardware version
	int protocolVersion;                         //protocol version
	int maxOutPutPower;                      //maximum output power of charger

	int manufactureCode;                 //manufacturer code
	int maxOutputVol;                          //maximum output voltage
	int minOutputVol;                         //minimum output voltage
	int maxOutputCurrent;                  //maximum output current

//	int localAreaCode;
//	int localStationCode;

	pingTaiTypeInfo pingTaiType;                  //cloud type

	char deviceIp[20];                                   //local ip
	char powerPortIp[20];                           //power terminal ip
	char serviceIp[20];                                // cloud of server ip
	char yunWeiIp[20];                                 //cloud of yunwei ip
	char deviceModel[35];                    //product model
	char serialNum[35];                          //device serial number
	char propertyCode[35];                  //equipment asset number
	
	
//	char outFactoryCode[35];
	
}ts_config_info;


typedef struct{
	char terminalGunNum;                                      //terminal gun number
	char terminalMacAddr[10];                             //terminal mac addr
	char terminalIpAddr[20];                                  // terminal ip addr
}terminal_config_info;


typedef struct{
	char productKey[25];  // gw product identification num
	char productSecret[70];  // ues to product ota upgrade secret key
	char deviceName[35];       //the device identification num, by the gw platform issued.
	char deviceSecret[70];    // use to device ota upgrade secret key
}gwIotConfigInfo;

//void overAllWriteInJson();

//ts_config_info *getConfigInfo();
void overAllWriteInJson();       //overall write data to json

ts_config_info *controlConfigInfo();     //get and set ts_config_info;


terminal_config_info *getTerminalConfigData(int terminal);       //get terminal information

terminal_config_info *setTerminalConfigData(int terminal);       //set terminal information

void writeTerminalConfig();      //write all terminals data

void gwConfigCreat();      //creat gw json

void readGwConfig();     //read gw infomation

void writeGwConfig();                  //write gw information

gwIotConfigInfo *getgwConfig();    //get and set gw gwIotConfigInfo


char *getSimNum();            //get sim card number       goose use

char *getMacAddr();              //get mac addr           goose use



typedef struct{
	char enableSwipeCard;         //enable swipe card function
	char settlementCard;             //wheter or not settlement card
	char lockAbnormalCard;     // normal card lock
	char enableInsulation;           //enable insulation
	char enableGateMonitor;      //enable gate monitor
	char enableVinCharge;               //enable vin charger
	char enableBatteryProtect;   //enable battery protection
	char setBatteryMaxSoc;                //maximum soc for charging battery
	char checkK1K2;                          //ckeck k1 k2 contact
	char contactOffTime;                    //contactor opening time
	char enableGunLockCheck;       //enable gun lock check
	char gunReducePercent;              //gun charging reduce percents
	char enableStationCardCheck;    //enable card of charger station check
	char enableOffLineStop;                //enable off line stop charging
	
	
	short systemTempAlarmValue;                //set charger system temperature alarm value
//	short minGunLineTempAlarmValue;
	short maxGunLineTempAlarmValue;     //set maximum temperature alarm value of gun line 
//	short inputOverVolAlarm;
//	short inputLowVolAlarm;
//	short inputOverCurrentAlarm;
	short gunTempAlarmValue;                    //set gun temperature alarm value 
	short deviateBatteryVol;                             //battery deviate voltage
	
	short vinDelayTime;                                 //vin charging delay time

	short moduleCombineNum;              //the number of module to combine a group 
	short maxFanOutput;                         //the fun maximum output power 
	short turnOnFanTempValue;              //set open fun temperature value 

	int turnOnTopLight;                     //open the top light
}device_set_info;


void writeSetDevice();

device_set_info *controlDeviceSetInfo();


void tsConfigInit();


#endif