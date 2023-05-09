/**
*   @file       slx_timer.h
*	@author 	  	raulli
*	@version 	
*	@date    		25Dec2016
* 
* @if copyright_display
*		Copyright (c) 2016 SLX Inc.                  
*		All rights reserved                                
*	                                                                          
*	 	The content of this file or document is CONFIDENTIAL and PROPRIETARY     
*		to SLX Inc.  It is subject to the terms of a           
*		License Agreement between  SLXInc.        
*		restricting among other things, the use, reproduction, distribution      
*		and transfer.  Each of the embodiments, including this information and   
*		any derivative work shall retain this copyright notice.
* @endif
*	
* More description ...
*	
* @if modification_History
*	
*		<b>Modification History:\n</b>                                                    
*		Date				Name			Comment \n\n                             
*
*					                    
* @endif                                                                          
*/

#ifndef _PROJ_TIMER_H_
#define _PROJ_TIMER_H_
#include <stdio.h>
#include <stdbool.h>
/**
*   @ingroup 	          
*   @fn			unsigned long proj_Timer_Init(char* ModuleName);
*   @brief 		Init the timer
*   @param[in]  ModuleName		Init one module(list)
*	@return		unsigned long  the timer list id, -1 if failed.
* 
*  Description
*  
* @if bug_display
*  	Bug1.
*  	...
* @endif
*  
* @if warning_display
*  	Warning1. 
*  	...
* @endif
*/



unsigned long  proj_Timer_Init(char* ModuleName);

/**
*   @ingroup 	
*   @fn			unsigned long proj_Timer_Add(unsigned long list_id, char Name[32], void (*func)(void* param), void* param, unsigned long interval, bool bRepeat);
*   @brief 		Add one timer to the Module(list)
*   @param[in]	list_id		module timer list id
*   @param[in]	Name        timer name
*   @param[in]	func		timer callback
*   @param[in]	param		callback parameter	
*   @param[in]	interval	interval time of the timer
*   @param[in]	bRepeat	     call once or always
*	@return		unsingned long timer id, -1 if failed
* 
*  Description
*  
* @if bug_display
*  	Bug1.
*  	...
* @endif
*  
* @if warning_display
*  	Warning1. 
*  	...
* @endif
*/
unsigned long proj_Timer_Add(unsigned long list_id, char Name[32], void (*func)(void* param), void* param, unsigned long interval, bool bRepeat);

/**
*   @ingroup 	        
*   @fn			RETURN_TYPE proj_Timer_Destroy(char* ModuleName);
*   @brief 		destroy the module timer list
*   @param[in]  ModuleName  	module name
*	@return		RETURN_TYPE
* 
*  Description
*  
* @if bug_display
*  	Bug1.
*  	...
* @endif
*  
* @if warning_display
*  	Warning1. 
*  	...
* @endif
*/
signed long proj_Timer_Destroy(char* ModuleName);

/**
*   @ingroup 	        
*   @fn			signed long proj_Timer_Del(unsigned long list_id, unsigned long timerid);
*   @brief 		delete the timer from the module
*   @param[in]	list_id		module timer list id
*   @param[in]	timerid		timer id
*	@return		signed long
* 
*  Description
*  
* @if bug_display
*  	Bug1.
*  	...
* @endif
*  
* @if warning_display
*  	Warning1. 
*  	...
* @endif
*/
signed long proj_Timer_Del(unsigned long list_id, unsigned long timerid);

/**
*   @ingroup 	        
*   @fn			signed long proj_Timer_Trigger(unsignedd list_id, unsigned timerid);
*   @brief 		Call the timer callback right now
*   @param[in]	list_id		module timer list id
*   @param[in]	timerid		timer id
*	@return		signed long
* 
*  Description
*  
* @if bug_display
*  	Bug1.
*  	...
* @endif
*  
* @if warning_display
*  	Warning1. 
*  	...
* @endif
*/
signed long proj_Timer_Trigger(unsigned long list_id, unsigned long timerid);

/**
*   @ingroup 	
*   @fn			signed long proj_Timer_Pause(unsigned long list_id, unsigned long timerid, bool bPaused);
*   @brief 		pause one timer of the list
*   @param[in]	list_id		module timer list id
*   @param[in]	timerid		timer id
*   @param[in]	bPaused		pause or not
*	@return		signed long
* 
*  Description
*  
* @if bug_display
*  	Bug1.
*  	...
* @endif
*  
* @if warning_display
*  	Warning1. 
*  	...
* @endif
*/
signed long proj_Timer_Pause(unsigned long list_id, unsigned long timerid, bool bPaused);

/**
*   @ingroup 	       
*   @fn			signed long proj_Timer_PauseAll(unsigned long list_id, bool bPaused);
*   @brief 		pause all the timers of the list
*   @param[in]	list_id		module timer list id
*   @param[in]	bPaused		pause or not
*	@return		signed long
* 
*  Description
*  
* @if bug_display
*  	Bug1.
*  	...
* @endif
*  
* @if warning_display
*  	Warning1. 
*  	...
* @endif
*/
signed long proj_Timer_PauseAll(unsigned long list_id, bool bPaused);

/**
*   @ingroup 	
*   @fn			signed long proj_Timer_UpdateInterval(unsigned long list_id, unsigned long timerid, unsigned long new_interval);
*   @brief 		update the interval time of timer
*   @param[in]	list_id			module timer list id
*   @param[in]	timerid			timerid
*   @param[in]	new_interval	new interval time
*	@return		signed long
* 
*  Description
*  
* @if bug_display
*  	Bug1.
*  	...
* @endif
*  
* @if warning_display
*  	Warning1. 
*  	...
* @endif
*/
signed long proj_Timer_UpdateInterval(unsigned long list_id, unsigned long timerid, unsigned long new_interval);

/**
*   @ingroup 	 
*   @fn			signed long  proj_Timer_GetRestTime(unsigned long list_id, unsigned long timerid, signed long *pMiliSec);
*   @brief 		get the rest time of the timer
*   @param[in]	list_id		module timer list id
*   @param[in]	timerid		timerid
*   @param[in]	pMiliSec	rest time
*	@return		signed long
* 
*  Description
*  
* @if bug_display
*  	Bug1.
*  	...
* @endif
*  
* @if warning_display
*  	Warning1. 
*  	...
* @endif
*/
signed long proj_Timer_GetRestTime(unsigned long list_id, unsigned long timerid, unsigned long *pMiliSec);

/**
*   @ingroup 	
*   @fn			signed long proj_Timer_Reset(unsigned long  list_id,unsigned long timerid);
*   @brief 		reset the timer
*   @param[in]	list_id		module timer list id
*   @param[in]	timerid		timer id
*	@return		signed long
* 
*  Description
*  
* @if bug_display
*  	Bug1.
*  	...
* @endif
*  
* @if warning_display
*  	Warning1. 
*  	...
* @endif
*/
signed long proj_Timer_Reset(unsigned long  list_id,unsigned long timerid);

/**
*   @ingroup 	
*   @fn			bool proj_Timer_IsValid(unsigned long list_id, unsigned long timerid);
*   @brief 		check whether the timer is valid or not
*   @param[in]	list_id		module timer list id
*   @param[in]	timerid		timer id
*	@return		bool
* 
*  Description
*  
* @if bug_display
*  	Bug1.
*  	...
* @endif
*  
* @if warning_display
*  	Warning1. 
*  	...
* @endif
*/
bool proj_Timer_IsValid(unsigned long list_id, unsigned long timerid);


#endif

