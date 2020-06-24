#pragma once
#include"spot.h"
#include"ArrayStack.h"
#include"UI/UI.h"
#include"spot.h"
#include"defs.h"
#include"rat.h"

class program
{
private:
	spot** spots; rat* R;
	ArrayStack<int>* lastposition;
	ArrayStack<spot*>* lastinter;
	UI* pGUI;
	int** maze;
	int mazex, mazey; int exitex, exitey;
public:
	program();
	void makingspots();
	void makingmaze();
	void assignrat( int x, int y);

	void RunProgram(const int x=-1,const int y=-1);
	void UpdateInterface();
	void UpdateInterfacem(drawmode i, const int x = -1, const int y = -1);
	void getinput(int& x, int& y);
	
	void simulate();
	void build2();

	void solvemaze();

	void getpositon(int i, int& posx, int& posy);
	void set(int p[], int x, int y, int sx, int sy);
	bool checkinter( int x, int y,int i);

	void save1();
	void load1();

	void clearmem();
	~program();
};

