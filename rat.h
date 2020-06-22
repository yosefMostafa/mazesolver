#pragma once


class rat {
private:
	int rx, ry;
public:
	rat(){
	}
	void setxandy(int x, int y)
	{
		rx = x; ry = y;
	}
	int getx() {
		return rx;
	}
	int gety() {
		return ry;
	}
};