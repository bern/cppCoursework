#include <iostream>
#include <sstream>
#include "Myexception.h"
#include "RatInMaze.h"

using namespace std;

char** maze;
int** numMaze;
int mX;
int mY;
stack* xStack;
stack* yStack;
queue* xQueue;
queue* yQueue;
queue* valQueue;

RatInMaze::RatInMaze() {
	mX = 0;
	mY = 0;
	xStack = new stack(100);
	yStack = new stack(100);
	xQueue = new queue(500);
	yQueue = new queue(500);
}

void RatInMaze::load(char m[][15], int maxX, int maxY) {
	mX = maxX;
	mY = maxY;
	
	maze = new char* [maxY];
	
	for(int i = 0; i < maxX; i++) {
		maze[i] = new char[maxY];
		for(int j = 0; j < maxY; j++) {
			maze[i][j] = m[i][j];
		}
	}
	
	numMaze = new int* [maxY];
	
	for(int i = 0; i < maxX; i++) {
		numMaze[i] = new int[maxY];
		for(int j = 0; j < maxY; j++) {
			numMaze[i][j] = -1;
		}
	}
}

bool RatInMaze::isValid(int curX, int curY, int goalX, int goalY) {
	if(curX >= mX || curY >= mY || curX < 0 || curY < 0) {
		cout << "Starting point is not inside the maze!" << endl;
		return false;
	}
	if(goalX >= mX || goalY >= mY|| curX < 0 || curY < 0) {
		cout << "Ending point is not inside the maze!" << endl;
		return false;
	}
	if(maze[curX][curY] == '1') {
		cout << "Starting point is not a valid space!" << endl;
		return false;
	}
	if(maze[goalX][goalY] == '1') {
		cout << "Ending point is not a valid space!" << endl;
		return false;
	}
	return true;
}

bool RatInMaze::searchStack(int fromX,int fromY,int toX,int toY) {
	xStack -> emptyStack();
	yStack -> emptyStack();
	
	int goalX = toY; int goalY = toX;
	int curX = fromY; int curY = fromX;

	if(!isValid(curX, curY, goalX, goalY))
		return false;
	
	xStack -> push(curX);
	yStack -> push(curY);
	
	maze[curX][curY] = '3';
	
	while(((xStack -> top()) != goalX) || ((yStack -> top()) != goalY))	{
		curX = xStack -> top();		
		curY = yStack -> top();
		if(curX < 0 || curX >= mX || curY < 0 || curY >= mY) {
			return false;
		}
		
		if((curY+1) < mY && maze[curX][curY+1] == '0') {
			maze[curX][curY+1] = '3';
			xStack -> push(curX);
			yStack -> push(curY+1);
		}
		else if((curX+1) < mX && maze[curX+1][curY] == '0') {
			maze[curX+1][curY] = '3';
			xStack -> push(curX+1);
			yStack -> push(curY);
		}
		else if((curY-1) >= 0 && maze[curX][curY-1] == '0') {
			maze[curX][curY-1] = '3';
			xStack -> push(curX);
			yStack -> push(curY-1);
		}
		else if((curX-1) >= 0 && maze[curX-1][curY] == '0') {
			maze[curX-1][curY] = '3';
			xStack -> push(curX-1);
			yStack -> push(curY);
		}
		else {
			xStack -> pop();
			yStack -> pop();
		}
		
		if(xStack -> empty()) {
			return false;
		}
	}
	return true;
}

bool RatInMaze::searchQueue(int fromX,int fromY,int toX,int toY){
	xQueue -> emptyQueue();
	yQueue -> emptyQueue();
	//valQueue -> emptyQueue();
	
	int goalX = toY; int goalY = toX;
	int curX = fromY; int curY = fromX;

	if(!isValid(curX, curY, goalX, goalY))
		return false;
	
	xQueue -> push(curX);
	yQueue -> push(curY);
	
	//right = maze[curX][curY+1]
	//down = maze[curX+1][curY]
	//left = maze[curX][curY-1]
	//up = maze[curX-1][curY]
	
	maze[curX][curY] = '5';
	numMaze[curX][curY] = 0;
	int curMin = 9999;
	
	while(((xQueue -> back()) != goalX) || ((yQueue -> back()) != goalY))	{
		
		curX = xQueue -> back();		
		curY = yQueue -> back();
		
		if(curX < 0 || curX >= mX || curY < 0 || curY >= mY) {
			return false;
		}
		
		if((curY+1) < mY && maze[curX][curY+1] == '0') {
			curMin = 9999;
			
			maze[curX][curY+1] = '5';
			//check all directions, mark as the smallest nonzero
			if(curX >= 0 && curY >= 0 && curX < mX && curY < mY && numMaze[curX][curY] < curMin && numMaze[curX][curY] > -1)
				curMin = numMaze[curX][curY];
			if(curX >= 0 && (curY+2) >= 0 && curX < mX && (curY+2) < mY && numMaze[curX][curY+2] < curMin && numMaze[curX][curY+2] > -1)
				curMin = numMaze[curX][curY+2];
			if(curX+1 >= 0 && curY+1 >= 0 && curX+1 < mX && curY+1 < mY && numMaze[curX+1][curY+1] < curMin && numMaze[curX+1][curY+1] > -1)
				curMin = numMaze[curX+1][curY+1];
			if(curX-1 >= 0 && curY+1 >= 0 && curX-1 < mX && curY+1 < mY && numMaze[curX-1][curY+1] < curMin && numMaze[curX-1][curY+1] > -1)
				curMin = numMaze[curX-1][curY+1];
				
			numMaze[curX][curY+1] = curMin+1;
			xQueue -> push(curX);
			yQueue -> push(curY+1);
		}
		if((curX+1) < mX && maze[curX+1][curY] == '0') {
			curMin = 9999;
			
			maze[curX+1][curY] = '5';
			
			if(curX >= 0 && curY >= 0 && curX < mX && curY < mY && numMaze[curX][curY] < curMin && numMaze[curX][curY] > -1) {
				curMin = numMaze[curX][curY];
				//cout << "up valid" << endl;
			}
			if(curX+2 >= 0 && curY >= 0 && curX+2 < mX && curY < mY && numMaze[curX+2][curY] < curMin && numMaze[curX+2][curY] > -1) {
				curMin = numMaze[curX+2][curY];
				//cout << "down valid" << endl;
			}
			if(curX+1 >= 0 && curY+1 >= 0 && curX+1 < mX && curY+1 < mY && numMaze[curX+1][curY+1] < curMin && numMaze[curX+1][curY+1] > -1) {
				curMin = numMaze[curX+1][curY+1];
				//cout << "right valid" << endl;
			}
			if(curX+1 >= 0 && curY-1 >= 0 && curX+1 < mX && curY-1 < mY && numMaze[curX+1][curY-1] < curMin && numMaze[curX+1][curY-1] > -1) {
				curMin = numMaze[curX+1][curY-1];
				//cout << "left valid" << endl;
			}
				
			numMaze[curX+1][curY] = curMin+1;
			xQueue -> push(curX+1);
			yQueue -> push(curY);
		}
		if((curY-1) >= 0 && maze[curX][curY-1] == '0') {
			curMin = 9999;
			
			maze[curX][curY-1] = '5';
			
			if(curX >= 0 && curY >= 0 && curX < mX && curY < mY && numMaze[curX][curY] < curMin && numMaze[curX][curY] > -1)
				curMin = numMaze[curX][curY];
			if(curX >= 0 && curY-2 >= 0 && curX < mX && curY-2 < mY && numMaze[curX][curY-2] < curMin && numMaze[curX][curY-2] > -1)
				curMin = numMaze[curX][curY-2];
			if(curX+1 >= 0 && curY-1 >= 0 && curX+1 < mX && curY-1 < mY && numMaze[curX+1][curY-1] < curMin && numMaze[curX+1][curY-1] > -1)
				curMin = numMaze[curX+1][curY-1];
			if(curX-1 >= 0 && curY-1 >= 0 && curX-1 < mX && curY-1 < mY && numMaze[curX-1][curY-1] < curMin && numMaze[curX-1][curY-1] > -1)
				curMin = numMaze[curX-1][curY-1];
				
			numMaze[curX][curY-1] = curMin+1;
			xQueue -> push(curX);
			yQueue -> push(curY-1);
		}
		if((curX-1) >= 0 && maze[curX-1][curY] == '0') {
			curMin = 9999;
			
			maze[curX-1][curY] = '5';
			
			if(curX >= 0 && curY >= 0 && curX < mX && curY < mY && numMaze[curX][curY] < curMin && numMaze[curX][curY] > -1)
				curMin = numMaze[curX][curY];
			if(curX-2 >= 0 && curY >= 0 && curX-2 < mX && curY < mY && numMaze[curX-2][curY] < curMin && numMaze[curX-2][curY] > -1)
				curMin = numMaze[curX-2][curY];
			if(curX-1 >= 0 && curY-1 >= 0 && curX-1 < mX && curY-1 < mY && numMaze[curX-1][curY-1] < curMin && numMaze[curX-1][curY-1] > -1)
				curMin = numMaze[curX-1][curY-1];
			if(curX-1 >= 0 && curY+1 >= 0 && curX-1 < mX && curY+1 < mY && numMaze[curX-1][curY+1] < curMin && numMaze[curX-1][curY+1] > -1)
				curMin = numMaze[curX-1][curY+1];
				
			numMaze[curX-1][curY] = curMin+1;
			xQueue -> push(curX-1);
			yQueue -> push(curY);
		}
		if (!((curX-1) >= 0 && maze[curX-1][curY] == '0') && !((curY-1) >= 0 && maze[curX][curY-1] == '0') && !((curX+1) < mX && maze[curX+1][curY] == '0') && !((curY+1) < mY && maze[curX][curY+1] == '0')) {
			xQueue -> pop();
			yQueue -> pop();
			
		}
		
		if(xQueue -> empty()) {
			return false;
		}
	}
	int goal = numMaze[goalX][goalY];
	xQueue -> emptyQueue();
	yQueue -> emptyQueue();
	
	curX = goalX;
	curY = goalY;
	
	xQueue -> push(curX);
	yQueue -> push(curY);
	
	while(goal > 0) {
		if(curX+1 < mX && numMaze[curX+1][curY] == (goal-1)) {
			curX++;
			//goal--;
		}
		else if(curY+1 < mY && numMaze[curX][curY+1] == (goal-1)) {
			curY++;
			//goal--;
		}
		else if(curX-1 >= 0 && numMaze[curX-1][curY] == (goal-1)) {
			curX--;
			//goal--;
		}
		else if(curY-1 >= 0 && numMaze[curX][curY-1] == (goal-1)) {
			curY--;
		}
		goal--;
		xQueue -> push(curX);
		yQueue -> push(curY);
	}
	
	return true;
}

bool RatInMaze::searchStackSmart(int fromX,int fromY,int toX,int toY){
	xStack -> emptyStack();
	yStack -> emptyStack();
	
	int goalX = toY; int goalY = toX;
	int curX = fromY; int curY = fromX;

	if(!isValid(curX, curY, goalX, goalY))
		return false;
	
	xStack -> push(curX);
	yStack -> push(curY);
	
	int dirPri = 0;
	//1 = right up
	//2 = left up
	//3 = left down
	//4 = right down
	//5 = right
	//6 = left
	//7 = down
	//8 = up
	
	
	maze[curX][curY] = '3';
	
	while(((xStack -> top()) != goalX) || ((yStack -> top()) != goalY))	{
		curX = xStack -> top();		
		curY = yStack -> top();
		
		if(curX > goalX && curY < goalY) {
			dirPri = 1;
		}
		else if(curX > goalX && curY > goalY) {
			dirPri = 2;
		}
		else if(curX < goalX && curY > goalY) {
			dirPri = 3;
		}
		else if(curX < goalX && curY < goalY) {
			dirPri = 4;
		}
		else if(curY < goalY) {
			dirPri = 5;
		}
		else if(curY > goalY) {
			dirPri = 6;
		}
		else if(curX < goalX) {
			dirPri = 7;
		}
		else dirPri = 8;
		
		if(curX < 0 || curX >= mX || curY < 0 || curY >= mY) {
			return false;
		}
		
		switch(dirPri) {
			case 1:
		//cout << "Going up and right" << endl;
		if((curY+1) < mY && maze[curX][curY+1] == '0') {
			//right
			maze[curX][curY+1] = '3';
			xStack -> push(curX);
			yStack -> push(curY+1);
		}
		else if((curX-1) >= 0 && maze[curX-1][curY] == '0') {
			//up
			maze[curX-1][curY] = '3';
			xStack -> push(curX-1);
			yStack -> push(curY);
		}
		else if((curX+1) < mX && maze[curX+1][curY] == '0') {
			//down
			maze[curX+1][curY] = '3';
			xStack -> push(curX+1);
			yStack -> push(curY);
		}
		else if((curY-1) >= 0 && maze[curX][curY-1] == '0') {
			//left
			maze[curX][curY-1] = '3';
			xStack -> push(curX);
			yStack -> push(curY-1);
		}
		else {
			xStack -> pop();
			yStack -> pop();
		}
				break;
			case 2:
		//cout << "Going up and left" << endl;
		if((curY-1) >= 0 && maze[curX][curY-1] == '0') {
			//left
			maze[curX][curY-1] = '3';
			xStack -> push(curX);
			yStack -> push(curY-1);
		}
		else if((curX-1) >= 0 && maze[curX-1][curY] == '0') {
			//up
			maze[curX-1][curY] = '3';
			xStack -> push(curX-1);
			yStack -> push(curY);
		}
		else if((curY+1) < mY && maze[curX][curY+1] == '0') {
			//right
			maze[curX][curY+1] = '3';
			xStack -> push(curX);
			yStack -> push(curY+1);
		}
		else if((curX+1) < mX && maze[curX+1][curY] == '0') {
			//down
			maze[curX+1][curY] = '3';
			xStack -> push(curX+1);
			yStack -> push(curY);
		}
		else {
			xStack -> pop();
			yStack -> pop();
		}
				break;
			case 3:
		//cout << "Going down and left" << endl;
		if((curY-1) >= 0 && maze[curX][curY-1] == '0') {
			//left
			maze[curX][curY-1] = '3';
			xStack -> push(curX);
			yStack -> push(curY-1);
		}
		else if((curX+1) < mX && maze[curX+1][curY] == '0') {
			//down
			maze[curX+1][curY] = '3';
			xStack -> push(curX+1);
			yStack -> push(curY);
		}
		else if((curY+1) < mY && maze[curX][curY+1] == '0') {
			//right
			maze[curX][curY+1] = '3';
			xStack -> push(curX);
			yStack -> push(curY+1);
		}
		else if((curX-1) >= 0 && maze[curX-1][curY] == '0') {
			//up
			maze[curX-1][curY] = '3';
			xStack -> push(curX-1);
			yStack -> push(curY);
		}
		else {
			xStack -> pop();
			yStack -> pop();
		}
				break;
			case 4:
		//cout << "Going down and right" << endl;
		if((curY+1) < mY && maze[curX][curY+1] == '0') {
			//right
			maze[curX][curY+1] = '3';
			xStack -> push(curX);
			yStack -> push(curY+1);
		}
		else if((curX+1) < mX && maze[curX+1][curY] == '0') {
			//down
			maze[curX+1][curY] = '3';
			xStack -> push(curX+1);
			yStack -> push(curY);
		}
		else if((curX-1) >= 0 && maze[curX-1][curY] == '0') {
			//up
			maze[curX-1][curY] = '3';
			xStack -> push(curX-1);
			yStack -> push(curY);
		}
		else if((curY-1) >= 0 && maze[curX][curY-1] == '0') {
			//left
			maze[curX][curY-1] = '3';
			xStack -> push(curX);
			yStack -> push(curY-1);
		}
		else {
			xStack -> pop();
			yStack -> pop();
		}
				break;
			case 5:
		//cout << "Going right" << endl;
		if((curY+1) < mY && maze[curX][curY+1] == '0') {
			//right
			maze[curX][curY+1] = '3';
			xStack -> push(curX);
			yStack -> push(curY+1);
		}
		else if((curX-1) >= 0 && maze[curX-1][curY] == '0') {
			//up
			maze[curX-1][curY] = '3';
			xStack -> push(curX-1);
			yStack -> push(curY);
		}
		else if((curX+1) < mX && maze[curX+1][curY] == '0') {
			//down
			maze[curX+1][curY] = '3';
			xStack -> push(curX+1);
			yStack -> push(curY);
		}
		else if((curY-1) >= 0 && maze[curX][curY-1] == '0') {
			//left
			maze[curX][curY-1] = '3';
			xStack -> push(curX);
			yStack -> push(curY-1);
		}
		else {
			xStack -> pop();
			yStack -> pop();
		}
				break;
			case 6:
		//cout << "Going left" << endl;
		if((curY-1) >= 0 && maze[curX][curY-1] == '0') {
			//left
			maze[curX][curY-1] = '3';
			xStack -> push(curX);
			yStack -> push(curY-1);
		}
		else if((curY+1) < mY && maze[curX][curY+1] == '0') {
			//right
			maze[curX][curY+1] = '3';
			xStack -> push(curX);
			yStack -> push(curY+1);
		}
		else if((curX+1) < mX && maze[curX+1][curY] == '0') {
			//down
			maze[curX+1][curY] = '3';
			xStack -> push(curX+1);
			yStack -> push(curY);
		}
		else if((curX-1) >= 0 && maze[curX-1][curY] == '0') {
			//up
			maze[curX-1][curY] = '3';
			xStack -> push(curX-1);
			yStack -> push(curY);
		}
		else {
			xStack -> pop();
			yStack -> pop();
		}
				break;
			case 7:
		//cout << "Going down" << endl;
		if((curX+1) < mX && maze[curX+1][curY] == '0') {
			//down
			maze[curX+1][curY] = '3';
			xStack -> push(curX+1);
			yStack -> push(curY);
		}
		else if((curY+1) < mY && maze[curX][curY+1] == '0') {
			//right
			maze[curX][curY+1] = '3';
			xStack -> push(curX);
			yStack -> push(curY+1);
		}
		else if((curY-1) >= 0 && maze[curX][curY-1] == '0') {
			//left
			maze[curX][curY-1] = '3';
			xStack -> push(curX);
			yStack -> push(curY-1);
		}
		else if((curX-1) >= 0 && maze[curX-1][curY] == '0') {
			//up
			maze[curX-1][curY] = '3';
			xStack -> push(curX-1);
			yStack -> push(curY);
		}
		else {
			xStack -> pop();
			yStack -> pop();
		}
				break;
			case 8:
		//cout << "Going up" << endl;
		if((curX-1) >= 0 && maze[curX-1][curY] == '0') {
			//up
			maze[curX-1][curY] = '3';
			xStack -> push(curX-1);
			yStack -> push(curY);
		}
		else if((curY+1) < mY && maze[curX][curY+1] == '0') {
			//right
			maze[curX][curY+1] = '3';
			xStack -> push(curX);
			yStack -> push(curY+1);
		}
		else if((curX+1) < mX && maze[curX+1][curY] == '0') {
			//down
			maze[curX+1][curY] = '3';
			xStack -> push(curX+1);
			yStack -> push(curY);
		}
		else if((curY-1) >= 0 && maze[curX][curY-1] == '0') {
			//left
			maze[curX][curY-1] = '3';
			xStack -> push(curX);
			yStack -> push(curY-1);
		}
		else {
			xStack -> pop();
			yStack -> pop();
		}
				break;
		}
		
		if(xStack -> empty()) {
			return false;
		}
	}
	return true;
}

void RatInMaze::print(bool print) {
	if(print) {
		int initCount = 0; int finCount = 0;
	
		for(int i = 0; i < mX; i++) {
			for(int j = 0; j < mY; j++) {
				if(maze[i][j]=='3' || maze[i][j]=='5') {
					maze[i][j] = '0';
					initCount++;
				}
			}
		}
		
		while(!xStack -> empty()) {	
			int curX = (xStack -> top());
			xStack -> pop();
			int curY = (yStack -> top());
			yStack -> pop();
			maze[curX][curY] = '2';
			finCount++;
		}
		
		while(!xQueue -> empty()) {
			int curX = (xQueue -> back());
			xQueue -> pop();
			int curY = (yQueue -> back());
			yQueue -> pop();
			maze[curX][curY] = '2';
			finCount++;
		}
		
		for(int i = 0; i < mX; i++) {
			for(int j = 0; j < mY; j++) {
				cout << maze[i][j] << " ";
			}
			cout << endl;
		}
		
		cout << "I've traveled through " << initCount << " square(s). The path contains " << finCount << " square(s)" << endl;
	}
	else
		cout << "Search canceled." << endl;
	cout << "\n\n";
}
