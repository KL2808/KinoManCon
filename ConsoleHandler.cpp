#include "ConsoleHandler.h"

#include <windows.h>   // WinApi header
#include <iostream>
#include <conio.h>
#include <vector>

//inspiration from: https://www.daniweb.com/programming/software-development/code/216345/add-a-little-color-to-your-console-text

void ConsoleHandler::Clear() 
{
	system("cls");
}

void ConsoleHandler::Write(std::string string)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //15 = bright white; 12 = nice red
	std::cout << string << "\n";
}

void ConsoleHandler::Write(std::string string, bool endl)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15); 
	std::cout << string << (endl ? "\n" : "");
}

void ConsoleHandler::Write(std::string string, bool endl, int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	std::cout << string << (endl ? "\n" : "");
}

void ConsoleHandler::WritePredefined(int messageId) 
{

}

int ConsoleHandler::ListSelection(std::string title, std::vector<std::string> items) //TODO: Cleanup
{
	int ascii = 0;
	int res = 0;
	do
	{
		Write(title);
		for (int i = 0; i < items.size(); i++) 
		{
			Write("[", false);
			Write(res == i ? "@" : " ", false, 10);
			Write("] : " + items[i]);
		}

		ascii = (int)_getch();

		ascii == 72 && res != 0 ? res-- : ascii == 80 && res != items.size() - 1 ? res++ : res; //idk y but i <3 this line

		Clear();

		if (ascii == 27) return -1;

	} while (ascii != 13);

	return res;
}