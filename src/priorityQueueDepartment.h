#ifndef _priorityQueueDepartment_h
#define _priorityQueueDepartment_h
#include <stdlib.h>
#include <stdbool.h>

#include "department.h"

typedef struct pqType
{
    double priority;           //priority of this element
    Department *info;          //Change this line to set the type for the priority queue to store
} pqType;

typedef struct PriorityQueue
{
    pqType *data;             //pqType data stored in the stack
    int last;                 //index of the last element in the array
    int capacity;             //current capacity of stack
} PriorityQueue;

PriorityQueue *createPQ( );
void freePQ( PriorityQueue *ppq );
//void freePQElements( PriorityQueue *ps  );

pqType removePQ( PriorityQueue *ppq );
void insertPQ( PriorityQueue *ppq, pqType pt );
pqType getNextPQ( PriorityQueue *ppq );

bool isEmptyPQ( PriorityQueue *ppq );
bool isFullPQ( PriorityQueue *ppq );

#endif
