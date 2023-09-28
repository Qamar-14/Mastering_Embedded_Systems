/*
 * main.c
 *
 * Created on: Oct 4, 2022
 *     Author: Qamar
 */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "conio.h"
#include "stdbool.h"

#define DPRINT(...)	{fflush(stdout); \
		fflush(stdin); \
		printf(__VA_ARGS__); \
		fflush(stdout); \
		fflush(stdin); }

//effective Data
struct Sdata{
	int ID;
	char name[40];
	float height;
};

//linked list node
struct SStudent{
	struct Sdata student;
	struct SStudent* PNextStudent;
};

struct SStudent* gpFirstStudent= NULL;

void add_student()
{
	char temp_text[50];
	struct SStudent* pNewStudent;
	struct SStudent* pLastStudent;

	//check if list is empty?
	if (gpFirstStudent==NULL)
	{
		//create new record
		pNewStudent =(struct SStudent*) malloc(sizeof(struct SStudent));
		//assign it to gpfirst
		gpFirstStudent = pNewStudent;
	}
	else
	{
		//navigate until we reach last record
		pLastStudent = gpFirstStudent;
		while (pLastStudent->PNextStudent)
			pLastStudent = pLastStudent->PNextStudent;
		//create new record
		pNewStudent = (struct SStudent*) malloc (sizeof(struct SStudent));
		pLastStudent->PNextStudent= pNewStudent;
	}

	//fill new record
	DPRINT("\n Enter the ID: ");
	gets(temp_text);
	pNewStudent->student.ID = atoi(temp_text);

	DPRINT("\n Enter student full name: ");
	gets(pNewStudent->student.name );

	DPRINT("\n Enter the height: ");
	gets(temp_text);
	pNewStudent->student.height = atof(temp_text);

	pNewStudent->PNextStudent = NULL;
}

void delete_student()
{
	char temp_text[40];
	unsigned int selected_ID;

	//get the selected ID
	DPRINT("\n Please enter the student ID to be deleted:");
	gets(temp_text);
	selected_ID= atoi(temp_text);

	//list is not empty
	if(gpFirstStudent)
	{
		struct SStudent* pSelectedStudent = gpFirstStudent;
		struct SStudent* pPreviousStudent = NULL;

		//loop on all records
		while(pSelectedStudent)
		{
			//compare each Node with the selected ID
			if(pSelectedStudent->student.ID== selected_ID)
			{
				if(pPreviousStudent) // The first student is not the selected one
				{
					pPreviousStudent->PNextStudent = pSelectedStudent->PNextStudent;
				}
				else //1st Student == ID
				{
					gpFirstStudent= pSelectedStudent->PNextStudent;
				}
				free(pSelectedStudent);

			}
			pPreviousStudent = pSelectedStudent;
			pSelectedStudent = pSelectedStudent->PNextStudent;
		}
	}
}

void view_students()
{
	struct SStudent* pCurrentStudent = gpFirstStudent;
	int count = 0;
	if(gpFirstStudent == NULL)
	{
		DPRINT("\n EMPTY LIST ");
	}
	else
	{
		while (pCurrentStudent)
		{
			DPRINT("\n RECORD NUMBER: %d", count+1);
			DPRINT("\n \t ID: %d", pCurrentStudent->student.ID);
			DPRINT("\n \t NAME: %s", pCurrentStudent->student.name);
			DPRINT("\n \t HEIGHT: %f", pCurrentStudent->student.height);
			pCurrentStudent = pCurrentStudent->PNextStudent;
			count++;
		}
	}
}

void delete_all()
{
	struct SStudent* pCurrentStudent = gpFirstStudent;
	if (!gpFirstStudent)
	{
		DPRINT("\n EMPTY LIST ");
	}
	else
	{
		while (pCurrentStudent)
		{
			struct SStudent* pTempStudent = pCurrentStudent;
			pCurrentStudent = pCurrentStudent->PNextStudent;
			free(pTempStudent);
		}
	}
}

void get_Nth_node(struct SStudent* pCurrentList, int index)
{
	struct SStudent* pTemp;
	int count =0;

	if (!pCurrentList)
	{
		DPRINT("\n EMPTY LIST ");
	}
	else
	{
		while (pCurrentList)
		{
			count++;
			if (count==index)
			{
				pTemp = pCurrentList;
				break;
			}
			else pCurrentList = pCurrentList->PNextStudent;
		}
	}

	DPRINT("\n RECORD NUMBER: %d", count);
	DPRINT("\n \t ID: %d", pTemp->student.ID);
	DPRINT("\n \t NAME: %s", pTemp->student.name);
	DPRINT("\n \t HEIGHT: %f", pTemp->student.height);
}

int get_length(struct SStudent* pCurrentList)
{
	if (!pCurrentList) return 0;
	else
	{
		return 1 + get_length(pCurrentList->PNextStudent);
	}
}
void get_Nth_node_from_end(struct SStudent* pCurrentList, int index)
{
	struct SStudent* pTemp;
	int count =0;
	int real_index = get_length(pCurrentList) - index +1;

	if (!pCurrentList)
	{
		DPRINT("\n EMPTY LIST ");
	}
	else
	{
		while (pCurrentList)
		{
			count++;
			if (count==index)
			{
				pTemp = pCurrentList;
				break;
			}
			else pCurrentList = pCurrentList->PNextStudent;
		}
	}

	DPRINT("\n RECORD NUMBER: %d", count);
	DPRINT("\n \t ID: %d", pTemp->student.ID);
	DPRINT("\n \t NAME: %s", pTemp->student.name);
	DPRINT("\n \t HEIGHT: %f", pTemp->student.height);
}
void get_middle(struct SStudent* pCurrentList)
{
	struct SStudent* pTemp = NULL;
	struct SStudent* pSlow;
	struct SStudent* pFast;
	pSlow = pCurrentList;
	pFast = pCurrentList;

	if (!pCurrentList)
	{
		DPRINT("\n EMPTY LIST ");
	}
	else
	{
		while(!pTemp)
		{
			pSlow=pSlow->PNextStudent;
			pFast=pFast->PNextStudent;
			pFast=pFast->PNextStudent;
			if ( pFast->PNextStudent == NULL) pTemp = pSlow;
		}
	}

	DPRINT("\n \t ID: %d", pTemp->student.ID);
	DPRINT("\n \t NAME: %s", pTemp->student.name);
	DPRINT("\n \t HEIGHT: %f", pTemp->student.height);
}
bool has_loop(struct SStudent* pCurrentList)
{
	struct SStudent* pSlow;
	struct SStudent* pFast;
	pSlow = pCurrentList;
	pFast = pCurrentList;

	if (!pCurrentList)
	{
		DPRINT("\n EMPTY LIST ");
	}
	else
	{

		pSlow=pSlow->PNextStudent;
		pFast=pFast->PNextStudent;
		pFast=pFast->PNextStudent;
		if ( pFast == pSlow) return true;

	}
	return false;
}
void reverse_list(struct SStudent* pCurrentList)
{
	struct SStudent* pNext=pCurrentList;
	struct SStudent* pPrevious=pCurrentList;


	if (!pCurrentList)
	{
		DPRINT("\n EMPTY LIST ");
	}
	else
	{
		while(pCurrentList)
		{
			pNext=pCurrentList->PNextStudent;
			pCurrentList->PNextStudent= pPrevious;
			pPrevious=pNext;
			pCurrentList=pNext;
		}

	}
}


void main()
{
	char temp_text[40];
	char index[5];

	while(1)
	{

		DPRINT("\n ---------------------");
		DPRINT("\n\t Choose one of the following options: \n");
		DPRINT("\n 1- Add student");
		DPRINT("\n 2- Delete student");
		DPRINT("\n 3- View students");
		DPRINT("\n 4- Delete all students");
		DPRINT("\n 5- Get nth node");
		DPRINT("\n 6- Get nth node from end of list");
		DPRINT("\n 7- Get number of Students");
		DPRINT("\n 8- Get middle of list");
		DPRINT("\n 9- Check for loop in list");
		DPRINT("\n 10- To reverse the list");


		DPRINT("\n Enter option number: ");

		gets(temp_text);
		DPRINT("\n ---------------------");

		switch(atoi(temp_text))
		{
		case 1:
			add_student();
			break;
		case 2:
			delete_student();
			break;
		case 3:
			view_students();
			break;
		case 4:
			delete_all();
			break;
		case 5:
			DPRINT("\n Enter number of node you want to view ");
			gets(index);
			get_Nth_node(gpFirstStudent, atoi(index));
			break;
		case 6:
			DPRINT("\n Enter number of node from the end of the list ");
			gets(index);
			get_Nth_node_from_end(gpFirstStudent, atoi(index));
			break;
		case 7:
			DPRINT("%d \n", get_length(gpFirstStudent));
			break;
		case 8:
			get_middle(gpFirstStudent);
			break;
		case 9:
			if (has_loop(gpFirstStudent))
				{DPRINT("List has loop within it. \n");}
			else  DPRINT("List does not have loop within it. \n");
			break;
		case 10:
			reverse_list(gpFirstStudent);
			break;
		default:
			DPRINT("\n\t WRONG OPTION");
			break;
		}

	}
}
