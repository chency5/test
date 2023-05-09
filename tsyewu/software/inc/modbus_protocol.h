#ifndef _MODBUS_PROTOCOL_H__
#define _MODBUS_PROTOCOL_H__

#define READ_WRITE_TIMES         5

#define BUFFER_SIZE                     200

#define UNUSED_TERM              0
#define ONE_GUN_TERM            1
#define TWO_GUN_TERM           2

//#define RELAY_TOTAL_NUM  512

typedef struct{
	int moduleNum;
	int modulePower;
	int moduleCode;
	int maxOutputVol;
	int minOutputVol;
	int maxOutputCurrent;
	int minOutputVCurrent;
	char WorkState[10];
	char CommState[10];
	char faultType[50];
}module_state_info;


typedef struct{
	int outputState;
	int outputVol;
	int outputCurrent;
	int setVol;
	int setCurrent;
	int moduleTemp;
}single_module_info;

typedef struct{
	int cost_price;
	int service_price;
}charge_price_info;


char *getRelayFaultState();

char *getRelayWorkState();

module_state_info getModuleStateInfo();

single_module_info getModuleWorkInfo(int moduleNum);

int  readModbusData(int gunNum,int addr, int nb, uint16_t *dest);

int  writeModbusData(int gunNum,int reg_addr, uint16_t value);

void initModbusMaster();

void initModbusPowerPort();

void modbusSlavePortInit();



void getModuleState();

void getPowerElectricData();

void getSingleRelayState();

void getSingleModuleInfo();

void controlMatrixRelay(int relayAddr,uint16_t controlData);

void controlChargeModule(int moduleAddr,uint16_t vol,uint16_t current,uint16_t isOpen);

void controlHostFan(uint16_t value);

#endif