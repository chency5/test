#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/time.h>
#include <sys/sem.h>


#include "proj_list.h"
#include "proj_timer.h"

#define	SYS_NOERROR			0
#define	SYS_FAILED			1
#define	SYS_NULL_POINTER		2
#define	SYS_SMALL_BUFFER		3
#define	SYS_NO_MEMORY			4
#define	SYS_BAD_PARAM			5
#define	SYS_NOT_SUPPORT			6

#if 1
const unsigned long crc32_table[256] = 
{
	0x00000000L, 0x77073096L, 0xee0e612cL, 0x990951baL, 0x076dc419L,
	0x706af48fL, 0xe963a535L, 0x9e6495a3L, 0x0edb8832L, 0x79dcb8a4L,
	0xe0d5e91eL, 0x97d2d988L, 0x09b64c2bL, 0x7eb17cbdL, 0xe7b82d07L,
	0x90bf1d91L, 0x1db71064L, 0x6ab020f2L, 0xf3b97148L, 0x84be41deL,
	0x1adad47dL, 0x6ddde4ebL, 0xf4d4b551L, 0x83d385c7L, 0x136c9856L,
	0x646ba8c0L, 0xfd62f97aL, 0x8a65c9ecL, 0x14015c4fL, 0x63066cd9L,
	0xfa0f3d63L, 0x8d080df5L, 0x3b6e20c8L, 0x4c69105eL, 0xd56041e4L,
	0xa2677172L, 0x3c03e4d1L, 0x4b04d447L, 0xd20d85fdL, 0xa50ab56bL,
	0x35b5a8faL, 0x42b2986cL, 0xdbbbc9d6L, 0xacbcf940L, 0x32d86ce3L,
	0x45df5c75L, 0xdcd60dcfL, 0xabd13d59L, 0x26d930acL, 0x51de003aL,
	0xc8d75180L, 0xbfd06116L, 0x21b4f4b5L, 0x56b3c423L, 0xcfba9599L,
	0xb8bda50fL, 0x2802b89eL, 0x5f058808L, 0xc60cd9b2L, 0xb10be924L,
	0x2f6f7c87L, 0x58684c11L, 0xc1611dabL, 0xb6662d3dL, 0x76dc4190L,
	0x01db7106L, 0x98d220bcL, 0xefd5102aL, 0x71b18589L, 0x06b6b51fL,
	0x9fbfe4a5L, 0xe8b8d433L, 0x7807c9a2L, 0x0f00f934L, 0x9609a88eL,
	0xe10e9818L, 0x7f6a0dbbL, 0x086d3d2dL, 0x91646c97L, 0xe6635c01L,
	0x6b6b51f4L, 0x1c6c6162L, 0x856530d8L, 0xf262004eL, 0x6c0695edL,
	0x1b01a57bL, 0x8208f4c1L, 0xf50fc457L, 0x65b0d9c6L, 0x12b7e950L,
	0x8bbeb8eaL, 0xfcb9887cL, 0x62dd1ddfL, 0x15da2d49L, 0x8cd37cf3L,
	0xfbd44c65L, 0x4db26158L, 0x3ab551ceL, 0xa3bc0074L, 0xd4bb30e2L,
	0x4adfa541L, 0x3dd895d7L, 0xa4d1c46dL, 0xd3d6f4fbL, 0x4369e96aL,
	0x346ed9fcL, 0xad678846L, 0xda60b8d0L, 0x44042d73L, 0x33031de5L,
	0xaa0a4c5fL, 0xdd0d7cc9L, 0x5005713cL, 0x270241aaL, 0xbe0b1010L,
	0xc90c2086L, 0x5768b525L, 0x206f85b3L, 0xb966d409L, 0xce61e49fL,
	0x5edef90eL, 0x29d9c998L, 0xb0d09822L, 0xc7d7a8b4L, 0x59b33d17L,
	0x2eb40d81L, 0xb7bd5c3bL, 0xc0ba6cadL, 0xedb88320L, 0x9abfb3b6L,
	0x03b6e20cL, 0x74b1d29aL, 0xead54739L, 0x9dd277afL, 0x04db2615L,
	0x73dc1683L, 0xe3630b12L, 0x94643b84L, 0x0d6d6a3eL, 0x7a6a5aa8L,
	0xe40ecf0bL, 0x9309ff9dL, 0x0a00ae27L, 0x7d079eb1L, 0xf00f9344L,
	0x8708a3d2L, 0x1e01f268L, 0x6906c2feL, 0xf762575dL, 0x806567cbL,
	0x196c3671L, 0x6e6b06e7L, 0xfed41b76L, 0x89d32be0L, 0x10da7a5aL,
	0x67dd4accL, 0xf9b9df6fL, 0x8ebeeff9L, 0x17b7be43L, 0x60b08ed5L,
	0xd6d6a3e8L, 0xa1d1937eL, 0x38d8c2c4L, 0x4fdff252L, 0xd1bb67f1L,
	0xa6bc5767L, 0x3fb506ddL, 0x48b2364bL, 0xd80d2bdaL, 0xaf0a1b4cL,
	0x36034af6L, 0x41047a60L, 0xdf60efc3L, 0xa867df55L, 0x316e8eefL,
	0x4669be79L, 0xcb61b38cL, 0xbc66831aL, 0x256fd2a0L, 0x5268e236L,
	0xcc0c7795L, 0xbb0b4703L, 0x220216b9L, 0x5505262fL, 0xc5ba3bbeL,
	0xb2bd0b28L, 0x2bb45a92L, 0x5cb36a04L, 0xc2d7ffa7L, 0xb5d0cf31L,
	0x2cd99e8bL, 0x5bdeae1dL, 0x9b64c2b0L, 0xec63f226L, 0x756aa39cL,
	0x026d930aL, 0x9c0906a9L, 0xeb0e363fL, 0x72076785L, 0x05005713L,
	0x95bf4a82L, 0xe2b87a14L, 0x7bb12baeL, 0x0cb61b38L, 0x92d28e9bL,
	0xe5d5be0dL, 0x7cdcefb7L, 0x0bdbdf21L, 0x86d3d2d4L, 0xf1d4e242L,
	0x68ddb3f8L, 0x1fda836eL, 0x81be16cdL, 0xf6b9265bL, 0x6fb077e1L,
	0x18b74777L, 0x88085ae6L, 0xff0f6a70L, 0x66063bcaL, 0x11010b5cL,
	0x8f659effL, 0xf862ae69L, 0x616bffd3L, 0x166ccf45L, 0xa00ae278L,
	0xd70dd2eeL, 0x4e048354L, 0x3903b3c2L, 0xa7672661L, 0xd06016f7L,
	0x4969474dL, 0x3e6e77dbL, 0xaed16a4aL, 0xd9d65adcL, 0x40df0b66L,
	0x37d83bf0L, 0xa9bcae53L, 0xdebb9ec5L, 0x47b2cf7fL, 0x30b5ffe9L,
	0xbdbdf21cL, 0xcabac28aL, 0x53b39330L, 0x24b4a3a6L, 0xbad03605L,
	0xcdd70693L, 0x54de5729L, 0x23d967bfL, 0xb3667a2eL, 0xc4614ab8L,
	0x5d681b02L, 0x2a6f2b94L, 0xb40bbe37L, 0xc30c8ea1L, 0x5a05df1bL,
	0x2d02ef8dL
};


unsigned long Util_CRC32( unsigned long val ,const void *ss, int len)
{
	const unsigned char *s = ss;
    while (--len >= 0)
       val = crc32_table[(val ^ *s++) & 0xff] ^ (val >> 8);
    return val;
}

inline static unsigned int Name2ID(char *param_name)
{
	unsigned int i;
	int size = strlen(param_name);
	if (size <= 0) return -1;
	i = 0x123456;
	return Util_CRC32(i,param_name,size);
}
#endif 
typedef struct _tagTriTimer
{
	unsigned long id;	//timer id
	char Name[32];
	void (*func)(void* param);	//timer routine
	void* param;				//timer parameter
	unsigned long interval;				//timer interval
	bool paused;		//timer is paused?
	unsigned char type;			//once or period
	struct timeval execute_time;	//next execute time
	struct list_head item;			//timer list linker
}TriTimer_t;

typedef struct _tagTriTimerList
{
	char name[16];		//Module name
	unsigned long id;				//Module id
	pthread_mutex_t mut;
	pthread_cond_t cond;
	bool paused;			//Module timer pause
	bool quit;				//
	struct list_head active_items;		//active list
	struct list_head paused_items;		//paused list
	struct list_head root;				//link for modules
}TimerList_t;

static LIST_HEAD(Tri_Timer_List);
static signed long TimerIDKey = 0x12345678;
static unsigned long NewTimerID(void)
{
	TimerIDKey++;
	if(TimerIDKey < 0)
		TimerIDKey = 0x12345678;
	return TimerIDKey;
}


/*
find the module timerlist by listid
*/
static TimerList_t* FindTimerList(unsigned long id)
{
	struct list_head *pos;
	TimerList_t* plist = NULL;
	list_for_each(pos, &Tri_Timer_List)
	{
		plist = list_entry(pos, TimerList_t, root);
		if(plist->id == id)
			break;
	}
	if(plist && (plist->id != id))
		plist = NULL;
	return plist;
}

/*
find the timer from timerlist by timer id
*/
static TriTimer_t* FindTimer(TimerList_t* plist, unsigned long timerid)
{
	struct list_head* pos;
	TriTimer_t* ptimer = NULL;
	list_for_each(pos, &(plist->active_items))
	{
		ptimer = list_entry(pos, TriTimer_t, item);
		if(ptimer->id == timerid)
			break;
	}
	if(ptimer == NULL ||ptimer->id != timerid)
	{
		list_for_each(pos, &(plist->paused_items))
		{
			ptimer = list_entry(pos, TriTimer_t, item);
			if(ptimer->id == timerid)
				break;
		}
	}
	if(ptimer == NULL ||ptimer->id != timerid)
		ptimer = NULL;
	return ptimer;
}

/*
Cut the timer from its timerlist
*/
static void CutTimerFromList(TriTimer_t* ptimer)
{
	list_del(&(ptimer->item));
	return;
}

/*
calculate the next execute time by the base time and interval
*/
static void CalExecuteTime(struct timeval *basetime, int interval, struct timeval *wantime)
{
	unsigned long savedmsec = (basetime->tv_usec/1000 + interval);	
	unsigned long  savedusec = (basetime->tv_usec%1000);	
	wantime->tv_usec = (savedmsec%1000)*1000 + savedusec;
	wantime->tv_sec = basetime->tv_sec + savedmsec/1000;
	return;
}

/*
Compare the times to check which is bigger
*/
static signed long CompareTime(struct timeval *pcurtime, struct timeval *pchecktime)
{
	int ret = (((pcurtime->tv_sec - pchecktime->tv_sec) * 1000) +
			((pcurtime->tv_usec - pchecktime->tv_usec) / 1000));
	return ret;
}

/*
Update the timer next execute time.
*/
static void UpdateExecuteTime(TriTimer_t* ptimer, struct timeval* basetime)
{
	struct timeval curtime;
	if(basetime == NULL)
		gettimeofday(&curtime, NULL);
	else
		curtime = ptimer->execute_time;
	CalExecuteTime(&curtime, ptimer->interval, &(ptimer->execute_time));	
}

static void UpdateCurrentExecuteTime(TriTimer_t* ptimer, struct timeval* basetime)
{
	struct timeval curtime;
	if(basetime == NULL)
		gettimeofday(&curtime, NULL);
	else
		curtime = ptimer->execute_time;
	CalExecuteTime(&curtime, 0, &(ptimer->execute_time));	
}

/*
Add the timer to the timerlist's paused list
*/
static void AddToPausedList(TimerList_t* plist, TriTimer_t* ptimer)
{
	list_add_tail(&(ptimer->item), &(plist->paused_items));
	return;
}

/*
Add the timer to the timerlist's active list
*/
static void AddToActiveList(TimerList_t* plist, TriTimer_t* ptimer)
{
	struct list_head *pos;
	TriTimer_t* pcurtimer = NULL;
	list_for_each(pos, &(plist->active_items))
	{
		pcurtimer = list_entry(pos, TriTimer_t, item);
		if(CompareTime(&(pcurtimer->execute_time), &(ptimer->execute_time)) > 0)
			break;
	}
	list_add_tail(&(ptimer->item), pos);	//the new added timer is added before the found timer
										//see detail of list_add_tail
	return;
}

static void SortActiveList(TimerList_t* plist)
{
	struct list_head *pos1, *pos2;
	LIST_HEAD(Tmp_List);	//for store tmp timer
	TriTimer_t* ptimer;

	list_for_each_safe(pos1, pos2, &(plist->active_items))
	{
		ptimer = list_entry(pos1, TriTimer_t, item);
		list_del(pos1);
		list_add(pos1, &Tmp_List);
	}
	//add back to timer
	list_for_each_safe(pos1, pos2, &Tmp_List)
	{
		ptimer = list_entry(pos1, TriTimer_t, item);
		list_del(pos1);
		AddToActiveList(plist, ptimer);
	}
	return;
}

/*
Get the next execute time the timerlist's active items.
*/
static void GetExecuteTime(TimerList_t* plist, struct timeval *nexttime)
{
	TriTimer_t* ptimer = NULL;
	if(!plist->paused)
	{
		struct list_head* pos;
		list_for_each(pos, &(plist->active_items))
		{
			ptimer = list_entry(pos, TriTimer_t, item);
			break;	//just find the first one timer
		}
	}
	if(ptimer == NULL)
	{
		//if no next time, just wait 1000 sec
		struct timeval curtime;
		gettimeofday(&curtime, NULL);
		*nexttime = curtime;
		nexttime->tv_sec +=1000;
	}
	else
	{
		*nexttime = ptimer->execute_time;
	}
	return;
}

/*
Main timer thread
*/
static void* TimerThread(void* param)
{
	TimerList_t *plist = (TimerList_t*)param;
	int retcode;
	struct timespec timeout;
	struct timeval mytimeout;
	struct list_head *pos1, *pos2;
	TriTimer_t* ptimer;
	LIST_HEAD(Tmp_List);	//for store tmp timer
	//TRACE_ERROR("INFO: %s module timer pid:%d\n", plist->name, getpid());
	pthread_mutex_lock(&(plist->mut));
	while(!(plist->quit))
	{
		//TRACE3("wait in timer thread of %s\n", plist->name);
		//find the next execute time
		//get next time out
		GetExecuteTime(plist, &mytimeout);
		timeout.tv_sec = mytimeout.tv_sec;
		timeout.tv_nsec = mytimeout.tv_usec*1000;
		retcode = pthread_cond_timedwait(&plist->cond, &plist->mut, &timeout);
		if(retcode == ETIMEDOUT)
		{
			//execute timer function
			gettimeofday(&mytimeout, NULL);
			list_for_each_safe(pos1, pos2, &(plist->active_items))
			{
				ptimer = list_entry(pos1, TriTimer_t, item);
				//check if timer timeout
				if(CompareTime( &mytimeout, &(ptimer->execute_time))>0)
				{
					list_del(pos1);
					list_add(pos1, &Tmp_List);
					//TRACE6("Name:%s\n", ptimer->Name);
					ptimer->func(ptimer->param);
				}
			}
			//add back to timer
			list_for_each_safe(pos1, pos2, &Tmp_List)
			{
				ptimer = list_entry(pos1, TriTimer_t, item);
				list_del(pos1);
				if(ptimer->type == 1)
				{
					//Blance check here
					//UpdateExecuteTime(ptimer, &mytimeout);	//recalculate the next time based on check point, 
															//exact timer, but will cause problem if one timer run too long
					UpdateExecuteTime(ptimer, NULL);			//recalcuate the next time based on current time
					AddToActiveList(plist, ptimer);
				}
				else
				{
					free(ptimer);	//just free it
				}
			}
		}
		else
		{
			//Trigged by timer setting update. We just need to sort the list according to the execute time
			SortActiveList(plist);
		}
	}

	//we need to release all resource here
	list_for_each_safe(pos1, pos2, &(plist->active_items))
	{
		ptimer = list_entry(pos1, TriTimer_t, item);
		list_del(pos1);
		free(ptimer);
	}
	list_for_each_safe(pos1, pos2, &(plist->paused_items))
	{
		ptimer = list_entry(pos1, TriTimer_t, item);
		list_del(pos1);
		free(ptimer);
	}
	pthread_mutex_unlock(&(plist->mut));
	
	plist->quit = 0;	//notify the caller to free the module timer list
	pthread_exit(&retcode);
	return 0;
}

/*
Timer init routine for module.
*/
unsigned long proj_Timer_Init(char* ModuleName)
{
	unsigned int id;
	pthread_t pid;
	TimerList_t* plist = NULL;
	id = Name2ID(ModuleName);
	if(id == -1)
		return -1;
	//TRACE_ERROR("Init Timer name:%s id:%ld\n", ModuleName, id);
	plist = FindTimerList(id);
	if(plist != NULL)
	{
		//TRACE_ERROR("Timer of Module %s is already initialized\n", ModuleName);
		return id;
	}

	plist = malloc(sizeof(TimerList_t));
	plist->id = id;
	plist->quit = 0;
	plist->paused = 0;
	strncpy(plist->name, ModuleName, 16);
	plist->name[15] = 0;
	pthread_cond_init(&(plist->cond), NULL);
	pthread_mutex_init(&(plist->mut), NULL);
	INIT_LIST_HEAD(&(plist->active_items));
	INIT_LIST_HEAD(&(plist->paused_items));
	INIT_LIST_HEAD(&(plist->root));
	list_add_tail(&(plist->root), &Tri_Timer_List);

    
	printf("proj_Timer_Init ModuleName=%s\n",ModuleName);
    /*if (strcmp("send_ccs",ModuleName) == 0) {
         struct sched_param sparam;
		 pthread_attr_t attr;
		 
		 int Priority = 100;
         if (Priority < sched_get_priority_min(SCHED_RR))
             Priority = sched_get_priority_min(SCHED_RR);

         if (Priority > sched_get_priority_max(SCHED_RR))
             Priority = sched_get_priority_max(SCHED_RR);

            sparam.sched_priority = Priority;
            pthread_attr_setschedpolicy(&attr, SCHED_RR);
            pthread_attr_setschedparam(&attr, &sparam);
		    pthread_create(&pid, &attr, TimerThread, plist);
     }else*/
	       	pthread_create(&pid, NULL, TimerThread, plist);
	return id;
}

/*
Timer Deinit routine for module
*/
signed long proj_Timer_Destroy(char* ModuleName)
{
	int id;
	TimerList_t* plist = NULL;
	id = Name2ID(ModuleName);
	plist = FindTimerList(id);
	if(plist == NULL)
		return SYS_FAILED;

	plist->quit = 1;
	pthread_cond_signal(&plist->cond);	//notify the wait thread to recalculate the next execute time
	while(plist->quit)
	{
		sleep(1);
		//TRACE5("wait for quit: %s\n", ModuleName);
	}
	list_del(&plist->root);
	free(plist);
	return SYS_NOERROR;
}


/*
Timer add routine
*/
unsigned long proj_Timer_Add(unsigned long list_id,char Name[32], void (*func)(void* param), void* param, unsigned long interval, bool bRepeat)
{
	TimerList_t* plist = NULL;
	TriTimer_t *ptimer = NULL;

	plist = FindTimerList(list_id);
	if(plist == NULL)
		return -1;

	ptimer = malloc(sizeof(TriTimer_t));
	ptimer->id = NewTimerID();
	ptimer->func = func;
	ptimer->param = param;
	ptimer->interval = interval;
	ptimer->paused = 0;
	ptimer->type = bRepeat;
	strncpy(ptimer->Name, Name, 31);
	ptimer->Name[31]='\0';
	//set next execute time
	UpdateExecuteTime(ptimer, NULL);
	INIT_LIST_HEAD(&(ptimer->item));
	pthread_mutex_lock(&plist->mut);
	AddToActiveList(plist, ptimer);
	pthread_cond_signal(&plist->cond);	//notify the wait thread to recalculate the next execute time
	pthread_mutex_unlock(&plist->mut);
	return ptimer->id;
}

/*
Timer remove routine
*/
signed long proj_Timer_Del(unsigned long list_id, unsigned long timerid)
{
	int ret = SYS_FAILED;
	TimerList_t* plist = NULL;
	TriTimer_t *ptimer = NULL;

	plist = FindTimerList(list_id);
	if(plist == NULL)
		return SYS_FAILED;

	pthread_mutex_lock(&plist->mut);
	ptimer = FindTimer(plist, timerid);
	if(ptimer != NULL)
	{
		list_del(&(ptimer->item));
		free(ptimer);
		pthread_cond_signal(&plist->cond);	//notify the wait thread to recalculate the next execute time
		ret = SYS_NOERROR;
	}
	pthread_mutex_unlock(&plist->mut);
	return ret;
}

/*
Timer pause routine
*/
signed long proj_Timer_Pause(unsigned long list_id, unsigned long timerid, bool bPaused)
{
	int ret = SYS_FAILED;
	TimerList_t* plist = NULL;
	TriTimer_t *ptimer = NULL;

	plist = FindTimerList(list_id);
	if(plist == NULL)
		return SYS_FAILED;

	pthread_mutex_lock(&plist->mut);
	ptimer = FindTimer(plist, timerid);
	if(ptimer != NULL)
	{
		if(ptimer->paused != bPaused)
		{
			CutTimerFromList(ptimer);
			ptimer->paused = bPaused;
			if(bPaused)
				AddToPausedList(plist, ptimer);
			else
			{
				//Blance Help me here, whether I should run this paused timer right now
				UpdateExecuteTime(ptimer, NULL);
				//UpdateExecuteTime(ptimer, ptimer->execute_time);
				AddToActiveList(plist, ptimer);
			}
			pthread_cond_signal(&plist->cond);	//notify the wait thread to recalculate the next execute time
		}
		ret = SYS_NOERROR;
	}
	pthread_mutex_unlock(&plist->mut);	
	return ret;
}



/*
Timer Trigger routine
*/
signed long proj_Timer_Trigger(unsigned long list_id, unsigned long timerid)
{
	int ret = SYS_FAILED;
	TimerList_t* plist = NULL;
	TriTimer_t *ptimer = NULL;
	plist = FindTimerList(list_id);
	if(plist == NULL)
		return SYS_FAILED;

	pthread_mutex_lock(&plist->mut);
	ptimer = FindTimer(plist, timerid);
	if(ptimer != NULL)
	{
		if(!ptimer->paused)
		{
			CutTimerFromList(ptimer);
			UpdateCurrentExecuteTime(ptimer, NULL);	//just set the timebase to 0, and this will cause the next execute time is already timed out
			AddToActiveList(plist, ptimer);
			pthread_cond_signal(&plist->cond);	//notify the wait thread to recalculate the next execute time
			ret = SYS_NOERROR;
		}
		else
			ret = SYS_FAILED;	//we cant trigger the paused timer
	}
	pthread_mutex_unlock(&plist->mut);	
	return ret;
}

/*
Timer list pause routine
*/
signed long proj_Timer_PauseAll(unsigned long list_id, bool bPaused)
{
	TimerList_t* plist = NULL;
	plist = FindTimerList(list_id);
	if(plist == NULL)
		return SYS_FAILED;

	pthread_mutex_lock(&plist->mut);
	if(plist->paused != bPaused)
	{
		plist->paused = bPaused;
		pthread_cond_signal(&plist->cond);	//notify the wait thread to recalculate the next execute time
	}
	pthread_mutex_unlock(&plist->mut);	
	return SYS_NOERROR;
}

/*
Timer interval update routine.
*/
signed long proj_Timer_UpdateInterval(unsigned long list_id, unsigned long timerid, unsigned long NewInterval)
{
	int ret = SYS_FAILED;
	TimerList_t* plist = NULL;
	TriTimer_t *ptimer = NULL;

	plist = FindTimerList(list_id);
	if(plist == NULL)
		return SYS_FAILED;

	pthread_mutex_lock(&plist->mut);
	ptimer = FindTimer(plist, timerid);
	if(ptimer != NULL)
	{
		if(ptimer->interval != NewInterval)
		{
			ptimer->interval = NewInterval;
			//If timer is paused, no need to wake up timer thread
			if(!ptimer->paused )
			{
				CutTimerFromList(ptimer);
				UpdateExecuteTime(ptimer, NULL);
				AddToActiveList(plist, ptimer);
				pthread_cond_signal(&plist->cond);	//notify the wait thread to recalculate the next execute time
			}
		}
		ret = SYS_NOERROR;
	}
	pthread_mutex_unlock(&plist->mut);
	return ret;
}

/*
Get the rest time of the timer	
*/
signed long proj_Timer_GetRestTime(unsigned long list_id, unsigned long timerid, unsigned long *pMiliSec)
{
	int ret = SYS_FAILED;
	TimerList_t* plist = NULL;
	TriTimer_t *ptimer = NULL;

	plist = FindTimerList(list_id);
	if(plist == NULL)
		return SYS_FAILED;

	pthread_mutex_lock(&plist->mut);
	ptimer = FindTimer(plist, timerid);
	if(ptimer != NULL)
	{
		struct timeval CurTime;
		gettimeofday(&CurTime, NULL);
		if(ptimer->paused)
			*pMiliSec = 0xffffffff;
		else	
			*pMiliSec = ((( ptimer->execute_time. tv_sec - CurTime.tv_sec ) * 1000) +
			(( ptimer->execute_time.tv_usec - CurTime.tv_usec) / 1000));
		ret = SYS_NOERROR;
	}
	pthread_mutex_unlock(&plist->mut);
	return ret;
}

/*
   Reset the excute time of the timer, 
*/
signed long proj_Timer_Reset(unsigned long  list_id,unsigned long timerid)
{
	int ret = SYS_FAILED;
	TimerList_t* plist = NULL;
	TriTimer_t *ptimer = NULL;

	plist = FindTimerList(list_id);
	if(plist == NULL)
		return SYS_FAILED;

	pthread_mutex_lock(&plist->mut);
	ptimer = FindTimer(plist, timerid);
	if(ptimer != NULL)
	{
		if(!ptimer->paused )
		{
			CutTimerFromList(ptimer);
			UpdateExecuteTime(ptimer,NULL);
			AddToActiveList(plist, ptimer);
			pthread_cond_signal(&plist->cond);	//notify the wait thread to recalculate the next execute time
		}
		ret = SYS_NOERROR;
	}
	pthread_mutex_unlock(&plist->mut);
	return ret;
}

/*
 Check whether the timer is valid or not.
*/
bool proj_Timer_IsValid(unsigned long list_id, unsigned long timerid)
{
	TimerList_t* plist = NULL;
	TriTimer_t *ptimer = NULL;

	plist = FindTimerList(list_id);
	if(plist == NULL)
		return 0;

	pthread_mutex_lock(&plist->mut);
	ptimer = FindTimer(plist, timerid);
	pthread_mutex_unlock(&plist->mut);

	return (ptimer != NULL);
}

/*-----------------------test program -----------------------------*/
#if 0
int aa(void* bb)
{
	struct timeval curtime;
	gettimeofday(&curtime, NULL);
	printf(" time%d %d-%d\n", (int)bb, curtime.tv_sec, curtime.tv_usec/1000);
	return 0;
}

int main(int argc, char* argv[])
{
	int list_id[10];
	int timer_id[10];
	list_id[0] = proj_Timer_Init("XY");
	printf("XY id:%d\n", list_id[0]);
	list_id[1] = proj_Timer_Init("cx");
	printf("cx id:%d\n", list_id[1]);
	timer_id[1] = proj_Timer_Add(list_id[1], aa, 2, 100, 1);
	timer_id[0] = proj_Timer_Add(list_id[0], aa, 1, 100, 1);
	sleep(1);
	proj_Timer_Pause(list_id[1], timer_id[1], 1);
	proj_Timer_Destroy("XY");	
	sleep(1);
	proj_Timer_Pause(list_id[1], timer_id[1], 0);
	sleep(1);
	proj_Timer_Destroy("cx");
	return 0;
}
#endif


#if 0
int aa(void* bb)
{
	int aa = (int)bb;
	printf("this is timer :%d\n", aa);
	return 0;
}

int main(int argc, char* argv[])
{
	int list_id[10];
	int timer_id[10];
	int i;
	list_id[0] = proj_Timer_Init("XY");
	for(i=0;i<10; i++)
	timer_id[i] = proj_Timer_Add(list_id[0], aa, i, 100, 0);
	proj_Timer_Del(list_id[0], timer_id[5]);
	sleep(1);
	proj_Timer_Destroy("XY");	
	return 0;
}
#endif

