/**
* This file contains our implementation of 
* a web crawler. This crawler handles 
* all .html and .xml files
**/

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
#include "crawlerutils.h"

#define CRAWL_COUNT 650
#define PAUSE_COUNT 40
#define TRUE	1
#define FALSE	0

int main(int argc, char *argv[])
{
	SQUEUE *urlQueue = createQueue(); //Stores urls to be crawled
	SLIST *visitedURLLIST = createStrList(); //Stores urls that have been crawled
	SLIST *keyList = createStrList(); //List of keys
	SLIST *tempUrlList = createStrList(); //Stores temporary list passed to extraction func.
	SLIST *tempWordList = createStrList(); //List of words parsed from webpage
	SLIST *notVisitedList = createStrList(); //Stores list of urls that where parsed, but not pushed onto the queue
	struct String *tempStr = createStr(); //Temporary string, used for building host/path things.
	GDBM_FILE db; //pointer to database
	int retval = 0;
	int isComplete = FALSE;
	int count = 0; //Keeps track of number of web pages crawled
	struct String *hostStr = createStr();
	struct String *pathStr = createStr();
	
	//Check user input	
	if (argc < 3) {
		printf("usage: %s%s", argv[0], " <compane> <path>\n");
		exit(1);
	}	
	
	else {
		/* convert arguments to binary computer and appnum */ 
		appendLit(hostStr, argv[1]);
		appendLit(pathStr, argv[2]);
	}
	
	//Build database (GDBM_SYNC does not exist), Maybe change such that it gives fixed size writing blocks
	db = gdbm_open("invertedIndex.gdb", 0, GDBM_WRCREAT | GDBM_NOLOCK, 0664, NULL);
	if (db == NULL) {
		printf("ERROR: Could not open db file.\n");
		exit(1);
	}
	
	while ((count <= CRAWL_COUNT) && !isComplete)
	{
		//Crawler has crawled 40 pages, pause program for 30 sec
		if ((count%PAUSE_COUNT == 0) && (count != 0))
		{
			printf("Crawled through %d pages, wait 30 seconds.\n", count);
			sleep(30);
		}
		//Keep crawling
		printf("Extracting information from web page host: %s path: %s.\n", hostStr->buf, pathStr->buf);
		
		//int extraction(char *host, char *path, SLIST *wordList, SLIST *urlList)
		retval = extraction(hostStr->buf, pathStr->buf, tempWordList, tempUrlList);
		if (retval != 0) {
			printf("Parsing web-page failed.\n");
			printf("host: %s, path: %s\n", hostStr->buf, pathStr->buf);
		}	
		//Extraction successful
		else
		{
			//Build complete version of url
			clearBufStr(tempStr);
			appendVar(tempStr, "%s%t%t", 3, "http://www.", hostStr, pathStr);
			addLit(visitedURLLIST, tempStr->buf); //Adding web page url to visited url list.
			populateQueue(urlQueue, visitedURLLIST, tempUrlList, notVisitedList); //Populating url queue with new values.
			
			//Populate database with contents of parsed words
			populateDB(db, tempWordList, tempStr); 
					
			//Add contents of tempWordList to wordList 
			tempWordList->cur = tempWordList->head;
			while (tempWordList->cur != NULL)
			{
				addLit(keyList, tempWordList->cur->str->buf); //Use add lit because it copies str contents to wordList
				tempWordList->cur = tempWordList->cur->next;
			}
		} //Successful extraction
		
		//Destroy temporary lists
		destroyStrList(tempUrlList); 
		destroyStrList(tempWordList); 
		
		//Re-create them so next url can utilize them
		tempUrlList = createStrList(); 
		tempWordList = createStrList(); 
		
		//Dequeue urlQueue and get new host/path combination
		clearBufStr(tempStr); 
		clearBufStr(hostStr);
		clearBufStr(pathStr);

		retval = dequeueStr(urlQueue, tempStr);
		if (retval == -1) {
			printf("Empty url queue.\n");
			isComplete = TRUE;
		}
		else {	
			//printf("Attempting to populate hostStr & pathStr.\n");
			retval = getHostAndPath(tempStr, hostStr, pathStr);
			printf("dequeued host: %s, path: %s\n\n", hostStr->buf, pathStr->buf);
		}
		count++;
	}
	//Free allocated memory
	destroyStr(tempStr);
	destroyStr(hostStr);
	destroyStr(pathStr);
	destroyStrList(tempUrlList);
	destroyStrList(tempWordList);
	
	
	gdbm_close(db); //close database
	
	//Write visited urls to file, and wordlist to file
	writeWordList(visitedURLLIST, "visitedpages.txt");
	writeWordList(keyList, "dbkeylist.txt");
	writeWordList(notVisitedList, "notVisited.txt");	
	return 0;
}
