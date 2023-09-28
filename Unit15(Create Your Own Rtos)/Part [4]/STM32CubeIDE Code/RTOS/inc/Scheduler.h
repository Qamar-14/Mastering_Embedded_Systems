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
	Mutex_Reached_Max_Users
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

typedef struct{
	Task_strcuture* TaskWithLock;
	Task_strcuture* NextTaskWithLock;
}Mutex;

typedef enum {
	SVC_ActivateTask,
	SVC_TerminateTask,
	SVC_WaitingTask,
	SVC_AcquireMutex,
	SVC_ReleaseMutex,
}SVC_ID;
#define element_type Task_strcuture*


//-------------------------------------------------
// APIs
//-------------------------------------------------
Error_StateID MyRTOS_init();
Error_StateID MyRTOS_Create_Task(Task_strcuture* task);

void MyRTOS_Activate_Task(Task_strcuture* task);
void MyRTOS_Terminate_Task(Task_strcuture* task);
void MyRTOS_Waiting_Task(unsigned int ticks, Task_strcuture* task);
Error_StateID MyRTOS_Acquire_Mutex(Mutex* mutex_obj, Task_strcuture* task);
void MyRTOS_Release_Mutex(Mutex* mutex_obj);

void MyRTOS_StartOS();

#endif /* INC_SCHEDULER_H_*/
