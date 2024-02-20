#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StrList.h"

// Node & List Data Structures:
typedef struct _node {
    char* _str;
    struct _node* _next;
} Node;

struct _StrList {
    Node* _head;
    size_t _size;
};

// Node implementation:
/**
 * This function allocates memory to a Node and initiating the node's values.
*/
Node* Node_alloc(const char* str, Node* next) {
	Node* p = (Node*)malloc(sizeof(Node));  // Actually allocating memory for 2 pointers (pointer of char and pointer to Node).
	p->_str = (char*)str;
	p->_next = next;
	return p;
}
/**
 * This function frees the allocated memory of a Node (including its string);
*/
void Node_free(Node* node) {
	if(node->_str != NULL){
		free(node->_str);
	}
	free(node);
}

// StrList implementation:

StrList* StrList_alloc(){
	StrList* p = (StrList*)malloc(sizeof(StrList));
	p->_head = NULL;
	p->_size = 0;
	return p;
}

void StrList_free(StrList* Strlist){
	if(Strlist == NULL){
		return;
	}
	if(Strlist->_head == NULL){
		free(Strlist);
		return;
	}
	Node* current = Strlist->_head;
	for(int i=1; i<Strlist->_size; i++){
		Node* tmp = current;
		current = current->_next;
		Node_free(tmp);
	}
	Node_free(current);
	free(Strlist);
}

size_t StrList_size(const StrList* StrList){
	size_t s = StrList->_size;
	return s;
}

void StrList_insertLast(StrList* StrList, const char* data){
	Node* new_node = Node_alloc(data, NULL);
	if(StrList->_size == 0){  // Handling case of the first str in the list:
		StrList->_head = new_node;
		StrList->_size++;
		return;
	}
	Node* current = StrList->_head;
	for(int i=1; i<StrList->_size; i++){
		current = current->_next;
	}
	current->_next = new_node;
	StrList->_size++;
}

void StrList_insertAt(StrList* StrList, const char* data,int index){
	if((size_t)index > (StrList->_size)-1 || index < 0){
		return;
	}
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
	if(current == NULL || current->_str == NULL){  // Means there is no head to the list or in the head there is no string
		return;
	}
	for(size_t i=0; i<StrList->_size; i++){
		if(current->_str != NULL){
			printf("%s\n", current->_str);
		}
		current = current->_next;
	}
}

void StrList_printAt(const StrList* Strlist, int index){
	if((size_t)index > (Strlist->_size)-1 || index < 0){
		return;
	}
	Node* current = Strlist->_head;
	if (current == NULL || current->_str ==NULL){
		return;
	}
	for(int i=0; i<index; i++){
		current = current->_next;
	}
	printf("%s\n", current->_str);
}

int StrList_printLen(const StrList* Strlist){
	int amount = 0;
	Node* current = Strlist->_head;
	if(current == NULL || current->_str == NULL){
		return 0;
	}
	for(size_t i=0; i<Strlist->_size; i++){
		if(current->_str != NULL){
			amount += strlen(current->_str);
		}
		current = current->_next;
	}
	return amount;
}

int StrList_count(StrList* StrList, const char* data){
	int counter = 0;
	Node* current = StrList->_head;
	if(current == NULL){  // Cheking if there is nodes in the list:
		return 0;
	}
	for(size_t i=0; i<StrList->_size; i++){
		if(strcmp(current->_str, data) == 0){
			counter++;
		}
		current = current->_next;
	}
	return counter;
}
/**
 * This functions removes a Node from the list, given the previous node and the index to remove.
 * Note: the function handles the allocations and the StrList new size.
 * In case the index is 0 , then previous_node will be the head.
*/
void StrList_remove_node(StrList* Strlist, Node* previous_node, size_t current_index){  
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
		Node_free(tmp);
		Strlist->_size--;
		return;
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
	Strlist->_size--;
}

void StrList_remove(StrList* Strlist, const char* data){
	Node* previous = Strlist->_head;
	if(previous == NULL){
		return;
	}
	if(strcmp(previous->_str, data) == 0){
		StrList_remove_node(Strlist, previous, 0);
	}
	for(size_t i=1; i<(Strlist->_size)-1; i++){
		if(strcmp(previous->_next->_str, data) == 0){
			StrList_remove_node(Strlist, previous, i);
			i--;
		}
		else{
			previous = previous->_next;
		}
	}
}

void StrList_removeAt(StrList* Strlist, int index){
	if((size_t)index > (Strlist->_size)-1 || index < 0){
		return;
	}
	Node* previous = Strlist->_head;
	if(previous == NULL){
		return;
	}
	for(int i=0; i<index-1; i++){
		previous = previous->_next;
	}
	StrList_remove_node(Strlist, previous, (size_t)index);
}

int StrList_isEqual(const StrList* StrList1, const StrList* StrList2){
	if(StrList1 == NULL || StrList2 == NULL){
		return 0;
	}
	if(StrList1->_size != StrList2->_size){
		return 0;
	}
	Node* current1 = StrList1->_head;
	Node* current2 = StrList2->_head;
	for(int i=0; i<StrList1->_size; i++){
		if(strcmp(current1->_str, current2->_str) != 0){
			return 0;
		}
		current1 = current1->_next;
		current2 = current2->_next;
	}
	return 1;
}

char* deep_copy_string(const char* original){
	if( original == NULL){
		return NULL;
	}
	char* copy = (char*)malloc(sizeof(char)*(strlen(original)+1));
	strcpy(copy, original);
	return copy;
}

StrList* StrList_clone(const StrList* Strlist){
	if(Strlist == NULL){
		return NULL;
	}

	char* tmp_str = deep_copy_string(Strlist->_head->_str); // Copying the string of the head of the StrList.

	Node* tmp_node = Node_alloc(tmp_str,NULL); // Creating the head node for the new list.
	StrList* new_list = StrList_alloc(tmp_node); // Creating the pointer to the new list.
	new_list->_size = Strlist->_size;

	Node* current = Strlist->_head;

	for(int i=1; i<Strlist->_size; i++){
		current = current->_next;
		tmp_str = deep_copy_string(current->_str);
		tmp_node->_next = (Node*)Node_alloc(tmp_str, NULL);
	}

	return new_list;
}

void StrList_reverse(StrList* Strlist){
	// Handling StrList of size = 1 or 0:
	if(Strlist->_size == 0 || Strlist->_size == 1){
		return;
	}
	Node* previous = Strlist->_head;
	Node* current = previous->_next;
	Node* next = current->_next;
	previous->_next = NULL;
	while(next != NULL){
		current->_next = previous;
		previous = current;
		current = next;
		next = next->_next;
	}
	current->_next = previous;
	Strlist->_head = current;
}
/**
 * This function swaps between two strings in two nodes.
 * Note: it does'nt swaps the node themselfs.
*/
void StrList_swap(StrList* Strlist, Node* node1, Node* node2){
	if(Strlist->_size == 0 || Strlist->_size ==1){
		return;
	}
	char* tmp = node1->_str;
	node1->_str = node2->_str;
	node2->_str = tmp;
}

void StrList_sort( StrList* Strlist){
	if(Strlist->_size == 0 || Strlist->_size == 1){
		return;
	}

	Node* current = Strlist->_head;
	for(int i=0; i<Strlist->_size; i++){  
		// Finding the minimum from the i'th index to the last:
		Node* min = current;
		Node* tmp = current;
		for(int j=i+1; j<Strlist->_size; j++){
			tmp = tmp->_next;
			if(strcmp(min->_str, tmp->_str) > 0){
				min = tmp;
			}
		}
		StrList_swap(Strlist, min, current);
		current = current->_next;
	}
}

int StrList_isSorted(StrList* Strlist){
	if(Strlist->_size == 0 || Strlist->_size == 1){
		return 1;
	}
	Node* current = Strlist->_head;
	for(int i=0; i<(Strlist->_size)-1; i++){
		Node* next = current->_next;
		if(strcmp(current->_str, next->_str) > 0){
			return 0;
		}
	}
	return 1;
}

