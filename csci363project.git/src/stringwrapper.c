/**
* Written by Thomas Ludwig
* The purpose of this program is 
* to abstract string manipulation 
* in C. This library only works for 
* ASCII characters.
* 
**/
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include "stringwrapper.h"
#define INIT_SIZE 128
#define NUM_BUF_LEN 512
#define TRUE	1
#define FALSE	0

/**
* function: wrp_calloc()
* 
* Purpose: Abstracts error-checking a call to calloc()
* away from the programmer.
**/

void *wrp_calloc(size_t nmemb, size_t size)
{
	void *retval;
	retval = calloc(nmemb, size);
	if (retval == NULL)
	{
		perror("Calloc call failed.\n");
		exit(1);
	}
	return retval;
}

/**
* function initiliazeStr()
*
* Purpose: Instantiate pseudo-object String
* by allocating INIT_SIZE bytes to member buf
* setting strLen to 0, and maxLen to INIT_SIZE
* Note: makes use of malloc.h
*
* input: struct String *str (already allocated)
**/
void initializeStr(struct String *str)
{
	str->buf = (char *)wrp_calloc(INIT_SIZE, sizeof(char));
	if (str->buf == NULL) 
	{
		printf("Error: initializeStr failed.\n");
		exit(-1);
	}
	str->strLen = 0;
	str->maxLen = INIT_SIZE;
}

/**
* function: createStr()
* Purpose: Allocate and initialize a new string structure.
**/

struct String *createStr(void)
{
	struct String *newStr;
	newStr = (struct String *)wrp_calloc(1, sizeof(struct String));
	initializeStr(newStr);
	return newStr;
}

/**
* function: createStrBySize(size_t minSize)
* Purpose: Allocate and initialize a new string structure such that
* allocated buffer length is no less than minSize
**/
struct String *createStrBySize(size_t minSize)
{
	struct String *newStr;
	newStr = (struct String *)wrp_calloc(1, sizeof(struct String));
	initializeStr(newStr);
	
	while (newStr->maxLen <= minSize)
		newStr->maxLen = 2*(newStr->maxLen);
	free(newStr->buf);
	newStr->buf = wrp_calloc(newStr->maxLen, sizeof(char));
	newStr->strLen = 0;
	return newStr;
}

/**
* function: destroyStr(struct String *str)
*
* Purpose: free str->buf and str
**/

void destroyStr(struct String *str)
{
	free(str->buf);
	free(str);
}
/**
* function: resizeStr()
* 
* Resizes struct str such that 
* it wastes less memory.
**/

void resizeStr(struct String *str)
{
	struct String *newStr = createStr();
	appendLit(newStr, str->buf);
	destroyStr(str);
	//Point *str to newStr
	str = newStr;
}

/**
* function: clearBufStr(struct String *str)
*
* Purpose: set elements of str->buf to 0
* set str->strLen to 0.
**/

void clearBufStr(struct String *str)
{
	memset(str->buf, 0, str->maxLen);
	str->strLen = 0;
}

/**
* function: printStr(struct String *str)
* 
* Purpose: print str->buf to standard output. Add newline
**/

void printStr(struct String *str)
{
	printf("%s\n", str->buf);
}

/**
* function: printAllStr(struct String *str)
*
* Purpose: print all members of String str to screen.
* Note: this is a debugging tool
**/

void printAllStr(struct String *str)
{
	printf("strLen: %zu\n", str->strLen);
	printf("maxLen: %zu\n", str->maxLen);
	printf("%s\n", str->buf);
}

/**
* function: prependStr(struct String *dest, struct String *pre)
* 
* Purpose: Concatenate dest->buf and pre->buf such that
* dest->buf =  pre->buf + dest->buf
* if dest->buf is not large enough to contain combined strings,
* keep doubling the dest->maxSize until it is able to contain
* the concatenated string.
* NOTE: makes use of malloc.h library
**/

void prependStr(struct String *dest, struct String *pre)
{
	size_t i = 0;
	size_t j = 0;
	char *newBuf; //char array that dest will point to
	size_t concatLength = dest->strLen + pre->strLen;
	
	//Check if concatenated length is large than dest->maxLen
	if (dest->maxLen <= concatLength) 
	{
		while (dest->maxLen <= concatLength)
			dest->maxLen = dest->maxLen << 1;
	}
	
	newBuf = (char *)wrp_calloc(dest->maxLen, sizeof(char));
	for(i = 0; i < pre->strLen; i++)
		newBuf[i] = pre->buf[i];
	for(j = 0; j <= dest->strLen; j++)
		newBuf[(j + pre->strLen)] = dest->buf[j];
	
	clearBufStr(dest);
	appendLit(dest, newBuf);
	free (newBuf);
	dest->strLen = concatLength;
} //prependStr

/**
* function: prependLit(struct String *dest, char *pre)
* 
* Purpose: Concatenate dest->buf and pre such that
* dest->buf = dest->buf + pre
* if dest->buf is not large enough to contain combined strings,
* keep doubling the dest->maxSize until it is able to contain
* the concatenated string.
* NOTE: makes use of malloc.h string.h library
**/

void prependLit(struct String *dest, char *pre)
{
	size_t i = 0;
	size_t j = 0;
	char *newBuf; //char array that dest will point to
	size_t preLength = strlen(pre); 
	size_t concatLength = dest->strLen + preLength;
	
	//Check if concatenated length is large than dest->maxLen,
	//Double dest->maxLen until you can fit concatenated string
	if (dest->maxLen <= concatLength) 
	{
		while (dest->maxLen <= concatLength)
			dest->maxLen = dest->maxLen << 1; 
	}
	
	newBuf = (char *)wrp_calloc(dest->maxLen, sizeof(char));
	for(i = 0; i < preLength; i++)
		newBuf[i] = pre[i];
	for(j = 0; j <= dest->strLen; j++)
		newBuf[i + j] = dest->buf[j];
	
	free(dest->buf);
	dest->buf = newBuf;
	dest->strLen = concatLength;

} //prependLit

/**
* function: appendStr(struct String *dest, struct String *app)
*
* Purpose: Concatenate Strings dest and app such that
* dest->buf = dest->buf + app->buf
*
*/

void appendStr(struct String *dest, struct String *app)
{
	size_t i = 0;
	size_t j = 0;
	size_t concatLength = dest->strLen + app->strLen;
	
	//Check if concatenated length is large than dest->maxLen,
	//Double dest->maxLen until you can fit concatenated string
	if (dest->maxLen <= concatLength) 
	{
		while (dest->maxLen <= concatLength)
			dest->maxLen = dest->maxLen << 1; 
		dest->buf = (char *)realloc(dest->buf, dest->maxLen);
		//Error checking for realloc
		if (dest->buf == NULL)
		{
			perror("appendStr realloc call failed.\n");
			exit(1);
		}
	}
	//Append to String app to dest
	i = dest->strLen;
	while (j <= app->strLen)
	{
		dest->buf[i + j] = app->buf[j];
		j++;
	}
	dest->strLen = concatLength;
}

/**
* function: appendLit(struct String *dest, char *app)
*
* Purpose: Concatenate String dest and char *app such that
* dest->buf = dest->buf + app
*
*/
void appendLit(struct String *dest, char *app)
{
	size_t i = 0;
	size_t j = 0;
	size_t appLength = strlen(app); 
	size_t concatLength = dest->strLen + appLength;
	
	//Check if concatenated length is large than dest->maxLen,
	//Double dest->maxLen until you can fit concatenated string
	if (dest->maxLen <= concatLength) 
	{
		while (dest->maxLen <= concatLength)
			dest->maxLen = dest->maxLen << 1; 
		dest->buf = (char *)realloc(dest->buf, dest->maxLen);
		//Error checking for realloc
		if (dest->buf == NULL)
		{
			perror("appendLit realloc call failed.\n");
			exit(1);
		}
	}
	//Append to String app to dest
	i = dest->strLen;
	while (j <= appLength)
	{
		dest->buf[i + j] = app[j];
		j++;
	}
	dest->strLen = concatLength;
} //appendLit

/**
* function: appendChar(struct String *dest, char c)
*
* Purpose: Add character to end of dest->buf. such 
* that:
* dest->buf = dest->buf + c.
* NOTE: Do not have add NULL-termination to string,
* the appendChar function automatically null-terminates.
* Appending a NULL ('\0') character has no effect.
**/
void appendChar(struct String *dest, char c)
{
	//Check if c is a '\0' termination character
	if (!c)
	{
		//printf("Attempted to append a null termination.\n");
	}
	else
	{
		//Appending the string would cause a buffer overflow
		if (dest->maxLen <= (dest->strLen + 1))
		{	
			dest->maxLen = 2*dest->maxLen; 
			dest->buf = (char *)realloc(dest->buf, dest->maxLen);
			//Error checking for realloc
			if (dest->buf == NULL)
			{
				perror("appendChar realloc call failed.\n");
				exit(1);
			}
		}
		dest->buf[dest->strLen] = c;
		dest->strLen++;
		dest->buf[dest->strLen] = 0;
	}
}

/**
* function appendInt(struct String *dest, int64_t num)
* Purpose: Append the string representation of num
* to dest. 
**/

void appendInt(struct String *dest, int64_t num)
{
	char tempBuffer[NUM_BUF_LEN] = {0};
	//%ld is not portable, only works for 64-bit machines
	sprintf(tempBuffer, "%" PRId64, num);
	appendLit(dest, tempBuffer);
}

/**
* function appendUInt(struct String *dest, uint64_t num)
* Purpose: Append the string representation of num,
* to dest. 
**/

void appendUInt(struct String *dest, uint64_t num)
{
	char tempBuffer[NUM_BUF_LEN] = {0};
	sprintf(tempBuffer, "%" PRIu64, num);
	appendLit(dest, tempBuffer);	
}


/**
* function appendVar()
* 
* In this function, I try to emulate sprintf format key letters
* as much as possible. I added the flag %t to append a
* struct String to the dest.
* %[flag][min width][precision][length modifier][conversion specifier]
* http://www.cprogramming.com/tutorial/printf-format-strings.html
* list: http://www.cdf.toronto.edu/~ajr/209/notes/printf.html
* format list:
*	%d - a signed integer (maximum 64-bit signed integer)
*	%u - an unsigned integer (maximum 64-bit unsigned integer)
*	%c - a character
*	%s - a character array
*	%t - a struct String pointer (appends the contents of a buf mem
* NOTES:
* ONLY USE the '%' character to start a format code. DO NOT TREAT 
* IT AS AN ORDINARY CHARACTER
* It is imperative that you accurately count the number of additional
* arguments you pass to the function in parameter int argc, otherwise
* the program that calls upon the function will crash.
* return values:
*	0: if successful
*	1: if an error occured.
**/

int appendVar(struct String *dest, const char *format, int argc, ...)
{
	int i = 0; //index of format string
	int stackCount = 0; //keeps track of number of arguments you counted.
	size_t strLen = strlen(format); //Length of the string
	int isError = FALSE;
	
	//Declarations of potential values
	int64_t tempInt;
	uint64_t tempUInt;
	char tempChar;
	char *tempCharArray;
	struct String *tempStr;
	
	va_list args;
	va_start (args, argc); //Start with last-defined variable argument 
	while ((i < strLen) && !isError)
	{
		if (format[i] == '%')
		{
			switch (format[(i+1)])
			{
				//Append an integer
				case 'd':
					tempInt = va_arg(args, int64_t);
					appendInt(dest, tempInt);
					stackCount++;
					break;
				//Append an unsigned integer
				case 'u':
					tempUInt = va_arg(args, uint64_t);
					appendUInt(dest, tempUInt);
					stackCount++;
					break;
				//Append a character
				case 'c':
					tempChar = va_arg(args, int);
					appendChar(dest, tempChar);
					stackCount++;
					break;
				//Append a character array
				case 's': 
					tempCharArray = va_arg(args, char *);
					appendLit(dest, tempCharArray);
					stackCount++;
					break;
				//Append a string struct
				case 't':
					tempStr = va_arg(args, struct String *);
					appendStr(dest, tempStr);
					stackCount++;
					break;
				//Unknown qualifier, display warning message
				default:
					printf("Error: Don't know what to do..\n");
					isError = TRUE;
					break;
			} //End of switch statement
			i += 2; //Jump past type qualifier in format string.
		}
		else
		{
			appendChar(dest, format[i]);
			i++;
		}
	}
	if (argc != stackCount)
	{
		perror("number arguments in format string do not match argc.\n");
		exit(-1);
	}
	va_end(args);
	return isError;
}

/**
* function: findLocStr(struct String *dest, struct String *sub, int i)
* 
* Purpose: This function iterates through dest->buf, looking for the string
* sub->buf. If there is a match, findLocStr returns the index value of where
* the first match of sub->buf is located. Otherwise, the function returns -1.
* 
* Inputs:
	struct String *dest: String that is to be searched
	struct String *sub: Substring to be matched.
	int i: index value of dest to start searching
* 
**/

int findLocStr(struct String *dest, struct String *sub, int i)
{
	int sIdx = i;
	int j = 0;
	int loc = -1; //index of starting string
	
	//Iterate through dest->buf
	while (sIdx < dest->strLen)
	{
		if (dest->buf[sIdx] == sub->buf[j])
		{
			loc = sIdx;
			//Iterate thru sub (up until '\0' termination)
			while (j < sub->strLen) 
			{
				//Match fails, set 
				if (dest->buf[sIdx + j] != sub->buf[j])
				{
					loc = -1;
					j = 0;
					break;
				}
				else
					j++;
			}
			//if sub string has been found, break
			if (loc != -1)
				break;
		}
		else
			sIdx++;
	}
	return loc;
}

/**
* function: findLocLit(struct String *dest, char *sub, int i)
* 
* Purpose: This function iterates through dest->buf, looking for the string
* sub. If there is a match, findLocLit returns the index value of where
* the first match of sub is located. Otherwise, the function returns -1.
* 
* Inputs:
*	struct String *dest: String that is to be searched
*	char *sub: Substring to be matched.
*	int i: index value of dest to start searching
* 
**/
int findLocLit(struct String *dest, char *sub, int i)
{
	int sIdx = i;
	int j = 0;
	int loc = -1; //index of starting string
	
	//Iterate through dest->buf
	while (sIdx < dest->strLen)
	{
		if (dest->buf[sIdx] == sub[j])
		{
			loc = sIdx;
			//Iterate thru sub (up until '\0' termination)
			while (j < strlen(sub)) 
			{
				//Match fails, set 
				if (dest->buf[sIdx] != sub[j])
				{
					loc = -1;
					j = 0;
					break;
				}
				else
				{
					sIdx++;
					j++;
				}
			}
			//if sub string has been found, break
			if (loc != -1)
				break;
			else
				loc = -1;
		}
		else
			sIdx++;
	}
	return loc;
} //findLocLit

/**
* function: compareStr(struct String *s1, struct String *s2)
*
* Purpose: determines if s1 should alphabetically appear 
* before s2. 
* return:
*	-1: s1 is alphabetically smaller than s2
*	0: s1 == s2
*	1: s2 is alphabetically smaller than s1
*/ 
int compareStr(struct String *s1, struct String *s2)
{
	//int retval;
	int i;
	
	if (s1->strLen < s2->strLen)
	{
		for(i = 0; i < s1->strLen; i++)
		{
			if (s1->buf[i] > s2->buf[i]) 
				return 1;
			else if (s1->buf[i] < s2->buf[i])
				return -1;
			else
				i++;
		}
		return -1;
	}
	else
	{
		for(i = 0; i < s2->strLen; i++)
		{
			if (s1->buf[i] > s2->buf[i]) 
				return 1;
			else if (s1->buf[i] < s2->buf[i])
				return -1;
			else
				i++;
		}
		if (s1->strLen == s2->strLen)
			return 0;
		else
		{
			return 1;
		}
	}
} //compareStr

/**
* function: truncateStr(struct String *str)
* Purpose: Replaces all non-alphanumeric 
* characters with ' ' (spaces). Also, lower-cases
* all alphabetic characters.
**/

void truncateStr(struct String *str)
{
	int i;
	for (i = 0; i < str->strLen; i++)
	{
		//Converts upper-case to lower-case character
		if ('A' <= str->buf[i] && str->buf[i] <= 'Z')
			str->buf[i] += 32;
		if (isAlphaNum(str->buf[i]) == 0)
			str->buf[i] = ' ';
	}
}

/**
* function: isAlphaNum(char c)
* 
* Purpose: Check if character is an 
* alphanumeric character.
* Return:
* 1: if character is alphanumeric
* 0: if not
**/

int isAlphaNum(char c)
{
	int retval;
	if ('A' <= c && c <= 'Z')
		retval = 1;
	else if ('a' <= c && c <= 'z')
		retval = 1;
	else
		retval = 0;
	return retval;
}

/**
* function isWhiteSpace(char c)
*
* Purpose: Checks if char c is a
* whitespace character or not 
*
* return value: 
*	if whitespace: 1
*	else: 0
*/

int isWhiteSpace(char c)
{
	int retval;
	if (c == ' ')
		retval = 1;
	else if (c == '\n')
		retval = 1;
	else if (c == '\r')
		retval = 1;
	else if (c == '\t')
		retval = 1;
	else if (c == '\v')
		retval = 1;
	else
		retval = 0;
	return retval;
}

/**
* function: createCharArray(src)
* Purpose: Allocates a character array,
* populated with the contents of src->buf.
**/

char *createCharArray(struct String *src)
{
	int i = 0;
	char *output;
	output = (char *)wrp_calloc(src->maxLen, sizeof(char));
	for (i =0; i <= src->strLen; i++)
		output[i] = src->buf[i];
	return output;
}