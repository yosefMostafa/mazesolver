#include "program.h"
#include<random>
#include<ctime>



program::program()
{
	pGUI = new UI();
	R = nullptr;
	makingmaze();
}

void program::makingspots()
{
	
	spots = new spot * [mazex];
	for (int i = 0; i < mazex; i++) {
		spot* temp = new spot[mazey];
		spots[i] = temp;
	}
	for (int i = 0; i < mazex; i++) {
		for (int j = 0; j < mazey; j++) {
			spot temp(maze, i, j,maze[i][j]);
			spots[i][j] = temp;
		}
	}
	
}

void program::makingmaze()
{
		string s;
		pGUI->PrintMsg("Enter the dimention of the maze (x then y).");
		pGUI->GetString(s);
		int len = s.length() / 2;
		char* x = new char[len];
		for (int i = 0; i < len; i++)
			x[i] = s[i];
		char* y = new char[len];
		for (int i = 0; i < len; i++)
			y[i] = s[i + len + 1];

		const char* tempx = x;
		const char* tempy = y;
		mazex = atoi(tempx);
		mazey = atoi(tempy);

		pGUI->PrintMsg("Enter the exite of the maze (x then y).");
		string temp2;
		pGUI->GetString(temp2);
		len = temp2.length() / 2;
		char* x2 = new char[len];
		char* y2 = new char[len];
		for (int i = 0; i < len; i++)
			x2[i] = temp2[i];
		for (int i = 0; i < len; i++)
			y2[i] = temp2[i + len + 1];
		const char* tempx2 = x2;
		const char* tempy2 = y2;
		exitex = atoi(tempx2) - 1;
		exitey = atoi(tempy2) - 1;

		maze = new int* [mazex];
		for (int i = 0; i < mazex; i++) {
			int* temp = new int[mazey];
			maze[i] = temp;
		}
		for (int i = 0; i < mazex; i++) {
			for (int j = 0; j < mazey; j++) {
				if (!(i == exitex && j == exitey))
					maze[i][j] = 1;
				else
					maze[i][j] = 0;
			}
		}
	lastposition = new ArrayStack<int>(mazey*18);
	lastinter = new ArrayStack<spot*>(mazey*6);
	UpdateInterfacem(initializing);
}

void program::RunProgram()
{
	ActionType temp=pGUI->GetUserAction();
	switch (temp)
	{
	case build:
		build2();
		break;
	case sim:
		simulate();
		break;
	case mod_count:
		break;
	default:
		break;
	}

}

void program::UpdateInterface()
{
	pGUI->drawspot(spots,R);
	Sleep(100);
}

void program::UpdateInterfacem(drawmode i,const int x,const int y)
{

	pGUI->drawspot(maze,mazex,mazey,exitex,exitey,i,x,y);
}

void program::getinput(int &x,int &y)
{
	pGUI->PrintMsg("Click on the mouse position .");
	pGUI->waitmouseclick(x,y);
	int tempy = y;
	y = (x-50) / 60;
	x = (tempy-110) / 60;
}

void program::assignrat( int x, int y)
{

	if (R!=nullptr)
		spots[R->getx()][R->gety()].setrat(nullptr);
	else
		R = new rat();
	spot* temp = &spots[x][y];
	R->setxandy(x, y);
	temp->setrat(R);
}

void program::simulate()
{
	int x=8, y=5;
	
	getinput(x,y);
	makingspots();
	spots[exitex][exitey].setstatus(exit1);
	assignrat( x, y);
	UpdateInterface();
	spot* temp = &spots[R->getx()][R->gety()];
	lastinter->push(temp);
	srand(time(0));
	solvemaze();
	clearmem();
}

void program::build2()
{
	int x, y;
	pGUI->PrintMsg("Click on the mouse to build .");
	pGUI->waitmouseclick(x, y);
	int tempy = y;
	y = (x - 50) / 60;
	x = (tempy - 110) / 60;
	while (x > 0 && x < mazex && y > 0 && y < mazey) {
		
		if (maze[x][y] == 1)
			maze[x][y] = 0;
		else
			maze[x][y] = 1;
		UpdateInterfacem(building, x, y);
		pGUI->waitmouseclick(x, y);
		tempy = y;
		y = (x - 50) / 60;
		x = (tempy - 110) / 60;
	}
}

void program::solvemaze()
{
	int startx = R->getx(), starty = R->gety();
	int* p = spots[startx][starty].getsides();
	int tempx, tempy, tempxs, tempys;

	if (spots[startx][starty].getstatus() == exit1)
		return;
	if (spots[startx][starty].getcount() == 4) {
		pGUI->PrintMsg("No exite not a good start position");
		return;
	}
	spots[startx][starty].updatestatus();
	for (int i = 0; i < 32; i++) {
		tempx = startx; tempy = starty; tempxs = -1; tempys = -1;
	
		int pos = rand() % 4;
		getpositon(pos, tempx, tempy);
		if (lastposition->pop(tempys))
			lastposition->pop(tempxs);

		if (p[pos] == 1 && (tempys != tempy || tempxs != tempx)) {
			
			status temp;
			lastposition->push(tempxs); lastposition->push(tempys);
			temp = spots[startx][starty].getstatus();
			if (temp == intersection) {
				spot* tempspot = &spots[startx][starty];
				lastinter->push(tempspot);
				//checkinter(tempspot,startx, starty, pos);
			}
			
			if (checkinter(startx, starty, pos))
				return;
			//spots[startx][starty].updatestatus();
			lastposition->push(startx);
			lastposition->push(starty);
			getpositon(pos, startx, starty);
			assignrat(startx, starty);
			UpdateInterface();


			solvemaze();
			return;
		}
		else if (tempys != -1) {
			lastposition->push(tempxs); lastposition->push(tempys);
		}
		spot* temp;
		if (spots[startx][starty].getstatus() == end1 && lastinter->pop(temp)) {
			int* tempint = temp->getsides();
			int lastsy, lastsx, spotx = temp->getx(), spoty = temp->gety();
			

			while (lastposition->pop(lastsy)) {
				lastposition->pop(lastsx);
				if (lastsy == spoty && lastsx == spotx) {
					set(tempint, startx, starty, spotx, spoty);
					temp->setsides(tempint);
				
					assignrat(spotx, spoty);
					UpdateInterface();

					solvemaze();
					return;
				}

				
				assignrat(lastsx, lastsy);
				UpdateInterface();

				int tempy, tempx;
				lastposition->pop(tempy); lastposition->pop(tempx);
				if (tempy == spoty && tempx == spotx) {
					
					set(tempint, lastsx, lastsy, spotx, spoty);
					temp->setsides(tempint);
	
					assignrat(spotx, spoty);
					UpdateInterface();

					solvemaze();
					return;
				}
				else {
					lastposition->push(tempx);
					lastposition->push(tempy);
					//spots[lastsx][lastsy].setrat(nullptr);
				}
			}
		}
	}
	if (lastinter->isEmpty()) {
		pGUI->PrintMsg("No exite not a good start position");
		return;
	}

}

void program::getpositon(int i, int& posx, int& posy)
{
	switch (i)
	{
	case 0:posx = posx - 1;
		break;
	case 1:posx = posx + 1;
		break;
	case 2:posy = posy + 1;
		break;
	case 3:posy = posy - 1;
		break;
	}
}

void program::set(int p[], int x, int y, int sx, int sy)
{
	if (x == sx - 1 && y == sy)
		p[0] = -1;
	if (x == sx + 1 && y == sy)
		p[1] = -1;
	if (y == sy + 1 && x == sx)
		p[2] = -1;
	if (y == sy - 1 && x == sx)
		p[3] = -1;
}

bool program::checkinter(int x, int y, int i)
{
	spot* tempinter;
	ArrayStack<spot*>* temp = new ArrayStack<spot*>(mazey*18);
	int tempx=x, tempy=y,flag=-1;
	getpositon(i, tempx, tempy);
	while (lastinter->pop(tempinter)){
		if (tempinter->getstatus() != continuing) {
			if (tempinter->getx() == tempx && tempinter->gety() == tempy) {
				int* p = spots[x][y].getsides();
				p[i] = -1;
				spots[x][y].setsides(p);
				spots[x][y].setstatus(end1);
				int* p2 = spots[tempx][tempy].getsides();
				set(p2, x, y, tempx, tempy);
				spots[tempx][tempy].setsides(p2);
				//tempspot->updatestatus();
				flag = 1;
			}
		}
			temp->push(tempinter);
		
}
	while (temp->pop(tempinter))
		lastinter->push(tempinter);
	if (flag == 1) {
		solvemaze();
		spots[x][y].updatestatus();
		spots[tempx][tempy].updatestatus();
		return true;
	}
	return false;
}


void program::clearmem()
{
	int temp; spot* temp2;
		while (lastposition->pop(temp)) {
			temp = temp + 1;
	}
		while (lastinter->pop(temp2)) {}
			
		spots[exitex][exitey].setrat(nullptr);
		UpdateInterface();
		
}

program::~program()
{
	delete lastinter;
	spot* temp2;
	delete spots;
	delete maze;
	delete lastposition;
	while (lastinter->pop(temp2)) {
		delete temp2;
	}
}
