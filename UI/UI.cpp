#include "UI.h"

UI::UI()
{
	AppMode = DESIGN;	//Design Mode is the startup mode

	//Initilaize interface colors
	DrawColor = BLACK;
	SelectColor = BLUE;
	ConnColor = RED;
	MsgColor = RED;
	BkGrndColor =WHITE;
	lastclickx = 0;
	lastclicky = 0;
	//Create the drawing window
	pWind = new window(width, height, wx, wy);	


	ChangeTitle("Rat maze");
	pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial");
	pWind->SetPen(MsgColor);
	//pWind->DrawString(800, 800 - 40, "Connect the Output to the input");

	CreateDesignToolBar();	//Create the desgin toolbar
	CreateStatusBar();		//Create Status bar
}


int UI::getGateWidth() const
{
	return GATE_Width;
}

int UI::getGateHeight() const
{
	return GATE_Height;
}

//======================================================================================//
//								Input Functions 										//
//======================================================================================//

void UI::GetPointClicked(int &x, int &y)
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

void UI::GetString(string &userInput)
{
	//Reads a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" is also supported
	//User should see what he is typing at the status bar

	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 13) {
			break;
		}
		switch(Key)
		{
		case 27: //ESCAPE key is pressed
			PrintMsg("");
			break; //returns nothing as user has cancelled the input
		
		case 13:		//ENTER key is pressed
			break;
		
		case 8:		//BackSpace is pressed
			if(userInput.size() > 0)
				userInput.resize(userInput.size() -1 );
			break;
		
		default:
			userInput+= Key;
		};
		
		PrintMsg(userInput);
	}

}
int z = 0;
//This function reads the position where the user clicks to determine the desired action
ActionType UI::GetUserAction(int x,int y) 
{	
	if (x == -1) {

		if (z != 0) {
			pWind->WaitMouseClick(x, y);//Get the coordinates of the user click
			lastclicky = y;
			lastclickx = x;
		}
		else {
			z = 1;
			y = 600, x = 600;
		}
	}
	if ((y >= 0 && y < ToolBarHeight) || (x > width - ToolItemWidth && y > (ToolBarHeight) && y < (height - StatusBarHeight)))
	{
		int ClickedItemOrder = (x / ToolItemWidth);
		switch (ClickedItemOrder)
					{
		case 0:return sim;
		case 1:return build;
		case 2:return reenter;
		case 3:return save;
		case 4:return load;
					}
	}
	//if(AppMode == DESIGN )	//application is in design mode
	//{
	//	//[1] If user clicks on the Toolbar
	//	if ( (y >= 0 && y < ToolBarHeight)||(x>width- ToolItemWidth&&y>(ToolBarHeight)&& y < (height- StatusBarHeight)))
	//	{	
	//		//Check whick Menu item was clicked
	//		//==> This assumes that menu items are lined up horizontally <==
	//		int ClickedItemOrder = (x / ToolItemWidth);
	//		//Divide x coord of the point clicked by the menu item width (int division)
	//			if (ClickedItemOrder == 15 && y > ToolBarHeight + 15) {
	//				ClickedItemOrder = 15+(((y-95)/ ToolBarHeight)+1);
	//			}
	//		//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

	//		switch (ClickedItemOrder)
	//		{
	//			//A click on empty place in desgin toolbar
	//		}
	//	}
	//
	//	//[2] User clicks on the drawing area
	//	if ( y >= ToolBarHeight && y < height - StatusBarHeight)
	//	{
	//		return mod_count;	//user want to select/unselect a statement in the flowchart
	//	}
	//	
	//	//[3] User clicks on the status bar
	//	return mod_count;
	//}
	//else	//Application is in Simulation mode
	//{
	//	if (y >= 0 && y < ToolBarHeight)
	//	{
	//		//Check whick Menu item was clicked
	//		//==> This assumes that menu items are lined up horizontally <==
	//		int ClickedItemOrder = (x / ToolItemWidth);
	//		//Divide x coord of the point clicked by the menu item width (int division)
	//		//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

	//		switch (ClickedItemOrder)
	//		{
	//			//A click on empty place in desgin toolbar
	//		}
	//	}	//This should be changed after creating the compelete simulation bar 
	//	if (y >= ToolBarHeight && y < height - StatusBarHeight)
	//	{
	//		return mod_count;	//user want to select/unselect a statement in the flowchart
	//	}
	//}

}



//======================================================================================//
//								Output Functions										//
//======================================================================================//

//////////////////////////////////////////////////////////////////////////////////
void UI::ChangeTitle(string Title) const
{
	pWind->ChangeTitle(Title);
}
//////////////////////////////////////////////////////////////////////////////////
void UI::CreateStatusBar() const
{
	pWind->DrawRectangle(0,0,150, 95,FRAME);
	pWind->DrawString(60, 35, "Sim");
	pWind->DrawRectangle(150, 0, 300, 95, FRAME);
	pWind->DrawString(60+150, 35, "Build");
	pWind->DrawRectangle(150+150, 0, 300+150, 95, FRAME);
	pWind->DrawString(20 + 150+150, 35, "Re Enter Maze ");
	pWind->DrawRectangle(150 + 150+150, 0, 300 + 150+150, 95, FRAME);
	pWind->DrawString(60 + 150 + 150+150, 35, "Save");
	pWind->DrawRectangle(150 *4, 0, 300 + 150 *3, 95, FRAME);
	pWind->DrawString(60 + 150*4, 35, "Load");
	pWind->SetPen(BLACK,3);
	pWind->DrawLine(0, height-StatusBarHeight, width, height-StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////
void UI::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = StatusBarHeight - 10;

	// Print the Message
    pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial"); 
	pWind->SetPen(MsgColor); 
	pWind->DrawString(MsgX, height - MsgY, msg);
}
//////////////////////////////////////////////////////////////////////////////////
void UI::ClearStatusBar()const
{
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = StatusBarHeight - 10;

	//Overwrite using bachground color to erase the message
	pWind->SetPen(BkGrndColor);
	pWind->SetBrush(BkGrndColor);
	pWind->DrawRectangle(MsgX, height - MsgY, width/2, height);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Clears the drawing (degin) area
void UI::ClearDrawingArea() const
{
	pWind->SetPen(BLACK, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, ToolBarHeight, width, height - StatusBarHeight);
	
}

//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the Design mode
void UI::CreateDesignToolBar()
  {
	AppMode = DESIGN;	//Design Mode
	pWind->SetPen(WHITE, 1);
	pWind->DrawRectangle(0, 0, width, ToolBarHeight + 14);
	//You can draw the tool bar icons in any way you want.

	//First prepare List of images for each menu item
	string MenuItemImages[ITM_DSN_CNT];
	//MenuItemImages[ITM_AND2] = "images\\Gates\\Gate_AND2.jpg";
	



	//TODO: Prepare image for each menu item and add it to the list

	//Draw menu item one image at a time
	//int j = 1;
	//for (int i = 0; i < ITM_DSN_CNT; i++) {
	//	if (i>= 16) {
	//		if (i == 16) {
	//			pWind->DrawImage(MenuItemImages[i], width - (ToolItemWidth + 14), (ToolBarHeight + 15) * (j), ToolItemWidth, ToolBarHeight);
	//			j++;
	//		}
	//		else {
	//			pWind->DrawImage(MenuItemImages[i], width - (ToolItemWidth + 14), (ToolBarHeight) * (j)+15, ToolItemWidth, ToolBarHeight);
	//			j++;
	//		}
	//	}
	//	else {
	//		pWind->DrawImage(MenuItemImages[i], i * ToolItemWidth, 0, ToolItemWidth, ToolBarHeight);
	//	}
	//}
	//int n = 1;
	////Draw a line under the toolbar
	//pWind->SetPen(BLACK, 20);
	//pWind->SetFont(15,5, MODERN);
	//string gatelabel[23]= { "AND","NAND","OR","NOR","XOR","XNOR","WIRE","Delete","Undo","Redo","Save",
	//	"Load","Edit label","Simulation","unselect",
	//	"EXIT","Switch","LED","NOT","Copy","Cut","Paste","Move" };
	//for (int i = 0; i < 23; i++) {
	//	if (i==12||i==13) {
	//		pWind->DrawString(i * ToolItemWidth +10, 80, gatelabel[i]);
	//	}
	//	else if(i>=16){
	//		pWind->DrawString(width-(ToolItemWidth+12) , 15+ToolItemWidth *(n), gatelabel[i]);
	//		n++;
	//	}else {
	//		pWind->DrawString(i * ToolItemWidth +25, 80, gatelabel[i]);
	//	}
	//}
	pWind->SetPen(BLACK,3);
	pWind->DrawLine(0, ToolBarHeight, width, ToolBarHeight );
	pWind->SetPen(BLACK, 3);
	//pWind->DrawLine(width - 95, 95, width - 95, height - 50);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the simulation mode
void UI::CreateSimulationToolBar()
{
	AppMode = SIMULATION;	//Simulation Mode
	pWind->SetPen(WHITE, 1);
	pWind->DrawRectangle(0, 0, width, ToolBarHeight+14);
	pWind->DrawRectangle(width -(ToolItemWidth+13), ToolBarHeight+13, width, height - StatusBarHeight);
	string STbarItemImages[ITM_STN_CNT];
	STbarItemImages[IIM_TRUTHTABLE] = "images\\Menu\\TTL.jpg";
	STbarItemImages[ITM_DM] = "images\\Menu\\Load.jpg";
	STbarItemImages[ITM_STM] = "images\\Menu\\SM.jpg";
	STbarItemImages[EXIT1] = "images\\Menu\\Menu_Exit.jpg";
	for (int i = 0; i < ITM_STN_CNT; i++) {
		pWind->DrawImage(STbarItemImages[i], i * ToolItemWidth, 0, ToolItemWidth, ToolBarHeight);
	}

	//Draw a line under the toolbar
	pWind->SetPen(BLACK, 20);
	pWind->SetFont(15, 5, MODERN);
	string gatelabel[4] = { "TRuth Table","Design mode","Stimulate","Exit program"};
	for (int i = 0; i < 4; i++) {
			pWind->DrawString(i * ToolItemWidth, 80, gatelabel[i]);
	}
	//TODO: Write code to draw the simualtion toolbar (similar to that of design toolbar drawing)

}

//======================================================================================//
//								Components Drawing Functions							//
//======================================================================================//


//TODO: Add similar functions to draw all components
void UI::drawspot(spot** temp,rat *R)
{
	float tempx = 50	, tempy = 110;
	string Image;
	
	
		int rx=R->getx(), ry=R->gety();
		tempx = tempx + (ry-1) * GATE_Width ;
		int x = tempx;
		tempy = tempy + GATE_Height *(rx-1);
		pWind->SetPen(BLACK);
		for (int n = rx - 1; n < rx + 2; n++) {
			for (int j = ry - 1; j < ry + 2; j++) {
				if (temp[n][j].getrat()) {
					Image = "photos\\rat.jpg";
					pWind->DrawImage(Image, tempx, tempy, GATE_Width, GATE_Height);
				}
				else if (temp[n][j].getstatus() == exit1) {
					Image = "photos\\exit.jpg";
					pWind->DrawImage(Image, tempx, tempy, GATE_Width, GATE_Height);
				}
				else {
					if (temp[n][j].getitem() == 1)
						pWind->SetBrush(black);
					else
						pWind->SetBrush(WHITESMOKE);

					pWind->DrawRectangle(tempx, tempy, tempx + GATE_Width, tempy + GATE_Height, FILLED);
				}
				tempx = tempx + GATE_Width;
			}
			tempy = tempy + GATE_Height;
			tempx = x;
		}
		
	
}
void UI::drawspot(int** maze, int mazex, int mazey,int exx,int exy, drawmode i, int x, int y)
{
	float tempx = 50, tempy = 110;
	string Image;
	GATE_Width = (float(width) - 100) / float(mazey);
	GATE_Height = (float(height) - 120 - StatusBarHeight) / float(mazex);
	pWind->SetPen(BLACK);
	if (i == initializing) {
		ClearDrawingArea();
		for (int i = 0; i < mazex; i++) {
			for (int j = 0; j < mazey; j++) {
				if (maze[i][j] == 1)
					pWind->SetBrush(black);
					//Image = "photos\\black.jpg";
				else if(maze[i][j]==0)
					pWind->SetBrush(WHITESMOKE);
					//Image = "photos\\white.jpg";
				if (i == exx && j == exy) {
					Image = "photos\\exit.jpg";
					pWind->DrawImage(Image, tempx, tempy, GATE_Width, GATE_Height);
				}
				else
					pWind->DrawRectangle(tempx, tempy, tempx+GATE_Width, tempy+GATE_Height, FILLED);
				tempx = tempx + GATE_Width;
			}
			tempy = tempy + GATE_Height;
			tempx = 50;
		}
	}
	else {
		tempx = tempx + y * GATE_Width;
		tempy = tempy + x * GATE_Height;

		
		if (x == exx && y == exy) {
			Image = "photos\\exit.jpg";
			pWind->DrawImage(Image, tempx, tempy, GATE_Width, GATE_Height);
		}
		else {
			if (maze[x][y] == 1)
				pWind->SetBrush(black);
			else
				pWind->SetBrush(WHITESMOKE);
			pWind->DrawRectangle(tempx, tempy, tempx + GATE_Width, tempy + GATE_Height, FILLED);
		}
	}
}

void UI::DrawConnection(const GraphicsInfo& r_GfxInfo, bool selected, string f)
{

	if (selected) {
		pWind->SetPen(BLACK, 5);
	}
	else {
		pWind->SetPen(RED, 5);
	}
		pWind->DrawLine(r_GfxInfo.PointsList[0].x, r_GfxInfo.PointsList[0].y, r_GfxInfo.PointsList[1].x, r_GfxInfo.PointsList[0].y);
		pWind->DrawLine(r_GfxInfo.PointsList[1].x, r_GfxInfo.PointsList[0].y, r_GfxInfo.PointsList[1].x, r_GfxInfo.PointsList[1].y);//TODO: Add code to draw connection00
		pWind->SetPen(BLACK, 20);
		pWind->SetFont(15, 5, MODERN);
		pWind->DrawString(((r_GfxInfo.PointsList[0].x + r_GfxInfo.PointsList[1].x) / 2), r_GfxInfo.PointsList[0].y - 25, f);
}


UI::~UI()
{
	delete pWind;
}
void UI::drawRectangle(int x, int y, int x1, int y1) {
	pWind->SetPen(WHITE, 1);
	pWind->DrawRectangle(x, y,x1, y1);
}
void UI::drawline(int x, int y, int x1, int y1) {
	pWind->SetPen(GREY, 1);
	pWind->DrawLine(x, y, x1, y1);
}
int UI::getlastclickx() {
	return lastclickx;
}
int UI::getlastclicky() {
	return lastclicky;
}
void UI::drawstring(int x, int y, string f) {
	pWind->DrawString(x, y, f);
}
void UI::WaitKeyPress(char& key) {
	pWind->WaitKeyPress(key);
}

void UI::getmousecor(int& x, int& y) {
	pWind->GetMouseCoord(x, y);
}
clicktype UI::getmouseclick(int& x, int& y) {
	return pWind->GetMouseClick(x, y);
}
int UI::getToolBarHeight(){
	return ToolBarHeight1;
}
int UI::getToolItemWidth() {
	return ToolItemWidth1;
}
int UI::getheight() {
	return height1;
}
int UI::getwidth() {
	return width1;
}
int UI::getStatusBarHeight() {
	return StatusBarHeight1;
}

int UI::getgatewidth()
{
	return GATE_Width;
}

int UI::getgatehieght()
{
	return GATE_Height;
}

void UI::waitmouseclick(int& x, int& y)
{
	pWind->WaitMouseClick(x, y);
}
