/**
* dbtools.c 
* Contains functions to build,
* find, delete, etc for 
* a gdb file
**/

#include "dbtools.h"

#define URL_LEN 256
#define PAUSE_COUNT 40
#define TRUE	1
#define FALSE	0


/**
* "public" function list
* 	int populateDB(GDBM_FILE db, SLIST *wordList, struct String *inputURL);
*	int generateValueFromStr(GDBM_FILE db, struct String *query, GDB_VAL *valList);
* 	int cleanValList()
**/
//assocVal df member must be set to zero for this to work
//(it must be empty)
// if query is not in database, returns -1, if it is returns 0
int generateValueFromStr(GDBM_FILE db, struct String *query, GDB_VAL *valList)
{
	datum key, value;
	int dbRet;
	populateKeyDatum(&key, query);
	dbRet = gdbm_exists(db, key);
	//Key does not exist in database.
	if (dbRet == 0)
	{
		printf("query (%s) does not exist in database.\n", (char *)key.dptr);
		return -1;
	}
	else
	{
		value = gdbm_fetch(db, key);
		if (value.dptr == NULL) {
			printf("Error: could not look up %s\n", (char *)key.dptr);
			exit(1);
		}
		//printf("Populating valList.\n");
		populateValList(valList, &value);
		return 0;
	}
}

int cleanValList(GDB_VAL *valList)
{
	UNODE *temp;
	if (valList->df == 0)
	{
		printf("List already empty.\n");
		return -1;
	}
	else
	{
		printf("cleanValList: entering while loop to remove UNODES.\n");
		while (valList->df > 0)
		{
			temp = valList->head->next;
			printf("Destroying string.\n");
			destroyStr(valList->head->url);
			printf("Freeing UNODE.\n");
			free(valList->head);
			valList->head = temp;
			valList->df--;
		}
		return 0;
	}
}

//Used for temporary keys
void populateKeyDatum(datum *key, struct String *keyStr)
{
	key->dptr = createCharArray(keyStr);
	key->dsize = strlen(key->dptr) + 1;
}

void destroyDatum(datum *dat)
{
	free(dat->dptr);
	free(dat);
}

void createValueDatum(datum *valDat, struct String *url, uint32_t wordCount)
{
	struct String *data = createStr();
	//value str syntax: "wordCount<url>", wordCount as a uint32
	appendVar(data, "%u<%t>", 2, (uint64_t)wordCount, url);
	valDat->dptr = createCharArray(data);
	valDat->dsize = strlen(valDat->dptr) + 1; //data->strLen;
	destroyStr(data);
}

void appendValueDatum(datum *valDat, struct String *url, uint32_t wordCount)
{
	struct String *data = createStr();
	appendVar(data, "%s|%u<%t>", 3, valDat->dptr, (uint64_t)wordCount, url);
	free(valDat->dptr); //prevent memory leak
	valDat->dptr = createCharArray(data);
	valDat->dsize = strlen(valDat->dptr) + 1;
	destroyStr(data);
}

/**
* This function is my version of exp() function in math.h
* I wrote it so I don't have to link program to math library.
* Does not work for negative exponents
**/
uint32_t myExp(uint32_t base, uint32_t power)
{
	uint32_t result = 1;
	while (power > 0)
	{
		result *= base;
		power--;
	}
	return result;
}

//Need to add error checking to see if '<' and '>' exist, otherwise overflow
UNODE *createUNODE(struct String *src)
{
	UNODE *newNode = (UNODE *)wrp_calloc(1, sizeof(UNODE));
	struct String *newUrl = createStr();
	unsigned char numBuf[256] = {0};
	int i = 0;
	int digits; //Number of digits wordCount has
	uint32_t out = 0;
	uint32_t temp;
	//First get wordCount
	//printf("Filling numbuf.\n");
	while (src->buf[i] != '<')
	{
		numBuf[i] = src->buf[i];
		i++;
	}
	digits = i - 1; //at this point, index i points to '<'
	//Then I'll get url
	i++; //Increment i to get index one after '<' character
	while(src->buf[i] != '>') {
		appendChar(newUrl, src->buf[i]);
		i++;
	}
	//Populate UNODE 
	//sscanf(numBuffer, "%" SCNu32, &out);
	i = 0;
	//printf("numBuffer contents: %s\n", numBuf);
	while (i < strlen((char *)numBuf))
	{
		temp = myExp(10, digits); //holds power of ten
		out += (numBuf[i] - '0')*temp;
		i++; //move to next index value
		digits--;
	}
	
	newNode->wc = out;
	newNode->url = newUrl;
	newNode->next = NULL;
	return newNode;
}

void appendDBList(GDB_VAL *dbList, UNODE *node)
{
	//Empty List
	if (dbList->df == 0)
	{ 
		dbList->head = node;
		dbList->tail = node;
	}
	//Add to back of list
	else
	{
		dbList->tail->next = node;
		node->next = NULL;
		dbList->tail = node;
	}
	dbList->df++;
}

//dbList has to have df = 0 if empty, otherwise function doesn't work
//To be used for server and debugging the crawler
void populateValList(GDB_VAL *dbList, datum *val)
{
	int i;
	struct String *tempStr = createStr();
	SLIST *tempList; 
	UNODE *nPtr; //Pointer to newly created node
	appendLit(tempStr, val->dptr); //create string to use charSplit
	
	i = findLocLit(tempStr, "|", 0);
	//Only one UNODE
	if (i == -1)
	{
		//printf("only one UNODE.\n");
		nPtr = createUNODE(tempStr);
		appendDBList(dbList, nPtr);
	}
	//Iterate through tempList to build dbList
	else
	{
		//printf("multiple UNODES.\n");
		tempList = createStrList();
		charSplit(tempList, tempStr, '|');
		destroyStr(tempStr);
		tempList->cur = tempList->head;
		while (tempList->cur != NULL)
		{
			printf("Chunk contents: %s\n", tempList->cur->str->buf);
			nPtr = createUNODE(tempList->cur->str);
			appendDBList(dbList, nPtr);
			tempList->cur = tempList->cur->next;
		}
		destroyStrList(tempList);
	}
}

//This is the the only function that the crawler should use
int populateDB(GDBM_FILE db, SLIST *wordList, struct String *inputURL)
{
	int dbRet; 
	datum key, value;
	//iterate through wordList
	wordList->cur = wordList->head;
	while (wordList->cur != NULL)
	{
		populateKeyDatum(&key, wordList->cur->str); //Don't use, don't need to copy contents of node
		//Check if key already exists in database
		dbRet = gdbm_exists(db, key);
		//Does not exist in database
		if (dbRet == 0) 
		{
			//printf("key (%s) does not currently exist in database.\n", key.dptr);
			createValueDatum(&value, inputURL, wordList->cur->count);
			dbRet = gdbm_store(db, key, value, GDBM_INSERT);
			switch(dbRet)
			{
				case 0:
					//printf("Store: %s ==> %s\n", (char *)key.dptr, (char *)value.dptr);
					break;
				case 1:
					//printf("Could not store %s because it already exists in database.\n", (char *)key.dptr);
					break;
				default:
					printf("Error: Could not insert key (%s).\n", (char *)key.dptr);
					exit(1);
					break;
			}
		}
		//Does exist in database
		else
		{
			//printf("key (%s) exists in database.\n", (char *)key.dptr);
			value = gdbm_fetch(db, key);
			if (value.dptr == NULL) {
				printf("Error: could not look up %s\n", (char *)key.dptr);
				exit(1);
			}
			appendValueDatum(&value, inputURL, wordList->cur->count);
			dbRet = gdbm_store(db, key, value, GDBM_REPLACE);
			switch(dbRet)
			{
				case 0:
					//printf("Store Successful: %s ==> %s\n", (char *)key.dptr, (char *)value.dptr);
					break;
				default:
					printf("Error: Could not insert key (%s).\n", (char *)key.dptr);
					exit(1);
					break;
			}
		}
		//prevent memory leaks
		//printf("Freeing dptr member for key and value structs.\n");
		free(value.dptr);
		free(key.dptr);
		//Go to next node
		wordList->cur = wordList->cur->next;
	}
	return 0;
}
