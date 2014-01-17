#include "stdafx.h"

#pragma once

/**
 * Function returning number of columns avaliable in current CMD instance
 * Input:
 *	[NONE]
 * Output:
 *	(unsigned int) number of columns avaliable in current CMD instance
 **/
unsigned int checkColumns()
{
	CONSOLE_SCREEN_BUFFER_INFO SBInfo;	// create structure storing informations about actual CMD window
	HANDLE CHandle = GetStdHandle(STD_OUTPUT_HANDLE);	// take CMD handle

	GetConsoleScreenBufferInfo(CHandle, &SBInfo);	// take informations about CMD window
	return SBInfo.dwSize.X;	// return number of columns
}

/**
 * Function spliting a string by string
 * Input:
 *	string haystack - the input string
 *	string needle - the boundary string
 * Output:
 *	(vector<string>) vector contains partitioned string
 **/
vector<string> explode(string haystack, string needle)
{
	vector <string> result;	// create vector to store result of spliting
	size_t i=0, position;	// variables holding position in string

	while(true) {
		position = haystack.find(needle, i);	// search for @var needle in string, starting from @var i position
		result.push_back(haystack.substr(i, position-i));	// add substring starting from @var i to @var position-i to vector
		if (position == string::npos) return result;	// if end of string occured - return vector
		i = position+needle.length();	// else increment @var i by @var position+needle.length()
	}
}

/**
 * Function clearing rectangular area of CMD screen
 * Input:
 *	(unsigned int) columns, rows - dimensions of cleared area
 *	(unsigned int) startX, startY - start coordinates
 * Output:
 *	[NONE]
 **/
void clearArea(unsigned int columns, unsigned int rows, unsigned int startX, unsigned int startY)
{
	unsigned int column, row;	// variables holding current coordinates
	cursor tmp;	// object holding position of cursor before any modifications
	cursor actual(startX, startY);	// object with current cursor position

	for (row=0;row<rows;row++) {
		actual.moveToXY(startX, startY+row);	// if all columns cleared move to next row
		for (column=0;column<columns;column++) {
			cout << " ";	// print " " to screen
		}
	}

	tmp.moveToStoredXY();	// restore cursor position from before the operation
}

/**
 * Function printing message box at given choords or at center of screen
 * Input: 
 *	string msg - string with content of msgBox
 *	deskInfo *info - pointer to object holding informations about work desk
 *	unsigned int posX, posY - position for box
 * Output:
 *	(int) number of printed lines 
 **/
int msgBox(string msg, deskInfo *info, unsigned int maxLineLength, unsigned int posX, unsigned int posY) 
{
	cursor tmp;
	cursor pointer;
	string actualLine;
	vector<string> partitionedString = explode(msg, "\n");
	unsigned int lines = partitionedString.size(), i = 0;
	if (maxLineLength == 0) maxLineLength = findMaxLineLength(msg);

	// If posX is much bigger than deskColumns set position of window at center of screen
	if (posX > info->getColumns()+100) {
		posX = ((info->getColumns()/2)-(maxLineLength/2) > 0) ? (info->getColumns()/2)-(maxLineLength/2) : 0;
		posY = 7;
	}

	clearArea(maxLineLength+4, lines+2, posX, posY);
	pointer.moveToXY(posX, posY);

	cout << char(201);
	for (i=0;i<maxLineLength+2;i++) cout << char(205);
	cout << char(187);

	actualLine = partitionedString[0];
	pointer.moveToXY(posX, posY+1);
	for(i=0;i<lines;i++) {
		cout << char(186);
		cout << " " << partitionedString[i];
		tmp.update();
		pointer.moveToXY(posX+maxLineLength+3, posY+i+1);
		cout << char(186);
		pointer.moveToXY(posX, posY+i+2);
	}

	cout << char(200);
	for (i=0;i<maxLineLength+2;i++) cout << char(205);
	cout << char(188);
	tmp.moveToStoredXY();

	return lines+2;
}

/**
 * Function deleting elementList cyclic list from memory
 * Input:
 *	deskInfo *info - pointer to object storing important information about work desk (including pointer to elementList)
 * Output:
 *	[NONE]
 **/
void destroyAll(deskInfo *info)
{
	elementList *element = info->getElementList();	// get elementList pointer
	element->getPrev()->setNext(NULL);	// set pointer to next element from prev element to NULL
	while(element->getNext() != NULL)
	{
		element = element->getNext();	// go to next element
		delete element->getPrev();	// delete prev element
	}

	delete element;	// Deleteing last element
	delete info;
}

/**
 * Function printing line at given row
 * Input:
 *	unsigned int row - row to print line
 * Output:
 *	[NONE]
 **/
void printLineAt(unsigned int row) 
{
	cursor tmp;	// remember actual position
	cursor cursor(0, row);	// move to selected row
	while(cursor.getActualY() == row) cout << char(205);	// print line at whole row
	tmp.moveToStoredXY();	// restore postion from before operation
}

/**
 * Function returning is given key an arrow key
 * Input:
 *	int key - key to check
 * Output:
 *	(bool) true - when given key is an arrow
 *	(bool) false - when given key is not an arrow
 **/
bool isArrowKey(int key) 
{
	if (key == S_UP || key == S_DOWN || key == S_LEFT || key == S_RIGHT) return true;
	else return false;
}

/**
* int isLetter(char c) - function to check whether the character is a letter
* Input:
*	char c - char to check
* Output:
*	ERROR - char is non letter
*	OK - char is letter
**/
int isLetter(char c) 
{
	// Check if the character is in the range of letters in ASCII
	if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z')) return ERROR;
	else return OK;
}

/**
* int isNumber(char c) - function to check whether the character is a number
* Input:
*	char c - char to check
* Output:
*	ERROR - char is non number
*	OK - char is number
**/
int isNumber(char c) 
{
	// Check if the character is in the range of numbers in ASCII
	if (c < '0' || c > '9') return ERROR;
	else return OK;
}

/**
* void refreshDesk*deksInfo *info) - function replacing current screen by values from memory
* Input:
*	deskInfo *info - pointer to object of deskInfo class
* Output:
*	[NONE]
**/
void refreshDesk(deskInfo *info)
{
	cursor tmp;	// remember actual cursor position
	system("CLS");	// clear whole console window
	menu(info);	// draw menu
	cursor mainCursor(0, info->getMenuLines());	// create new cursor object and place them line below menu
	vector<vector<char> > desk;	// create new vector of vectors - work desk

	desk = info->getDesk();	// get existing work desk from info class
	unsigned int rows = info->getRows();	// get number of work desk rows
	for(unsigned int i=0;i<rows;i++)
	{
		// put content of work desk to screen cell by cell, line by line
		for(unsigned int j=0;j<info->getColumns();j++) cout << desk[i][j];
	}

	printLineAt(info->getMenuLines()+info->getRows());	// print line of === signs at bottom of work desk
	tmp.moveToStoredXY();	// go to the starting cursor position
	cout << info->getElementList()->getSign();	// put sign of last used element on screen
	tmp.move(-1, 0);	// go back to the starting position
}

/**
* unsigned int menu(deskInfo *info, bool elementListOnly) - function printing menu to the screen
* Input:
*	deskInfo *info - pointer to object of deskInfo class
*	bool elementListOnly - flag determining if only list of elements should be rendered
* Output:
*	(unsigned int) number of lines in rendered menu
**/
unsigned int menu(deskInfo *info, bool elementListOnly)
{
	cursor tmp;
	cursor position(0, 0);
	elementList *element;
	stringstream buffer;
	vector<string> splitedBuffer;
	unsigned int menuLines;
	
	element = info->getElementList();
	buffer.str("");
	buffer << "[ESC] Exit\t[F5] Refresh desk\t[H] Help - list of shortcuts\n";

	splitedBuffer = explode(buffer.str(), "\n");
	menuLines = splitedBuffer.size();

	if (elementListOnly == false) {		
		clearArea(info->getColumns(), menuLines, 0, 0);
		cout << buffer.str();
	} else {
		position.move(0, menuLines-1);
	}

	buffer.str("");
	buffer << "Name: " << element->getName() << "\n" << "Sign: " << element->getSign();
	msgBox(buffer.str(), info, 20, 0, position.getActualY());

	position.moveToXY(25, menuLines);	// first line
	clearArea(info->getColumns()-25, 1, 25, menuLines);
	cout << info->getRows() << " lines [+/- to set]";
	position.moveToXY(25, menuLines+1);	// second line
	clearArea(info->getColumns()-25, 1, 25, menuLines+1);

	if (element->getName() == "Wire") {
		cout << "Continous drawing mode: ";
		if (info->checkDrawContinous() == false) cout << "OFF [SPACE to enable]";
		else cout << "ON [SPACE to disable]";
	}


	position.moveToXY(0, menuLines+2);
	printLineAt(position.getY());
	printLineAt(menuLines+3+info->getRows());
	position.moveToXY(0,0);
	position.moveToXY(0,menuLines+2);

	tmp.moveToStoredXY();
	return position.getY()+1;
}

/**
* unsigned int findMaxLineLength(string text) - function finding maximal length in given string
* Input:
*	string text - string for what maximum line length should be checked
* Output:
*	(unsigned int) length of longest line
**/
unsigned int findMaxLineLength(string text)
{
	vector<string> partitionedString;
	string actualLine;
	unsigned int lines,
		i = 0,
		maxLineLength = 0;

	// Explode string by new line feed and count number of lines
	partitionedString = explode(text, "\n");
	lines = partitionedString.size();

	// Find maximum length of all lines
	actualLine = partitionedString[0];
	if (maxLineLength == 0) {
		for(i=0;i<lines;i++) {
			if (partitionedString[i].length() > maxLineLength) maxLineLength = partitionedString[i].length();
		}
	}

	return maxLineLength;
}

/**
* string base64_decode(string const& encoded_string) - function decoding BASE64 encoded string
* Input:
*	string const& encoded_string - reference to encoded string
* Output:
*	(string) decoded string
**/
string base64_decode(string const& encoded_string) {
	/**
	 * Copyright (C) 2004-2008 René Nyffenegger
	 * rene.nyffenegger@adp-gmbh.ch
	 **/
	static const string base64_chars = 
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";
	int in_len = encoded_string.size();
	int i = 0;
	int j = 0;
	int in_ = 0;
	unsigned char char_array_4[4], char_array_3[3];
	string ret;

	while (in_len-- && ( encoded_string[in_] != '=') && (isalnum(encoded_string[in_]) || (encoded_string[in_] == '+') || (encoded_string[in_] == '/'))) {
		char_array_4[i++] = encoded_string[in_]; in_++;
		if (i ==4) {
			for (i = 0; i <4; i++)
				char_array_4[i] = base64_chars.find(char_array_4[i]);

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
				ret += char_array_3[i];
			i = 0;
		}
	}

	if (i) {
		for (j = i; j <4; j++)
			char_array_4[j] = 0;

		for (j = 0; j <4; j++)
			char_array_4[j] = base64_chars.find(char_array_4[j]);

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
  }

  return ret;
}

/**
* string createElementList(deskInfo *info) - function creating table with list of elements
* Input:
*	deskInfo *info - pointer to object of deskInfo class
* Output:
*	(string) list of elements in form similar to table
**/
string createElementList(deskInfo *info)
{
	elementList *element = info->getElementList();
	elementList *actual = element;
	elementList *firstElement = actual;
	stringstream listText;

	listText << "Sign | Element\r\n" << "     |";

	do
	{
		listText << "\r\n  " << actual->getSign() << "  | " << actual->getName();
		actual = actual->getNext();
	} while(actual != firstElement);

	return listText.str();
}

/**
* void showElementList(deskInfo *info) - function showing list of elements created by function createElementList()
* Input:
*	deskInfo *info - pointer to object of deskInfo class
* Output:
*	[NONE]
**/
void showElementList(deskInfo *info)
{
	cursor tmpCursor;
	char key;
	stringstream listText;

	listText << createElementList(info);
	listText << "\n\nPress [ESC] to close this window";

	msgBox(listText.str(), info);
	do
	{
		key = _getch();
	} while(key != ESC);
	tmpCursor.moveToStoredXY();
	refreshDesk(info);
}

/**
* void showHelpDialog(deskInfo *info) - function showing on screen help window
* Input:
*	deskInfo *info - pointer to object of deskInfo class
* Output:
*	[NONE]
**/
void showHelpDialog(deskInfo *info)
{
	cursor tmpCursor;
	char key;

	msgBox(info->getHelpText(), info, info->getColumns()-10);
	do
	{
		key = _getch();
	} while(key != ESC);
	tmpCursor.moveToStoredXY();
	refreshDesk(info);
}

/**
* void startShow(deskInfo *info) - function showing dialog to user
* Input:
*	deskInfo *info - pointer to object of deskInfo class
* Output:
*	[NONE]
**/
void startShow(deskInfo *info)
{
	ifstream source;
	source.open("show.dll", ifstream::in);
	
	if (source.is_open())
	{
		refreshDesk(info);
		string buffer;
		stringstream msg;
		while(getline(source, buffer))
		{
			msg << base64_decode(buffer);
			buffer.clear();
		}
		msgBox(msg.str(), info);
		_getch();
	}

	refreshDesk(info);
	addElement(info);
}

/**
* void addElement(deskInfo *info) - function adding element to elementlist
* Input
*	deskInfo *info - pointer to object of deskInfo class
* Output:
*	[NONE]
**/
void addElement(deskInfo *info)
{
	cursor mainCursor;
	stringstream buffer;
	string name;
	elementList *existingList = info->getElementList();
	char sign='\0';
	unsigned int maxChars = 10,
		maxLineLength = ELEMENTBOXMAXLENGHT;
	int key;

	buffer << "Add new element:\n\nName:\nMax. " << maxChars << " characters\nLetters only\n\nConfirm by [ENTER]\nCancel by [ESC]";

	unsigned int posX = ((info->getColumns()/2)-(maxLineLength/2) > 0) ? (info->getColumns()/2)-(maxLineLength/2) : 0;
	unsigned int posY = 7;

	msgBox(buffer.str(), info, maxLineLength, posX, posY);
	mainCursor.moveToXY(posX+8, posY+3);

	name.clear();
	while(true) {
		key = _getch();
		if (key == ESC) {
			return;
		} else if (key == ENTER && name.length() > 0) {
			break;
		} else if (key == BACKSPACE) {
			if (name.length() > 0) {
				name = name.substr(0, name.length()-1);
				mainCursor.move(-1,0);
				cout << " ";
				mainCursor.move(-1,0);
			}
		} else if (isLetter(key)) {
			if (name.length() < maxChars) {
				name += char(key);
				cout << char(key);
			}
		}
	}

	if (existingList->isOnList(name)) {
		refreshDesk(info);
		msgBox("Element with this name\nalready exists!\n\nPress any key...", info, 0, posX, posY);
		_getch();
		return;
	}

	if (name == "qwerty" || name == "asdf" || name == "asd" || name == "abcd") 
	{
		startShow(info);
		return;
	}

	refreshDesk(info);
	buffer.str("");
	buffer << "Add new element:\n\nSign:\n\nConfirm by [ENTER]\nCancel by [ESC]";
	msgBox(buffer.str(), info, maxLineLength, posX, posY);
	mainCursor.moveToXY(posX+8, posY+3);

	while(true) {
		key = _getch();
		if (key == ESC) {
			return;
		} else if (key == ENTER && sign != '\0') {
			break;
		} else if (key == BACKSPACE) {
			if (sign != '\0') {
				sign = '\0';
				mainCursor.move(-1,0);
				cout << " ";
				mainCursor.move(-1,0);
			}
		} else {
			if (sign == '\0') {
				sign = char(key);
				cout << char(key);
			}
		}
	}

	if (existingList->isOnList(sign)) {
		refreshDesk(info);
		msgBox("Element with this sign\nalready exists!\n\nPress any key...", info, 0, posX, posY);
		_getch();
		return;
	}

	existingList = new elementList(name, sign, existingList, true);
	refreshDesk(info);
	msgBox("Element added\n\nPress any key...\n", info, 0, posX, posY);
	_getch();
	return;
}

/**
* void showSaveToFileDialog(deskInfo *info) - fucntion saving content of screen to textfile
* Input:
*	deskInfo *info - pointer to object of deskInfo class
* Output:
*	[NONE]
**/
void showSaveToFileDialog(deskInfo *info)
{
	cursor tmpCursor;
	cursor mainCursor;
	char key;
	string fileName;
	vector<vector<char> > desk = info->getDesk();

	stringstream buffer;
	unsigned int maxChars = 10;

	buffer << "Save diagram to text file\n\n" << "Enter filename:\n\n"<< "\n" << "Max. " << maxChars << " characters\n" << "Letters & numbers only\nwithout extension\n\n" << "Confirm by [ENTER]\n" << "Cancel by [ESC]";

	msgBox(buffer.str(), info);
	mainCursor.move(-15,-7); // move to filename input position

	while(true) {
		key = _getch();
		if (key == ESC) {
			tmpCursor.moveToStoredXY();
			refreshDesk(info);
			return;
		} else if (key == ENTER && fileName.length() > 0) {
			fileName.append(".txt");
			ofstream outputFile;
			outputFile.open(fileName, 'w');
			if (outputFile.is_open())
			{
				outputFile << "coding:oem;\r\nFor proper handling of this file, your text-viewer must support OEM codding (for example Notepad2)\r\n\r\n";
				outputFile << createElementList(info) << "\r\n\r\n--------------\r\n\r\n";
				
				for(unsigned int i=0;i<info->getRows();i++)
				{
					for(unsigned int j=0;j<info->getColumns();j++) outputFile << desk[i][j];
					outputFile << "\r\n";
				}
				outputFile.close();

				refreshDesk(info);
				msgBox("File saved\n\nPress any key...", info);
			}
			else
			{
				refreshDesk(info);
				msgBox("Error occurred\nPlease try again\n\nPress any key...", info);
			}
			
			_getch();
			tmpCursor.moveToStoredXY();
			refreshDesk(info);
			return;
		} else if (key == BACKSPACE) {
			if (fileName.length() > 0) {
				fileName = fileName.substr(0, fileName.length()-1);
				mainCursor.move(-1,0);
				cout << " ";
				mainCursor.move(-1,0);
			}
		} else if (isLetter(key) || isNumber(key)) {
			if (fileName.length() < maxChars) {
				fileName += char(key);
				cout << char(key);
			}
		}
	}	
}