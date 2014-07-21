#ifndef EXTRACTION_H_
#define EXTRACTION_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
 /* list is used to store the resulting urls */
#include "list.h"  
#include "tcplib.h"
 /* string functions */
#include "stringutil.h"  
#include "htmllinks.h"
#include "url.h"
/* Contains parsing functions and linked list containing urls */
#include "stringwrapper.h"
#include "stringlist.h"
#include "htmlparse.h"


//Function prototypes
int writeFile(char *inputURL, SLIST *urlList, SLIST *wordList, char *outputFile);

//struct pageExtract *extraction(char *host, char *path, char *outputFile);
int extraction(char *host, char *path, SLIST *wordList, SLIST *urlList);
int extractText(char *host, char *path, SLIST *wordList);
int localExtract(char *fInput, SLIST *wordList);
void rmStopWords(SLIST *wordList);
#endif 