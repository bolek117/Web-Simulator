// 20120511_webSimulatorCMD_V1.3.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#define DEBUG 0
#define LEAK 0

#if LEAK
// Visual Leak Detector in folder C:\Program Files (x86)\Visual Leak Detector needed
#include <vld.h>
#endif


int main()
{
	int key;	// Current key
	unsigned int menuLines, rowInTable, tmpX, tmpY;
	string buffer;
	vector<vector <char> > desk;	// vector holding whole work desk data in form [row][column] (for line by line reading)
	bool drawContinuously=false;
	
	elementList *element;	// Create pointer to elementList object (object is in form of cyclic list)
	element = new elementList("Computer", 'C');				//
	element = new elementList("Printer", 'P', element);		//
	element = new elementList("Router", 'R', element);		// 
	element = new elementList("Server", 'S', element);		// Fill list with 
	element = new elementList("PLC", char(219), element);	// prefefinied elements
	element = new elementList("Eraser", ' ', element);		//
	element = new elementList("Node", char(197), element);	//
	element = new elementList("Wire", char(196), element);	//

	cursor mainCursor(0, 0);	// Create cursor object with coords 0, 0
	cursor tmpCursor;	// Create cursor object to hold temproary locations

	stringstream helpText;	// stringstream holding content of help dialog
	helpText << "Key\tAction\n\n" <<
				"[ESC]\tClose this window\n" <<
				"[PG UP]\tSelect next element from list\n" <<
				"[PG DN]\tSelect prev element from list\n" <<
				"[INS]\tAdd new element to list\n" <<
				"[L]\tList of all elements on list\n" <<
				"[SPACE]\tPut actual element/draw wire\n" <<
				"[F5]\tRefresh desk\n" <<
				"Arrows\tNavigate on desk\n" <<
				"[+]/[-]\tResize desk\n" <<
				"[S]\tSave diagram to file\n" <<
				"[H]\tThis window";
	deskInfo *info;	// Create pointer to deskInfo object holding all important informations about actual work desk
	info = new deskInfo(element, START_DESKROWS, checkColumns(), ELEMENTBOXMAXLENGHT, helpText.str());	// Created in form of pointer because of using in many functions calls

	// fill vector with ' '
	for (unsigned int i=0;i<info->getRows();i++)	
	{
		vector<char> row;
		desk.push_back(row);
		for (unsigned int j=0;j<info->getColumns();j++) desk[i].push_back(' ');
	}

	info->setDesk(desk);
	menuLines = menu(info);
	info->setMenuLines(menuLines);
	mainCursor.moveToXY(0, menuLines);

	cout << element->getSign();
	mainCursor.move(-1,0);

#if DEBUG
	//desk[5][10] = '@';	// for padding testing purposes
#endif

	while(true)
	{
		tmpCursor.update();
		key = _getch();	// get key from user

		// exit from application handle
		if (key == ESC)
		{	
			msgBox("Really want to quit?\n\n[ENTER] Yes\n[ESC] No", info);
			do
			{
				key = _getch();
				if (key == ESC)
				{	// refresh work desk and move cursor to position from before the operation
					tmpCursor.moveToStoredXY();
					refreshDesk(info);					
				} 
				else if (key == ENTER)
				{	// quit from application
					destroyAll(info);
					return 0;
				}
			} while(key != ESC);
		}
		// F1-F12 chord start
		else if (key == F_START)
		{	
			key = _getch();
			if (key == F_5) refreshDesk(info);
		}
		// Special keys chord start
		else if (key == S_START)
		{
			key = _getch();
			if (isArrowKey(key))
			{
				tmpCursor.moveToStoredXY();
				rowInTable = mainCursor.getActualY()-info->getMenuLines();
				if (element->getName() == "Wire" && info->checkDrawContinous() == true)
				{
					// tworzenie zakrêtów
					if ((element->getSign() == char(196) && (key == S_UP || key == S_DOWN)) || 
						(element->getSign() == char(179) && (key == S_LEFT || key == S_RIGHT))) 
					{
						desk[mainCursor.getActualY()-info->getMenuLines()][mainCursor.getActualX()] = char(197);
						cout << char(197);
					}
					else cout << element->getSign();
				}
				else
				{
					cout << desk[rowInTable][mainCursor.getActualX()];
				}
				
				if (mainCursor.getActualY() == tmpCursor.getY()) mainCursor.move(-1, 0);
				else tmpCursor.moveToStoredXY();

				if (key == S_UP && rowInTable > 0) mainCursor.move(0, -1);
				else if (key == S_DOWN && rowInTable < info->getRows()-1) mainCursor.move(0, 1);
				else if (key == S_LEFT && mainCursor.getActualX() > 0) mainCursor.move(-1, 0);
				else if (key == S_RIGHT && mainCursor.getActualX() < info->getColumns()) 
				{
					mainCursor.move(1, 0);
				}

				if (element->getName() == "Wire")
				{
					if (key == S_RIGHT || key == S_LEFT) element->setSign(196);
					else element->setSign(179);

					// wires padding
					if (mainCursor.getActualY() > info->getMenuLines() && mainCursor.getActualY() < info->getMenuLines()+info->getRows()-1 && mainCursor.getActualX() > 0 && mainCursor.getActualX() < info->getColumns()-1)
					{
						tmpX = mainCursor.getActualX();
						tmpY = mainCursor.getActualY()-info->getMenuLines();
						if ((desk[tmpY][tmpX+1] != ' ' && desk[tmpY][tmpX+1] != element->getSign()) || (desk[tmpY][tmpX-1] != ' ' && desk[tmpY][tmpX-1] != element->getSign()))
						{
							element->setSign(196);
						}
						else if ((desk[tmpY+1][tmpX] != ' ' && desk[tmpY+1][tmpX] != element->getSign()) || (desk[tmpY-1][tmpX] != ' ' && desk[tmpY-1][tmpX] != element->getSign()))
						{
							element->setSign(179);
						}
					}

					if (info->checkDrawContinous() == true) desk[mainCursor.getActualY()-info->getMenuLines()][mainCursor.getActualX()] = element->getSign();
				}

				if (mainCursor.getActualY() <= info->getColumns()) {
					cout << element->getSign();

					tmpCursor.moveToStoredXY();
					mainCursor.update();
					if (key == S_RIGHT) mainCursor.move(1, 0);
					else if (key == S_UP && mainCursor.getActualY() > info->getMenuLines()) {
							mainCursor.move(0,-1);
					}
					else if (key == S_DOWN && mainCursor.getActualY() < info->getRows()+info->getMenuLines()-1) mainCursor.move(0,1);
					else mainCursor.move(-1, 0);
				}
				else mainCursor.move(-1, 0);

				// Hotfix for columns skipping bug
				if (((key == S_UP && tmpCursor.getY() == info->getMenuLines()) || (key == S_DOWN && tmpCursor.getY() == info->getMenuLines()+info->getRows()-1)) && tmpCursor.getX() != 0) tmpCursor.move(1,0);
			} 
			else if (key == S_PGUP || key == S_PGDN)
			{
				if (key == S_PGUP) element = element->getNext();
				else element = element->getPrev();

				info->setElementList(element);
				menu(info, true);
				cout << element->getSign();
				mainCursor.move(-1, 0);
			}
			else if (key == S_INSERT)
			{
				addElement(info);
				refreshDesk(info);
			}
#if DEBUG
			else
			{

				cout << "S" << setw(3) << key;
				mainCursor.move(-4, 0);
			}
#endif
		}
		else
		{
			if ((key == PLUS && info->getRows() < 100) || (key == MINUS && info->getRows() > 5))
			{
				clearArea(info->getColumns(), 1, 0, info->getMenuLines()+info->getRows());
				if (key == PLUS)
				{
					info->setRows(info->getRows()+1);
					vector <char> row;
					desk.push_back(row);
					for (unsigned int i=0;i<info->getColumns();i++) desk[info->getRows()-1].push_back(' ');
				}
				else
				{
					info->setRows(info->getRows()-1);
					for (unsigned int i=0;i<info->getColumns();i++) desk[info->getRows()].pop_back();
					desk.pop_back();
				}

				menu(info, true);
				printLineAt(info->getMenuLines()+info->getRows());
				mainCursor.moveToXY(0,0);
				tmpCursor.moveToStoredXY();
			}
			else if (key == SPACE)
			{
				if (element->getName() == "Wire")
				{
					if (info->checkDrawContinous() == false) {
						desk[mainCursor.getActualY()-info->getMenuLines()][mainCursor.getActualX()] = element->getSign();
						info->setDrawContinous(true);
					}
					else info->setDrawContinous(false);

					menu(info);
				}
				else 
				{
					info->setDrawContinous(false);
					desk[mainCursor.getActualY()-info->getMenuLines()][mainCursor.getActualX()] = element->getSign();
					cout << element->getSign();
					mainCursor.move(-1, 0);
				}
			}
			else if (key == 'h' || key == 'H') showHelpDialog(info);
			else if (key == 'l' || key == 'L') showElementList(info);
			else if (key == 's' || key == 'S') showSaveToFileDialog(info);
#if DEBUG
			else 
			{

				// Show keycode of pressed button
				cout << setw(3) << key;
				mainCursor.move(-3, 0);
			}
#endif
		}

		info->setDesk(desk);
	}
	return 0;
}