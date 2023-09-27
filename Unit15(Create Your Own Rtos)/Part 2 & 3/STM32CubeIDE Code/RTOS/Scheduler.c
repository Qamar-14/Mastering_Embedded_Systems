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
		OS_Running,
	}OS_Mode;

}OS_Structure;

FIFO_Buf_t Ready_QUEUE ;

Task_strcuture* Ready_QUEUE_FIFO[100] ;
Task_strcuture MyRTOS_idleTask ;

//-------------------------------------------------
// Generic Functions
//-------------------------------------------------


// perform the bubble sort
void bubbleSort()
{
	int size = OS_Structure.NumOfActiveTasks;
	Task_strcuture* temp;
	// loop to access each array element
	for (int step = 0; step < size - 1; step++) {

		// loop to compare array elements
		for (int i = 0; i < size - step - 1; i++) {

			// compare two adjacent elements
			if (OS_Structure.OS_Tasks[i]->priority > OS_Structure.OS_Tasks[i+1]->priority) {

				// swapping occurs if elements are not in the intended order
				temp = OS_Structure.OS_Tasks[i];
				OS_Structure.OS_Tasks[i] = OS_Structure.OS_Tasks[i+1];
				OS_Structure.OS_Tasks[i+1] = temp;
			}
		}
	}
}

void MyRTOS_Update_SchedTable()
{
	Task_strcuture* task = NULL;
	Task_strcuture* Ptask;
	Task_strcuture* PnextTask;
	int i =0;

	//BubbleSort ScheduleTable of OS_Tasks based on priority
	bubbleSort();
	//Empty ready queue
	while(FIFO_dequeue(&Ready_QUEUE, &task)!= FIFO_EMPTY);

	//Update ready queue
	while(i<OS_Structure.NumOfActiveTasks)
	{
		Ptask = OS_Structure.OS_Tasks[i];
		PnextTask = OS_Structure.OS_Tasks[i+1];
		if(Ptask->TaskState != Suspend )
		{
			if(PnextTask->TaskState == Suspend )
			{
				FIFO_enqueue(&Ready_QUEUE, Ptask);
				Ptask->TaskState = Ready;
				break;
			}
			if (PnextTask->priority > Ptask->priority)
			{
				FIFO_enqueue(&Ready_QUEUE, Ptask);
				Ptask->TaskState = Ready;
				break;
			}
			if (PnextTask->priority == Ptask->priority)
			{
				// Both with the same priority then we push Ptask to ready queue and when i is incremented
				// then the next task will be executed in one of the above conditions
				FIFO_enqueue(&Ready_QUEUE, Ptask);
				Ptask->TaskState = Ready;
			}

			else if (PnextTask->priority < Ptask->priority)
			{
				// Error (then bubbleSort function isn't working properly)
				break;
			}
		}
		i++;
	}
}

void OS_Decision()
{
	//If ready queue is empty & CurrentTask != suspend
	if((Ready_QUEUE.counter == 0) && (OS_Structure.CurrentTask->TaskState != Suspend))
	{
		//Then keep till task terminates
		OS_Structure.CurrentTask->TaskState = Running;
		//Add the current task again (RoundRobin)
		FIFO_enqueue(&Ready_QUEUE, OS_Structure.CurrentTask);
		OS_Structure.NextTask = OS_Structure.CurrentTask;
	}
	else
	{
		FIFO_dequeue(&Ready_QUEUE, &OS_Structure.NextTask);
		OS_Structure.NextTask->TaskState = Running;
		//Round Robin Algo
		if ((OS_Structure.CurrentTask->priority == OS_Structure.NextTask->priority)&&(OS_Structure.CurrentTask->TaskState != Suspend))
		{
			FIFO_enqueue(&Ready_QUEUE, OS_Structure.CurrentTask);
			OS_Structure.CurrentTask->TaskState = Ready;
		}
	}
}


void OS_SVC_SET(SVC_ID id)
{
	switch(id)
	{
	case SVC_ActivateTask: // Activate Task
		__asm("svc #0x00");
		break;
	case SVC_TerminateTask: // Terminate Task
		__asm("svc #0x01");
		break;
	case SVC_WaitingTask: // Waiting task
		__asm("svc #0x02");
		break;

	}

}
//Handler mode
void OS_SVC(int* StackFrame)
{

	//r0 r1 r2 r3 r12 LR, return address (PC) and XPSR
	unsigned char SVC_NO;
	SVC_NO = *((unsigned char*)(((unsigned char*)StackFrame[6])-2));

	switch(SVC_NO)
	{
	case SVC_ActivateTask: // Activate Task
	case SVC_TerminateTask: // Terminate Task
		// Update Scheduler Table & Ready Queue
		MyRTOS_Update_SchedTable();
		// OS is in running state
		if (OS_Structure.OS_Mode== OS_Running)
		{
			if ( strcmp(OS_Structure.CurrentTask->TaskName, "idleTask") != 0)
			{
				// Decide what next
				OS_Decision();
				// Trigger OS_PendSV (Switch context/Restore)
				trigger_OS_PendSV();

			}
		}
		break;
	case SVC_WaitingTask: // Waiting task
		break;


	}
}


__attribute ((naked)) void PendSV_Handler()
{
	//Save context of current task
	//Get the current PSP
	OS_GET_PSP(OS_Structure.CurrentTask->CurrentPSP);

	OS_Structure.CurrentTask->CurrentPSP--;
	__asm volatile("mov %0, r4" : "=r" (*(OS_Structure.CurrentTask->CurrentPSP)) );
	OS_Structure.CurrentTask->CurrentPSP--;


	__asm volatile("mov %0, r5" : "=r" (*(OS_Structure.CurrentTask->CurrentPSP)) );
	OS_Structure.CurrentTask->CurrentPSP--;

	__asm volatile("mov %0, r6" : "=r" (*(OS_Structure.CurrentTask->CurrentPSP)) );
	OS_Structure.CurrentTask->CurrentPSP--;

	__asm volatile("mov %0, r7" : "=r" (*(OS_Structure.CurrentTask->CurrentPSP)) );
	OS_Structure.CurrentTask->CurrentPSP--;

	__asm volatile("mov %0, r8" : "=r" (*(OS_Structure.CurrentTask->CurrentPSP)) );
	OS_Structure.CurrentTask->CurrentPSP--;

	__asm volatile("mov %0, r9" : "=r" (*(OS_Structure.CurrentTask->CurrentPSP)) );
	OS_Structure.CurrentTask->CurrentPSP--;

	__asm volatile("mov %0, r10" : "=r" (*(OS_Structure.CurrentTask->CurrentPSP)) );
	OS_Structure.CurrentTask->CurrentPSP--;

	__asm volatile("mov %0, r11" : "=r" (*(OS_Structure.CurrentTask->CurrentPSP)) );

	//Restore context of next task
	//====================================

	if (OS_Structure.NextTask != NULL)
	{
		OS_Structure.CurrentTask = OS_Structure.NextTask;
		OS_Structure.NextTask = NULL;

	}

	__asm volatile("mov r11, %0" : : "r" (*(OS_Structure.CurrentTask->CurrentPSP)) );
	OS_Structure.CurrentTask->CurrentPSP++;

	__asm volatile("mov r10, %0" : : "r" (*(OS_Structure.CurrentTask->CurrentPSP)) );
	OS_Structure.CurrentTask->CurrentPSP++;

	__asm volatile("mov r9, %0" : : "r" (*(OS_Structure.CurrentTask->CurrentPSP)) );
	OS_Structure.CurrentTask->CurrentPSP++;

	__asm volatile("mov r8, %0" : : "r" (*(OS_Structure.CurrentTask->CurrentPSP)) );
	OS_Structure.CurrentTask->CurrentPSP++;

	__asm volatile("mov r7, %0" : : "r" (*(OS_Structure.CurrentTask->CurrentPSP)) );
	OS_Structure.CurrentTask->CurrentPSP++;

	__asm volatile("mov r6, %0" : : "r" (*(OS_Structure.CurrentTask->CurrentPSP)) );
	OS_Structure.CurrentTask->CurrentPSP++;

	__asm volatile("mov r5, %0" : : "r" (*(OS_Structure.CurrentTask->CurrentPSP)) );
	OS_Structure.CurrentTask->CurrentPSP++;

	__asm volatile("mov r4, %0" : : "r" (*(OS_Structure.CurrentTask->CurrentPSP)) );
	OS_Structure.CurrentTask->CurrentPSP++;

	//Update PSP and exit
	OS_SET_PSP(OS_Structure.CurrentTask->CurrentPSP);
	__asm volatile("BX LR");



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

unsigned char Idletask_led;
void MyRTOS_IdleTask()
{
	while(1)
	{
		Idletask_led^=1;
		__asm("wfe");
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

	//update sch Table
	OS_Structure.OS_Tasks[OS_Structure.NumOfActiveTasks]= task ;
	OS_Structure.NumOfActiveTasks++ ;

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

void MyRTOS_Activate_Task(Task_strcuture* task)
{
	task->TaskState=Waiting;
	OS_SVC_SET(SVC_ActivateTask);
}

void MyRTOS_Terminate_Task(Task_strcuture* task)
{
	task->TaskState=Suspend;
	OS_SVC_SET(SVC_TerminateTask);


}

void MyRTOS_StartOS()
{
	OS_Structure.OS_Mode = OS_Running;

	//Set default current task as IdleTask
	OS_Structure.CurrentTask = &MyRTOS_idleTask;

	//Activate IdleTask
	MyRTOS_Activate_Task(&MyRTOS_idleTask);

	Start_Ticker(); //1 Ms
	OS_SET_PSP(OS_Structure.CurrentTask->CurrentPSP);

	//Switch SP from MSP to PSP
	OS_SWITCH_SP_TO_PSP;
	OS_SWITCH_TO_UNPRIVILEGED;
	MyRTOS_idleTask.P_TaskEntry();

}

