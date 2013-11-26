#include "stack.h"
#include "queue.h"

using namespace std;

class RatInMaze {
	protected:
	char** maze;
	int mX;
	int mY;
	stack* xStack;
	stack* yStack;
	queue* xQueue;
	queue* yQueue;
	
	public:
	RatInMaze();
	void load(char m[][15], int maxX, int maxY);
	void print(bool print);
	bool isValid(int curX, int curY, int goalX, int goalY);
	bool searchStack(int fromX,int fromY,int toX,int toY);
	bool searchQueue(int fromX,int fromY,int toX,int toY);
	bool searchStackSmart(int fromX,int fromY,int toX,int toY);
};
