#include "stdafx.h"

#pragma once

class elementList {
private:
	string name;	// Name of element
	char sign;		// String representating element on screen
	bool userSpecified;	// Flag - 0 if element exist from beggining, 1 if element is added by user
	elementList *next, *prev;	// Pointers to next and previous elements - cyclic list

public:
	// Constructors
	elementList();
	elementList(string name, char sign, elementList *elementOfExistingList=NULL, bool userSpecified=false);
	// Desctructor
	~elementList();

	/**************************************************************
	* Setters
	***************************************************************/

	/**
	* void setName(string name) - set name of actual element
	* Input:
	*	string name - name for actual element
	* Output:
	*	[NONE]
	**/
	void setName(string name) {this->name = name;}
	
	/**
	* void setSign(char sign)
	* Input:
	*	char sing - sign for actual element
	* Output:
	*	[NONE]
	**/
	void setSign(char sign) {this->sign = sign;}
	
	/**
	* void setSign(int sign) - set sign for current element
	* Input:
	*	int sign - sign for actual element in decimal form
	* Output:
	*	[NONE]
	**/
	void setSign(int sign) {this->sign = char(sign);}
	
	/**
	* void setNext(elementList *next) - set next element
	* Input:
	*	elementList *next - pointer to next element
	* Output:
	*	[NONE]
	**/
	void setNext(elementList *next) {this->next = next;}
	
	/**
	* void setPrev(elementList *next) - set prev element
	* Input:
	*	elementList *prev - pointer to prev element
	* Output:
	*	[NONE]
	**/
	void setPrev(elementList *prev) {this->prev = prev;}
	
	/**
	* void setUserSpecified(bool userSpecified)
	* Input:
	*	bool userSpecified - flag to set
	* Output:
	*	[NONE]
	**/
	void setUserSpecified(bool userSpecified) {this->userSpecified = userSpecified;}
	
	/**
	* void setElement(string name, char sign, elementList *next, elementList *prev, bool userSpecified=false) - setting all 
	* variables of class in one method
	* Input:
	*	string name - name of element
	*	char sign - sign of element
	*	elementList *next - pointer to next element of list
	*	elementList *prev - pointer to prev element of list
	*	bool userSpecified - flag describing if element is added by user
	* Output:
	*	[NONE]
	**/
	void setElement(string name, char sign, elementList *next, elementList *prev, bool userSpecified=false) {
		setName(name);
		setSign(sign);
		setNext(next);
		setPrev(prev);
		setUserSpecified(userSpecified);
	}

	/**************************************************************
	* Getters
	***************************************************************/

	/**
	* string getName() - get name of actual element
	* Input:
	*	[NONE]
	* Output:
	*	(string) name of actual element
	**/
	string getName() {return name;}

	/**
	* string getNSign() - get sign of actual element
	* Input:
	*	[NONE]
	* Output:
	*	(string) sign of actual element
	**/
	char getSign() {return sign;}

	/**
	* string getnext() - get pointer to next element
	* Input:
	*	[NONE]
	* Output:
	*	(elementList*) Pointer to next element
	**/
	elementList* getNext() {return next;}

	/**
	* string getPrev() - get pointer to previous element
	* Input:
	*	[NONE]
	* Output:
	*	(elementList*) Pointer to previous element
	**/
	elementList* getPrev() {return prev;}

	/**
	* string getUserSpecified() - get content of userSpecified flag
	* Input:
	*	[NONE]
	* Output:
	*	(bool) Content of userSpecified flag
	**/
	bool getUserSpecified() {return userSpecified;}

	/**
	* bool isOnList(string name) - function checking if element with given name exists on list
	* Input:
	*	string name - name to check
	* Output:
	*	(true) if element exists on list
	*	(false) if element doesn't exists
	**/
	bool isOnList(string name) {
		elementList *actual;

		actual = this;
		do {			
			if (actual->getName() == name) return true;
			actual = actual->getNext();
		} while(actual != this);
		return false;
	}
	
	/**
	* bool isOnList(string name) - function checking if element with given name exists on list
	* Input:
	*	string name - name to check
	* Output:
	*	(true) if element exists on list
	*	(false) if element doesn't exists
	**/
	bool isOnList(char sign) {
		elementList *actual;

		actual = this;
		do {			
			if (actual->getSign() == sign) return true;
			actual = actual->getNext();
		} while(actual != this);
		return false;
	}
};