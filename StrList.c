#include <stdio.h>
#include <stdlib.h>
#include "StrList.h"

// Node & List Data Structures:
typedef struct _node {
    char* _myStr;
    struct _node* _next;
} Node;

typedef struct _StrList {
    Node* _head;
    size_t _size;
} StrList;

// Node implementation:
/**
 * This function allocates memory to a Node and initiating the node's values.
*/
Node* Node_alloc(char* myStr, Node* next) {
	Node* p = (Node*)malloc(sizeof(Node));  // Actually allocating memory for 2 pointers (pointer of char and pointer to Node).
	p->_myStr = myStr;
	p->_next = next;
	return p;
}
/**
 * This function frees the allocated memory of a Node.
*/
void Node_free(Node* node) {
	free(node);
}
