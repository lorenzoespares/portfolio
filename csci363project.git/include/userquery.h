//Header file for userquery.c, file to handle user search requests
#ifndef USERQUERY_H_
#define USERQUERY_H_

#define _GNU_SOURCE
#include <search.h>
#include "stringwrapper.h"
#include "stringlist.h"

void parseInputStr(SLIST *queryList, struct String *inputStr);
void buildResults(struct hsearch_data *WORD_TABLE, SLIST *resultsList, SLIST *queryList);
int checkWordList(SLIST *resultsList, SLIST *wordList, struct String *query);
void createOutput(struct String *dest, SLIST *queryList, SLIST *results);
void writeResponse(struct hsearch_data *WORD_TABLE, struct String *htmlResponse, struct String *inputStr);

#endif 