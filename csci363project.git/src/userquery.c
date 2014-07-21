/**
* The purpose this file is to handle user queries
* and return output.
**/
#define _GNU_SOURCE
#include <stdio.h>
#include <search.h>
#include "userquery.h"
#include "hashutils.h"

//Encapsulates all of the functions here to be used in extraction.c
void writeResponse(struct hsearch_data *WORD_TABLE, struct String *htmlResponse, struct String *inputStr)
{
	SLIST *queryList = (SLIST *)calloc(1, sizeof(SLIST));
	SLIST *resultsList = (SLIST *)calloc(1, sizeof(SLIST));
	initStrList(queryList);
	initStrList(resultsList);
	
	parseInputStr(queryList, inputStr);
	buildResults(WORD_TABLE, resultsList, queryList);
	createOutput(htmlResponse, queryList, resultsList);
	destroyStrList(queryList);
	destroyStrList(resultsList);
}

void parseInputStr(SLIST *queryList, struct String *inputStr)
{
	charSplit(queryList, inputStr, '+');
	queryList->cur = queryList->head;
	while (queryList->cur != NULL)
	{
		truncateStr(queryList->cur->str);
		queryList->cur = queryList->cur->next;
	}
	queryList->key = inputStr;
}

void buildResults(struct hsearch_data *WORD_TABLE, SLIST *resultsList, SLIST *queryList)
{
	struct String *assocValue = (struct String *)calloc(1, sizeof(struct String));
	initializeStr(assocValue);
	queryList->cur = queryList->head;
	int retval = -1;
	while (queryList->cur != NULL)
	{
		retval = findStrKey(WORD_TABLE, queryList->cur->str, assocValue);
		if (retval == 0)
		{
			printf("key was found.\n");
			addLitToBack(resultsList, assocValue->buf);
			clearBufStr(assocValue);
		}
		
		queryList->cur = queryList->cur->next;
	}
	//destroyStr(assocValue);
}
/*
int checkWordList(SLIST *resultsList, SLIST *wordList, struct String *query)
{
	int retval = -1;
	if (wordList->length == 0)
	{
		return retval;
	}
	else
	{
		wordList->cur = wordList->head;
		while (wordList->cur != NULL)
		{
			//Found match
			if (compareStr(wordList->cur->str, query) == 0)
			{
				retval = 0;
				return retval;
			}
			else
				wordList->cur = wordList->cur->next;
		}
		retval = -1;
		return retval;
	}
}
*/
void createOutput(struct String *dest, SLIST *queryList, SLIST *results)
{
	int i = 1;
	char tempBuffer[1024] = {0};
	appendLit(dest, "User query: ");
	appendStr(dest, queryList->key);
	appendLit(dest, "<br>Search engine answer:<br>");
	if (results->length == 0)
	{
		appendLit(dest, "No page was found.<br>");
	}
	else
	{
		appendLit(dest, "a total of ");
		sprintf(tempBuffer, "%d URLs found, the first %d of 20 of these URLs are:<br><br>", results->length, results->length);
		appendLit(dest, tempBuffer);
		memset(tempBuffer, 0, 1024);
		results->cur = results->head;
		while ((results->cur != NULL) && (i <= 20))
		{
			sprintf(tempBuffer, "%d. <a href =\" %s\">%s</a><br>", i, results->cur->str->buf, results->cur->str->buf);
			appendLit(dest, tempBuffer);
			memset(tempBuffer, 0, 1024);
			i++;
			results->cur = results->cur->next;
		}
	}
}
