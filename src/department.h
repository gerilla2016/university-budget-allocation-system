#ifndef _department_h
#define _department_h
#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

typedef struct Department
{
    char* name;                 //name of this department
	double totalSpent;          //total spent on this department so far
	
	Queue* itemsDesired;        //Queue of items desired by this department
	Queue* itemsReceived;       //Queue of items received by this department
	Queue* itemsRemoved;        //Queue of items not received by this department
}  Department;

#endif
