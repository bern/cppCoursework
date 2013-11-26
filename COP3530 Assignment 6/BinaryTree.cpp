/*

	Bernard Marger
	COP3530 Assignment 6
	UFID: 2533-2839
	Section 1085

*/

#include <iostream>
#include <sstream>
#include "BinaryTree.h"

using namespace std;

BinaryTreeNode* root;
int binCap;
int curKey;

BinaryTree::BinaryTree(int b) {
	binCap = b;
	curKey = 1;
	root = new BinaryTreeNode(curKey, binCap);
	curKey++;
}

BinaryTree::~BinaryTree() {
}
