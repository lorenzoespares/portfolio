#ifndef HTMLPARSE_H_
#define HTMLPARSE_H_

//#include <glib.h>
#include <stdio.h>
#include "stringlist.h"
#include "stringwrapper.h"

void fixChunk(SLIST *chunkList);
void buildLinkList(SLIST *, struct String *, struct String *);
int parseURL(SLIST *, struct String *, int);
int cleanURL(struct String *url);
int parseBaseURL(struct String *baseURL, struct String *htmlString);
int parseLinks(SLIST *linkList, struct String *html);
int convertRelPath(struct String *absURL, struct String *path, struct String *baseURL);
#endif 
