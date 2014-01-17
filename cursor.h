#include "stdafx.h"

#pragma once

class cursor {
private:
	unsigned int x;	// x coordinate of cursor
	unsigned int y;	// y coordinate of cursor
	HANDLE CHandle;	// Handle to console window

public:
	cursor();	// Parameterless constructor
	cursor(unsigned int x, unsigned int y);	// constructor with defined coordinates

	/**************************************************************
	* Getters
	***************************************************************/

	/**
	* unsigned int getX() - get X coordinate stored in memory
	* Input:
	*	[NONE]
	* Output:
	*	(unsigned int) X coordinate
	**/
	unsigned int getX() {return x;}

	/**
	* unsigned int getY() - get y coordinate stored in memory
	* Input:
	*	[NONE]
	* Output:
	*	(unsigned int) y coordinate
	**/
	unsigned int getY() {return y;}

	/**
	* HANDLE getHandle() - get Handle to console window
	* Input:
	*	[NONE]
	* Output:
	*	(HANDLE) handle to console window
	**/
	HANDLE getHandle() {return CHandle;}

	/**
	* unsigned int getActualX() - get actual x coordinate and put to memory
	* Input:
	*	[NONE]
	* Output:
	*	(unsigned int) actual X coordinate
	**/
	unsigned int getActualX() {
		update();
		return x;
	}
	
	/**
	* unsigned int getActualY() - get actual y coordinate and put to memory
	* Input:
	*	[NONE]
	* Output:
	*	(unsigned int) actual Y coordinate
	**/
	unsigned int getActualY() {
		update();
		return y;
	}

	/**************************************************************
	* Setters
	***************************************************************/
	
	/**
	* void setX(unsigned int x=0) - modify content of X coordinate
	* Input:
	*	unsigned int x - value of X coordinate
	* Output:
	*	[NONE]
	**/
	void setX(unsigned int x=0) {this->x = x;}

	/**
	* void setY(unsigned int x=0) - modify content of Y coordinate
	* Input:
	*	unsigned int y - value of Y coordinate
	* Output:
	*	[NONE]
	**/
	void setY(unsigned int y=0) {this->y = y;}

	/**
	* void setXY(unsigned int x=0, unsigned int y=0) - modify content of XY coordinate
	* Input:
	*	unsigned int x - value of X coordinate
	*	unsigned int y - value of Y coordinate
	* Output:
	*	[NONE]
	**/
	void setXY(unsigned int x=0, unsigned int y=0)
	{
		setX(x);
		setY(y);
	}

	/**
	* void update(char axis=' ') - update coordinates according to actual position of cursor
	* Input:
	*	char axis - axis for which coordinate should be updated
	* Output:
	*	[NONE]
	**/
	void update(char axis=' ')
	{
		CONSOLE_SCREEN_BUFFER_INFO SBInfo;
		GetConsoleScreenBufferInfo(CHandle, &SBInfo);
		if (axis == ' ' || axis == 'x') x = SBInfo.dwCursorPosition.X;
		if (axis == ' ' || axis == 'y') y = SBInfo.dwCursorPosition.Y;
	}

	/**
	* void updateX() - update coordinate X according to actual position of cursor
	* Input:
	*	[NONE]
	* Output:
	*	[NONE]
	**/
	void updateX() {update('x');}

	/**
	* void updateY() - update coordinate Y according to actual position of cursor
	* Input:
	*	[NONE]
	* Output:
	*	[NONE]
	**/
	void updateY() {update('y');}

	/**
	* void move(int x, int y) - move cursor relative to actual XY
	* Input:
	*	int x - relative change of X coordinate
	*	int y - relative change of Y coordinate
	* Output:
	*	[NONE]
	**/
	void move(int x, int y)
	{
		update();
		COORD coord = {this->x+x, this->y+y};
		SetConsoleCursorPosition(CHandle, coord);
		update();
	}

	/**
	* void moveToStoredXY() - move cursor to position stored in memory
	* Input:
	*	[NONE]
	* Output:
	*	[NONE]
	**/
	void moveToStoredXY() {
		moveToXY(getX(), getY());
	}

	/**
	* void moveToXY(unsigned int x, unsigned int y) - move cursor to given XY
	* Input:
	*	unsigned int x - desired X coordinate
	*	unsigned int y - desired Y coordinate
	* Output:
	*	[NONE]
	**/
	void moveToXY(unsigned int x, unsigned int y) {
		COORD coord = {x, y};
		SetConsoleCursorPosition(CHandle, coord);
		update();
	}
};