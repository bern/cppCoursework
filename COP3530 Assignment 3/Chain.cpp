/*

	Bernard Marger
	COP3530 Assignment 3
	UFID: 2533-2839
	Section 1085

*/

#include <iostream>
#include <sstream>
#include "Myexception.h"
//#include "ChainNode.h"
#include "Chain.h"

using namespace std;

		ChainNode* firstNode;
		int listSize;	
		
		chain::chain(int initialCapacity) {
			initialCapacity = 10;
			if(initialCapacity < 1)
			{
				ostringstream s;
				s << "Initial capacity = " << initialCapacity << " Must be > 0 ";
				throw illegalParameterValue(s.str());
			}
			firstNode = NULL;
			listSize = 0;
		}
		
		chain::~chain() {
			while(firstNode != NULL) {
				ChainNode* nextNode = firstNode -> next;
				delete firstNode;
				firstNode = nextNode;
			}
		}
		
		int* chain::get(int theIndex) const{
			try{checkIndex(theIndex);}catch(illegalIndex &e){e.outputMessage(); return NULL;}
			ChainNode* currentNode = firstNode;
			for(int i = 0; i < theIndex; i++)
				currentNode = currentNode -> next;
			return &(currentNode -> element);
		}
		
		int chain::indexOf(const int& theElement) const {
			ChainNode* currentNode = firstNode;
			int index = 0;
			while(currentNode!= NULL && currentNode -> element != theElement) {
				currentNode = currentNode -> next;
				index++;
			}
			if(currentNode == NULL)
				return -1;
			else
				return index;
		}
		
		void chain::erase(int theIndex) {
			checkIndex(theIndex);
			ChainNode* deleteNode;
			if(theIndex == 0) {
				deleteNode = firstNode;
				firstNode = firstNode -> next;
			}
			else {
				ChainNode* p = firstNode;
				for(int i = 0; i < theIndex - 1; i++) {
					p = p -> next;
				}
				deleteNode = p -> next;
				p -> next = p -> next -> next;
			}
			listSize--;
			delete deleteNode;
		}
		
		void chain::insert(int theIndex, const int& theElement) {
			try {
				if(theIndex < 0 || theIndex > listSize) {
					ostringstream s;
					s << "index = " << theIndex << " size = " << listSize << ", the input index is invalid";
					throw illegalIndex(s.str());
				}
			} catch (illegalIndex &e) {e.outputMessage(); return;} 
			
			if(theIndex == 0) {
				//insert at front
				firstNode = new ChainNode(theElement, firstNode);
			}
			else
			{
				ChainNode* p = firstNode;
				for(int i = 0; i < theIndex - 1; i++)
					p = p -> next;
					
				p -> next = new ChainNode (theElement, p -> next);
			}
			listSize++;
		} 
		
		void chain::checkIndex(int theIndex) const {
			if(theIndex < 0 || theIndex >= listSize) {
				ostringstream s;
				s << "index = " << theIndex << " size = " << listSize << ", the input index is invalid";
				throw illegalIndex(s.str());
			}
		}
		
		void chain::traverse() {
			if(listSize == 0) {
				cout << "List is empty." << endl;
				return;
			}
			ChainNode* currentNode = firstNode;
			for(int i = 0; i < listSize; i++) {
				cout << (currentNode -> element) << " ";
				currentNode = currentNode -> next;
			}
			cout << endl;
		}
		
		void chain::MaxMin() {
			int max = firstNode -> element;
			int min = firstNode -> element;
			
			ChainNode* currentNode = firstNode;
			for(int i = 0; i < listSize; i++) {
				if((currentNode -> element) < min) {
					min = (currentNode -> element);
				}
				if((currentNode -> element) > max) {
					max = (currentNode -> element);
				}
				currentNode = currentNode -> next;
			}
			cout << "Maximum element is: " << max << " Minimum element is: " << min << endl;
		}

