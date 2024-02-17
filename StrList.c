#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StrList.h"

// Node & List Data Structures:
typedef struct _node {
    char* _str;
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
Node* Node_alloc(char* str, Node* next) {
	Node* p = (Node*)malloc(sizeof(Node));  // Actually allocating memory for 2 pointers (pointer of char and pointer to Node).
	p->_str = str;
	p->_next = next;
	return p;
}
/**
 * This function frees the allocated memory of a Node.
*/
void Node_free(Node* node) {
	free(node);
}

// StrList implementation:

StrList* StrList_alloc(Node* head){
	StrList* p = (StrList*)malloc(sizeof(StrList));
	p->_head = head;
	p->_size = 1;
	return p;
}

void StrList_free(StrList* StrList){
	free(StrList);
}

size_t StrList_size(const StrList* StrList){
	size_t s = StrList->_size;
	return s;
}

void StrList_insertLast(StrList* StrList, const char* data){
	Node* new_node = Node_alloc(data, NULL);
	Node* current = StrList->_head;
	for(int i=1; i<StrList->_size; i++){
		current = current->_next;
	}
	current->_next = new_node;
	StrList->_size++;
}

void StrList_insertAt(StrList* StrList, const char* data,int index){
	Node* new_node = Node_alloc(data, NULL);
	// Inserting the new Node instead the current head:
	if(index == 0){ 
		new_node->_next = StrList->_head;
		StrList->_head = new_node;
		StrList->_size++;
		return;
	}
	Node* current = StrList->_head;
	for(int i=0; i<index-1; i++){
		current = current->_next;
	}
	// Now the current is the Node that should be before the new Node.
	new_node->_next = current->_next;
	current->_next = new_node;
	StrList->_size++;
}

char* StrList_firstData(const StrList* StrList){
	return StrList->_head->_str;
}

void StrList_print(const StrList* StrList){
	Node* current = StrList->_head;
	printf("%s\n", current->_str);
	for(int i=0; i<(StrList->_size)-1; i++){
		current = current->_next;
		printf("%s\n", current->_str);
	}
}

void StrList_printAt(const StrList* Strlist, int index){
	Node* current = Strlist->_head;
	for(int i=0; i<index; i++){
		current = current->_next;
	}
	printf("%s\n", current->_str);
}

int StrList_printLen(const StrList* Strlist){
	int amount = 0;
	Node* current = Strlist->_head;
	amount += strlen(current->_str);
	for(int i=0; i<(Strlist->_size)-1; i++){
		current = current->_next;
		amount += strlen(current->_str);
	}
	return amount;
}

int StrList_count(StrList* StrList, const char* data){
	int counter = 0;
	Node* current = StrList->_head;
	if(strcmp(current->_str, data) == 0){
		counter++;
	}
	for(int i=0; i<(StrList->_size)-1; i++){
		current = current->_next;
		if(strcmp(current->_str, data) == 0){
		counter++;
		}
	}
	return counter;
}
/**
 * In case the index is 0 , then previous_node will be the head.
*/
void StrList_remove_node(StrList* Strlist, Node* previous_node, int current_index){
	Node* tmp;
	// Handling removing the head:
	if(current_index == 0){
		tmp = Strlist->_head;
		if(Strlist->_size > 1){
			Strlist->_head = Strlist->_head->_next;
		}
		else{
			Strlist->_head = NULL;
		}
	}
	//Handling removing other node:
	tmp = previous_node->_next;
	if(current_index == Strlist->_size-1){  // Means trying to remove the last
		previous_node->_next = NULL;
	}
	else{
		previous_node->_next = previous_node->_next->_next;
	}
	Node_free(tmp);
}

void StrList_remove(StrList* Strlist, const char* data){
	Node* previous = Strlist->_head;
	if(strcmp(previous->_str, data) == 0){
		StrList_remove_node(Strlist, previous, 0);
	}
	for(int i=0; i<(Strlist->_size)-1; i++){
		if(strcmp(previous->_next->_str, data) == 0){
			StrList_remove_node(Strlist, i);
		}
		if(i < (Strlist->_size)-1){
			current = current->_next;
		}
	}
}

void StrList_removeAt(StrList* Strlist, int index){
	Node* current = Strlist->_head;
	if(index == 0){
		Strlist->_head = Strlist->_head->_next;
		return;
	}
	for(int i=0; i<index; i++){

	}
}