#ifndef STRINGLIST_H_
#define STRINGLIST_H_

#include "stringwrapper.h"

typedef struct String STR;

typedef struct StringNode 
{
	int count; //Number instances of string
	struct String *str;
	struct StringNode *next;
	struct StringNode *prev; 
} SNODE;

typedef struct StringList
{
	int length;
	struct String *key; //To be used for hash map
	SNODE *head;
	SNODE *tail; 
	SNODE *cur; //current Node
} SLIST;

//SNODE functions
void initStrNode(SNODE *node, struct String *str);
void destroyStrNode(SNODE *node); //Don't use
int joinNextNode(SNODE *node);
int joinPrevNode(SNODE *node);
void printAllNode(SNODE *node);

//SLIST functions
void initStrList(SLIST *strList);
SLIST *createStrList(void);
void destroyStrList(SLIST *strList);
int destroyNode(SLIST *strList, SNODE *node);
void iterStrList(SLIST *strList, int isReversed);
void joinList(SLIST *strList, struct String *dest);

void addStr(SLIST *strList, struct String *s);
void addLit(SLIST *strList, char *lit);
void addStrToBack(SLIST *strList, struct String *s);
void addLitToBack(SLIST *strList, char *lit);
void addToEnd(SLIST *strList, SNODE *node);
void addNode(SLIST *strList, SNODE *node);

void addToFront(SLIST *strList, SNODE *node);
void addStrToFront(SLIST *strList, struct String *s);
void addLitToFront(SLIST *strList, char *lit);

void removeDupStr(SLIST *strList);
int findStrNode(SLIST *strList, struct String *str); //node containing str located in strList->cur
//not necessary b/c addnode adds alphabetically, and using node->prev can reverse iterate
//void sortStrList(SLIST *strList, int isReverse); 
void joinAllStrList(SLIST *strList, struct String *dest);
void splitByNum(SLIST *strList, struct String *src, int bufLen);
void charSplit(SLIST *strList, struct String *src, char c);
void strSplit(SLIST *strList, struct String *src, struct String *split);

int splitByChar(SLIST *strList, struct String *src, char c, int start);
int splitByLit(SLIST *strList, struct String *src, char *lit, int start);
void cleanStrList(SLIST *strList);
#endif 