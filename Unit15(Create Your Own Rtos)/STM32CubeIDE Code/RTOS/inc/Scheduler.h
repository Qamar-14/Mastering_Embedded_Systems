/*
 *
 * Scheduler.h
 *
 *
 *	Created on: 9/22/2023
 *	Author: Qamar Elgohary
 *	Mastering Embedded Systems
 */


#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

//-------------------------------------------------
// INCLUDES
//-------------------------------------------------

#include "CortexMX_OS_Porting.h"


//-------------------------------------------------
// CONFIG STRUCTURES
//-------------------------------------------------


typedef enum{
	NoError,
	Ready_Queue_Error,
	task_Exceeded_StackSize,
}Error_StateID;


typedef struct{
	unsigned int stack_sz;
	unsigned char priority;

	//Pointer to task c function
	void(*P_TaskEntry)(void);

	unsigned char AutoStart;

	unsigned int _S_PSP_TASK;	//Not entered by the user
	unsigned int _E_PSP_TASK;	//Not entered by the user

	unsigned int* CurrentPSP;	//Not entered by the user

	char TaskName[30];

	//Not entered by the user
	enum {
		Suspend,
		Running,
		Waiting,
		Ready,
	}TaskState;

	struct{
		enum{
			enable,
			disable,
		}Blocking;
		unsigned int TicksCount;
	}TimeWaiting;

}Task_strcuture;

#define element_type Task_strcuture*


//-------------------------------------------------
// APIs
//-------------------------------------------------
Error_StateID MyRTOS_init();
Error_StateID MyRTOS_Create_Task(Task_strcuture* task);

#endif /* INC_SCHEDULER_H_*/
