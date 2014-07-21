/*
 * server.c - main
 * http://tom-virtualbox:14016/form
 * does not work for Google Chrome Internet Browser
 */
//#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <search.h>
#include <string.h>
#include <gdbm.h>
#include "tcplib.h"
#include "stringlist.h"
#include "stringwrapper.h"
#include "dbtools.h"

#define ALWAYS			1
#define ECHOPORT        14016       /* a non-privilege port so all can use */
#define MAX             512

//Function prototypes
//void doEcho(int, struct hsearch_data *WORD_TABLE);
void doEcho(int, GDBM_FILE);
void buildResponse(GDBM_FILE, struct String *, struct String *);
void createOutput(struct String *dest, struct String *query, GDB_VAL *valList);
//void buildResponse(struct hsearch_data *,struct String *, struct String *);

int main(int argc,char *argv[])    {

	int s, t;
	GDBM_FILE db;
	db = gdbm_open("invertedIndex.gdb", 0, GDBM_READER | GDBM_NOLOCK, 0664, NULL);
	if (db == NULL) {
		printf("ERROR: Could not open db file.\n");
		exit(1);
	}
  //struct hsearch_data *WORD_TABLE = (struct hsearch_data *)wrp_calloc(1, sizeof(struct hsearch_data));
  //Create hash table so that user queries can be serviced.
  //buildTable(WORD_TABLE);
  
  s = socketServer(ECHOPORT);
  while (ALWAYS)    {
    if (s > 0)
      t = acceptConn(s);
    else	{
      fprintf(stderr," socket error\n");
      exit(1);
    }
    if (t > 0)  {
      printf("echo service requested\n");
	  fflush(stdout);
      doEcho(t, db);
      shutdown(t, 2);
    }  else {
      fprintf(stderr," connection error\n");
      exit(2);
    }
  } /* while(1) */
  close(s);
  return 0;
}

void doEcho(int sock, GDBM_FILE db)  
{
	char echo_buf[BUFSIZ+10];
	char *buf = "HTTP/1.0 200 OK\r\n\r\n";
	int length;
	FILE *file;
	SLIST *queryList = createStrList();
	struct String *searchString = createStr();
	struct String *searchquery = createStr();
	struct String *response = createStr();
	struct String *reject = createStr();
	
	appendLit(response, buf);
	file = fopen("form.html", "r");
	fseek(file, 0, SEEK_END);
	length = ftell(file);
	fseek(file, 0, SEEK_SET);
	fread(echo_buf, 1, length, file);
	fclose(file);
	appendLit(response, echo_buf);
	
	write(sock, response->buf, response->strLen);

	int n = read(sock, echo_buf, BUFSIZ);
	echo_buf[n] = 0;
	
	char * searchword = (char *)wrp_calloc(BUFSIZ+10, sizeof(char));
	strcpy(searchword, echo_buf);
	char * Search;//(char *)malloc(50*sizeof(char));
	Search = strstr(searchword,"FirstInput=");
	
	if (Search != NULL) {
		appendLit(searchString, Search);
		charSplit(queryList, searchString, '&');
		queryList->cur = queryList->head;

		int i = findLocLit(queryList->cur->str, "=", 0);

		for (int j = i+1; j < queryList->cur->str->strLen; j++) {
			appendChar(searchquery, queryList->cur->str->buf[j]);
		} 
		
		printf("query is %s\n", searchquery->buf);	
		printf("querylength is %d\n", (int)searchquery->strLen);	
		
		if(searchquery->strLen != 0){
		    //build and write query response
		    clearBufStr(response);
			buildResponse(db, response, searchquery); 
		    write(sock, response->buf, response->strLen);
		} else {
			appendLit(reject, "<html>\n<body>\n<p>");
			appendLit(reject, "<font color=\"red\">Search for a word</font><br>");
	        appendLit(reject, "</p>\n</body>\n</html>\n");
	        write(sock, reject->buf, reject->strLen);
		}
	}
			  
	memset(echo_buf, 0, n);
}

//void buildResponse(struct hsearch_data *WORD_TABLE, struct String *response, struct String *query)
void buildResponse(GDBM_FILE db, struct String *response, struct String *query)
{	
	int retval;
	GDB_VAL valList;
	SLIST *qList = createStrList();
	//Writing html response message for user
	appendLit(response, "<html>\n<body>\n<p>");
	
	charSplit(qList, query, '+'); //Split into list of strings
	//right now it only gets one search query
	//Iterate through queryList
	for (qList->cur = qList->head; qList->cur != NULL; qList->cur = qList->cur->next) 
	{
		//initialize valList
		valList.df = 0;
		retval = generateValueFromStr(db, qList->cur->str, &valList);
		//Could not find query in database
		if (retval == -1) 
		{
			//Write query not found response...
			appendLit(response, "User query: ");
			appendStr(response, qList->cur->str);
			appendLit(response, "<br>Search engine answer:<br>");
			appendLit(response, "No page was found.<br>");
		}
		else
		{
			//Iterate through GDB_VAL
			createOutput(response, qList->cur->str, &valList);
		}
		//free valList members
		cleanValList(&valList);
	}
	destroyStrList(qList);
	appendLit(response, "</p>\n</body>\n</html>\n");
}

void createOutput(struct String *dest, struct String *query, GDB_VAL *valList)
{
	int i = 1;
	UNODE *tempNode;
	char tempBuffer[1024] = {0};
	appendLit(dest, "User query: ");
	appendStr(dest, query);

	appendLit(dest, " a total of ");
	sprintf(tempBuffer, "%d URLs found, the first %d of 20 of these URLs are:<br><br>", valList->df, valList->df);
	appendLit(dest, tempBuffer);
	memset(tempBuffer, 0, 1024);
	
	tempNode = valList->head;
	while ((tempNode!= NULL) && (i <= 20))
	{
		sprintf(tempBuffer, "%d. <a href =\" %s\">%s</a><br>", i, tempNode->url->buf, tempNode->url->buf);
		appendLit(dest, tempBuffer);
		memset(tempBuffer, 0, 1024);
		i++;
		tempNode = tempNode->next;
	}
}



