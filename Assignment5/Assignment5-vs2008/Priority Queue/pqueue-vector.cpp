/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
	length = 0;
	vec.clear();
}

VectorPriorityQueue::~VectorPriorityQueue() {
	vec.clear();
}

int VectorPriorityQueue::size() {
	return length;
}

bool VectorPriorityQueue::isEmpty() {
	return (size() == 0);
}

void VectorPriorityQueue::enqueue(string value) {
	bool addedLast = true;
		for(int i = 0; i < size(); i++){
			if(vec[i] > value){
				vec.insert(i, value);
				addedLast = false;
				break;
			}
		}
	if(addedLast) vec.add(value);
	length ++;
}

string VectorPriorityQueue::peek() {
	if(isEmpty()) error("No element in queue.");
	return vec[0];
}

string VectorPriorityQueue::dequeueMin() {
		string result = peek();
		vec.remove(0);
		length --;
		return result;
	}

