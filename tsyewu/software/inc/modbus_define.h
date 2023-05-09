#ifndef _MODBUS_DEFINE_H__
#define _MODBUS_DEFINE_H__


#define PRODUCT_TYPE                                         0x0000
#define PRODUCT_MODEL                                     0x0001
#define HARDWARE_VERSION                             0x0011
#define SOFTWARE_VERSION                               0x0013
#define PROTOCOL_VERSION                               0x0015
#define COMPILE_TIME                                            0x0016
#define DEVICE_UNIQUE_IDENTIFY                     0x0026

#define FIRMWARE_UPGRADE                             0x0400
#define TERMINAL_STATUS                                  0x0401
#define CLOUD_ON_LINE_STATUS                     0x0401
#define SWIPE_CARD_STATUS                            0x0402
#define OBTAIN_VIN_STATUS                               0x0403
#define CARD_DATA                                                0x0404
#define OBTAIN_VIN                                                 0x0419
#define OUTPUT_VOL                                               0x0422
#define OUTPUT_CURRENT                                   0x0424
#define OUTPUT_POWER_RATE                          0x0426
#define OUTPUT_POWER                                       0x0428
#define GUN_LINE_TEMP                                       0x042a
#define GUN_CC1                                                     0x042b  
#define ELECTRIC_LOCK                                       0x042c
#define K1K2_STATUS                                            0x042d
#define METER_CONNECT_STATUS                  0x042e
#define METER_WORK_STATUS                         0x042f
#define START_K1K2_VOL                                   0x0430
#define START_CHARGE_TIME                           0x0431
#define STOP_CHARGE_TIME                              0x0433
#define IDENTIFY_SEGMENT                                0x0435

#define CONFIG_SEGMENT                                   0x044e
#define CHARGING_SEGMENT                            0x0455
#define CHARGING_STOP_SEGMENT               0x0463
#define CHARGE_STATISTICS_SEGMENT       0x0464
#define BMS_DAULT_INFO                                   0x046a
#define CHARGER_FAULT_INFO                        0x046c
#define SECTION_ONE_POWER                          0x046d
#define SECTION_TWO_POWER                         0x046f
#define SECTION_THREE_POWER                     0x0471
#define SECTION_FOUR_POWER                       0x0473
#define SECTION_FIVE_POWER                          0x0475
#define SECTION_SIX_POWER                            0x0477
#define SECTION_SEVEN_POWER                    0x0479
#define SECTION_EIGHT_POWER                      0x047b
#define SECTION_NINE_POWER                        0x047d
#define SECTION_TEN_POWER                          0x047f
#define SECTION_ELEVEN_POWER                  0x0481
#define SECTION_TWELVE_POWER                  0x0483
#define SECTION_THIRTEEN_POWER              0x0485
#define SECTION_FOURTEEN_POWER            0x0487
#define SECTION_FIFTEEN_POWER                  0x0489
#define SECTION_SIXTEEN_POWER                  0x048b
#define SECTION_SEVENTEEN_POWER          0x048d
#define SECTION_EIGHTEEN_POWER              0x048f
#define SECTION_NINETEEN_POWER               0x0491
#define SECTION_TWENTY_POWER                   0x0493
#define SECTION_TWENTY_ONE_POWER        0x0495
#define SECTION_TWENTY_TWO_POWER        0x0497
#define SECTION_TWENTY_THREE_POWER          0x0499
#define SECTION_TWENTY_FOUR_POWER            0x049b
#define SECTION_TWENTY_FIVE_POWER               0x049d
#define SECTION_TWENTY_SIX_POWER                 0x049f
#define SECTION_TWENTY_SEVEN_POWER          0x04a1
#define SECTION_TWENTY_EIGHT_POWER            0x04a3
#define SECTION_TWENTY_NINE_POWER              0x04a5
#define SECTION_THIRTY_POWER                            0x04a7
#define SECTION_THIRTY_ONE_POWER                 0x04a9
#define SECTION_THIRTY_TWO_POWER                 0x04ab
#define SECTION_THIRTY_THREE_POWER            0x04ad
#define SECTION_THIRTY_FOUR_POWER               0x04af
#define SECTION_THIRTY_FIVE_POWER                 0x04b1
#define SECTION_THIRTY_SIX_POWER                   0x04b3
#define SECTION_THIRTY_SEVEN_POWER            0x04b5
#define SECTION_THIRTY_EIGHT_POWER              0x04b7
#define SECTION_THIRTY_NINE_POWER                0x04b9
#define SECTION_FORTY_POWER                             0x04bb
#define SECTION_FORTY_ONE_POWER                  0x04bd
#define SECTION_FORTY_TWO_POWER                  0x04bf
#define SECTION_FORTY_THREE_POWER             0x04c1
#define SECTION_FORTY_FOUR_POWER                0x04c3
#define SECTION_FORTY_FIVE_POWER                  0x04c5
#define SECTION_FORTY_SIX_POWER                    0x04c7
#define SECTION_FORTY_SEVEN_POWER             0x04c9
#define SECTION_FORTY_EIGHT_POWER               0x04cb

#define THIS_CHARGE_COST                                     0x04ce
#define THIS_CHARGE_POWER                                 0x04d0



#define CLOUD_IDENTIFY_RESULT	                   0x2000
#define TS_START_CHARGE                                      0x2001
#define TS_STOP_CHARGE                                         0x2002
#define TS_CHARGE_COST                                        0x2003
#define TOP_LIGHT_CONTROL                                  0x2004
#define K1_K2_SWITCH_CONTROL                         0x2005
#define K3_K4_SWITCH_CONTROL                         0x2006
#define LIQUID_COLD_CONTROL                             0x2007
#define GUN_LOCK_CONTROL                                 0x2008
#define ACCOUNT_MONEY                                        0x2009


#define CONFIG_MODE                                                0x2400
#define ASSET_CODE                                                  0x2401
#define  MAC_ADDR                                                     0x2411
#define IP_ADDR                                                            0x2414
#define SUB_NET_MASK                                             0x2416
#define GATEWAY							0x2418
#define DNS								0x241a
#define GOOSE_MULTI_CAST_ADDR                      0x241c
#define VLANID                                                               0x241f
#define UNIX_TIME_STAMP                                        0x2420
#define FIRMWARE_UPGRADE_MODE                   0x2422
#define FIRMWARE_NEW_CODE                              0x2423
#define FIRMWARE_TYPE_CLOUD                           0x2425
#define UPPER_COMPUTER_ADDR                        0x2445
#define FIRMWARE_TYPE_RTU                                 0x2447


#define LOCAL_IP_ADDR                                          0x2467
#define EXTEBSION_ADDR                                       0x2469
#define SET_SINGLE_OR_DOUBLE_GUN             0x246a
#define A_GUN_NUM                                                   0x246b
#define B_GUN_NUM                                                   0x246c

#define IS_SETTLEMENT_CARD                             0x246d
#define IS_UNUSUAL_CARD_LOCK                      0x246e
#define IS_START_INSULATION_CHECK             0x246f
#define IS_TURN_ON_ENTRANCE_GUARD_CHECK                  0x2470
#define IS_TURN_ON_VIN_CHARGE                                                0x2471
#define VIN_CHARGE_DELAY_TIME                            0x2472
#define ENABLE_BATTERY_PROTECT                       0x2473
#define MAX_BATTERY_SOC                                         0x2474
#define CHECK_K1_K2                                                    0x2475
#define BATTERY_VOL_OFFSET                                   0x2476
#define CONTRACTOR_BREAK_OFF_TIME               0x2477
#define IS_TURN_ON_GUN_CHECK                            0x2478
#define SYSTEM_TEMPERATURE_ALARM_VALUE                  0x2479
#define GUN_TEMPERATURE_LOW_ALARM_VALUE              0x247a
#define GUN_TEMPERATURE_HIGH_ALARM_VALUE             0x247b
#define INPUT_VOL_HIGH_ALARM_VALUE                                 0x247c
#define INPUT_VOL_LOW_ALARM_VALUE                                  0x247d
#define INPUT_CURRENT_HIGH_ALARM_VALUE                     0x247e
#define OUTPUT_VOL_HIGH_ALARM_VALUE                             0x247f
#define OUTPUT_VOL_LOW_ALARM_VALUE                              0x2480
#define OUTPUT_CURRENT_HIGH_ALARM_VALUE                 0x2481
#define REDUCE_OUTPUT_TEMPERATURE_VALUE                0x2482
#define REDUCE_OUTPUT_PERCENTAGE_VALUE                  0x2483
#define AREAR_CODE                                                        0x2484
#define STATION_CODE                                                     0x2485
#define IS_OPEN_STATION_CARD_CKECK                0x2486
#define IS_OPEN_OFF_LINE_POWER_OFF                  0x2487
#define OPEN_TERMINAL_TOP_LIGHT                         0x2488
#define CLOUD_INFO                                                          0x248a
#define MAX_OUTPUT_VOL                                              0x248b
#define MIN_OUTPUT_VOL                                                0x248d
#define MAX_OUTPUT_CURRENT                                  0x248f
#define MIN_OUTPUT_CURRENT                                    0x2491
#define IS_OPEN_SWIPE_CARD                                     0x2493




#define INSERT_GUN_NUM                                                0x0401
#define INSERT_MODULE_NUM                                        0x0402
#define INSERT_MODULE_POWER                                  0x0403
#define MODULE_FACTORY_CODE                                 0x0404
#define MAX_MODULE_OUTPUT_VOL                            0x0406
#define MIN_MODULE_OUTPUT_VOL                              0x0407
#define MAX_MODULE_OUTPUT_CURRENT                0x0408
#define MIN_MODULE_OUTPUT_CURRENT                  0x0409
#define MODULE_WORK_STATE                                      0x040a
#define MODULE_COMM_STAET                                      0x040d
#define MODULE_ALARM_FAULT                                    0x0410
#define MATRIX_BOARD_COMM_STATE                       0x0428
#define PHASE_A_VOL                                                        0x0429
#define PHASE_B_VOL                                                        0x042b
#define PHASE_C_VOL                                                        0x042d
#define PHASE_A_CURRENT                                            0x042f
#define PHASE_B_CURRENT                                            0x0431
#define PHASE_C_CURRENT                                            0x0433
#define ONE_GUN_DEMAND_VOL                                   0x0435
#define ONE_GUN_DEMAND_CURRENT                       0x0437
#define ONE_GUN_OUTPUT_VOL                                     0x0439
#define ONE_GUN_OUTPUT_CURRENT                         0x043b

#define TWO_GUN_DEMAND_VOL                                   0x043d
#define TWO_GUN_DEMAND_CURRENT                       0x043f
#define TWO_GUN_OUTPUT_VOL                                     0x0441
#define TWO_GUN_OUTPUT_CURRENT                         0x0443

#define THREE_GUN_DEMAND_VOL                               0x0445
#define THREE_GUN_DEMAND_CURRENT                   0x0447
#define THREE_GUN_OUTPUT_VOL                                 0x0449
#define THREE_GUN_OUTPUT_CURRENT                     0x044b

#define FOUR_GUN_DEMAND_VOL                                  0x044d
#define FOUR_GUN_DEMAND_CURRENT                      0x044f
#define FOUR_GUN_OUTPUT_VOL                                    0x0451
#define FOUR_GUN_OUTPUT_CURRENT                        0x0453

#define FIVE_GUN_DEMAND_VOL                                     0x0455
#define FIVE_GUN_DEMAND_CURRENT                         0x0457
#define FIVE_GUN_OUTPUT_VOL                                       0x0459
#define FIVE_GUN_OUTPUT_CURRENT                           0x045b

#define SIX_GUN_DEMAND_VOL                                       0x045d
#define SIX_GUN_DEMAND_CURRENT                           0x045f
#define SIX_GUN_OUTPUT_VOL                                         0x0461
#define SIX_GUN_OUTPUT_CURRENT                             0x0463

#define SEVEN_GUN_DEMAND_VOL                                   0x0465
#define SEVEN_GUN_DEMAND_CURRENT                       0x0467
#define SEVEN_GUN_OUTPUT_VOL                                     0x0469
#define SEVEN_GUN_OUTPUT_CURRENT                         0x046b

#define EIGHT_GUN_DEMAND_VOL                                   0x046d
#define EIGHT_GUN_DEMAND_CURRENT                       0x046f
#define EIGHT_GUN_OUTPUT_VOL                                     0x0471
#define EIGHT_GUN_OUTPUT_CURRENT                         0x0473

#define NINE_GUN_DEMAND_VOL                                   0x0475
#define NINE_GUN_DEMAND_CURRENT                       0x0477
#define NINE_GUN_OUTPUT_VOL                                     0x0479
#define NINE_GUN_OUTPUT_CURRENT                         0x047b

#define TEN_GUN_DEMAND_VOL                                   0x047d
#define TEN_GUN_DEMAND_CURRENT                       0x047f
#define TEN_GUN_OUTPUT_VOL                                     0x0481
#define TEN_GUN_OUTPUT_CURRENT                         0x0483

#define ELEVEN_GUN_DEMAND_VOL                                   0x0485
#define ELEVEN_GUN_DEMAND_CURRENT                       0x0487
#define ELEVEN_GUN_OUTPUT_VOL                                     0x0489
#define ELEVEN_GUN_OUTPUT_CURRENT                         0x048b

#define TWELVE_GUN_DEMAND_VOL                                   0x048d
#define TWELVE_GUN_DEMAND_CURRENT                       0x048f
#define TWELVE_GUN_OUTPUT_VOL                                     0x0491
#define TWELVE_GUN_OUTPUT_CURRENT                         0x0493

#define THIRTEEN_GUN_DEMAND_VOL                                   0x0495
#define THIRTEEN_GUN_DEMAND_CURRENT                       0x0497
#define THIRTEEN_GUN_OUTPUT_VOL                                     0x0499
#define THIRTEEN_GUN_OUTPUT_CURRENT                         0x049b

#define FOURTEEN_GUN_DEMAND_VOL                                   0x049d
#define FOURTEEN_GUN_DEMAND_CURRENT                       0x049f
#define FOURTEEN_GUN_OUTPUT_VOL                                     0x04a1
#define FOURTEEN_GUN_OUTPUT_CURRENT                         0x04a3

#define FIFTEEN_GUN_DEMAND_VOL                                   0x04a5
#define FIFTEEN_GUN_DEMAND_CURRENT                       0x04a7
#define FIFTEEN_GUN_OUTPUT_VOL                                     0x04a9
#define FIFTEEN_GUN_OUTPUT_CURRENT                         0x04ab

#define SIXTEEN_GUN_DEMAND_VOL                                   0x04ad
#define SIXTEEN_GUN_DEMAND_CURRENT                       0x04af
#define SIXTEEN_GUN_OUTPUT_VOL                                     0x04b1
#define SIXTEEN_GUN_OUTPUT_CURRENT                         0x04b3



#define MATRIX_ONE_RELAY_STATE                                   0x04b5
#define MATRIX_TWO_RELAY_STATE                                   0x04b6
#define MATRIX_THREE_RELAY_STATE                              0x04b7
#define MATRIX_FOUR_RELAY_STATE                                0x04b8
#define MATRIX_FIVE_RELAY_STATE                                   0x04b9
#define MATRIX_SIX_RELAY_STATE                                     0x04ba
#define MATRIX_SEVEN_RELAY_STATE                              0x04bb
#define MATRIX_EITGHT_RELAY_STATE                             0x04bc
#define MATRIX_NINE_RELAY_STATE                                  0x04bd
#define MATRIX_TEN_RELAY_STATE                                    0x04be
#define MATRIX_ELEVEN_RELAY_STATE                            0x04bf
#define MATRIX_TWELVE_RELAY_STATE                            0x04c0
#define MATRIX_THIRTEEN_RELAY_STATE                        0x04c1
#define MATRIX_FOURTEEN_RELAY_STATE                      0x04c2
#define MATRIX_FIFTEEN_RELAY_STATE                            0x04c3
#define MATRIX_SIXTEEN_RELAY_STATE                           0x04c4
#define MATRIX_SEVENTEEN_RELAY_STATE                    0x04c5
#define MATRIX_EIGHTTEEN_RELAY_STATE                      0x04c6
#define MATRIX_NINETEEN_RELAY_STATE                        0x04c7
#define MATRIX_TWENTY_RELAY_STATE                            0x04c8
#define MATRIX_TWENTY_ONE_RELAY_STATE                 0x04c9
#define MATRIX_TWENTY_TWO_RELAY_STATE                 0x04ca
#define MATRIX_TWENTY_THREE_RELAY_STATE             0x04cb
#define MATRIX_TWENTY_FOUR_RELAY_STATE               0x04cc
#define MATRIX_TWENTY_FIVE_RELAY_STATE                  0x04cd
#define MATRIX_TWENTY_SIX_RELAY_STATE                    0x04ce
#define MATRIX_TWENTY_SEVEN_RELAY_STATE             0x04cf
#define MATRIX_TWENTY_EIGHT_RELAY_STATE               0x04d0
#define MATRIX_TWENTY_NINE_RELAY_STATE                  0x04d1
#define MATRIX_THIRTY_RELAY_STATE                                0x04d2
#define MATRIX_THIRTY_ONE_RELAY_STATE                     0x04d3
#define MATRIX_THIRTY_TWO_RELAY_STATE                     0x04d4



#define ONE_MODULE_OUTPUT_STATE                                     0x04d5
#define ONE_MODULE_OUTPUT_VOL                                          0x04d6
#define ONE_MODULE_OUTPUT_CURRENT                              0x04d8
#define ONE_MODULE_TEMPERATURE                                      0x04da

#define TWO_MODULE_OUTPUT_STATE                                     0x04db
#define TWO_MODULE_OUTPUT_VOL                                          0x04dc
#define TWO_MODULE_OUTPUT_CURRENT                              0x04de
#define TWO_MODULE_TEMPERATURE                                      0x04e0

#define THREE_MODULE_OUTPUT_STATE                                     0x04e1
#define THREE_MODULE_OUTPUT_VOL                                          0x04e2
#define THREE_MODULE_OUTPUT_CURRENT                              0x04e4
#define THREE_MODULE_TEMPERATURE                                      0x04e6

#define FOUR_MODULE_OUTPUT_STATE                                     0x04e7
#define FOUR_MODULE_OUTPUT_VOL                                          0x04e8
#define FOUR_MODULE_OUTPUT_CURRENT                              0x04ea
#define FOUR_MODULE_TEMPERATURE                                      0x04ec

#define FIVE_MODULE_OUTPUT_STATE                                     0x04ed
#define FIVE_MODULE_OUTPUT_VOL                                          0x04ee
#define FIVE_MODULE_OUTPUT_CURRENT                              0x04f0
#define FIVE_MODULE_TEMPERATURE                                      0x04f2

#define SIX_MODULE_OUTPUT_STATE                                     0x04f3
#define SIX_MODULE_OUTPUT_VOL                                          0x04f4
#define SIX_MODULE_OUTPUT_CURRENT                              0x04f6
#define SIX_MODULE_TEMPERATURE                                      0x04f8

#define SEVEN_MODULE_OUTPUT_STATE                                     0x04f9
#define SEVEN_MODULE_OUTPUT_VOL                                          0x04fa
#define SEVEN_MODULE_OUTPUT_CURRENT                              0x04fc
#define SEVEN_MODULE_TEMPERATURE                                      0x04fe

#define EIGHT_MODULE_OUTPUT_STATE                                     0x04ff
#define EIGHT_MODULE_OUTPUT_VOL                                          0x0500
#define EIGHT_MODULE_OUTPUT_CURRENT                              0x0502
#define EIGHT_MODULE_TEMPERATURE                                      0x0504

#define NINE_MODULE_OUTPUT_STATE                                     0x0505
#define NINE_MODULE_OUTPUT_VOL                                          0x0506
#define NINE_MODULE_OUTPUT_CURRENT                              0x0508
#define NINE_MODULE_TEMPERATURE                                      0x050a

#define TEN_MODULE_OUTPUT_STATE                                     0x050b
#define TEN_MODULE_OUTPUT_VOL                                          0x050c
#define TEN_MODULE_OUTPUT_CURRENT                              0x050e
#define TEN_MODULE_TEMPERATURE                                      0x0510

#define ELEVEN_MODULE_OUTPUT_STATE                                     0x0511
#define ELEVEN_MODULE_OUTPUT_VOL                                          0x0512
#define ELEVEN_MODULE_OUTPUT_CURRENT                              0x0514
#define ELEVEN_MODULE_TEMPERATURE                                      0x0516

#define TWELVE_MODULE_OUTPUT_STATE                                     0x0517
#define TWELVE_MODULE_OUTPUT_VOL                                          0x0518
#define TWELVE_MODULE_OUTPUT_CURRENT                              0x051a
#define TWELVE_MODULE_TEMPERATURE                                      0x051c

#define THIRTEEN_MODULE_OUTPUT_STATE                                     0x051d
#define THIRTEEN_MODULE_OUTPUT_VOL                                          0x051e
#define THIRTEEN_MODULE_OUTPUT_CURRENT                              0x0520
#define THIRTEEN_MODULE_TEMPERATURE                                      0x0522

#define FOURTEEN_MODULE_OUTPUT_STATE                                     0x0523
#define FOURTEEN_MODULE_OUTPUT_VOL                                          0x0524
#define FOURTEEN_MODULE_OUTPUT_CURRENT                              0x0526
#define FOURTEEN_MODULE_TEMPERATURE                                      0x0528

#define FIFTEEN_MODULE_OUTPUT_STATE                                     0x0529
#define FIFTEEN_MODULE_OUTPUT_VOL                                          0x052a
#define FIFTEEN_MODULE_OUTPUT_CURRENT                              0x052c
#define FIFTEEN_MODULE_TEMPERATURE                                      0x052e

#define SIXTEEN_MODULE_OUTPUT_STATE                                     0x052f
#define SIXTEEN_MODULE_OUTPUT_VOL                                          0x0530
#define SIXTEEN_MODULE_OUTPUT_CURRENT                              0x0532
#define SIXTEEN_MODULE_TEMPERATURE                                      0x0534

#define SEVENTEEN_MODULE_OUTPUT_STATE                                     0x0535
#define SEVENTEEN_MODULE_OUTPUT_VOL                                          0x0536
#define SEVENTEEN_MODULE_OUTPUT_CURRENT                              0x0538
#define SEVENTEEN_MODULE_TEMPERATURE                                      0x053a

#define EIGHTTEEN_MODULE_OUTPUT_STATE                                     0x053b
#define EIGHTTEEN_MODULE_OUTPUT_VOL                                          0x053c
#define EIGHTTEEN_MODULE_OUTPUT_CURRENT                              0x053e
#define EIGHTTEEN_MODULE_TEMPERATURE                                      0x0540

#define NINIETEEN_MODULE_OUTPUT_STATE                                     0x0541
#define NINIETEEN_MODULE_OUTPUT_VOL                                          0x0542
#define NINIETEEN_MODULE_OUTPUT_CURRENT                              0x0544
#define NINIETEEN_MODULE_TEMPERATURE                                      0x0546

#define TWENTY_MODULE_OUTPUT_STATE                                     0x0547
#define TWENTY_MODULE_OUTPUT_VOL                                          0x0548
#define TWENTY_MODULE_OUTPUT_CURRENT                              0x054a
#define TWENTY_MODULE_TEMPERATURE                                      0x054c

#define TWENTY_ONE_MODULE_OUTPUT_STATE                                     0x054d
#define TWENTY_ONE_MODULE_OUTPUT_VOL                                          0x054e
#define TWENTY_ONE_MODULE_OUTPUT_CURRENT                              0x0550
#define TWENTY_ONE_MODULE_TEMPERATURE                                      0x0552

#define TWENTY_TWO_MODULE_OUTPUT_STATE                                     0x0553
#define TWENTY_TWO_MODULE_OUTPUT_VOL                                          0x0554
#define TWENTY_TWO_MODULE_OUTPUT_CURRENT                              0x0556
#define TWENTY_TWO_MODULE_TEMPERATURE                                      0x0558

#define TWENTY_THREE_MODULE_OUTPUT_STATE                                     0x0559
#define TWENTY_THREE_MODULE_OUTPUT_VOL                                          0x055a
#define TWENTY_THREE_MODULE_OUTPUT_CURRENT                              0x055c
#define TWENTY_THREE_MODULE_TEMPERATURE                                      0x055e

#define TWENTY_FOUR_MODULE_OUTPUT_STATE                                     0x055f
#define TWENTY_FOUR_MODULE_OUTPUT_VOL                                          0x0560
#define TWENTY_FOUR_MODULE_OUTPUT_CURRENT                              0x0562
#define TWENTY_FOUR_MODULE_TEMPERATURE                                      0x0564

#define TWENTY_FIVE_MODULE_OUTPUT_STATE                                     0x0565
#define TWENTY_FIVE_MODULE_OUTPUT_VOL                                          0x0566
#define TWENTY_FIVE_MODULE_OUTPUT_CURRENT                              0x0568
#define TWENTY_FIVE_MODULE_TEMPERATURE                                      0x056a

#define TWENTY_SIX_MODULE_OUTPUT_STATE                                     0x056b
#define TWENTY_SIX_MODULE_OUTPUT_VOL                                          0x056c
#define TWENTY_SIX_MODULE_OUTPUT_CURRENT                              0x056e
#define TWENTY_SIX_MODULE_TEMPERATURE                                      0x0570

#define TWENTY_SEVEN_MODULE_OUTPUT_STATE                                     0x0571
#define TWENTY_SEVEN_MODULE_OUTPUT_VOL                                          0x0572
#define TWENTY_SEVEN_MODULE_OUTPUT_CURRENT                              0x0574
#define TWENTY_SEVEN_MODULE_TEMPERATURE                                      0x0576

#define TWENTY_EIGHT_MODULE_OUTPUT_STATE                                     0x0577
#define TWENTY_EIGHT_MODULE_OUTPUT_VOL                                          0x0578
#define TWENTY_EIGHT_MODULE_OUTPUT_CURRENT                              0x057a
#define TWENTY_EIGHT_MODULE_TEMPERATURE                                      0x057c

#define TWENTY_NINE_MODULE_OUTPUT_STATE                                     0x057d
#define TWENTY_NINE_MODULE_OUTPUT_VOL                                          0x057e
#define TWENTY_NINE_MODULE_OUTPUT_CURRENT                              0x0580
#define TWENTY_NINE_MODULE_TEMPERATURE                                      0x0582

#define THIRTY_MODULE_OUTPUT_STATE                                     0x0583
#define THIRTY_MODULE_OUTPUT_VOL                                          0x0584
#define THIRTY_MODULE_OUTPUT_CURRENT                              0x0586
#define THIRTY_MODULE_TEMPERATURE                                      0x0588

#define THIRTY_ONE_MODULE_OUTPUT_STATE                                     0x0589
#define THIRTY_ONE_MODULE_OUTPUT_VOL                                          0x058a
#define THIRTY_ONE_MODULE_OUTPUT_CURRENT                              0x058c
#define THIRTY_ONE_MODULE_TEMPERATURE                                      0x058e

#define THIRTY_TWO_MODULE_OUTPUT_STATE                                     0x058f
#define THIRTY_TWO_MODULE_OUTPUT_VOL                                          0x0590
#define THIRTY_TWO_MODULE_OUTPUT_CURRENT                              0x0592
#define THIRTY_TWO_MODULE_TEMPERATURE                                      0x0594

#define THIRTY_THREE_MODULE_OUTPUT_STATE                                     0x0595
#define THIRTY_THREE_MODULE_OUTPUT_VOL                                          0x0596
#define THIRTY_THREE_MODULE_OUTPUT_CURRENT                              0x0598
#define THIRTY_THREE_MODULE_TEMPERATURE                                      0x059a

#define THIRTY_FOUR_MODULE_OUTPUT_STATE                                     0x059b
#define THIRTY_FOUR_MODULE_OUTPUT_VOL                                          0x059c
#define THIRTY_FOUR_MODULE_OUTPUT_CURRENT                              0x059e
#define THIRTY_FOUR_MODULE_TEMPERATURE                                      0x05a0

#define THIRTY_FIVE_MODULE_OUTPUT_STATE                                     0x05a1
#define THIRTY_FIVE_MODULE_OUTPUT_VOL                                          0x05a2
#define THIRTY_FIVE_MODULE_OUTPUT_CURRENT                              0x05a4
#define THIRTY_FIVE_MODULE_TEMPERATURE                                      0x05a6

#define THIRTY_SIX_MODULE_OUTPUT_STATE                                     0x05a7
#define THIRTY_SIX_MODULE_OUTPUT_VOL                                          0x05a8
#define THIRTY_SIX_MODULE_OUTPUT_CURRENT                              0x05aa
#define THIRTY_SIX_MODULE_TEMPERATURE                                      0x05ac

#define THIRTY_SEVEN_MODULE_OUTPUT_STATE                                     0x05ad
#define THIRTY_SEVEN_MODULE_OUTPUT_VOL                                          0x05ae
#define THIRTY_SEVEN_MODULE_OUTPUT_CURRENT                              0x05b0
#define THIRTY_SEVEN_MODULE_TEMPERATURE                                      0x05b2

#define THIRTY_EIGHT_MODULE_OUTPUT_STATE                                     0x05b3
#define THIRTY_EIGHT_MODULE_OUTPUT_VOL                                          0x05b4
#define THIRTY_EIGHT_MODULE_OUTPUT_CURRENT                              0x05b6
#define THIRTY_EIGHT_MODULE_TEMPERATURE                                      0x05b8

#define THIRTY_NINE_MODULE_OUTPUT_STATE                                     0x05b9
#define THIRTY_NINE_MODULE_OUTPUT_VOL                                          0x05ba
#define THIRTY_NINE_MODULE_OUTPUT_CURRENT                              0x05bc
#define THIRTY_NINE_MODULE_TEMPERATURE                                      0x05be

#define FOURTY_MODULE_OUTPUT_STATE                                     0x05bf
#define FOURTY_MODULE_OUTPUT_VOL                                          0x05c0
#define FOURTY_MODULE_OUTPUT_CURRENT                              0x05c2
#define FOURTY_MODULE_TEMPERATURE                                      0x05c4

#define FOURTY_ONE_MODULE_OUTPUT_STATE                                     0x05c5
#define FOURTY_ONE_MODULE_OUTPUT_VOL                                          0x05c6
#define FOURTY_ONE_MODULE_OUTPUT_CURRENT                              0x05c8
#define FOURTY_ONE_MODULE_TEMPERATURE                                      0x05ca

#define FOURTY_TWO_MODULE_OUTPUT_STATE                                     0x05cb
#define FOURTY_TWO_MODULE_OUTPUT_VOL                                          0x05cc
#define FOURTY_TWO_MODULE_OUTPUT_CURRENT                              0x05ce
#define FOURTY_TWO_MODULE_TEMPERATURE                                      0x05d0

#define FOURTY_THREE_MODULE_OUTPUT_STATE                                     0x05d1
#define FOURTY_THREE_MODULE_OUTPUT_VOL                                          0x05d2
#define FOURTY_THREE_MODULE_OUTPUT_CURRENT                              0x05d4
#define FOURTY_THREE_MODULE_TEMPERATURE                                      0x05d6

#define FOURTY_FOUR_MODULE_OUTPUT_STATE                                     0x05d7
#define FOURTY_FOUR_MODULE_OUTPUT_VOL                                          0x05d8
#define FOURTY_FOUR_MODULE_OUTPUT_CURRENT                              0x05da
#define FOURTY_FOUR_MODULE_TEMPERATURE                                      0x05dc

#define FOURTY_FIVE_MODULE_OUTPUT_STATE                                     0x05dd
#define FOURTY_FIVE_MODULE_OUTPUT_VOL                                          0x05de
#define FOURTY_FIVE_MODULE_OUTPUT_CURRENT                              0x05e0
#define FOURTY_FIVE_MODULE_TEMPERATURE                                      0x05e2

#define FOURTY_SIX_MODULE_OUTPUT_STATE                                     0x05e3
#define FOURTY_SIX_MODULE_OUTPUT_VOL                                          0x05e4
#define FOURTY_SIX_MODULE_OUTPUT_CURRENT                              0x05e6
#define FOURTY_SIX_MODULE_TEMPERATURE                                      0x05e8

#define FOURTY_SEVEN_MODULE_OUTPUT_STATE                                     0x05e9
#define FOURTY_SEVEN_MODULE_OUTPUT_VOL                                          0x05ea
#define FOURTY_SEVEN_MODULE_OUTPUT_CURRENT                              0x05ec
#define FOURTY_SEVEN_MODULE_TEMPERATURE                                      0x05ee

#define FOURTY_EIGHT_MODULE_OUTPUT_STATE                                     0x05ef
#define FOURTY_EIGHT_MODULE_OUTPUT_VOL                                          0x05f0
#define FOURTY_EIGHT_MODULE_OUTPUT_CURRENT                              0x05f2
#define FOURTY_EIGHT_MODULE_TEMPERATURE                                      0x05f4

#define ONE_MODULE_SET_VOL_ID                                                 0x0635


#define RELAY_FAULT_ADDR       0x05f5


#define MATRIX_ONE_RELAY_CONTROL                                              0x2000
#define MATRIX_TWO_RELAY_CONTROL                                              0x2001
#define MATRIX_THREE_RELAY_CONTROL                                         0x2002
#define MATRIX_FOUR_RELAY_CONTROL                                            0x2003
#define MATRIX_FIVE_RELAY_CONTROL                                              0x2004
#define MATRIX_SIX_RELAY_CONTROL                                                 0x2005
#define MATRIX_SEVEN_RELAY_CONTROL                                          0x2006
#define MATRIX_EIGHT_RELAY_CONTROL                                            0x2007
#define MATRIX_NINE_RELAY_CONTROL                                              0x2008
#define MATRIX_TEN_RELAY_CONTROL                                                0x2009
#define MATRIX_ELEVEN_RELAY_CONTROL                                        0x200a
#define MATRIX_TWELVE_RELAY_CONTROL                                        0x200b
#define MATRIX_THIRTEEN_RELAY_CONTROL                                     0x200c
#define MATRIX_FOURTEEN_RELAY_CONTROL                                   0x200d
#define MATRIX_FIFTEEN_RELAY_CONTROL                                         0x200e
#define MATRIX_SIXTEEN_RELAY_CONTROL                                        0x200f
#define MATRIX_SEVENTEEN_RELAY_CONTROL                                 0x2010
#define MATRIX_EIGHTTEEN_RELAY_CONTROL                                   0x2011
#define MATRIX_NINETEEN_RELAY_CONTROL                                     0x2012
#define MATRIX_TWENTY_RELAY_CONTROL                                         0x2013
#define MATRIX_TWENTY_ONE_RELAY_CONTROL                              0x2014
#define MATRIX_TWENTY_TWO_RELAY_CONTROL                              0x2015
#define MATRIX_TWENTY_THREE_RELAY_CONTROL                          0x2016
#define MATRIX_TWENTY_FOUR_RELAY_CONTROL                            0x2017
#define MATRIX_TWENTY_FIVE_RELAY_CONTROL                               0x2018
#define MATRIX_TWENTY_SIX_RELAY_CONTROL                                 0x2019
#define MATRIX_TWENTY_SEVEN_RELAY_CONTROL                          0x201a
#define MATRIX_TWENTY_EIGHT_RELAY_CONTROL                            0x201b
#define MATRIX_TWENTY_NINE_RELAY_CONTROL                               0x201c
#define MATRIX_THIRTY_RELAY_CONTROL                                             0x201d
#define MATRIX_THIRTY_ONE_RELAY_CONTROL                                  0x201e
#define MATRIX_THIRTY_TWO_RELAY_CONTROL                                  0x201f


#define ONE_MODULE_OUTPUT_VOL_CONTROL                                     0x2020
#define ONE_MODULE_OUTPUT_CURRENT_CONTROL                         0x2021
#define ONE_MODULE_OUTPUT_SWITCH_CONTROL                             0x2022

#define TWO_MODULE_OUTPUT_VOL_CONTROL                                     0x2023
#define TWO_MODULE_OUTPUT_CURRENT_CONTROL                         0x2024
#define TWO_MODULE_OUTPUT_SWITCH_CONTROL                             0x2025

#define THREE_MODULE_OUTPUT_VOL_CONTROL                                     0x2026
#define THREE_MODULE_OUTPUT_CURRENT_CONTROL                         0x2027
#define THREE_MODULE_OUTPUT_SWITCH_CONTROL                             0x2028

#define FOUR_MODULE_OUTPUT_VOL_CONTROL                                     0x2029
#define FOUR_MODULE_OUTPUT_CURRENT_CONTROL                         0x202a
#define FOUR_MODULE_OUTPUT_SWITCH_CONTROL                             0x202b

#define FIVE_MODULE_OUTPUT_VOL_CONTROL                                     0x202c
#define FIVE_MODULE_OUTPUT_CURRENT_CONTROL                         0x202d
#define FIVE_MODULE_OUTPUT_SWITCH_CONTROL                             0x202e

#define SIX_MODULE_OUTPUT_VOL_CONTROL                                     0x202f
#define SIX_MODULE_OUTPUT_CURRENT_CONTROL                         0x2030
#define SIX_MODULE_OUTPUT_SWITCH_CONTROL                             0x2031

#define SEVEN_MODULE_OUTPUT_VOL_CONTROL                                     0x2032
#define SEVEN_MODULE_OUTPUT_CURRENT_CONTROL                         0x2033
#define SEVEN_MODULE_OUTPUT_SWITCH_CONTROL                             0x2034

#define EIGHT_MODULE_OUTPUT_VOL_CONTROL                                     0x2035
#define EIGHT_MODULE_OUTPUT_CURRENT_CONTROL                         0x2036
#define EIGHT_MODULE_OUTPUT_SWITCH_CONTROL                             0x2037

#define NINE_MODULE_OUTPUT_VOL_CONTROL                                     0x2038
#define NINE_MODULE_OUTPUT_CURRENT_CONTROL                         0x2039
#define NINE_MODULE_OUTPUT_SWITCH_CONTROL                             0x203a

#define TEN_MODULE_OUTPUT_VOL_CONTROL                                     0x203b
#define TEN_MODULE_OUTPUT_CURRENT_CONTROL                         0x203c
#define TEN_MODULE_OUTPUT_SWITCH_CONTROL                             0x203d

#define ELEVEN_MODULE_OUTPUT_VOL_CONTROL                                     0x203e
#define ELEVEN_MODULE_OUTPUT_CURRENT_CONTROL                         0x203f
#define ELEVEN_MODULE_OUTPUT_SWITCH_CONTROL                             0x2040

#define TWELVE_MODULE_OUTPUT_VOL_CONTROL                                     0x2041
#define TWELVE_MODULE_OUTPUT_CURRENT_CONTROL                         0x2042
#define TWELVE_MODULE_OUTPUT_SWITCH_CONTROL                             0x2043

#define THIRTEEN_MODULE_OUTPUT_VOL_CONTROL                                     0x2044
#define THIRTEEN_MODULE_OUTPUT_CURRENT_CONTROL                         0x2045
#define THIRTEEN_MODULE_OUTPUT_SWITCH_CONTROL                             0x2046

#define FOURTEEN_MODULE_OUTPUT_VOL_CONTROL                                     0x2047
#define FOURTEEN_MODULE_OUTPUT_CURRENT_CONTROL                         0x2048
#define FOURTEEN_MODULE_OUTPUT_SWITCH_CONTROL                             0x2049

#define FIFTEEN_MODULE_OUTPUT_VOL_CONTROL                                     0x204a
#define FIFTEEN_MODULE_OUTPUT_CURRENT_CONTROL                         0x204b
#define FIFTEEN_MODULE_OUTPUT_SWITCH_CONTROL                             0x204c

#define SIXTEEN_MODULE_OUTPUT_VOL_CONTROL                                     0x204d
#define SIXTEEN_MODULE_OUTPUT_CURRENT_CONTROL                         0x204e
#define SIXTEEN_MODULE_OUTPUT_SWITCH_CONTROL                             0x204f

#define SEVENTEEN_MODULE_OUTPUT_VOL_CONTROL                                     0x2050
#define SEVENTEEN_MODULE_OUTPUT_CURRENT_CONTROL                         0x2051
#define SEVENTEEN_MODULE_OUTPUT_SWITCH_CONTROL                             0x2052

#define EIGHTTEEN_MODULE_OUTPUT_VOL_CONTROL                                     0x2053
#define EIGHTTEEN_MODULE_OUTPUT_CURRENT_CONTROL                         0x2054
#define EIGHTTEEN_MODULE_OUTPUT_SWITCH_CONTROL                             0x2055

#define NINETEEN_MODULE_OUTPUT_VOL_CONTROL                                     0x2056
#define NINETEEN_MODULE_OUTPUT_CURRENT_CONTROL                         0x2057
#define NINETEEN_MODULE_OUTPUT_SWITCH_CONTROL                             0x2058

#define TWENTY_MODULE_OUTPUT_VOL_CONTROL                                     0x2059
#define TWENTY_MODULE_OUTPUT_CURRENT_CONTROL                         0x205a
#define TWENTY_MODULE_OUTPUT_SWITCH_CONTROL                             0x205b

#define TWENTY_ONE_MODULE_OUTPUT_VOL_CONTROL                                     0x205c
#define TWENTY_ONE_MODULE_OUTPUT_CURRENT_CONTROL                         0x205d
#define TWENTY_ONE_MODULE_OUTPUT_SWITCH_CONTROL                             0x205e

#define TWENTY_TWO_MODULE_OUTPUT_VOL_CONTROL                                     0x205f
#define TWENTY_TWO_MODULE_OUTPUT_CURRENT_CONTROL                         0x2060
#define TWENTY_TWO_MODULE_OUTPUT_SWITCH_CONTROL                             0x2061

#define TWENTY_THREE_MODULE_OUTPUT_VOL_CONTROL                                     0x2062
#define TWENTY_THREE_MODULE_OUTPUT_CURRENT_CONTROL                         0x2063
#define TWENTY_THREE_MODULE_OUTPUT_SWITCH_CONTROL                             0x2064

#define TWENTY_FOUR_MODULE_OUTPUT_VOL_CONTROL                                     0x2065
#define TWENTY_FOUR_MODULE_OUTPUT_CURRENT_CONTROL                         0x2066
#define TWENTY_FOUR_MODULE_OUTPUT_SWITCH_CONTROL                             0x2067

#define TWENTY_FIVE_MODULE_OUTPUT_VOL_CONTROL                                     0x2068
#define TWENTY_FIVE_MODULE_OUTPUT_CURRENT_CONTROL                         0x2069
#define TWENTY_FIVE_MODULE_OUTPUT_SWITCH_CONTROL                             0x206a

#define TWENTY_SIX_MODULE_OUTPUT_VOL_CONTROL                                     0x206b
#define TWENTY_SIX_MODULE_OUTPUT_CURRENT_CONTROL                         0x206c
#define TWENTY_SIX_MODULE_OUTPUT_SWITCH_CONTROL                             0x206d

#define TWENTY_SEVEN_MODULE_OUTPUT_VOL_CONTROL                                     0x206e
#define TWENTY_SEVEN_MODULE_OUTPUT_CURRENT_CONTROL                         0x206f
#define TWENTY_SEVEN_MODULE_OUTPUT_SWITCH_CONTROL                             0x2070

#define TWENTY_EIGHT_MODULE_OUTPUT_VOL_CONTROL                                     0x2071
#define TWENTY_EIGHT_MODULE_OUTPUT_CURRENT_CONTROL                         0x2072
#define TWENTY_EIGHT_MODULE_OUTPUT_SWITCH_CONTROL                             0x2073

#define TWENTY_NINE_MODULE_OUTPUT_VOL_CONTROL                                     0x2074
#define TWENTY_NINE_MODULE_OUTPUT_CURRENT_CONTROL                         0x2075
#define TWENTY_NINE_MODULE_OUTPUT_SWITCH_CONTROL                             0x2076

#define THIRTY_MODULE_OUTPUT_VOL_CONTROL                                     0x2077
#define THIRTY_MODULE_OUTPUT_CURRENT_CONTROL                         0x2078
#define THIRTY_MODULE_OUTPUT_SWITCH_CONTROL                             0x2079

#define THIRTY_ONE_MODULE_OUTPUT_VOL_CONTROL                                     0x207a
#define THIRTY_ONE_MODULE_OUTPUT_CURRENT_CONTROL                         0x207b
#define THIRTY_ONE_MODULE_OUTPUT_SWITCH_CONTROL                             0x207c

#define THIRTY_TWO_MODULE_OUTPUT_VOL_CONTROL                                     0x207d
#define THIRTY_TWO_MODULE_OUTPUT_CURRENT_CONTROL                         0x207e
#define THIRTY_TWO_MODULE_OUTPUT_SWITCH_CONTROL                             0x207f

#define THIRTY_THREE_MODULE_OUTPUT_VOL_CONTROL                                     0x2080
#define THIRTY_THREE_MODULE_OUTPUT_CURRENT_CONTROL                         0x2081
#define THIRTY_THREE_MODULE_OUTPUT_SWITCH_CONTROL                             0x2082

#define THIRTY_FOUR_MODULE_OUTPUT_VOL_CONTROL                                     0x2083
#define THIRTY_FOUR_MODULE_OUTPUT_CURRENT_CONTROL                         0x2084
#define THIRTY_FOUR_MODULE_OUTPUT_SWITCH_CONTROL                             0x2085

#define THIRTY_FIVE_MODULE_OUTPUT_VOL_CONTROL                                     0x2086
#define THIRTY_FIVE_MODULE_OUTPUT_CURRENT_CONTROL                         0x2087
#define THIRTY_FIVE_MODULE_OUTPUT_SWITCH_CONTROL                             0x2088

#define THIRTY_SIX_MODULE_OUTPUT_VOL_CONTROL                                     0x2089
#define THIRTY_SIX_MODULE_OUTPUT_CURRENT_CONTROL                         0x208a
#define THIRTY_SIX_MODULE_OUTPUT_SWITCH_CONTROL                             0x208b

#define THIRTY_SEVEN_MODULE_OUTPUT_VOL_CONTROL                                     0x208c
#define THIRTY_SEVEN_MODULE_OUTPUT_CURRENT_CONTROL                         0x208d
#define THIRTY_SEVEN_MODULE_OUTPUT_SWITCH_CONTROL                             0x208e

#define THIRTY_EIGHT_MODULE_OUTPUT_VOL_CONTROL                                     0x208f
#define THIRTY_EIGHT_MODULE_OUTPUT_CURRENT_CONTROL                         0x2090
#define THIRTY_EIGHT_MODULE_OUTPUT_SWITCH_CONTROL                             0x2091

#define THIRTY_NINE_MODULE_OUTPUT_VOL_CONTROL                                     0x2092
#define THIRTY_NINE_MODULE_OUTPUT_CURRENT_CONTROL                         0x2093
#define THIRTY_NINE_MODULE_OUTPUT_SWITCH_CONTROL                             0x2094

#define FOURTY_MODULE_OUTPUT_VOL_CONTROL                                     0x2095
#define FOURTY_MODULE_OUTPUT_CURRENT_CONTROL                         0x2096
#define FOURTY_MODULE_OUTPUT_SWITCH_CONTROL                             0x2097

#define FOURTY_ONE_MODULE_OUTPUT_VOL_CONTROL                                     0x2098
#define FOURTY_ONE_MODULE_OUTPUT_CURRENT_CONTROL                         0x2099
#define FOURTY_ONE_MODULE_OUTPUT_SWITCH_CONTROL                             0x209a

#define FOURTY_TWO_MODULE_OUTPUT_VOL_CONTROL                                     0x209b
#define FOURTY_TWO_MODULE_OUTPUT_CURRENT_CONTROL                         0x209c
#define FOURTY_TWO_MODULE_OUTPUT_SWITCH_CONTROL                             0x209d

#define FOURTY_THREE_MODULE_OUTPUT_VOL_CONTROL                                     0x209e
#define FOURTY_THREE_MODULE_OUTPUT_CURRENT_CONTROL                         0x209f
#define FOURTY_THREE_MODULE_OUTPUT_SWITCH_CONTROL                             0x20a0

#define FOURTY_FOUR_MODULE_OUTPUT_VOL_CONTROL                                     0x20a1
#define FOURTY_FOUR_MODULE_OUTPUT_CURRENT_CONTROL                         0x20a2
#define FOURTY_FOUR_MODULE_OUTPUT_SWITCH_CONTROL                             0x20a3

#define FOURTY_FIVE_MODULE_OUTPUT_VOL_CONTROL                                     0x20a4
#define FOURTY_FIVE_MODULE_OUTPUT_CURRENT_CONTROL                         0x20a5
#define FOURTY_FIVE_MODULE_OUTPUT_SWITCH_CONTROL                             0x20a6

#define FOURTY_SIX_MODULE_OUTPUT_VOL_CONTROL                                     0x20a7
#define FOURTY_SIX_MODULE_OUTPUT_CURRENT_CONTROL                         0x20a8
#define FOURTY_SIX_MODULE_OUTPUT_SWITCH_CONTROL                             0x20a9

#define FOURTY_SEVEN_MODULE_OUTPUT_VOL_CONTROL                                     0x20aa
#define FOURTY_SEVEN_MODULE_OUTPUT_CURRENT_CONTROL                         0x20ab
#define FOURTY_SEVEN_MODULE_OUTPUT_SWITCH_CONTROL                             0x20ac

#define FOURTY_EIGHT_MODULE_OUTPUT_VOL_CONTROL                                     0x20ad
#define FOURTY_EIGHT_MODULE_OUTPUT_CURRENT_CONTROL                         0x20ae
#define FOURTY_EIGHT_MODULE_OUTPUT_SWITCH_CONTROL                             0x20af

#define CHARGER_FAN_CONTROl                                    0x20b0




#define SYSTEM_CONFIG_MODE                              0x2400
#define ENTRANCE_MODULE_NUM                         0x2469
#define ENTRANCE_MODULE_POWER                   0x246a
#define MODULE_PARTICLE                                       0x246b
#define FAN_MAX_OUT_PUT                                      0x246c
#define OPEN_FUN_TEMPERATURE                        0x246d




#define CLOULD_ON_LINE_STATE                            0x0401


#define ONE_GUN_VIP_CHARGE                              0x2000
#define TWO_GUN_VIP_CHARGE                              0x2001
#define THREE_GUN_VIP_CHARGE                         0x2002
#define FOUR_GUN_VIP_CHARGE                           0x2003
#define FIVE_GUN_VIP_CHARGE                              0x2004
#define SIX_GUN_VIP_CHARGE                                0x2005
#define SEVEN_GUN_VIP_CHARGE                         0x2006
#define EIGHT_GUN_VIP_CHARGE                           0x2007
#define NINE_GUN_VIP_CHARGE                             0x2008
#define TEN_GUN_VIP_CHARGE                               0x2009
#define ELEVEN_GUN_VIP_CHARGE                       0x200a
#define TWELVE_GUN_VIP_CHARGE                       0x200b
#define THIRTEEN_GUN_VIP_CHARGE                    0x200c
#define FOURTEEN_GUN_VIP_CHARGE                  0x200d
#define FIFTEEN_GUN_VIP_CHARGE                        0x200e
#define SIXTEEN_GUN_VIP_CHARGE                       0x200f



#define OUTSIDE_COMM_MAC_ADDR                           0x2467
#define OUTSIDE_COMM_OBTAIN_IP_TYPE                0x246a
#define OUTSIDE_COMM_IP_ADDR                                0x246b
#define OUTSIDE_COMM_SUBNET_MASK                   0x246d
#define OUTSIDE_COMM_GATEWAY                              0x246f
#define OUTSIDE_DNS_SERVICE                                     0x2471


#define ONE_GUN_IP_ADDR                                          0x2473
#define TWO_GUN_IP_ADDR                                          0x2475
#define THREE_GUN_IP_ADDR                                     0x2477
#define FOUR_GUN_IP_ADDR                                        0x2479
#define FIVE_GUN_IP_ADDR                                           0x247b
#define SIX_GUN_IP_ADDR                                             0x247d
#define SEVEN_GUN_IP_ADDR                                      0x247f
#define EIGHT_GUN_IP_ADDR                                        0x2481
#define NINE_GUN_IP_ADDR                                          0x2483
#define TEN_GUN_IP_ADDR                                            0x2485
#define ELEVEN_GUN_IP_ADDR                                    0x2487
#define TWELVE_GUN_IP_ADDR                                    0x2489
#define THIRTEEN_GUN_IP_ADDR                                0x248b
#define FOURTEEN_GUN_IP_ADDR                              0x248d
#define FIFTEEN_GUN_IP_ADDR                                    0x248f
#define SIXTEEN_GUN_IP_ADDR                                   0x2491


#define POWER_BOARD_IP_ADDR                         0x2493
#define VIP_INSERT_AND_CHARGE                       0x2495

#define INSERT_TOTAL_GUN_NUM                         0x2496

#define ONE_GUN_CONFIG                                        0x2497
#define TWO_GUN_CONFIG                                        0x2498
#define THREE_GUN_CONFIG                                    0x2499
#define FOUR_GUN_CONFIG                                      0x249a
#define FIVE_GUN_CONFIG                                         0x249b
#define SIX_GUN_CONFIG                                           0x249c
#define SEVEN_GUN_CONFIG                                    0x249d
#define EIGHT_GUN_CONFIG                                      0x249e
#define NINE_GUN_CONFIG                                        0x24af
#define TEN_GUN_CONFIG                                          0x24a0
#define ELEVEN_GUN_CONFIG                                  0x24a1
#define TWELVE_GUN_CONFIG                                  0x24a2
#define THIRTEEN_GUN_CONFIG                              0x24a3
#define FOURTEEN_GUN_CONFIG                            0x24a4
#define FIFTEEN_GUN_CONFIG                                  0x24a5
#define SIXTEEN_GUN_CONFIG                                  0x24a6


#define OPERATE_CLOUD_TYPE                                                   0x24a7
#define OPERATE_CLOUD_IP                                                         0x24a8
#define OPERATE_CLOUD_PORT                                                  0x2528
#define OPERATE_CLOUD_SERIAL_CODE                                0x2529
#define MONITOR_CLOUD_TYPE                                                0x2539
#define MONITOR_CLOUD_IP                                                       0x253a
#define MONITOR_CLOUD_PORT                                                0x25ba
#define MONITOR_CLOUD_SERIAL_CODE                              0x25bb


#define OPEN_OTHER_FUNCTION                          0x25cb                          
#define CHARGE_COST_MODE                               0x25cc

#define SHARP_CHAEGE_RATE                            0x25cd
#define PEAK_CHARGE_RATE                               0x25cf
#define FLAT_CHARGE_RATE                                0x25d1
#define VALLEY_CHARGE_RATE                          0x24d3


#define SHARP_SERVICE_RATE                            0x25d5
#define PEAK_SERVICE_RATE                               0x25d7
#define FLAT_SERVICE_RATE                                0x25d9
#define VALLEY_SERVICE_RATE                          0x25db

#define SECTION_RATE                                           0x25dd

#define ADD_PARK_COST                                   0x25f5
#define PARK_RATE                                              0x25f6


#define FC_OFF_LINE_UP_LOAD                              0x25f8


#define GW_PRODUCT_CLOUD_ON_LINE            0x25f9
#define GW_DEVICE_MONITOR_FREQ                   0x25fa
#define GW_GUN_CHARGING_FREQ                      0x25fb
#define GW_GUN_UNCHARGEING_FREQ             0x25fc
#define GW_ALARM_FREQ                                        0x25fd
#define GW_AC_MATER_VALUE_FREQ                0x25fe
#define GW_DC_MATER_VALUE_FREQ                0x25ff
#define GW_OFF_LINE_CHARGE_TIME                 0x2600
#define GW_FLOOR_LOCK_FREQ                           0x2601
#define GW_GATE_LOCK_FREQ                             0x2602
#define GW_OFF_LINE_STOP                                   0x2603

#endif
