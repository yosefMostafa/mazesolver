#pragma once
#include"defs.h"
#include"rat.h"
#include<iostream>


using namespace std;

class spot {
private:
	int item;
	rat* R;
	status st;
	int x, y;
	int* p = new int[4];
	int count;
public:
	spot() {
		R = nullptr; x = -1; y = -1;
		for (int i = 0; i < 4; i++)
			p[i] = -1;
	}
	spot(int **maze, int x1, int y1,int i) {
		R = nullptr;
		st = end1; x = x1, y = y1;
		count;
		for (int i = 0; i < 4; i++)
			p[i] = -1;
		checkstatus(maze, x, y); item = i;
	}
	void checkstatus(int **maze,int x,int y)
	{
		
		if (maze[x][y] == 1)
			st = black;
		/*else if (x == 4 && y == 11) {
			st = exit1;
		}*/ else{
			check4sides(maze, x, y);
			int c=countallowed(maze, x,  y);
			if (c > 2)
				st = end1;
			else if (c == 2)
				st = continuing;
			else
				st = intersection;
		}
	}
	void check4sides(int **maze,int x,int y)
	{
		if (maze[x - 1][y] == 0) {
			p[0] = 1; count--;
		}//up first 
		if (maze[x + 1][y] == 0) {
			p[1] = 1; count--;//down second  
		}if (maze[x][y + 1] == 0) {
			p[2] = 1; count--;//right second  
		}if (maze[x][y - 1] == 0) {
			p[3] = 1; count--;
		}//left second  
	}
	int* getsides() {
		return p;
	}
	int  countallowed(int **maze, int x, int y) {
			return maze[x+1][y] + maze[x][y+1] + maze[x-1][y] + maze[x][y-1];
	}
	status getstatus() { 
		return st;
	}
	void updatestatus() {
		count = 0;
		for (int i = 0; i < 4; i++) {
			if (p[i] == -1) {
				count++;
			}
		}
		switch (count)
		{
		case 2:setstatus(continuing);
			break;
		case 3:setstatus(end1);
			break;
		case  1: setstatus(intersection);
			break;
		}
	}
	void setstatus(status x) {
		st = x;
	}
	int getx() {
		return x;
	}
	int gety() {
		return y;
	}
	void setxy(int x1,int y1) {
		x = x1; y = y1;
	}
	void draw() {
		if (R == nullptr) {
			switch (st)
			{
			case black:cout << "1 ";
				break;
			default:
				cout << "  ";
				break;
			}
		}
		else {
			cout << "R ";
		}
	}
	void setrat(rat* x) {
		R = x;
	}
	void setsides(int* temp) {
		p = temp;
		count = 0;
		for (int i = 0; i < 4; i++) {
			if (p[i] == -1) {
				count++;
			}
		}
	}
	int getcount() {
		return count;
	}
	int getitem() {
		return item;
	}
	rat* getrat() {
		return R;
	}
};