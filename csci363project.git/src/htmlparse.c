/**
* This file contains the functions needed to parse the raw html
* code to build a list of urls, and a list of strings.
**/
#include "htmlparse.h"
#include "stringlist.h"
#include "stringwrapper.h"

/**
* function: parseURL(SLIST *linkList, struct String *html)
*
* Purpose: This function parses an <a href ... > tag from
* the html code. This function begins parsing at html->buf
* index i.
* Return value: 
*	parseURL returns -1 in the event that the program
* 	has reached the end of the html code, and/or
*	there are no more <a href ..> tags in the code.
* 	OR
*	parseURL returns the next index value after the closing
*	'>' character of a <a href..> tag.
* DO NOT USE. DEFAULTY
**/

int parseURL(SLIST *linkList, struct String *html, int i)
{
	int start;
	int end; 
	struct String *newURL = createStr(); 
	
	if (i >= html->strLen) {
		printf("Hit end of html code.\n");
		return -1;
	}
	
	//Change from <a href because there can be unlimited white-space between <a and href"
	start = findLocLit(html, "<a", i);
	if (start != -1)
	{
		end = findLocLit(html, ">", start+1);
		if (end == -1)
			return -1;
		else
		{
			while (start < end)
			{
				appendChar(newURL, html->buf[start]);
				start++;
			}
			cleanURL(newURL);
			//addStrToBack(linkList, newURL);
			addLit(linkList, newURL->buf);
			destroyStr(newURL);
			return end+1;
		}
	}
	else
	{
		return -1;
	}
}


int parseLinks(SLIST *linkList, struct String *html)
{
	struct String *buffer = createStr();
	int i = 0;
	int s = 0; //Start 
	int count = -1;
	while (i < html->strLen)
	{
		if((s = findLocLit(html, "<a", i)) != -1)
		{
			i = s;
			while (html->buf[i] != '>') {
				appendChar(buffer, html->buf[i]);
				i++;
			}
			addLitToBack(linkList, buffer->buf);
			count++;
			clearBufStr(buffer);
		}
		else
		{
			break;
		}
	}
	destroyStr(buffer);
	return count;
}

/**
* function: buildLinkList(SLIST *linkList, struct String *html, String *baseURL);
* Purpose: Parses urls in html code, and adds them to the string 
* list linkList. Furthermore, this function converts relative urls to absolute urls
**/

void buildLinkList(SLIST *linkList, struct String *html, struct String *baseURL)
{
	int retval;
	struct String *absURL = createStr();
	
	if ((retval = parseLinks(linkList, html)) != -1)
	{
		linkList->cur = linkList->head;
		while (linkList->cur != NULL)
		{
			cleanURL(linkList->cur->str);
			retval = convertRelPath(absURL, linkList->cur->str, baseURL);
			//Case 1: if link in linkList is already an absolute string
			if (retval == 0)
			{
				clearBufStr(linkList->cur->str);
				appendStr(linkList->cur->str, absURL);
				clearBufStr(absURL);
			}			
			linkList->cur = linkList->cur->next;
		}
	}
	destroyStr(absURL);
	//iterStrList(linkList, 0); //For debugging purposes only
}

/**
* function: cleanURL, removes extraneous characters from url
* i.e., cleans the url such that it only contains the url
* inside the double quotes.
* return = 0: good url, -1: bad url
*
**/

int cleanURL(struct String *url)
{
	int i = 0;
	int j = 0;
	struct String *goodURL = createStr();
	
	if (url->strLen == 0)
	{
		return -1;
	}
	
	i = findLocLit(url, "\"", 0) + 1; //Find first '"'
	j = findLocLit(url, "\"", i); //Find second '"'
	
	//only get url between double quotes marks
	while (i != j)
	{
		if (url->buf[i] == '#')
			break;
		else
		{
			appendChar(goodURL, url->buf[i]);
			i++;
		}
	}
	
	clearBufStr(url);
	appendStr(url, goodURL);
	destroyStr(goodURL); //Free memory 
	return 0;
}


/** 
* function: parseBaseURL(struct String *baseURL, struct String *htmlString)
*
* Purpose: Parse the base url from htmlString
* 	
* Return values:
*	-1: not found
*	0: Successfully pulled html code
**/

int parseBaseURL(struct String *baseURL, struct String *htmlString)
{
	int x = 0;
	int i = 0;
	int retval = -1;
	
	x = findLocLit(htmlString, "<base href", 0);	
	
	if (x != -1)
	{	
		retval = 0;
		i = findLocLit(htmlString, "\"", x) + 1; //index value of first '"'
		while (htmlString->buf[i] != '"')
		{
			appendChar(baseURL, htmlString->buf[i]);
			i++;
		}	
	}
	return retval;
}

/**
* function int url_convertRelPath()...
* This function has been cannibalized from url.c, updated to
* incorporate struct Strings instead of char arrays.
* The final version of the url is stored in absURL.
* this function returns -1 if the url is not a relative url.
**/
int convertRelPath(struct String *absURL, struct String *path, struct String *baseURL)
{
	struct String *workBuf; 
	int i;
	int i2;
	int j; 
	int retval;
	
	/* a relative path */
	if ((retval = findLocLit(path, "http://", 0)) == -1){ 
		workBuf = createStr(); //Allocate string to be used for manipulate later
		appendStr(absURL, baseURL);
		appendStr(absURL, path);
	}
	else {
		return -1;
	}

	/* collapse all "/./" */
	i = findLocLit(absURL, "/./", 0);
	while (i >= 0) 
	{
		//Read up until index i, then ignore 2, and then read until end of string
		for(j = 0; j < i; j++)
			appendChar(workBuf, absURL->buf[j]);
		for(j = i+2; j < absURL->strLen; j++) {
			appendChar(workBuf, absURL->buf[j]);
		}
		//Clear contents of absURL and replace with workBuf,
		//Then delete clear contents of work buffer
		clearBufStr(absURL);
		appendStr(absURL, workBuf);
		clearBufStr(workBuf);
		i = findLocLit(absURL, "/./", 0);
	}

	/* collapse all "/../" */
	i = findLocLit(absURL, "/../", 0);
	while (i >= 0) {
		i2 = i-1;
		while ((absURL->buf[i2] != '/') && (i2 >= 0)){
			i2--;
		}
		/* copy the first part */
		for (j = 0; j < i2; j++)
			appendChar(workBuf, absURL->buf[j]);
		/* then the second part */
		for (j = i+3; j < absURL->strLen; j++)
			appendChar(workBuf, absURL->buf[j]);
		
		//Clear buffer contents of absURL and replace them with workBuf
		clearBufStr(absURL);
		appendStr(absURL, workBuf);
		clearBufStr(workBuf);
		i = findLocLit(absURL, "/../", 0);
	}

	destroyStr(workBuf);

	return 0;
}

