#include "stdafx.h"

#pragma once

// Parameterless constructor
deskInfo::deskInfo() {
	setDimensions(0, 0);
	setMaxLineLength(0);
	setMenuLines(0);
	setDrawContinous(false);
	setHelpText('\0');
}

// Constructor with parameters
deskInfo::deskInfo(elementList *element, unsigned int rows, unsigned int columns, unsigned int maxLineLength, string helpText) {
	setElementList(element);
	setDimensions(rows, columns);
	setMaxLineLength(maxLineLength);
	setDrawContinous(false);
	setHelpText(helpText);
}