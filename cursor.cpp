#include "stdafx.h"

#pragma once

// Parameterless constructor
cursor::cursor() {
	CHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	update();
}

// Constructor moving cursor to given position
cursor::cursor(unsigned int x, unsigned int y) {
	CHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	setXY(x, y);
	moveToXY(x, y);
}