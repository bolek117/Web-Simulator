// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <iostream>	// standard input/output operations
#include <string>	// string handling
#include <sstream>	// string << concatenation << with << "<<" operator
#include <vector>	// vector.pushBack();
#include <Windows.h>	// console cursor handle
#include <conio.h>	// _getch();
#include <iomanip>	// setw();
#include <fstream>	// file handling

using namespace std;

// keycodes for functional keys
#define BACKSPACE 8
#define ESC 27
#define ENTER 13
#define SPACE 32
#define MINUS 45
#define PLUS 43

// Start of special chord
#define F_START 0
// keycodes from special chords
#define S_START 224
#define S_UP 72
#define S_PGUP 73
#define S_LEFT 75
#define S_RIGHT 77
#define S_DOWN 80
#define S_PGDN 81
#define S_INSERT 82
#define F_5 63

// Bolean values returned by functions
#define ERROR 0
#define OK 1

// Default values needed for aligning message box to center of screen
#define ELEMENTBOXMAXLENGHT 20
#define CENTER 999

// Number of rows of desk at start of program
#define START_DESKROWS 10

#include "cursor.h"	// cursor class
#include "elementList.h"	// elementList class
#include "deskInfo.h"	// deskInfo class

// Additional functions - verbose description is avaliable in file fucntions.cpp, near definition of functions
unsigned int checkColumns();
void clearArea(unsigned int columns, unsigned int rows, unsigned int startX, unsigned int startY);
int msgBox(string msg, deskInfo *info, unsigned int maxLineLength=0, unsigned int posX=CENTER, unsigned int posY=CENTER);
void printLineAt(unsigned int row);
bool isArrowKey(int key);
unsigned int findMaxLineLength(string text);
void startShow(deskInfo *info);
void refreshDesk(deskInfo *info);
unsigned int menu(deskInfo *info, bool elementListOnly=false);
int isLetter(char c);
string base64_decode(string const& s);
void addElement(deskInfo *info);
vector<string> explode(string haystack, string needle);
void refreshDesk(deskInfo *info);
void destroyAll(deskInfo *info);
void showElementList(deskInfo *info);
void showHelpDialog(deskInfo *info);
void showSaveToFileDialog(deskInfo *info);
string createElementList(deskInfo *info);