/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include <iostream>
#include "error.h"


HeapPriorityQueue::HeapPriorityQueue() {
	list = new string[32];
	list[0] = "filler";
	arrLength = 32;
	logicalLength = 0;
}

HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] list;
}

int HeapPriorityQueue::size() {
	return logicalLength;
}

bool HeapPriorityQueue::isEmpty() {
	return (size() == 0);
}

void HeapPriorityQueue::enqueue(string value) {
	if(logicalLength + 1 >= arrLength) grow();
	logicalLength ++;
	list[logicalLength] = value;	
	bubbleUp();
}

string HeapPriorityQueue::peek() {
	if(isEmpty()) error("no elements.");
	return list[1];
}

string HeapPriorityQueue::dequeueMin() {
	string res = peek();
	swap(list[1], list[logicalLength]);
	logicalLength--;
	bubbleDown();
	return res;
}

void HeapPriorityQueue::grow(){
	string* cur = new string[2*arrLength];
	arrLength *= 2;
	for(int i = 1; i <= size(); i++){
		cur[i] = list[i];
	}
	delete[] list;
	list = cur;
}

void HeapPriorityQueue::bubbleUp(){
	int curIndex = logicalLength;
	int temp;
	while(true){
		temp = curIndex/2;
		if(temp <= 0) break;
		if(list[temp] < list[curIndex]) break;
		swap(list[temp], list[curIndex]);
		curIndex = temp;
	}
}

void HeapPriorityQueue::bubbleDown(){
	int curIndex = 1;
	int temp1, temp2;
	while(true){
		temp1 = curIndex * 2;
		temp2 = curIndex * 2 + 1;
		if(temp1 > logicalLength && temp2 > logicalLength) break;
		else if(temp1 <= logicalLength && temp2 > logicalLength){
			// do nth
		} else if(temp1 > logicalLength && temp2 <= logicalLength){
			temp1 = temp2;
		} else if(list[temp2] < list[temp1]){
			temp1 = temp2;
		}
		if(list[temp1] > list[curIndex]) break;
		swap(list[temp1], list[curIndex]);
		curIndex = temp1;
	}
}
