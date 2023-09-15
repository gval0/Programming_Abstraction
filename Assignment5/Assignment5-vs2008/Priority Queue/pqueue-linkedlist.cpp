/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include <iostream>
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	head = NULL;
	length = 0;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	while(head != NULL){
		List* cur = head->next;
		delete head;
		head = cur;
	}
}

int LinkedListPriorityQueue::size() {
	return length;
}

bool LinkedListPriorityQueue::isEmpty() {
	return (size() <= 0);
}

void LinkedListPriorityQueue::enqueue(string value) {
	List* list = new List;
	list->val = value;
	List* cur = head;
	List* priv;
	if(cur == NULL || cur->val > value){
		list->next = cur;
		head = list;
	} else {
		priv = cur;
		cur = cur->next;
		bool added = false;
		while(cur != NULL){
			if(cur->val > value){
				priv->next = list;
				list->next = cur;
				added = true;
				break;
			}
			priv = cur;
			cur = cur->next;
		}
		if(!added) {
			priv->next = list;
			list->next = cur;
		}
	}
	length++;
}

string LinkedListPriorityQueue::peek() {
	if(isEmpty()) error("No element in queue");
	return head->val;
}

string LinkedListPriorityQueue::dequeueMin() {
	string res = peek();
	List* cur = head->next;
	delete head;
	head = cur;
	length--;
	return res;
}

