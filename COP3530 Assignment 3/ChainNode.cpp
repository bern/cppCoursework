/*

	Bernard Marger
	COP3530 Assignment 3
	UFID: 2533-2839
	Section 1085

*/

#include "ChainNode.h"
#include "Myexception.h"

using namespace std;
	
	// constructors
	ChainNode::ChainNode() {}
	
	ChainNode::ChainNode(const int& element) {
		this -> element = element;
	}
	
	ChainNode::ChainNode(const int& element, ChainNode* next) {
		this -> element = element;
		this -> next = next;
	}
