/*-----------------------------------------------------------------------
 *
 * Program: extraction
 * Purpose: fetch page from a webpage , extracts urls from HTML files
 * Usage:   url-extractor <compname> <path> [appnum]
 * Note:    Appnum is optional. If not specified the standard www appnum
 *          (80) is used.
 *-----------------------------------------------------------------------
 */

#include "extraction.h"
#define BUFFSIZE	512
#define HTTPPORT    80
#define ECHOPORT 	14016
#define TRUE		1
#define FALSE		0

/**
* function extraction(host, path, outputFile, app)
* Purpose: Request webpage and parse webpage's html code.
* outputs a struct containing the input url (host + path), 
* a list of url links, and a list of words parsed from the html.
* In the event of a failure, the output structure will be a NULL
**/

int extraction(char *host, char *path, SLIST *wordList, SLIST *urlList)
{
	int	conn;
	char buff[(BUFFSIZE + 1)] = {0};
	int	len;
	
	struct String *htmlString = createStr(); //Contains raw html pulled from web page
	struct String *cleanString = createStr(); //Contains the truncated html code 
	struct String *baseURL = createStr(); //Contains the url in the <base href = "">

	/* contact the web server */
	conn = socketClient(host, HTTPPORT);
	if (conn < 0) {
		exit(1);
	}

	/* send an HTTP/1.1 request to the webserver */
	sprintf(buff, "GET %s HTTP/1.1\r\nHost: %s\r\n", path, host);
	strcat(buff, "User-Agent: self-module\r\n");
	strcat(buff, "Accept: text/html,application/xhtml+xml\r\n");
	strcat(buff, "Accept-Language: en-us,en;q=0.5\r\n");
	//	strcat(buff, "Accept-Encoding: gzip,defalte\r\n");
	strcat(buff, "Accept-Charset: ISO-8859-1,utf-8;q=0.7\r\n");
	strcat(buff, "Keep-Alive: 115\r\n");
	strcat(buff, "Connection: keep-alive\r\n");
	strcat(buff, "\r\n");

	len = strlen(buff);
	(void) send(conn, buff, len, 0);

	/* convert all data received into chunks, append it to htmlString */
	while((len = recv(conn, buff, BUFFSIZE, 0)) > 0) {
		appendLit(htmlString, buff);
		memset(buff, 0, BUFFSIZE);
	}

	//Parsing base url
	if (-1 == parseBaseURL(baseURL, htmlString)) {
		printf("Could not locate base url.\n");
		return -1;
	}	
	
	//Parsing url links
	//printf("Building url link list.\n");
	buildLinkList(urlList, htmlString, baseURL);
	//Add the url that the crawler parsed the html from
	urlList->key = createStr();
	appendStr(urlList->key, baseURL);

	//creating word list
	appendStr(cleanString, htmlString);
	
	//cleaning html string by replacing all non-alphanumeric characters with spaces.
	truncateStr(cleanString);
	charSplit(wordList, cleanString, ' ');
	wordList->key = createStr();
	appendStr(wordList->key, baseURL);
		
	//cleaning word list based on existing stop words
	//printf("Started removing stop words.\n");
	rmStopWords(wordList);
	
	//free up memory
	//printf("Extraction: destroying htmlString, cleanString, & baseURL.\n");
	destroyStr(htmlString);
	destroyStr(cleanString);
	destroyStr(baseURL);
	
	return 0;
} 


/**
* function: extractText(char *host, char *path, SLIST *wordList)
* This function duplicates the functionality of extraction
* function, intended to parse a .txt file on some remote host.
**/
int extractText(char *host, char *path, SLIST *wordList)
{
	int	conn;
	char buff[(BUFFSIZE + 1)] = {0};
	int	len;
	struct String *textString = createStr();
	//struct String *tempWordList = createStr();
	
	/* contact the web server */
	conn = socketClient(host, HTTPPORT);
	if (conn < 0) {
		exit(1);
	}

	/* send an HTTP/1.1 request to the webserver */
	sprintf(buff, "GET %s HTTP/1.1\r\nHost: %s\r\n", path, host);
	strcat(buff, "User-Agent: self-module\r\n");
	strcat(buff, "Accept: text/plain,text/html\r\n");
	strcat(buff, "Accept-Language: en-us,en;q=0.5\r\n");
	strcat(buff, "Accept-Charset: ISO-8859-1,utf-8;q=0.7\r\n");
	strcat(buff, "Keep-Alive: 115\r\n");
	strcat(buff, "Connection: keep-alive\r\n");
	strcat(buff, "\r\n");

	len = strlen(buff);
	(void) send(conn, buff, len, 0);

	/* convert all data received into chunks, append it to textString */
	while((len = recv(conn, buff, BUFFSIZE, 0)) > 0) {
		appendLit(textString, buff);
		memset(buff, 0, BUFFSIZE);
	}
	
	//cleaning text string by replacing all non-alphanumeric characters with spaces.
	truncateStr(textString);
	charSplit(wordList, textString, ' ');
	
	//cleaning word list based on existing stop words
	//printf("Started removing stop words.\n");
	rmStopWords(wordList);
	
	//free up memory
	//printf("Extraction: destroying textString.\n");
	destroyStr(textString);
	return 0;
}

/**
* function: localExtract
* This function is a modified version of extractText,
* but designed to parse a text file on the local host.
**/

int localExtract(char *fInput, SLIST *wordList)
{
	FILE *fp;
	char c;
	struct String *buffer = createStr();
	
	//Attempt to open file 
	fp = fopen(fInput, "r");
	if (fp == NULL)
	{
		printf("Unable to open file: %s\n", fInput);
		return -1;
	}
	while((c = fgetc(fp)) != EOF)
		appendChar(buffer, c);
		
	fclose(fp);
	
	//Truncate and clean string to be ready for parsing
	truncateStr(buffer);
	charSplit(wordList, buffer, ' ');
	rmStopWords(wordList);
	
	destroyStr(buffer); //free allocated memory
	return 0;
}

/**
* function: rmStopWords
* This function opens stoplist.txt, 
* and builds a list of words stored 
* in that file. It then iterates through
* that list of words, removing all words
* that are shared by wordList and the list
* of stop words.
**/

void rmStopWords(SLIST *wordList)
{
	//long fLen;
	int retval;
	char c;
	//char *tempBuffer;
	SNODE *n = NULL; //Points to current node
	SLIST *stopList = createStrList();
	struct String *tempStr = createStr();
	FILE *fp = fopen("stoplist.txt", "r");
	if (fp == NULL) {
		printf("failed to open stoplist.txt.\n");
		exit(-1);
	}
	//Read contents of file into tempStr
	while((c = fgetc(fp)) != EOF)
		appendChar(tempStr, c);
		
	fclose(fp);
	charSplit(stopList, tempStr, '\n'); //Build list of words from tempStr (each node is a line)
	
	//Iterate through wordList
	wordList->cur = wordList->head;
	while(wordList->cur != NULL) 
	{
		retval = findStrNode(stopList, wordList->cur->str);
		//current word not in stoplist
		if (retval == -1) {
			n = NULL;
			wordList->cur = wordList->cur->next;
		}
		//Current word in stoplist
		else
		{
			n = wordList->cur;
			if (n == wordList->tail)
			{
				//printf("node (%s) is tail node.\n", n->str->buf);
				destroyNode(wordList, n);
				break;
			}
			wordList->cur = wordList->cur->next;
			//printf("node (%s) in stop words, removing it.\n", wordList->cur->str->buf);
			//int destroyNode(SLIST *strList, SNODE *node)
			destroyNode(wordList, n);
		}
	}
	//free variables from memory
	destroyStr(tempStr);
	destroyStrList(stopList);
}