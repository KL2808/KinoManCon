#include "ConsoleHandler.h"

#include <windows.h>   // WinApi header
#include <iostream>

//inspiration from: https://www.daniweb.com/programming/software-development/code/216345/add-a-little-color-to-your-console-text

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
	std::cout << string;
}

void ConsoleHandler::WritePredefined(int messageId) 
{

}