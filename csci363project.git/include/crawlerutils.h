#ifndef CRAWLERUTILS_H_
#define CRAWLERUTILS_H_


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <gdbm.h>
#include "stringwrapper.h"
#include "stringlist.h"
#include "queueADT.h"
#include "extraction.h"
#include "dbtools.h"

//Function prototypes
int writeWordList(SLIST *, char *path);
int populateQueue(SQUEUE *urlQueue, SLIST *visitedURLLIST, SLIST *urlList, SLIST *notVisitedList);
int getHostAndPath(struct String *src, struct String *host, struct String *path);

#endif