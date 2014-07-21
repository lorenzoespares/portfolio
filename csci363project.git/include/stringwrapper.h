#ifndef STRINGWRAPPER_H_
#define STRINGWRAPPER_H_

/***
* Header file for stringwrapper.c
* The purpose of this program is to provide an abstracted 
* string library for C programming that is intended to
* minimize problems with the implementation of strings
* in c. I attempted to give it an OOP-feel to strings.
***/

#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define INIT_SIZE 128

struct String
{
	char *buf; /* Contains the actual string */
	size_t strLen; /* the length of the string, including '/0' character */
	size_t maxLen; /* the number of bytes allocated to the string */
};

/**
* Function prototypes:
*
* function conventions: 
* The first parameter is always of type (struct String *) and 
* its the parameter that is altered.
* 
**/

void appendUInt(struct String *dest, uint64_t num);
void appendInt(struct String *dest, int64_t num);
int appendVar(struct String *dest, const char *format, int argc, ...);

void *wrp_calloc(size_t nmemb, size_t size);
struct String *createStr(void);
struct String *createStrBySize(size_t minSize);
void resizeStr(struct String *str);
char *createCharArray(struct String *src);

void initializeStr(struct String *str);
void destroyStr(struct String *str);
void clearBufStr(struct String *str); //Zeroes the char *buf member 
void printStr(struct String *str); //Just prints the buf member
void printAllStr(struct String *str); //Prints all members

void prependStr(struct String *dest, struct String *pre);
void prependLit(struct String *dest, char *pre);
void appendStr(struct String *dest, struct String *app);
void appendLit(struct String *dest, char *app);
void appendChar(struct String *dest, char c);

int findLocStr(struct String *dest, struct String *sub, int i);
int findLocLit(struct String *dest, char *sub, int i);

int compStr(struct String *str1, struct String *str2);
void toLower(struct String *str); 

int compareStr(struct String *s1, struct String *s2);
void truncateStr(struct String *str);
int isAlphaNum(char c);
int isWhiteSpace(char c);

#endif 
