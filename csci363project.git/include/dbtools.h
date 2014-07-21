#ifndef DBTOOLS_H_
#define DBTOOLS_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <gdbm.h>
#include "stringwrapper.h"
#include "stringlist.h"

typedef struct uNode
{
	uint32_t wc; //number of instances of word in web-page
	struct String *url;
	struct uNode *next;
} UNODE;

//This structure contains 
typedef struct
{
	uint32_t df; //Document frequency, also number of elements in uArray
	UNODE *head;
	UNODE *tail;
	UNODE *cur;
} GDB_VAL;

int generateValueFromStr(GDBM_FILE db, struct String *query, GDB_VAL *valList);
int cleanValList(GDB_VAL *valList);

//Function prototypes
uint32_t myExp(uint32_t, uint32_t);
void populateKeyDatum(datum *key, struct String *keyStr);
void destroyDatum(datum *dat);
void createValueDatum(datum *valDat, struct String *url, uint32_t wordCount);
void appendValueDatum(datum *valDat, struct String *url, uint32_t wordCount);
UNODE *createUNODE(struct String *src);
void appendDBList(GDB_VAL *dbList, UNODE *node);
void populateValList(GDB_VAL *dbList, datum *val);
int populateDB(GDBM_FILE db, SLIST *wordList, struct String *inputURL);

#endif