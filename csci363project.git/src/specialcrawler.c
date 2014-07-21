/***
* This file contains our specialized webcrawler
* program. Unlike crawler.c, which only handles
* .html and .xml files. This program handles
* .txt and .pdf files (which are converted to .txt
* files using pdftotext.
**/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <gdbm.h>
#include "stringwrapper.h"
#include "stringlist.h"
#include "extraction.h"
#include "dbtools.h"
#include "crawlerutils.h"

//#define CRAWL_COUNT 50
#define TRUE	1
#define FALSE	0

//Function prototypes
int handlePDF(struct String *url, SLIST *wordList);

int main(void)
{
	SLIST *visitList = createStrList();
	SLIST *visitedList = createStrList();
	SLIST *wordList = createStrList();
	SLIST *tempWords = createStrList();
	struct String *buffer = createStr();
	struct String *host = createStr();
	struct String *path = createStr();
	SNODE *tempNode;
	SNODE *word;
	char c;
	FILE *fp;
	GDBM_FILE db;
	int retval;
	
	//Open notvisited file, parse contents and populate toVisitList
	fp = fopen("notVisited.txt", "r");
	if (fp == NULL)
	{
		printf("ERROR: could not open notVisited.txt file.\n");
		exit(1);
	}
	
	//Read file contents into buffer, then close file pointer
	while((c = fgetc(fp)) != EOF)
		appendChar(buffer, c);
	fclose(fp);
	
	charSplit(visitList, buffer, '\n');
	
	//Open database
	db = gdbm_open("invertedIndex.gdb", 0, GDBM_WRCREAT | GDBM_NOLOCK, 0664, NULL);
	if (db == NULL) {
		printf("ERROR: Could not open db file.\n");
		exit(1);
	}
	
	//Iterate through visitList
	for (tempNode = visitList->head; tempNode != NULL; tempNode = tempNode->next)
	{
		//Check if bucknell is in url
		if ((retval = findLocLit(tempNode->str, "bucknell", 0)) != -1)
		{ 
			//look for .txt file
			if ((retval = findLocLit(tempNode->str, ".txt", 0)) != -1) {
				printf("Found .txt: %s\n", tempNode->str->buf);
				getHostAndPath(tempNode->str, host, path);
				extractText(host->buf, path->buf, tempWords);
				printf("populating database with %d words.\n", tempWords->length);
				populateDB(db, tempWords, tempNode->str); 
				clearBufStr(host);
				clearBufStr(path);
				addLitToBack(visitedList, tempNode->str->buf);
			}
			//look for .pdf file
			else if ((retval = findLocLit(tempNode->str, ".pdf", 0)) != -1)
			{
				printf("Found .pdf: %s\n", tempNode->str->buf);
				if ((retval = handlePDF(tempNode->str, tempWords)) == 0)
				{
					printf("populating database with %d words.\n", tempWords->length);
					populateDB(db, tempWords, tempNode->str);
					addLitToBack(visitedList, tempNode->str->buf);
				}
				else
					tempNode = tempNode->next;
			}
			
			//Add words from tempWordList to wordList
			if (tempWords->length > 0)
			{
				printf("Adding words to wordList.\n");
				for (word = tempWords->head; word != NULL; word = word->next)	
					addLit(wordList, word->str->buf);
					
				//Destroy and re-create tempWordList so that it can be reused 
				destroyStrList(tempWords);
				tempWords = createStrList();
			}
		}	
		tempNode = tempNode->next;
	}
	
	gdbm_close(db);
	
	//Append dbkeylist.txt
	printf("Appending dbkeylist.txt.\n");
	fp = fopen("dbkeylist.txt", "a+");
	if (fp == NULL) {
		printf("ERROR: attempting to append dbkeylist.txt is a failure.\n");
		exit(1);
	}
	fprintf(fp, "\n\n==== specialcrawler.c ====\n\n");
	//Append each word in wordList to dbkeylist.txt
	for (word = wordList->head; word != NULL; word = word->next)
		fprintf(fp, "%s\n", word->str->buf);
	
	fclose(fp);
	
	printf("Appending visitedpages.txt.\n");
	fp = fopen("visitedpages.txt", "a+");
		if (fp == NULL) {
		printf("ERROR: attempting to append visitedpages.txt is a failure.\n");
		exit(1);
	}
	fprintf(fp, "\n\n==== specialcrawler.c ====\n\n");
	for (word = visitedList->head; word != NULL; word = word->next)
		fprintf(fp, "%s\n", word->str->buf);
		
	fclose(fp);
	
	return 0;
}

int handlePDF(struct String *url, SLIST *wordList)
{
	int retval;
	struct String *command = createStr();
	//appendVar(command, "python3.3 desperation.py %t", 1, url);
	appendVar(command, "python3.2 desperation.py %t", 1, url);
	
	retval = system(command->buf);
	if (retval == -1)
	{
		printf("Unable to use system.\n");
		exit(1);
	}
	
	//Python script was able to successfully generate pdfTemp.txt
	if (access("pdfTemp.txt", F_OK ) != -1 )
	{
		localExtract("pdfTemp.txt", wordList);
		system("/bin/rm -f pdfTemp.txt");
		destroyStr(command);
		return 0; 
	}
	//Python script was unsuccessful in its attempt to generate pdfTemp.txt
	else
	{
		printf("Unable to generate pdfTemp.txt.\n");
		destroyStr(command);
		return -1;
	}
}

