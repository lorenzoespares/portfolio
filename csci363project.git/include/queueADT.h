#ifndef QUEUEADT_H_
#define QUEUEADT_H_

#include "stringwrapper.h"
#include "stringlist.h"

typedef SLIST SQUEUE;

//Function prototypes
SQUEUE *createQueue(void);
void destroyQueue(SQUEUE *queue);
int enqueueStr(SQUEUE *queue, struct String *src);
int enqueueLit(SQUEUE *queue, char *lit);
int dequeueStr(SQUEUE *queue, struct String *dest);

#endif