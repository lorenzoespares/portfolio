/**
* Header file for hashutils, a file aimed at 
* utilizing gcc's hash table (located in <search.h>
* for Search Engine.
* http://man7.org/linux/man-pages/man3/hsearch.3.html
* http://pubs.opengroup.org/onlinepubs/7990989775/xsh/hsearch.html
* http://profesores.elo.utfsm.cl/~agv/icd326/curry/examples/ch16/common/hsearch.c
* http://www.thinkage.ca/english/gcos/expl/c/lib/hsearc.html
* https://bugzilla.redhat.com/attachment.cgi?id=93928
**/

#define _GNU_SOURCE
#include <search.h>
#include <stdio.h>
#include <malloc.h>
#include "stringwrapper.h"
#include "stringlist.h"

//extern struct hsearch_data *WORD_TABLE;
void readFileContents(SLIST *wordList);
void buildTable(struct hsearch_data *WORD_TABLE);
int addStrKeyValue(struct hsearch_data *WORD_TABLE ,struct String *key, struct String *value);
int findStrKey(struct hsearch_data *WORD_TABLE, struct String *key, struct String *assocValue);
