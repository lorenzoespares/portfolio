/**
* This file contains the code that helps the crawler
* function make use of the words and urls parsed
* from each web-page.
* cases that function extraction.c cannot
* handle alone, namely parsing .txt files
* and .pdf files.
**/

#include "crawlerutils.h"

//host starts after first ".", path starts immediately after host
int getHostAndPath(struct String *src, struct String *host, struct String *path)
{
	int i; //Index for String src
	i = findLocLit(src, ".", 0);
	if (i == -1) {
		printf("finding host a failure.\n");
		return -1;
	}
	else
	{
		i++; //Get first index value
		while ((src->buf[i] != '/') && (i <= src->strLen)) {
			appendChar(host, src->buf[i]);
			i++;
		}
		while (i <= src->strLen) {
			appendChar(path, src->buf[i]);	
			i++;
		}
		return 0;
	}	
}


int writeWordList(SLIST *wordList, char *path)
{
	FILE *fp = fopen(path, "w");
	if (fp == NULL)
	{
		printf("Error opening file.\n");
		exit(1);
	}
	wordList->cur = wordList->head;
	while (wordList->cur != NULL)
	{
		fprintf(fp, "%s\n", wordList->cur->str->buf);
		wordList->cur = wordList->cur->next;
	}
	fclose(fp);
	return 0;
}

int populateQueue(SQUEUE *urlQueue, SLIST *visitedURLLIST, SLIST *urlList, SLIST *notVisitedList)
{
	/*const char *goodhosts[] = {"http://www.eg.bucknell.edu/~csci204/",
							"http://www.eg.bucknell.edu/~csci203/2014-spring/",
							"http://www.eg.bucknell.edu/~cs206/",
							"http://www.eg.bucknell.edu/~cs240/2014-spring/",
							"http://www.eg.bucknell.edu/~csci311/S14/",
							"http://www.eg.bucknell.edu/~cs363/2014-spring/"}; */
	int isVisited;
	int isEnqueued;
	int i = 0;
	int retval;
	urlList->cur = urlList->head;
	while (urlList->cur != NULL)
	{	
		//retval = findLocLit(urlList->cur->str, "eg.bucknell.edu/", 0);
		retval = findLocLit(urlList->cur->str, "bucknell", 0);
		if (retval == -1)
		{
			//printf("url (%s) is not hosted by bucknell comp sci department.\n", urlList->cur->str->buf);
			addLitToBack(notVisitedList, urlList->cur->str->buf);
		}
		else
		{
			//Check if url is in queue or visited list
			isVisited = findStrNode(visitedURLLIST, urlList->cur->str);
			isEnqueued = findStrNode(urlQueue, urlList->cur->str);
			//If url has not been visited or in the queue
			if ((isVisited != 0) && (isEnqueued != 0))
			{
				//Need to work on this to include .xml, .txt, and .pdf files
				if (findLocLit(urlList->cur->str, ".html", 0) != -1)
					enqueueLit(urlQueue, urlList->cur->str->buf);
				else if (findLocLit(urlList->cur->str, ".xml", 0) != -1)
					enqueueLit(urlQueue, urlList->cur->str->buf);
				else
					addLitToBack(notVisitedList, urlList->cur->str->buf);
				//else if (findLocLit(urlList->cur->str, ".txt", 0) != -1)
				//	enqueueLit(urlQueue, urlList->cur->str->buf);
			}
		}
		urlList->cur = urlList->cur->next;
	}
	return 0;
}
