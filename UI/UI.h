#pragma once

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\defs.h"
#include <string>
#include"..\spot.h"
#include"..\rat.h"

using namespace std;

struct Point
{
	int x,y;
};


//A structure to contain drawing parameters for each component
//Each component stores its drawing points in this struct 
//For example, a Gate can store points of the rectangluar area it occupies
//				The Connection 
//this structure can be extended if desired
struct GraphicsInfo
{
	int PointsCount;
	Point* PointsList;
	GraphicsInfo(int PtsCnt)
	{
		PointsCount = PtsCnt;
		PointsList = new Point[PointsCount];	//allocate required points
	}

};


class UI
{
	enum StgnMenuItem
	{
		IIM_TRUTHTABLE,
		ITM_DM,
		ITM_STM,
		EXIT1,
		ITM_STN_CNT
	};
	enum DsgnMenuItem //The items of the design menu (you should add more items)
	{
		//Note: Items are ordered here as they appear in menu
		//If you want to change the menu items order, change the order here
		ITM_AND2,		//AND gate item in menu
		ITM_NAND2,
		ITM_OR2,		//OR gate item in menu
		ITM_NOR2,
		ITM_XOR,
		ITM_XNOR,
		ITM_pen,
		ITM_DELETE,//pen item in menu
		ITM_UNDO,
		ITM_REDO,
		ITM_SAVE,
		ITM_LOAD,
		ITM_EDIT,
		ITM_SM,
		ITM_UNSELECT,
		ITM_EXIT,		//Exit item
		ITM_SWITCH,
		ITM_LED,
		ITM_NOT,
		ITM_COPY,
		ITM_CUT,
		ITM_PASTE,
		ITM_MOVE,
		//TODO: Add more items names here
	
		ITM_DSN_CNT		//no. of design menu items ==> This should be the last line in this enum
	
	};




	MODE AppMode;		//Application Mode (design or simulation)
	
	static const int	width = 980, height = 800,	//Window width and height
						wx = 15 , wy = 15,			//Window starting coordinates
						StatusBarHeight = 50,	//Status Bar Height
						ToolBarHeight = 95,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
						ToolItemWidth = 150;		//Width of each item in toolbar menu

	color DrawColor;		//Drawing color
	color SelectColor;		//Highlighting color
	color ConnColor;		//Connector color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Back ground color


	//This should be calculated accurately because it will be used later to create connections between gates
	//For now, we will assume that rect width = 50 and height = 50
	static const int	GATE_Width = 60,		//Gate Image default width
						GATE_Height = 60;		//Gate Image default height

	window* pWind;
private:
	int lastclickx;
	int lastclicky;
	int width1 = 1280, height1 = 800,	//Window width and height
		wx1 = 15, wy1 = 15,			//Window starting coordinates
		StatusBarHeight1 = 50,	//Status Bar Height
		ToolBarHeight1 = 80,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		ToolItemWidth1 = 80;		//Width of each item in toolbar menu
public:
	int getlastclickx();
	int getlastclicky();
	UI();
	int getGateWidth() const;
	int getGateHeight() const;	
	// Input Functions  ---------------------------
	void GetPointClicked(int &, int &);	//Get coordinate where user clicks
	void GetString(string& userInput);		//Returns a string entered by the user
	void drawRectangle(int x,int y,int x1,int x2);
	void drawline(int x, int y, int x1, int x2);
	void drawstring(int x, int y,string f);
	void WaitKeyPress(char& cKey);
	void getmousecor(int& x, int& y);
	void getmouseclick(int& X, int& y);
	int getToolBarHeight();
	int  getToolItemWidth();
	int  getheight();
	int  getwidth();
	int getStatusBarHeight();
	void waitmouseclick(int& x, int &y);

	ActionType GetUserAction() ; //Reads the user click and maps it to an action

	
	// Output Functions  ---------------------------

	void ChangeTitle(string Title) const;

	void CreateDesignToolBar();	//Tool bar of the design mode
	void CreateSimulationToolBar();//Tool bar of the simulation mode
	void CreateStatusBar() const;	//Create Status bar

	void ClearStatusBar() const;		//Clears the status bar
	void ClearDrawingArea() const;	//Clears the drawing area

	void drawspot(spot** temp,rat*R);
	void drawspot(int **maze,int mazex,int mazey, int exx, int exy,drawmode i,int x,int y);
	// Draws 2-input AND gate

	///TODO: Make similar functions for drawing all other gates, switch, and LED, .. etc

	// Draws Connection
	void DrawConnection(const GraphicsInfo& r_GfxInfo, bool selected,string f) ;
	
	void PrintMsg(string msg) const;	//Print a message on Status bar

	~UI();
};

