//#include<iostream>
//#include"spot.h"
//#include"defs.h"
//#include"rat.h"
//#include"ArrayStack.h"
//#include "UI/UI.h"
//
//using namespace std;
//
//
//void printmaze(spot** spots, int x, int y);
//spot** makingspots(int maze[][12], int x, int y);
//void inputs(int maze[][12], int& x, int& y); \
//void assignrat(spot** spots,rat* r, int x, int y);
//void stimulate(ArrayStack<int>* lastposition,spot** spots, rat* R);
//void solvemaze(ArrayStack<spot*>* lastinter,ArrayStack<int>* lastposition,spot** spots, rat* R);
//void getpositon(int i,int &posx, int &posy);
//void set(int p[], int x, int y, int sx, int sy);
//
//int main()
//{
//	UI* pGUI = new UI(); int x1,y1;
//	//pGUI->getmousecor(x1, y1);
//	spot** spots; rat* R = new rat();
//	ArrayStack<int>* lastposition=new ArrayStack<int>(50);
//	int maze[10][12] = { {1,1,1,1,1,1,1,1,1,1,1,1},
//						 {0,0,0,0,1,1,0,1,0,1,0,1},
//						 {1,1,1,0,1,1,0,0,0,0,0,1},
//						 {1,1,0,0,0,0,0,1,0,1,1,1},
//						 {1,1,0,1,1,1,0,1,0,0,0,1},
//						 {1,1,0,1,0,1,1,1,1,1,0,1},
//						 {1,0,0,0,0,0,0,0,0,1,0,1},
//						 {1,1,1,0,1,1,1,1,1,1,0,1},
//						 {1,0,0,0,0,0,0,1,0,0,0,1},
//						 {1,1,1,1,1,1,1,1,1,1,1,1} };
//	int x, y;
//	spots=makingspots(maze, 10, 12);
//	spots[1][0].setstatus(exit1);
//	printmaze(spots, 10, 12);
//	inputs(maze,x, y);
//	assignrat(spots,R, x, y);
//	printmaze(spots, 10, 12);
//	stimulate(lastposition,spots,R);
//	return 0;
//}
//void stimulate(ArrayStack<int>* lastposition,spot** spots,rat*R)
//{
//	//this part is were the algorithm will be added 
//	ArrayStack<spot*>* lastinter = new ArrayStack<spot*>(20);
//	spot* temp = &spots[R->getx()][R->gety()];
//	lastinter->push(temp);
//	solvemaze(lastinter,lastposition,spots, R);
//	//printmaze(spots, 10, 12);
//}
//void inputs(int maze[][12], int& x, int& y) {
//	cout << "Enter the starting point(x then y): ";
//	cin >> x>> y;
//	while (maze[x][y] == 1) {
//		cout << "ReEnter the starting point(x then y): ";
//		cin >> x>>y;
//	}
//}
//spot** makingspots( int maze[][12], int x, int y) 
//{
//	spot** z = new spot*[x];
//	for (int i = 0; i < x; i++) {
//		spot* temp = new spot[y];
//		z[i] = temp;
//	}
//	for (int i = 0; i < x; i++) {
//		for (int j = 0; j < y; j++) {
//			spot temp(maze, i, j, 10);
//			z[i][j] = temp;
//		}
//	}
//	return z;
//}
//
//void printmaze(spot** spots, int x, int y) {
//	for (int i = 0; i < x; i++) {
//		for (int j = 0; j < y; j++) {
//			spots[i][j].draw();
//		}
//		cout << endl;
//	}
//}
//void assignrat(spot** spots, rat* r, int x, int y) 
//{
//	spot* temp = &spots[x][y];
//	r->setxandy(x, y);
//	temp->setrat(r);
//}
//void solvemaze(ArrayStack<spot*>* lastinter ,ArrayStack<int>* lastposition,spot** spots, rat* R) {
//	int startx = R->getx(), starty = R->gety();
//	int* p = spots[startx][starty].getsides();
//	int tempx, tempy,tempxs,tempys;
//
//	if (spots[startx][starty].getstatus() == exit1)
//		return;
//
//	spots[startx][starty].updatestatus();
//
//	for (int i = 0; i < 4; i++) {
//		tempx = startx; tempy = starty; tempxs = -1; tempys = -1;
//		getpositon(i,tempx, tempy);
//
//		if(lastposition->pop(tempys))
//			lastposition->pop(tempxs);
//
//		if (p[i] == 1 && (tempys != tempy || tempxs != tempx)) {
//			status temp;
//			lastposition->push(tempxs); lastposition->push(tempys);
//			temp = spots[startx][starty].getstatus();
//			if (temp == intersection) {
//				spot* tempspot = &spots[startx][starty];
//				lastinter->push(tempspot);
//			}
//			spots[startx][starty].setrat(nullptr);
//			lastposition->push(startx);
//			lastposition->push(starty);
//			getpositon(i, startx, starty);
//			R->setxandy(startx, starty);
//			spots[startx][starty].setrat(R);
//			printmaze(spots, 10, 12);
//			
//
//			solvemaze(lastinter,lastposition, spots, R);
//			return;
//		}
//		else if(tempys!=-1){
//			lastposition->push(tempxs); lastposition->push(tempys);
//		}
//		spot* temp;
//		if (spots[startx][starty].getstatus() == end1 && lastinter->pop(temp)) {
//			int* tempint = temp->getsides();
//			int lastsy, lastsx, spotx = temp->getx(), spoty = temp->gety();
//			spots[startx][starty].setrat(nullptr);
//
//			while (lastposition->pop(lastsy)) {
//				lastposition->pop(lastsx);
//				if (lastsy == spoty && lastsx == spotx) {
//					set(tempint, startx, starty, spotx, spoty);
//					temp->setsides(tempint);
// 					R->setxandy(spotx, spoty);
//					spots[spotx][spoty].setrat(R);
//					printmaze(spots, 10, 12);
//
//					solvemaze(lastinter, lastposition, spots, R);
//					return;
//				}
//
//				R->setxandy(lastsx, lastsy);
//				spots[lastsx][lastsy].setrat(R);
//				printmaze(spots, 10, 12);
//
//				int tempy, tempx;
//				lastposition->pop(tempy); lastposition->pop(tempx);
//				if (tempy == spoty && tempx == spotx) {
//					spots[lastsx][lastsy].setrat(nullptr);
//					set(tempint, lastsx, lastsy, spotx, spoty);
//					temp->setsides(tempint);
//					R->setxandy(spotx, spoty);
//					spots[spotx][spoty].setrat(R);
//					printmaze(spots, 10, 12);
//
//					solvemaze(lastinter, lastposition, spots, R);
//					return;
//				}
//				else {
//					lastposition->push(tempx);
//					lastposition->push(tempy); 
//					spots[lastsx][lastsy].setrat(nullptr);
//				}
//			}
//		}
//		spot *temp5;
//	}
//	
//		spot* temp;
//		if (lastinter->isEmpty()) {
//			cout << "No exite not a good start position\n";
//			return;
//		}
//	
//}
//void getpositon(int i,int &posx,int &posy) {
//	int* p = new int[2];
//	switch (i)
//	{
//	case 0:posx = posx - 1;
//		break;
//	case 1:posx = posx + 1;
//		break;
//	case 2:posy = posy + 1;
//		break;
//	case 3:posy = posy - 1;
//		break;
//	}
//}
//void set(int p[], int x, int y, int sx, int sy) {
//	if (x == sx - 1&&y==sy)
//		p[0] = -1;
//	if (x ==sx + 1&& y == sy)
//		p[1] = -1;
//	if (y ==sy + 1&&x==sx)
//		p[2] = -1;
//	if (y ==sy - 1 && x == sx)
//		p[3] = -1;
//}