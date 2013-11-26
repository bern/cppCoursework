/*

	Bernard Marger
	COP3530 Assignment 6
	UFID: 2533-2839
	Section 1085

*/

#include <iostream>
#include "BinarySearchTree.h"
#ifndef BTREE
#define BTREE
#include "BinaryTree.h"
#endif

using namespace std;

BinaryTree* bTree;
BinaryTreeNode* lastBestFit;
bool doneAdding = false;
int bCapacity;

BinarySearchTree::BinarySearchTree(int cap) {
	bCapacity = cap;
	bTree = new BinaryTree(bCapacity);
}

BinarySearchTree::~BinarySearchTree() {
}

void BinarySearchTree::find(BinaryTreeNode* node, int objectSize) {
	if(node->value >= objectSize && ((lastBestFit == NULL)||(node->value < lastBestFit -> value))) {
		lastBestFit = node;
	}
	if(node->value <= objectSize && node->right!=NULL) {
		find(node->right, objectSize);
	}
	if(node->value > objectSize && node->left!=NULL) {
		find(node->left, objectSize);
	}
}

void BinarySearchTree::insert(int n, int objectNum) {
	lastBestFit = NULL;
	find(bTree->root, n);
	if(lastBestFit != NULL) {
		cout << "Pack object " << objectNum << " in bin " << lastBestFit->key << endl;
		lastBestFit->addItem(n);
		if(bTree->root!=lastBestFit)
			remove();
		if(bTree->root!=lastBestFit) {
			doneAdding = false;
			addNode(bTree->root);
		}
		if(lastBestFit->parent==NULL) {
			bTree->setRoot(lastBestFit);
		}
	}
	else {
		addBin(bTree->root);
		insert(n, objectNum);
	}
}

void BinarySearchTree::addBin(BinaryTreeNode* node) {
	while(node->right!=NULL) {
		node = node->right;
	}
	node->setRight(new BinaryTreeNode(bTree->curKey, bCapacity));
	node->right->setParent(node);
	bTree->nextKey();
}

void BinarySearchTree::addNode(BinaryTreeNode* node) {
	if(lastBestFit->value < node->value && node->left==NULL && !doneAdding) {
		node->setLeft(lastBestFit);
		lastBestFit->setParent(node);
		doneAdding = true;
	}
	if(lastBestFit->value >= node->value && node->right==NULL && !doneAdding) {
		node->setRight(lastBestFit);
		lastBestFit->setParent(node);
		doneAdding = true;
	}
	if(lastBestFit->value >= node->value && node->right!=NULL && !doneAdding) {
		addNode(node->right);
	}
	if(lastBestFit->value < node->value && node->left!=NULL && !doneAdding) {
		addNode(node->left);
	}
}

void BinarySearchTree::remove() {
	if(lastBestFit->left==NULL && lastBestFit->right==NULL) {
		if(lastBestFit->parent->left==lastBestFit) {
			lastBestFit->parent->setLeft(NULL);
			lastBestFit->setParent(NULL);
		}
		else if(lastBestFit->parent->right==lastBestFit) {
			lastBestFit->parent->setRight(NULL);
			lastBestFit->setParent(NULL);
		}
	}
	if((lastBestFit->left==NULL&&lastBestFit->right!=NULL)) {
		if(lastBestFit->parent->left==lastBestFit) {
			lastBestFit->parent->setLeft(lastBestFit->right);
			lastBestFit->right->setParent(lastBestFit->parent);
			lastBestFit->setParent(NULL);
			lastBestFit->setRight(NULL);
		}
		else if(lastBestFit->parent->right==lastBestFit) {
			lastBestFit->parent->setRight(lastBestFit->right);
			lastBestFit->right->setParent(lastBestFit->parent);
			lastBestFit->setParent(NULL);
			lastBestFit->setRight(NULL);
		}
	}
	if((lastBestFit->left!=NULL&&lastBestFit->right==NULL)) {
		if(lastBestFit->parent->left==lastBestFit) {
			lastBestFit->parent->setLeft(lastBestFit->left);
			lastBestFit->left->setParent(lastBestFit->parent);
			lastBestFit->setParent(NULL);
			lastBestFit->setLeft(NULL);
		}
		else if(lastBestFit->parent->right==lastBestFit) {
			lastBestFit->parent->setRight(lastBestFit->left);
			lastBestFit->left->setParent(lastBestFit->parent);
			lastBestFit->setParent(NULL);
			lastBestFit->setLeft(NULL);
		}
	}
	if(lastBestFit->left!=NULL&&lastBestFit->right!=NULL) {
		BinaryTreeNode* bigLeft = findBiggestLeft(lastBestFit, 0, NULL);
		if(bigLeft->parent->left==bigLeft) {
			bigLeft->parent->setLeft(NULL);
			bigLeft->setParent(lastBestFit->parent);
			bigLeft->setLeft(lastBestFit->left);
			bigLeft->left->setParent(bigLeft);
			bigLeft->setRight(lastBestFit->right);
			bigLeft->right->setParent(bigLeft);
			lastBestFit->setParent(NULL);
			lastBestFit->setRight(NULL);
			lastBestFit->setLeft(NULL); 
		}
		if(bigLeft->parent->right==bigLeft) {
			bigLeft->parent->setRight(NULL);
			bigLeft->setParent(lastBestFit->parent);
			bigLeft->setLeft(lastBestFit->left);
			bigLeft->left->setParent(bigLeft);
			bigLeft->setRight(lastBestFit->right);
			bigLeft->right->setParent(bigLeft);
			lastBestFit->setParent(NULL);
			lastBestFit->setRight(NULL);
			lastBestFit->setLeft(NULL); 
		}
	}
}

BinaryTreeNode* BinarySearchTree::findBiggestLeft(BinaryTreeNode* node, int max, BinaryTreeNode* returnNode) {
	if(returnNode==NULL||node->value > max) {
		returnNode = node;
		max = node->value;
	}
	if(node->left!=NULL) {
		findBiggestLeft(node->left, max, returnNode);
	}
	if(node->right!=NULL) {
		findBiggestLeft(node->right, max, returnNode);
	}
	return returnNode;
}
