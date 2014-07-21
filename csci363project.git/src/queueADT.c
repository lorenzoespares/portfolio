/**
* This file contains the functionality of a FIFO
* queue Abstract data type. note
* SQUEUE is the same thing as SLIST.
* SQUEUE->front contains last string enqueued.
* SQUEUE->back contains first string enqueued.
**/

#include "queueADT.h"

SQUEUE *createQueue(void)
{
	SQUEUE *newQueue = (SQUEUE *)createStrList();
	return newQueue;
}

void destroyQueue(SQUEUE *queue)
{
	destroyStrList((SLIST *)queue);
}

int enqueueStr(SQUEUE *queue, struct String *src)
{
	addStrToFront((SLIST *)queue, src);
	return 0;
}

int enqueueLit(SQUEUE *queue, char *lit)
{
	addLitToFront((SLIST *)queue, lit);
	return 0;
}

/**
* Removes end node, and populates string dest with
* contents of end node.
**/
int dequeueStr(SQUEUE *queue, struct String *dest)
{
	int retval;
	SNODE *tempNode;
	if (queue->length != 0)
	{
		appendStr(dest, queue->tail->str);
		tempNode = queue->tail;
		retval = destroyNode((SLIST *)queue, tempNode);
		return 0;
	}
	else
	{
		return -1;
	}
}

