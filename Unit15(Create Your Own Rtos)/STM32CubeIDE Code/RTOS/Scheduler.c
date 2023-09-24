/*
 * Scheduler.c
 *
 *
 *	Created on: 9/22/2023
 *	Author: Qamar Elgohary
 *	Mastering Embedded Systems
 */


//-------------------------------------------------
// INCLUDES
//-------------------------------------------------


#include "Scheduler.h"
#include "MyRTOS_FIFO.h"



//-------------------------------------------------
// Generic Variables
//-------------------------------------------------



struct{
	Task_strcuture* OS_Tasks[100];	//Schedule Table
	unsigned int _S_MSP_TASK;	//Not entered by the user
	unsigned int _E_MSP_TASK;	//Not entered by the user

	unsigned int PSP_TaskLocator;
	unsigned int NumOfActiveTasks;

	Task_strcuture* CurrentTask;
	Task_strcuture* NextTask;

	enum
	{
		OS_Suspend,
		OS_Run,
	}OS_Mode;

}OS_Structure;

FIFO_Buf_t Ready_QUEUE ;

Task_strcuture* Ready_QUEUE_FIFO[100] ;
Task_strcuture MyRTOS_idleTask ;

//-------------------------------------------------
// Generic Functions
//-------------------------------------------------
void OS_SVC(int* StackFrame)
{

	//r0 r1 r2 r3 r12 LR, return address (PC) and XPSR
	unsigned char SVC_NO;
	SVC_NO = *((unsigned char*)(((unsigned char*)StackFrame[6])-2));
	unsigned int val1 = StackFrame[0];
	unsigned int val2 = StackFrame[1];

	switch(SVC_NO)
	{
	case 0: //Activate Task1

		break;
	case 1: //

		break;
	case 2: //

		break;
	case 3: //

		break;
	}

}

void PendSV_Handler()
{
	//Clear PendSV
	//SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}


int OS_SVC_SET(int SVC_ID)
{
	int result;
	switch(SVC_ID)
	{
	case 0: //OS
		__asm("svc #0x00");
		break;
	case 1: //OS
		__asm("svc #0x01");
		break;
	case 2: //
		__asm("svc #0x02");
		break;
	case 3: //
		__asm("svc #0x03");
		break;
	}

}

void MyRTOS_CreateTaskStack(Task_strcuture* TaskRef)
{
	/*TaskFrame
	 * XPSR
	 * PC
	 * LR
	 * R12
	 * R4
	 * R3
	 * R2
	 * R1
	 * R0
	 *
	 *
	 * R11 R10 R9 R8 R7 R6 R5 -> Saved/Restore manually
	 */


	TaskRef->CurrentPSP= TaskRef->_S_PSP_TASK;

	TaskRef->CurrentPSP --;
	*(TaskRef->CurrentPSP)= 0x01000000;		//Dummy XPSR should T = 1 to avoid bus fault

	TaskRef->CurrentPSP --;
	*(TaskRef->CurrentPSP)= (unsigned int)TaskRef->P_TaskEntry;

	TaskRef->CurrentPSP --;
	*(TaskRef->CurrentPSP)= 0xFFFFFFFD;		//Dummy LR (EXEC_RETURN to thread with PSP)

	for (int i =0;i<13;i++)
	{
		TaskRef->CurrentPSP --;
		*(TaskRef->CurrentPSP)=0;
	}
}
void MyRTOS_IdleTask()
{
	while(1)
	{
		__asm("nop");
	}
}


void MyRTOS_Create_MainStack()
{
	//MAIN STACK
	OS_Structure._S_MSP_TASK = &_estack;
	OS_Structure._E_MSP_TASK = OS_Structure._S_MSP_TASK -MainStackSize;


	OS_Structure.PSP_TaskLocator=(OS_Structure._E_MSP_TASK -8);

}

//----------------------------------------------------------

Error_StateID MyRTOS_Create_Task(Task_strcuture* task)
{
	Error_StateID error = NoError;

	//Create it's own PSP stack

	task->_S_PSP_TASK = OS_Structure.PSP_TaskLocator;
	task->_E_PSP_TASK = task->_S_PSP_TASK + task->stack_sz;

	//Check task size exceeded the PSP stack
	if(task->_E_PSP_TASK < (unsigned int)(&_eheap))
	{
		return task_Exceeded_StackSize;

	}

	//Aligned 8 bytes spaces between stack PSP and other
	OS_Structure.PSP_TaskLocator = task->_E_PSP_TASK - 8;

	//Initialize PSP Task Stack
	MyRTOS_CreateTaskStack(task);

	task->TaskState = Suspend;

	return error;

}
Error_StateID MyRTOS_init()
{
	Error_StateID error = NoError;

	//Update OS Mode
	OS_Structure.OS_Mode = OS_Suspend;

	//Specify Main Stack for the ISR and OS
	MyRTOS_Create_MainStack();

	//Update anything specific by HW (clock tree)
	//HW_init();

	//Create Ready Queue
	if(FIFO_init(&Ready_QUEUE, Ready_QUEUE_FIFO,100)!= FIFO_NO_ERROR)
	{
		error += Ready_Queue_Error;
	}
	//Configure Idle task
	strcpy(MyRTOS_idleTask.TaskName,"idleTask");
	MyRTOS_idleTask.priority = 255;
	MyRTOS_idleTask.P_TaskEntry = MyRTOS_IdleTask;
	MyRTOS_idleTask.stack_sz=300;

	error += MyRTOS_Create_Task(&MyRTOS_idleTask);

	return error ;
}





