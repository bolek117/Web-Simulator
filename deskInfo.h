#include "stdafx.h"

#pragma once

class deskInfo {
private:
	unsigned int deskRows, deskColumns, maxLineLength, menuLines; // number of rows in workdesk, number of columns in workdesk, maximal length of line, number of lines of menu
	bool drawContinous;	// flag 
	elementList *element;	// Pointer to element list
	vector<vector<char> > desk;	// Workdesk
	string helpText;	// String containing Help message

public:
	deskInfo();	// Parameterless constructor
	deskInfo(elementList *element, unsigned int rows, unsigned int columns, unsigned int maxLineLength, string helpText="");	// Constructor with parameters

	/**************************************************************
	* Getters
	***************************************************************/
	
	/**
	* elementList *getElementList() - get pointer to ElementList
	* Input:
	*	[NONE]
	* Output:
	*	(elementList*) pointer to ElementList object
	*/
	elementList *getElementList() {return element;}
	
	/**
	* unsigned int getRows() - get number of rows of workdesk
	* Input:
	*	[NONE]
	* Output:
	*	(unsigned int) number of rows of workdesk
	*/
	unsigned int getRows() {return deskRows;}
	
	/** 
	* unsigned int getColumns() - get number of columns of workdesk
	* Input:
	*	[NONE]
	* Output:
	*	(unsigned int) number of columns of workdesk
	*/
	unsigned int getColumns() {return deskColumns;}
	
	/**
	* unsigned int getMaxLineLength() - get maximal length of line
	* Input:
	*	[NONE]
	* Output:
	*	(unsigned int) maximal length of line
	*/
	unsigned int getMaxLineLength() {return maxLineLength;}
	
	/**
	* unsigned int getMenuLines() - get number of lines of menu
	* Input:
	*	[NONE]
	* Output:
	*	(unsigned int) number of lines of menu
	*/
	unsigned int getMenuLines() {return menuLines;}
	
	/**
	* vector<vector<char> > getDesk() - get content of workdesk
	* Input:
	*	[NONE]
	* Output:
	*	(vector<vector<char> >) content of workdesk
	*/
	vector<vector<char> > getDesk() {return desk;}
	
	/**
	* bool checkDrawContinous() - check if actual mode is "continous" mode
	* Input:
	*	[NONE]
	* Output:
	*	(bool) true if "continous" is enabled, else false
	*/
	bool checkDrawContinous() {return drawContinous;}
	
	/**
	* string getHelpText() - get content of Help Text
	* Input:
	*	[NONE]
	* Output:
	*	(string) content of Help Text
	*/
	string getHelpText() { return helpText; }


	/**
	* void setElementList(elementList *element)
	* Input:
	*	elementList *element - pointer to elementList
	* Output:
	*	[NONE]
	*/
	void setElementList(elementList *element) {this->element = element;}
	
	/**
	* void setRows(unsigned int rows) - set number of rows of workdesk
	* Input:
	*	unsigned int rows - number of rows
	* Output:
	*	[NONE]
	*/
	void setRows(unsigned int rows) {deskRows = rows;}
	
	/**
	* void setColumns(unsigned int columns) - set number of columns of workdesk
	* Input:
	*	unsigned int columns - number of columns
	* Output:
	*	[NONE]
	*/
	void setColumns(unsigned int columns) {deskColumns = columns;}
	
	/**
	* void setDimensions(unsigned int rows, unsigned int columns) - set dimensions of workdesk
	* Input:
	*	unsigned int rows - number of rows
	*	unsigned int columns - number of columns
	* Output:
	*	[NONE]
	*/
	void setDimensions(unsigned int rows, unsigned int columns) {
		setRows(rows);
		setColumns(columns);
	}
	
	/**
	* void setMaxLineLength(unsigned int value) - set max line length
	* Input:
	*	unsigned int value - desired value of maxLineLength variable
	* Output:
	*	[NONE]
	*/
	void setMaxLineLength(unsigned int value) {maxLineLength = value;}
	
	/**
	* void setMenuLines(unsigned int value) - set menuLines property
	* Input:
	*	unsigned int value - desired value of menuLines variable
	* Output:
	*	[NONE]
	*/
	void setMenuLines(unsigned int value) {menuLines = value;}
	
	/**
	* void setDesk(vector<vector<char> > desk) - set content of work desk
	* Input:
	*	vector<vector<char> > desk - content of work desk
	* Output:
	*	[NONE]
	*/
	void setDesk(vector<vector<char> > desk) {this->desk = desk;}
	
	/**
	* void setDrawContinous(bool mode) - set DrawContinous flag
	* Input:
	*	bool mode - value of flag
	* Output:
	*	[NONE]
	*/
	void setDrawContinous(bool mode) {drawContinous = mode;}
	
	/**
	* void setHelpText(string helpText) - set help text
	* Input:
	*	string helpText - content of help text
	* Output:
	*	[NONE]
	*/
	void setHelpText(string helpText) { this->helpText = helpText; }
};