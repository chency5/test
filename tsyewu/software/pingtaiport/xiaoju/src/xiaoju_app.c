#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "redefine.h"
#include "xiaojuprotocol.h"
#include "xiaoju.h"
#include "xiaoju_error.h"
#include "datacenter.h"
#include "xiaoju_app.h"
#include "projdebug.h"


st_user_gun_info         xiaoJuGunInfo[CHARGE_GUN_CNT];
st_user_bms_info        xiaoJuBmsInfo[CHARGE_GUN_CNT];

st_bms_basic_info       bmsBasicInfo[CHARGE_GUN_CNT];

st_bms_finish_statistical_data       bmsFinidhStatisticalData[CHARGE_GUN_CNT];

xj_work_stat_type          xjWorkState[CHARGE_GUN_CNT];


static bool isStart = false;
static bool isStop = false;

void assignIdelInfo(int gunNum){
	xiaoJuBmsInfo[gunNum].bcl_voltage_need = 0;
	xiaoJuBmsInfo[gunNum].bcl_current_need = 0;
	xiaoJuBmsInfo[gunNum].bcl_charge_mode = 0; //    constant voltage 0x01  constant current 0x02  but this is idel mode so its 0 is ok?
	xiaoJuBmsInfo[gunNum].bcs_test_voltage = 0;
	xiaoJuBmsInfo[gunNum].bcs_test_current = 0;
	xiaoJuBmsInfo[gunNum].bcs_max_single_voltage = 0;
	xiaoJuBmsInfo[gunNum].bcs_min_single_voltage = 0;
	xiaoJuBmsInfo[gunNum].bcs_max_single_no = 0;

	xiaoJuBmsInfo[gunNum].bcs_current_soc = 0;
	xiaoJuBmsInfo[gunNum].charge_time_left = 0;
	xiaoJuBmsInfo[gunNum].bsm_single_no = 0;
	xiaoJuBmsInfo[gunNum].bsm_max_temperature = 0;
	xiaoJuBmsInfo[gunNum].bsm_max_temperature_check_no = 0;
	xiaoJuBmsInfo[gunNum].bsm_min_temperature = 0;
	xiaoJuBmsInfo[gunNum].bsm_min_temperature_check_no = 0;
	xiaoJuBmsInfo[gunNum].bsm_voltage_too_high_or_too_low = 0;
	xiaoJuBmsInfo[gunNum].bsm_car_battery_soc_too_high_or_too_low = 0;
	xiaoJuBmsInfo[gunNum].bsm_car_battery_charge_over_current = 0;
	xiaoJuBmsInfo[gunNum].bsm_battery_temperature_too_high = 10;
	xiaoJuBmsInfo[gunNum].bsm_battery_insulation_state = 0;
	xiaoJuBmsInfo[gunNum].bsm_battery_connect_state = 0;
	xiaoJuBmsInfo[gunNum].bsm_allow_charge = 0;

	xiaoJuBmsInfo[gunNum].dc_charge_voltage = 0;
	xiaoJuBmsInfo[gunNum].dc_charge_current = 0;

	xiaoJuGunInfo[gunNum].soc_percent = 0;
	xiaoJuGunInfo[gunNum].dc_charge_voltage = 0;
	xiaoJuGunInfo[gunNum].dc_charge_current = 0;
	xiaoJuGunInfo[gunNum].bms_need_voltage = 0;
	xiaoJuGunInfo[gunNum].bms_need_current = 0;
	xiaoJuGunInfo[gunNum].ac_a_vol = 0;
	xiaoJuGunInfo[gunNum].ac_a_cur = 0;
	xiaoJuGunInfo[gunNum].ac_b_vol = 0;
	xiaoJuGunInfo[gunNum].ac_b_cur = 0;
	xiaoJuGunInfo[gunNum].ac_c_vol = 0;
	xiaoJuGunInfo[gunNum].ac_c_cur = 0;

	xiaoJuGunInfo[gunNum].meter_kwh_num = getChargerBlockInfo(gunNum).currentMeterData;
	xiaoJuGunInfo[gunNum].charge_power_kw = 0;
	return;
}



void assignBistInfo(int gunNum){
	int count = 0;
	bmsBasicInfo[gunNum].brm_bms_connect_version[0] = getChargerBlockInfo(gunNum).BMSConnectVersion & 0xff;
	bmsBasicInfo[gunNum].brm_bms_connect_version[1] = getChargerBlockInfo(gunNum).BMSConnectVersion >> 8 & 0xff;
	bmsBasicInfo[gunNum].brm_bms_connect_version[2] = getChargerBlockInfo(gunNum).BMSConnectVersion >> 16 & 0xff;
	bmsBasicInfo[gunNum].brm_bms_connect_version[3] = getChargerBlockInfo(gunNum).BMSConnectVersion >> 24 & 0xff;

	bmsBasicInfo[gunNum].brm_battery_type = getBatteryBlockInfo(gunNum).batteryType;
	bmsBasicInfo[gunNum].brm_battery_power = getBatteryBlockInfo(gunNum).batteryRateCapacity;
	bmsBasicInfo[gunNum].brm_battery_volt = getBatteryBlockInfo(gunNum).batteryTotalVol;
	bmsBasicInfo[gunNum].brm_battery_supplier = getBatteryBlockInfo(gunNum).batteryManufacture;
	bmsBasicInfo[gunNum].brm_battery_seq = getBatteryBlockInfo(gunNum).batteryList;
	bmsBasicInfo[gunNum].brm_battery_produce_year = getBatteryBlockInfo( gunNum).batteryProduceYear;
	bmsBasicInfo[gunNum].brm_battery_produce_month = getBatteryBlockInfo( gunNum).batteryProduceMonth;
	bmsBasicInfo[gunNum].brm_battery_produce_day = getBatteryBlockInfo( gunNum).batteryProduceDay;
	bmsBasicInfo[gunNum].brm_battery_charge_count = getBatteryBlockInfo( gunNum).batteryChargeNum;
	bmsBasicInfo[gunNum].brm_battery_property_identification = getBatteryBlockInfo( gunNum).batteryFlag;
	memcpy(&bmsBasicInfo[gunNum].brm_vin[0],&getChargerBlockInfo(gunNum).vehicleVin[0],17);
	memcpy(&bmsBasicInfo[gunNum].brm_bms_software_version,&getChargerBlockInfo(gunNum).BMSVersion[0],8);
	bmsBasicInfo[gunNum].bcp_max_voltage = getBatteryBlockInfo(gunNum).singleBatteryMaxVol;
	bmsBasicInfo[gunNum].bcp_max_current = getBatteryBlockInfo( gunNum).maxChargeCurrent;
	bmsBasicInfo[gunNum].bcp_max_current = getBatteryBlockInfo( gunNum).batteryRateCapacity;
	bmsBasicInfo[gunNum].bcp_total_voltage = getBatteryBlockInfo(gunNum).batteryTotalVol;
	bmsBasicInfo[gunNum].bcp_max_temperature = getBatteryBlockInfo(gunNum).batteryMaxChargeTemp;
	bmsBasicInfo[gunNum].bcp_battery_soc = getChargerBlockInfo(gunNum).firstSoc;
	bmsBasicInfo[gunNum].bcp_battery_soc_current_voltage = getBatteryBlockInfo(gunNum).batteryCurrentVol;
	bmsBasicInfo[gunNum].bro_bms_is_ready = getChargerBlockInfo(gunNum).gunState;
	bmsBasicInfo[gunNum].CRO_isReady = CHARGER_READY;
	count ++;
	if(count > 2){
		count = 0;
		isStart = false;
	}
	return;
}

void assignChargingInfo(int gunNum){
	xiaoJuBmsInfo[gunNum].bcl_voltage_need = getChargerBlockInfo(gunNum).requireVol;
	xiaoJuBmsInfo[gunNum].bcl_current_need = getChargerBlockInfo(gunNum).requireCurrent;
	xiaoJuBmsInfo[gunNum].bcl_charge_mode = getChargerBlockInfo(gunNum).chargeMode;
	xiaoJuBmsInfo[gunNum].bcs_test_voltage = getChargerBlockInfo(gunNum).chargingVol;
	xiaoJuBmsInfo[gunNum].bcs_test_current = getChargerBlockInfo(gunNum).chargingCurrent;
	xiaoJuBmsInfo[gunNum].bcs_max_single_voltage = getBatteryBlockInfo(gunNum).maxBatteryVol;
	xiaoJuBmsInfo[gunNum].bcs_max_single_no = getBatteryBlockInfo(gunNum).singleBatteryMaxNum;
	xiaoJuBmsInfo[gunNum].bcs_current_soc = getChargerBlockInfo(gunNum).currentSoc;
	xiaoJuBmsInfo[gunNum].charge_time_left = getChargerBlockInfo(gunNum).remaindTime;

	xiaoJuGunInfo[gunNum].dc_charge_voltage = getChargerBlockInfo(gunNum).chargingVol;
	xiaoJuGunInfo[gunNum].dc_charge_current = getChargerBlockInfo(gunNum).chargingCurrent;
	xiaoJuGunInfo[gunNum].bms_need_voltage = getChargerBlockInfo(gunNum).requireVol;
	xiaoJuGunInfo[gunNum].bms_need_current = getChargerBlockInfo(gunNum).requireCurrent;
	xiaoJuGunInfo[gunNum].ac_a_vol = getDeviceInfo().APhaseVol;
	xiaoJuGunInfo[gunNum].ac_a_cur = getDeviceInfo().APhaseCurrent;
	xiaoJuGunInfo[gunNum].ac_b_vol = getDeviceInfo().BPhaseVol;
	xiaoJuGunInfo[gunNum].ac_b_cur = getDeviceInfo().BPhaseCurrent;
	xiaoJuGunInfo[gunNum].ac_c_vol = getDeviceInfo().CPhaseVol;
	xiaoJuGunInfo[gunNum].ac_c_cur = getDeviceInfo().CPhaseCurrent;
	xiaoJuGunInfo[gunNum].meter_kwh_num = getChargerBlockInfo(gunNum).currentMeterData;
	xiaoJuGunInfo[gunNum].charge_power_kw = getChargerBlockInfo(gunNum).chargingPower;
		
	return;
}

void assignStopInfo(int gunNum){
	bmsFinidhStatisticalData[gunNum].bsd_stop_soc = getChargerBlockInfo(gunNum).currentSoc;
	bmsFinidhStatisticalData[gunNum].bsd_battery_low_voltage = NORMAL_DATA;
	bmsFinidhStatisticalData[gunNum].bsd_battery_high_voltage = NORMAL_DATA;
	bmsFinidhStatisticalData[gunNum].bsd_battery_low_temperature = NORMAL_DATA;
	bmsFinidhStatisticalData[gunNum].bsd_battery_high_temperature = NORMAL_DATA;
	bmsFinidhStatisticalData[gunNum].bem_error_spn2560_00 = NORMAL_DATA;
	bmsFinidhStatisticalData[gunNum].bem_error_spn2560_aa = NORMAL_DATA;
	bmsFinidhStatisticalData[gunNum].bem_error_time_sync = NORMAL_DATA;
	bmsFinidhStatisticalData[gunNum].bem_error_ready_to_charge = NORMAL_DATA;
	bmsFinidhStatisticalData[gunNum].bem_error_receive_status = NORMAL_DATA;
	bmsFinidhStatisticalData[gunNum].bem_error_receive_stop_charge = NORMAL_DATA;
	bmsFinidhStatisticalData[gunNum].bem_error_receive_report = NORMAL_DATA;  
	bmsFinidhStatisticalData[gunNum].bem_error_other = NORMAL_DATA;
	return;
}


void assignStartCharge(int gunNum){
	if(getChargerBlockInfo(gunNum).isStartCharge == IDEL_STATE)
		return;
	
	if(isStart){
		return;
	}
	touch_send_bms_basic_info(gunNum,getUserAccountInfo(gunNum).cloudTradeNum,&bmsBasicInfo[gunNum]);
	xj_send_touch_charge_start(gunNum,XJ_SUCCEED_RESULT);
	xjWorkState[gunNum] = xj_work_stat_type_charging;
	isStart = true;;
	return;
}

void assignStopCharge(int gunNum){
	if(getChargerBlockInfo(gunNum).isStartCharge == WORK_STATE)
		return;

	if(isStop)
		return;
	
	st_off_bms_cst_data  data_308;
	data_308.CST_error_reason = 0;
	data_308.CST_fault_reason = 0;
	data_308.CST_stop_reason = 0;
	touch_send_bms_cst_data(gunNum,getUserAccountInfo(gunNum).cloudTradeNum,&data_308);

	st_off_bms_bst_data data_310;
	data_310.BST_error_reason = 0;
	data_310.BST_fault_reason = 0;
	data_310.BST_stop_reason = 0;
	touch_send_bms_bst_data(gunNum,getUserAccountInfo(gunNum).cloudTradeNum,&data_310);

	touch_send_bms_inish_statistical_data(gunNum,getUserAccountInfo(gunNum).cloudTradeNum,&bmsFinidhStatisticalData[gunNum]);
	xj_send_touch_charge_stoped(gunNum,XJ_SDK_ERR_1000,XJ_SUCCEED_RESULT);

	xjWorkState[gunNum] = xj_work_stat_type_gun_not_pluged_out;
	isStop = true;
	return;
}


void *producerXiaoJuInfo(){
	int i = 0 ;
	bool idelFlag = false;
	while(1){
		for(i = 0 ; i < CHARGE_GUN_CNT ; i ++){
			switch(xjWorkState[i]){
				case xj_work_stat_type_idle:{
					if(!idelFlag){
						idelFlag = true;
						assignIdelInfo(i);
						IdelDataClearFun(i);
					}
				}break;
				
				case xj_work_stat_type_bist:{
					assignBistInfo(i);
				}break;

				case xj_work_stat_type_charging:{
					assignChargingInfo(i);
				}break;

				case xj_work_stat_type_stoping:{
					assignStopInfo(i);
				}break;

				case xj_work_stat_type_gun_pluged_in:{        //no used

				}break;

				case xj_work_stat_type_gun_not_pluged_out:{

				}break;

				case xj_work_stat_type_reserve:{

				}break;

				default:break;
			}
			assignStartCharge(i);
			assignStopCharge(i);
		}
		mSleep(500);
	}
	
	return NULL;
}

int8_t callback_software_download(xj_software_upgrade_param * param){   //need to improve
	whole_device_info deviceInfo;
	deviceInfo = getDeviceInfo();
	memcpy(deviceInfo.ftpUrl,param->url,XJ_MAX_URL_LEN);
	memcpy(deviceInfo.md5SumNum,param->md5,XJ_MAX_CHECKSUM_LEN);
	setWholeDeviceInfo(deviceInfo);

	touch_send_1102_code(0,(unsigned char*)getDeviceInfo().md5SumNum,param->serial_code);
	return 0;
}

void callback_stop_charge(uint8_t gun_cnt,char * err){   //need to improve

	strcpy(err,XJ_SUCCEED_RESULT);
	xjWorkState[gun_cnt] = xj_work_stat_type_stoping;
	isStop = false;
	
	return;
}

void callback_start_charge(uint8_t gun_cnt,char * err,char * id,uint8_t id_len,uint16_t user_tel,uint8_t charge_policy,uint32_t charge_policy_param){    //need to improve
	userAccountInfo accountInfo;
	
	accountInfo = getUserAccountInfo(gun_cnt);
	memset(accountInfo.cloudTradeNum,0,35);
	memcpy(accountInfo.cloudTradeNum,id,id_len);	
	accountInfo.phoneNum = user_tel;
	lockUserAccount(accountInfo,gun_cnt);
	xjWorkState[gun_cnt] = xj_work_stat_type_bist;
	
	return;
}

int8_t callback_power_control(uint8_t gun_cnt,uint32_t kwh){    //need to improve
	
	return 0;
}

void callback_display_qr(uint8_t gun_cnt,uint8_t * qr_str,uint16_t len,char * err){   //need to improve
	strcpy(err,XJ_SUCCEED_RESULT);
	return;
}
void callback_set_sys_time(xj_sync_system_time_param time,char * err){   //need to improve
	whole_device_info deviceInfo;
	deviceInfo = getDeviceInfo();
	deviceInfo.checkTime[0] = time.year & 0xff;
	deviceInfo.checkTime[1] = time.year >> 8 & 0xff;
	deviceInfo.checkTime[2] = time.month;
	deviceInfo.checkTime[3] = time.day;
	deviceInfo.checkTime[4] = time.hour;
	deviceInfo.checkTime[5] = time.minute;
	deviceInfo.checkTime[6] = time.sec;
	setWholeDeviceInfo(deviceInfo);
	strcpy(err,XJ_SUCCEED_RESULT);
	return;
}

void callback_safety_protect_param(xj_l2_safety_prot_param * param,uint8_t * err){    //need to improve

	return;
}

int8_t callback_save_bill(char * bill,uint32_t size){   
	FILE *p = NULL;
	p = fopen(XIAOJU_BILL_PATH,"w");
	if(p == NULL)
		return 0;
	fprintf(p,"%s",bill);
	fclose(p);
	p = NULL;
	return 0;
}

int8_t callback_read_bill(char * bill,uint32_t len){
	FILE *p = NULL;
//	int line = 0;
//	int i = 0;
	 fopen(XIAOJU_BILL_PATH,"r");
	 if(p == NULL)
		return 0;
//	line = fileRowValue(XIAOJU_BILL_PATH);
//	for(i = 0 ; i < line ; i ++)
		fscanf(p,"%s",bill);
	fclose(p);
	p = NULL;
	
	return 0;
}

int8_t callback_upload_log(const xj_upload_log_param * upload_url,char * log_name,uint16_t max_len){
	
	return 0;
}

int8_t callback_show_bill(xj_bill_info bill_data,uint8_t gun_cnt){

	return 0;
}


int8_t callback_lock_control(uint8_t gun_cnt,uint8_t type){

	return 0;
}
 
int8_t callback_vin_start_charge_result(st_user_vin_send_result result){
	if(result.Request_result ==0){
		char err[5] = {0};
		callback_start_charge(result.gun_index,err,result.charge_user_id,strnlen(result.charge_user_id,32),result.phone,0,0);
	}
	return 0;
}

#if 0

void callback_set_vin_white_list(T_VIN_SET *vin_data,T_VIN_SET *vin_data_result){

	return;
}

void callback_set_card_white_list(T_CARD_SET *card_data,T_CARD_SET *card_data_result){

	return;
}

void callback_clean_vin_white_list(int8_t *result){
	*result = 0;
	return;
}

void callback_clean_card_white_list(int8_t *result){
	*result = 0;
	return;
}

#endif

void doPlugIn(int gunNum){
	xjWorkState[gunNum] = xj_work_stat_type_gun_pluged_in;
	return;
}

void doPlugOut(int gunNum){
	xjWorkState[gunNum] = xj_work_stat_type_idle;
	return;
}

void doWarningLoad(){

	return;
}

void xiaoJuInit(){
	TRACE_PROJ_SOCKET_INFO("#########  xiaoJuInit   #############\n");
	create_thread(NULL,producerXiaoJuInfo,10);
	
	return;
}
