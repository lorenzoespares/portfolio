/**
* The purpose of this file is to read searchwords.txt
* and generate a hash table for the searchserver.c to use
**/
#define _GNU_SOURCE
#include <malloc.h>
#include <stdio.h>
#include <search.h>
#include "stringwrapper.h"
#include "stringlist.h"
#include "hashutils.h"

//struct hsearch_data *WORD_TABLE = NULL;

/**
* function buildTable(WORD_TABLE)
* 
* Purpose: This function creates the hash table
* WORD_TABLE and populates it with the words from
* "searchwords.txt". WORD_TABLE must be initially
* allocated and its contents must be originally zeroed.
**/

void buildTable(struct hsearch_data *WORD_TABLE)
{
	SLIST *wordList = (SLIST *)calloc(1, sizeof(SLIST));
	
	//Generate a list of words from file searchwords.txt
	initStrList(wordList);
	readFileContents(wordList); 
	
	//Create the hash table
	hcreate_r(wordList->length*2, WORD_TABLE);
	wordList->cur = wordList->head;
	while (wordList->cur != NULL)
	{
		addStrKeyValue(WORD_TABLE, wordList->cur->str, wordList->key);
		wordList->cur = wordList->cur->next;
	}
}

/**
* function: readFileContents
*
* Purpose: This function parses through searchwords.txt
* and populates SLIST wordList.
* For this function to work properly, the first line of 
* searchwords.txt must be of the form "url: the_page_url"
* or the parsing will not work.
**/

void readFileContents(SLIST *wordList)
{
	FILE *fp;
	int i = 0;
	int x = 0;
	size_t fileLen;
	char *buffer;
	struct String *fileString = (struct String *)calloc(1, sizeof(struct String));
	struct String *baseURL = (struct String *)calloc(1, sizeof(struct String));
	
	initializeStr(fileString);
	initializeStr(baseURL);
	
	fp = fopen("searchwords.txt", "r");
	//Error opening the file
	if (fp == NULL)
	{
		exit(-1);
	}
	else
	{
		//Read entire file contents into buffer
		fseek(fp, 0, SEEK_END);
		fileLen = ftell(fp);
		rewind(fp);
		buffer = (char *)calloc((fileLen + 1), sizeof(char));
		fread(buffer, sizeof(char), fileLen, fp);
		appendLit(fileString, buffer);
		free(buffer);  
		fclose(fp);
		
		//Build baseURL
		x = findLocLit(fileString, "\n", 5);
		for(i = 5; i < x; i++)
			appendChar(baseURL, fileString->buf[i]);
		wordList->key = baseURL;
		
		//Build wordList
		memset(fileString->buf, '\n', x); 
		charSplit(wordList, fileString, '\n');
		destroyStr(fileString); 
	}
}

/**
* function: findStrKey
*
* Purpose: This function searches the hash table WORD_TABLE for
* the key and populates assocValue with the key's associated value
* from the hash table.
* findStrKey returns 0 if the key was successfully found. Otherwise,
* the function returns -1.
**/

int findStrKey(struct hsearch_data *WORD_TABLE, struct String *key, struct String *assocValue)
{
	ENTRY e, *ep;
	int retval;
	e.key = key->buf;
	retval = hsearch_r(e, FIND, &ep, WORD_TABLE);
	if (retval > 0)
	{
		if (ep == NULL)
		{
			printf("Entry not found.\n");
			return -1;
		}	
		else
		{
			printf("value: %s\n", (char *)ep->data);
			appendLit(assocValue, (char *)ep->data);
			return 0;
		}
	}
	else
	{
		printf("Searching in hash-table was a failure.\n");
		return -1;
	}
}

/**
* function: addStrKeyValue
*
* Purpose: This function adds the key, value pair to the hash
* table WORD_TABLE. 
*/

int addStrKeyValue(struct hsearch_data *WORD_TABLE, struct String *key, struct String *value)
{
	//int hsearch_r(ENTRY item, ACTION action, ENTRY **retval, struct hsearch_data *htab);
	ENTRY e, *ep;
	int retval = 0;
	e.key = key->buf;
	e.data = (void *)value->buf;
	retval = hsearch_r(e, ENTER, &ep, WORD_TABLE);
	/* there should be no failures */
	if (retval > 0)
	{
		//printf("entry successful.\n");
		if (ep == NULL) {
			fprintf(stderr, "entry failed\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		printf("Entry unsuccessful.\n");
		exit(-1);
	}
	return 0;
}
