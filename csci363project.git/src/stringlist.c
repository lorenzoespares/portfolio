/**
* Written by Thomas Ludwig
* Purpose: Incorporate stringwrapper.c
* functions into a linked list.
*
*/

#include "stringlist.h"
#include "stringwrapper.h"
#define bufLen

/**
* function: initStrNode(SNODE *node, struct String *str)
*
* Purpose: Instantiates a SNODE with a count of 1, a str memeber
* pointing to struct String *str
* NOTE: Both node and str must be allocated before calling
* this function. 
**/
void initStrNode(SNODE *node, struct String *str)
{
	node->str = str;
	node->next = NULL;
	node->prev = NULL;
	node->count = 1;
}

/**
* function: destroyStrNode(SNODE *node)
* 
* Purpose: free memory contained in node->str,
* and then node.
* DO NOT USE. IT DOES NOT WORK!!!
* Reason why: in the event 
* that node is the head/tail of a list
* does not change list's head/tail members.
* I'm leaving this here because I don't want to change
* destroyStrList()
* For some reason, using destroyNode() with
* destroyStrList causes a segmentation fault
**/

void destroyStrNode(SNODE *node)
{
	if (node->next != NULL)
		node->next->prev = node->prev;
	if (node->prev != NULL)
		node->prev->next = node->next;
	destroyStr(node->str);
	free(node);
}

/**
* function: destroyNode(strList, node)
* This function removes node from strList.
* The node must be in strList for this to work.
**/

int destroyNode(SLIST *strList, SNODE *node)
{
	SNODE *nextNode = node->next;
	SNODE *prevNode = node->prev;
	
	//Debugging
	
	//strList is empty
	if (strList->length == 0) {
		return -1;
	}
	//strList contains only one node, so removing the node 
	//results in an empty list
	else if (strList->length == 1) {
		destroyStr(node->str);
		free(node);
		strList->length = 0; //Set list length to 0
		strList->head = NULL;
		strList->tail = NULL;
		return 0;
	}
	else {
		//Case 1: node is strList->tail
		if (node == strList->tail) {
			//Set previous node 
			//printf("Setting prevNode->next to NULL.\n");
			prevNode->next = NULL;
			//printf("setting strList->tail to prevNode.\n");
			strList->tail = prevNode;
		}
		//Case 2: node is strList->head
		else if (node == strList->head) {
			nextNode->prev = NULL;
			strList->head = nextNode;
		}
		//Case 3: node is neither the head or tail
		else {
			prevNode->next = nextNode;
			nextNode->prev = prevNode;
		}
	
		//printf("destroyNode: destroying string.\n");
		destroyStr(node->str);
		//printf("Freeing node.\n");
		free(node);
		strList->length--; //Decrement the length of strList
		return 0;
	}
}

/**
* function: printAllNode(SNODE *node)
* Purpose: This is a debugging tool to print the
* node member count and str.
**/

void printAllNode(SNODE *node)
{
	printf("count: %d, str: ", node->count);
	printAllStr(node->str);
}

/** SLIST functions **/

/**
* function: initStrList()
* Purpose: Initializes a SLIST structure
* (which has already been allocated), by  
* populating its members with the necessary 
* information.
**/
void initStrList(SLIST *strList)
{
	strList->length = 0;
	strList->head = NULL;
	strList->tail = NULL;
	strList->cur = NULL;
}

/**
* function: createStrList()
* Purpose: Allocates and initializes
* a new SLIST structure. 
**/

SLIST *createStrList(void)
{
	SLIST *newList;
	newList = (SLIST *)wrp_calloc(1, sizeof(SLIST));
	initStrList(newList);
	return newList;
}

/**
* function destroyStrList(SLIST *strList)
* 
* Purpose: This function destroys the SLIST strList
* by iterating through the list, and freeing each node
* in memory.
**/
void destroyStrList(SLIST *strList)
{
	SNODE *n = strList->head;
	if (strList->key != NULL)
		destroyStr(strList->key);
	if (strList->length != 0)
	{
		do 
		{
			strList->head = strList->head->next;
			destroyStrNode(n); 
			//destroyNode(strList, n); CAUSES seg fault
			n = strList->head;
		} while (strList->head != NULL);
	}
	free(strList);	
}

/**
* function: iterStrList()
* 
* Purpose: This function iterates a SLIST structure,
* printing the contents of each node. The order of the 
* strList traversal is dependent on input isReversed,
* if isReversed == 0, the function will go from head to
* tail (alphabetical order). Otherwise, iterStrList will
* iterate from tail to head (reverse alphabetical order).
**/ 

void iterStrList(SLIST *strList, int isReversed)
{
	//print in alphabetical order 
	if (isReversed == 0)
	{
		strList->cur = strList->head;
		while (strList->cur != NULL)
		{
			//printAllNode(strList->cur);
			printStr(strList->cur->str);
			strList->cur = strList->cur->next;
		}
		strList->cur = NULL;
	}
	//print in reverse alphabetical order
	else
	{
		strList->cur = strList->tail;
		while (strList->cur != NULL)
		{
			printAllNode(strList->cur);
			strList->cur = strList->cur->prev;
		}
		strList->cur = NULL;
	}
}

/**
* function: joinList
* Purpose: This function iterates through a SLIST
* structure (from head to tail), appending contents 
* of each traversed node to string dest. The string 
* contained in each node is separated by a space. 
**/

void joinList(SLIST *strList, struct String *dest)
{
	strList->cur = strList->head;
	while(strList->cur != NULL) {
		appendStr(dest, strList->cur->str);
		appendChar(dest, ' ');
		strList->cur = strList->cur->next;
	}
	strList->cur = NULL;
}

/**
* function: addToFront(strList, node)
* Purpose: This function prepends strList
* with node.
**/

void addToFront(SLIST *strList, SNODE *node)
{
	//Initialize node's previous and next values to NULL
	node->prev = NULL;
	node->next = NULL;
	//add node to empty list
	if (strList->length == 0)
	{
		strList->head = node;
		strList->tail = node;
		strList->length++;
	}
	//list is not empty
	else
	{
		//First have node point to currentHead
		node->next = strList->head;
		//Next have current head point to node
		strList->head->prev = node;
		//Finally move list's head pointer to new node
		strList->head = node; 
		strList->length++;
	}
}

/**
* function: addStrToFront(SLIST *strList, struct String *s)
* Purpose: Prepends strList with node whose contents are 
* struct String s
**/

void addStrToFront(SLIST *strList, struct String *s)
{
	SNODE *node = (SNODE *)wrp_calloc(1, sizeof(SNODE));
	initStrNode(node, s);
	addToFront(strList, node);
}

/** 
* function: addLitToFront()
* Same as function addStrToFront, only 
* input is a character array
**/

void addLitToFront(SLIST *strList, char *lit)
{
	struct String *newStr = createStr();
	SNODE *newNode = (SNODE *)wrp_calloc(1, sizeof(SNODE));
	appendLit(newStr, lit);
	initStrNode(newNode, newStr);
	addToFront(strList, newNode);
}

/**
* function: addToBack()
* Purpose: This function appends SLIST
* structure strList with SNODE node.
**/

void addToBack(SLIST *strList, SNODE *node)
{
	node->prev = NULL;
	node->next = NULL;
	//add node to empty list
	if (strList->length == 0)
	{
		strList->head = node;
		strList->tail = node;
		strList->length++;
	}
	
	//add node non-empty list
	else
	{
		//Set prev member of node to addr. of tail
		node->prev = strList->tail;
		strList->tail->next = node;
		strList->tail = node;
		strList->length++;
	}
}

/**
* function addNode(SLIST *strList, SNODE *node)
* Purpose: add a node into the alphabetically sorted 
* strList (a -> z). The addition of the node must not
* break the alphabetical ordering of the strList
*/

void addNode(SLIST *strList, SNODE *node)
{
	SNODE *prevNode;
	//Add node to empty list
	if (strList->length == 0)
	{
		strList->head = node;
		strList->tail = node;
		strList->length++;
	}
	//non-empty list
	else
	{
		//new node should appear alphabetically before strList->head
		if (compareStr(node->str, strList->head->str) == -1)
		{
			addToFront(strList, node);
		}
		//new node is equal to strList->head
		else if (compareStr(node->str, strList->head->str) == 0)
			strList->head->count++;
			
		//node should appear alphabetically after strList->tail
		else if ((compareStr(node->str, strList->tail->str)) == 1)
		{
			addToBack(strList, node);
		}
		//new node is equal to strList->tail
		else if (compareStr(node->str, strList->tail->str) == 0)
			strList->tail->count++;
		//new node is not smaller than strList->head nor greater than strList->tail
		else
		{
			//Start at node after head
			strList->cur = strList->head;
			while (strList->cur != NULL)
			{
				//new node contains the same string as strList->cur
				if (compareStr(node->str, strList->cur->str) == 0)
				{
					strList->cur->count++;
					break;
				}			
				//node->str should appear alphabetically after cur->str
				else if (compareStr(node->str, strList->cur->str) == 1)
				{
					strList->cur = strList->cur->next;					
				}
				//node->str should appear alphabetically before cur->str
				else
				{
					prevNode = strList->cur->prev;
					//First have node point to forwards to current and backwards to previous node
					node->next = strList->cur;
					node->prev = prevNode;
					prevNode->next = node; //Point old previous node to new node
					strList->cur->prev = node;
					strList->length++;
					break;
				}
			}
		}
	}
}

/**
* function: addStrToBack()
* Purpose: This function encapsulates struct String *s
* in an SNODE structure, and then appends the new node
* to strList.
**/

void addStrToBack(SLIST *strList, struct String *s)
{
	SNODE *node = (SNODE *)wrp_calloc(1, sizeof(SNODE));
	initStrNode(node, s);
	addToBack(strList, node);
}

/**
* function: addLitToBack()
*
* Purpose: Duplicates the functionality of addStrToBack, but
* for a string literal or null-terminated character array
* instead of a struct String.
**/

void addLitToBack(SLIST *strList, char *lit)
{
	struct String *newStr = createStr();
	SNODE *newNode = (SNODE *)wrp_calloc(1, sizeof(SNODE));
	appendLit(newStr, lit);
	initStrNode(newNode, newStr);
	addToBack(strList, newNode);
}

/**
* function: addStr()
* Duplicates the functionality of addNode(), 
* but for a struct String instead of a SNODE.
**/
void addStr(SLIST *strList, struct String *s)
{
	SNODE *node = (SNODE *)wrp_calloc(1, sizeof(SNODE));
	initStrNode(node, s);
	addNode(strList, node);
}
/**
* function: addLit()
* Duplicates the functionality of addStr and addNode,
* but alphabetically adds parameter lit to strList.
**/

void addLit(SLIST *strList, char *lit)
{
	struct String *newStr = createStr();
	appendLit(newStr, lit); //Copy contents of char *lit into newStr
	SNODE *newNode = (SNODE *)wrp_calloc(1, sizeof(SNODE));
	initStrNode(newNode, newStr);
	addNode(strList, newNode);
}

/**
* function findStrNode
* Purpose: Iterate through strList to find the first
* node is equal to str.
* NOTE: List starts iteration starts at strList->cur
* and when a node is found, strList->cur points to 
* that node.
* return:
*	-1: on failure to find str
*	0: found a node that contains str
**/

int findStrNode(SLIST *strList, struct String *src)
{
	int retval = -1;
	int cmp;
	strList->cur = strList->head;
	while (strList->cur != NULL)
	{
		cmp = compareStr(strList->cur->str, src);
		//cmp = findLocStr(strList->cur->str, src, 0);
		//Found string
		if (cmp == 0)
		{
			retval = 0;
			break;
		}
		else
			strList->cur = strList->cur->next;
	}
	return retval;
}

/**
* Function: void splitByNum(SLIST *strList, struct String *src, int bufLen)
* 
* Purpose: Split src into a SLIST comprised of string chunks of strLen bufLen.
* NOTE: sub-strings are added in order of their original position in src,
* not in alphabetical order
**/
/*
void splitByNum(SLIST *strList, struct String *src, int bufLen)
{
	char *tempBuffer;
	tempBuffer = (char *)wrp_calloc(bufLen, sizeof(char));
	int i = 0;
	int b = 0;
	
	while (i <= src->strLen)
	{
		//Case 1: tempBuffer has reached bufLen
		if (b == (bufLen - 1))
		{
			tempBuffer[bufLen] = 0; //Null-terminate
			addLitToBack(strList, tempBuffer);
			memset(b, 0, bufLen);
			b = 0;
			i++;
		}
		//Case 2: Reached end of src->strLen
		else if (i == src->strLen)
		{	
			tempBuffer[b] = src->buf[i];
			addLitToBack(strList, tempBuffer);
			b = 0;
			i++;
		}
		//Case 3: Have not reached end of src or bufLen
		else 
		{
			tempBuffer[b] = src->buf[i];
			i++;
			b++;
		}
	}
	free(tempBuffer);
}
*/
/** 
* Function: void charSplit(SLIST *strList, struct String *src, char c)
*
* Purpose: This function iterates through String src, and populates a strList
* with substrings of src. This function essentially attempts to provide the
* same functionality of Python's split method.
*
* Note: Need to check strList->length to see src has been split (in the event 
* src does not contain char 'c', One node will be added to strList, which 
* contains a copy of String src.
**/

void charSplit(SLIST *strList, struct String *src, char c)
{
	int i = 0;
	struct String *tempStr = createStr();
	while (i <= src->strLen)
	{
		if ((src->buf[i]) == c && (tempStr->strLen != 0)) {
			//add tempStr contents to strList, clear tempStr
			//printf("tempStr contents: %s\n", tempStr->buf);
			addLit(strList, tempStr->buf);
			clearBufStr(tempStr);
			i++;
		}
		else if ((src->buf[i]) == c && (tempStr->strLen == 0)) {
			i++;
		}
		else {
			appendChar(tempStr, src->buf[i]);
			i++;
		}
	}
	if (tempStr->strLen != 0)
	{
		addLit(strList, tempStr->buf);
	}
	destroyStr(tempStr);
}

/**
* function splitByChar(SLIST *strList, struct String *src, char c, int start)
* 
* Purpose: Helper function to split a string into a list of strings 
* based on a char. Note: strings are added in alphabetical order to strList.
**/
int splitByChar(SLIST *strList, struct String *src, char c, int start)
{
	int i = start;
	int retval = -1;
	struct String *newStr;
	newStr = createStr(); //Allocate and initialize newStr
	
	//Iterate through src->buf
	while (i < src->strLen)
	{
		if (src->buf[i] == c) 
		{
			//appendChar(newStr, 0);
			retval = i + 1;
			break;
		}
		else
		{
			appendChar(newStr, src->buf[i]);
			i++;
		}
	}

	//Empty String
	if ((newStr->buf[0] == '\0'))
		destroyStr(newStr);
	else if(start == i)
		destroyStr(newStr);
	//non-empty string, add to list
	else
		addStr(strList, newStr);
	
	return retval;
}

/**
* function: clearStrList
*
**/
/* void cleanStrList(SLIST *strList)
{
	
} */