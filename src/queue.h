#ifndef _queue_h
#define _queue_h
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "item.h"

typedef struct Item* queueType;  //This queue contains items 

typedef struct LLNode
{
    queueType qt;               //queueType contained in this node  (i.e. an item)
    struct LLNode *pNext;       //pointer to the next node in the linked list
}  LLNode;

typedef struct Queue
{
    LLNode *qFront;             //pointer to the first element of the queue
    LLNode *qRear;              //pointer to the last element of the queue
} Queue;

Queue *createQueue( );
void freeQueue( Queue *pq );

queueType getNext( Queue *pq );
queueType dequeue( Queue *pq );
void enqueue( Queue *pq, queueType qt );

bool isEmpty( Queue *pq );

#endif
