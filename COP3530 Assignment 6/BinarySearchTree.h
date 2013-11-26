/*

	Bernard Marger
	COP3530 Assignment 6
	UFID: 2533-2839
	Section 1085

*/

#ifndef BTREE
#define BTREE
#include "BinaryTree.h"
#endif

using namespace std;

class BinarySearchTree {
	public:
	BinarySearchTree(int cap);
	~BinarySearchTree();
	void insert(int n, int objectNum);
	void addBin(BinaryTreeNode* node);
	void find(BinaryTreeNode* node, int objectSize);
	void remove();
	BinaryTreeNode* findBiggestLeft(BinaryTreeNode* node, int max, BinaryTreeNode* returnNode);
	void addNode(BinaryTreeNode* node);
};
