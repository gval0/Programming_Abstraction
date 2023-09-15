/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	length = 0;
	head = tail = NULL;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	while (head != NULL){
		List* cur = head->next;
		delete head;
		head = cur;
	}
}

int DoublyLinkedListPriorityQueue::size() {
	return length;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	return (size() == 0);
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	List* list = new List;
	list->val = value;
	if(head == NULL){
		list->next = tail;
		list->priv = head;
		head = list;
	} else {
		list->next = head;
		head->priv = list;
		list->priv = NULL;
		head = list;
	}
	length++;
}

string DoublyLinkedListPriorityQueue::peek() {
	if(isEmpty()) error("no elements to remove");
	List* cur = head;
	List* min = head;
	while(cur != NULL){
		if(cur->val < min->val){
			min = cur;
		}
		cur = cur->next;
	}
	return min->val;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	string res = peek();
	List* cur = head;
	while(cur != NULL){
		if(cur->val == res)break;
		cur = cur->next;
	}
	List* priv = cur->priv;
	List* next = cur->next;
	if(priv == NULL){
		if(next != NULL){
			cur->next->priv = NULL;
			head = cur->next;
		}else {
			head = NULL;
		}
	} else {
		priv->next = next;
		if(next != NULL)next->priv = priv;
	}
	length --;
	return res;
}

