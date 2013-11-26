/*

	Bernard Marger
	COP3530 Assignment 3
	UFID: 2533-2839
	Section 1085

*/

using namespace std;

struct ChainNode {
	public:
		ChainNode();
		ChainNode(const int& element);
		ChainNode(const int& element, ChainNode* next);			
		int element;
		ChainNode* next;
};
