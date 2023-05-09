#ifndef __PROJ_DEBUG__
#define __PROJ_DEBUG__
#include <stdarg.h>
#include "utily.h"

//#define PROJ_TRACE
#define PROJ_SOFT
#define PROJ_CHARGER_MODULE
//#define PROJ_RECEIVER
//#define PROJ_UI
//#define PROJ_TRACE_ERROR
#define PROJ_HISTROY
//#define PROJ_REMOTE
//#define PROJ_GPIO
//#define PROJ_CAN
#define PROJ_METER
//#define PROJ_ONE_INFO
//#define PROJ_MONITOR
//#define PROJ_PAGE
//#define PROJ_ICCARD
//#define PROJ_TEST
#define PROJ_SOCKET
//#define PROJ_COLLECTION

//#define PROJ_FILE_PRINT
//#define PROJ_MONITOR_DATA_INFO
//#define PROJ_LOCAL_REMOTE
//#define PROJ_PROTOCOL

#define COLOR_NONE                                "\033[0m"
#define FONT_COLOR_RED                        "\033[0;31m"
#define FONT_COLOR_BLUE                      "\033[1;34m"
#define BACKGROUND_COLOR_RED        "\033[41m"    
#define BG_RED_FONT_YELLOW               "\033[41;33m"
#define NONE                                              "\e[0m"
#define BLACK                                             "\e[0;30m"
#define L_BLACK                                         "\e[1;30m"
#define RED                                                 "\e[0;31m"
#define L_RED                                             "\e[1;31m"
#define GREEN                                            "\e[0;32m"
#define L_GREEN                                        "\e[1;32m"
#define BROWN                                         "\e[0;33m"
#define YELLOW                                         "\e[1;33m"
#define BLUE                                              "\e[0;34m"
#define L_BLUE                                          "\e[1;34m"
#define PURPLE                                         "\e[0;35m"
#define L_PURPLE                                     "\e[1;35m"
#define CYAN                                             "\e[0;36m"
#define L_CYAN                                         "\e[1;36m"
#define GRAY                                             "\e[0;37m"
#define WHITE                                          "\e[1;37m"

#define BOLD                                            "\e[1m"
#define UNDERLINE                                 "\e[4m"
#define BLINK                                           "\e[5m"
#define REVERSE                                       "\e[7m"
#define HIDE                                             "\e[8m"
#define CLEAR                                          "\e[2J"
#define CLRLINE                                      "\r\e[K" //or "\e[1K\r"

#ifdef PROJ_PROTOCOL
#define TRACE_DATE_CENTER_INFO( varformat... )    \
        do                          \
        {                           \
            Message (GREEN"[receiver] file:%s [%d] func:%s  \n"GREEN,__FILE__, __LINE__, __func__); \
            Message (varformat);                        \
        } while(0)
#else
#define TRACE_DATE_CENTER_INFO( varformat... )  do ; while ( 0 )      /* nothing */
#endif


#ifdef PROJ_SOCKET
#define TRACE_PROJ_SOCKET_INFO( varformat... )    \
        do                          \
        {                           \
            Message (GRAY"[trace]file:%s [%d] func:%s  \n"GRAY,__FILE__, __LINE__, __func__); \
            Message (varformat);                        \
        } while(0)
#else
#define TRACE_PROJ_SOCKET_INFO( varformat... )  do ; while ( 0 )      /* nothing */
#endif


#ifdef PROJ_REMOTE
#define TRACE_PROJ_REMOTE_INFO( varformat... )    \
        do                          \
        {                           \
            Message (GRAY"[trace]file:%s [%d] func:%s  \n"GRAY,__FILE__, __LINE__, __func__); \
            Message (varformat);                        \
        } while(0)
#else
#define TRACE_PROJ_REMOTE_INFO( varformat... )  do ; while ( 0 )      /* nothing */
#endif


#ifdef PROJ_LOCAL_REMOTE
#define TRACE_PROJ_LOCAL_REMOTE_INFO( varformat... )    \
        do                          \
        {                           \
            Message (GRAY"[trace error]file:%s [%d] func:%s  \n"GRAY,__FILE__, __LINE__, __func__); \
            Message (varformat);                        \
        } while(0)
#else
#define TRACE_PROJ_LOCAL_REMOTE_INFO( varformat... )  do ; while ( 0 )      /* nothing */
#endif




#ifdef PROJ_HISTROY
#define TRACE_PROJ_HISTORY_INFO( varformat... )    \
        do                          \
        {                           \
            Message (BG_RED_FONT_YELLOW"[trace error]file:%s [%d] func:%s  \n"BG_RED_FONT_YELLOW,__FILE__, __LINE__, __func__); \
            Message (varformat);                        \
        } while(0)
#else
#define TRACE_PROJ_HISTORY_INFO( varformat... )  do ; while ( 0 )      /* nothing */
#endif




#ifdef PROJ_ONE_INFO
#define TRACE_PROJ_ONE_INFO( varformat... )    \
        do                          \
        {                           \
            Message (FONT_COLOR_RED"[trace error]file:%s [%d] func:%s  \n"FONT_COLOR_RED,__FILE__, __LINE__, __func__); \
            Message (varformat);                        \
        } while(0)
#else
#define TRACE_PROJ_ONE_INFO( varformat... )  do ; while ( 0 )      /* nothing */
#endif

#ifdef PROJ_MONITOR_DATA_INFO
#define TRACE_PROJ_MONITOR_DATA_INFO( varformat... )    \
        do                          \
        {                           \
            Message (FONT_COLOR_RED"[trace error]file:%s [%d] func:%s  \n"FONT_COLOR_RED,__FILE__, __LINE__, __func__); \
            Message (varformat);                        \
        } while(0)
#else
#define TRACE_PROJ_MONITOR_DATA_INFO( varformat... )  do ; while ( 0 )      /* nothing */
#endif





#ifdef PROJ_TRACE_ERROR
#define TRACE_PROJ_ERROR( varformat... )    \
        do                          \
        {                           \
            Message (FONT_COLOR_RED"[trace error]file:%s [%d] func:%s  \n"FONT_COLOR_RED,__FILE__, __LINE__, __func__); \
            Message (varformat);                        \
        } while(0)
#else
#define TRACE_PROJ_ERROR( varformat... )  do ; while ( 0 )      /* nothing */
#endif



#ifdef PROJ_TRACE
#define TRACE_PROJ_INFO( varformat... )    \
        do                          \
        {                           \
            Message (L_GREEN"[trace info] file:%s [%d] func:%s  \n"L_GREEN,__FILE__, __LINE__, __func__); \
            Message (varformat);                        \
        } while(0)
#else
#define TRACE_PROJ_INFO( varformat... )  do ; while ( 0 )      /* nothing */
#endif


#ifdef PROJ_SOFT
#define TRACE_SOFT_INFO( varformat... )    \
        do                          \
        {                           \
            Message (FONT_COLOR_BLUE"[maincontrol] file:%s [%d] func:%s  \n"FONT_COLOR_BLUE,__FILE__, __LINE__, __func__); \
            Message (varformat);                        \
        } while(0)
#else
#define TRACE_CORE_INFO( varformat... )  do ; while ( 0 )      /* nothing */
#endif


#ifdef PROJ_CHARGER_MODULE

#define TRACE_CHARGER_MODULE_INFO( varformat... )    \
        do                          \
        {                           \
            Message (PURPLE"[chargermodule] file:%s [%d] func:%s  \n"PURPLE,__FILE__, __LINE__, __func__); \
            Message (varformat);                        \
        } while(0)
#else
#define TRACE_CHARGER_MODULE_INFO( varformat... )  do ; while ( 0 )      /* nothing */
#endif


#ifdef PROJ_RECEIVER

#define TRACE_RECEIVER_INFO( varformat... )    \
        do                          \
        {                           \
            Message (YELLOW"[receiver] file:%s [%d] func:%s  \n"YELLOW,__FILE__, __LINE__, __func__); \
            Message (varformat);                        \
        } while(0)
#else
#define TRACE_RECEIVER_INFO( varformat... )  do ; while ( 0 )      /* nothing */
#endif



#ifdef PROJ_UI
#define TRACE_UI_INFO( varformat... )    \
        do                          \
        {                           \
            Message (BG_RED_FONT_YELLOW"[ui] file:%s [%d] func:%s  \n"BG_RED_FONT_YELLOW,__FILE__, __LINE__, __func__); \
            Message (varformat);                        \
        } while(0)
#else
#define TRACE_UI_INFO( varformat... )  do ; while ( 0 )      /* nothing */
#endif



#ifdef PROJ_PAGE
#define TRACE_PAGE_INFO( varformat... )    \
        do                          \
        {                           \
            Message (BG_RED_FONT_YELLOW"[ui] file:%s [%d] func:%s  \n"BG_RED_FONT_YELLOW,__FILE__, __LINE__, __func__); \
            Message (varformat);                        \
        } while(0)
#else
#define TRACE_PAGE_INFO( varformat... )  do ; while ( 0 )      /* nothing */
#endif


#ifdef PROJ_GPIO
#define TRACE_GPIO_INFO( varformat... )    \
        do                          \
        {                           \
            Message (GRAY"[gpio] file:%s [%d] func:%s  \n"GRAY,__FILE__, __LINE__, __func__); \
            Message (varformat);                        \
        } while(0)
#else
#define TRACE_GPIO_INFO( varformat... )  do ; while ( 0 )      /* nothing */
#endif


#ifdef PROJ_CAN
#define TRACE_CAN_INFO( varformat... )    \
 do                          \
 {                           \
            Message (GRAY"[can module] file:%s [%d] func:%s  \n"GRAY,__FILE__, __LINE__, __func__); \
            Message (varformat);                        \
 } while(0)
#else
#define TRACE_CAN_INFO( varformat... )  do ; while ( 0 )      /* nothing */
#endif


#ifdef PROJ_METER
#define TRACE_METER_INFO( varformat... )    \
do							\
{							\
	Message (BOLD"[meter] file:%s [%d] func:%s  \n"BOLD,__FILE__, __LINE__, __func__); \
	Message (varformat);						\
} while(0)
#else
#define TRACE_METER_INFO( varformat... )  do ; while ( 0 )      /* nothing */
#endif



#ifdef PROJ_MONITOR
#define TRACE_MONITOR_INFO( varformat... )    \
do							\
{							\
	Message (L_PURPLE"[monitor] file:%s [%d] func:%s  \n"L_PURPLE,__FILE__, __LINE__, __func__); \
	Message (varformat);						\
} while(0)
#else
#define TRACE_MONITOR_INFO( varformat... )  do ; while ( 0 )      /* nothing */
#endif

 
#ifdef PROJ_ICCARD
#define TRACE_ICCARD_INFO( varformat... )    \
do							\
{							\
	Message (L_PURPLE"[iccard] file:%s [%d] func:%s  \n"L_PURPLE,__FILE__, __LINE__, __func__); \
	Message (varformat);						\
} while(0)
#else
#define TRACE_ICCARD_INFO( varformat... )  do ; while ( 0 )      /* nothing */
#endif


#endif
