#include "stdafx.h"

#pragma once

// Parameterless constructor
elementList::elementList() {
	setElement("", '\0', this, this);
}

// Constructor with parameters
elementList::elementList(string name, char sign, elementList *elementOfExistingList, bool userSpecified) {
	if (elementOfExistingList == NULL)
	{
		setElement(name, sign, this, this, userSpecified);
	}
	else
	{
		elementList *next = elementOfExistingList->getNext();
		elementOfExistingList->setNext(this);
		next->setPrev(this);
		
		setElement(name, sign, next, elementOfExistingList, userSpecified);		
	}
}

// Descructor
elementList::~elementList() {
	
}