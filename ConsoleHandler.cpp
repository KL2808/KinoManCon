#include "ConsoleHandler.h"

#include <windows.h>
#include <iostream>
#include <conio.h>
#include <vector>

#include "CustomersDB.h"
#include "MoviesDB.h"
#include "CinemasDB.h"

#include "StringTools.cpp"

void ConsoleHandler::Clear() 
{
	system("cls");
}

void ConsoleHandler::Write(std::string string)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //inspiration from: https://www.daniweb.com/programming/software-development/code/216345/add-a-little-color-to-your-console-text
	std::cout << string << "\n";
}

void ConsoleHandler::Write(std::string string, bool endl)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15); //inspiration from: https://www.daniweb.com/programming/software-development/code/216345/add-a-little-color-to-your-console-text
	std::cout << string << (endl ? "\n" : "");
}

void ConsoleHandler::Write(std::string string, bool endl, int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); //inspiration from: https://www.daniweb.com/programming/software-development/code/216345/add-a-little-color-to-your-console-text
	std::cout << string << (endl ? "\n" : "");
}

std::string ConsoleHandler::ReadString(std::string string, int color)
{
	Write(string, false, color);
	std::string input;
	std::getline(std::cin, input);
	return input;
}

int ConsoleHandler::ReadInt(std::string string, int color)
{
	std::string input;
	do 
	{
		Write(string, false, color);
		std::getline(std::cin, input);
	} while (!isInt(input));
	return atoi(input.c_str());
}

int ConsoleHandler::ListSelection(std::string title, std::vector<std::string> items) //TODO: Cleanup
{
	int ascii = 0;
	int res = 0;
	do
	{
		Write(title + "\n");

		for (int i = 0; i < items.size(); i++) 
		{
			Write("[", false);
			Write(res == i ? "@" : " ", false, 10);
			Write("] : " + items[i]);
		}

		Write("\n[arrow_up] : up | [arrow_down] : down\n[enter] : select | [esc] : back");

		ascii = (int)_getch();

		ascii == 72 && res != 0 ? res-- : ascii == 80 && res != items.size() - 1 ? res++ : res; //idk y but i <3 this line

		Clear();

		if (ascii == 27) return -1;

	} while (ascii != 13);

	return res;
}

void ConsoleHandler::MainMenu()
{
	Clear();
	const std::vector<std::string> mainMenuItems =
	{
		"Add new items",
		"Show existing items",
		"Start booking Wizard",
		"Settings",
	};
	switch (ListSelection("Main menu\nPlease select an item:", mainMenuItems))
	{
	case 0:
		AddItemsMenu();
		break;
	case 1:
		ShowItemsMenu();
		break;
	case 2:
		BookingWizard();
		break;
	case 3:
		break;
	}
}

void ConsoleHandler::AddItemsMenu()
{
	Clear();
	const std::vector<std::string> addItemsMenuItems =
	{
		"Customer",
		"Movie",
		"Cinema"
	};
	switch (ListSelection("Add item menu\nPlease select the item you want to add:", addItemsMenuItems))
	{
	case -1:
		MainMenu();
		break;
	case 0:
		AddCustomer();
		break;
	case 1:
		AddMovie();
		break;
	case 2:
		AddCinema();
		break;
	}
}

void ConsoleHandler::ShowItemsMenu()
{

}

void ConsoleHandler::BookingWizard()
{

}

void ConsoleHandler::ShowWizard()
{

}

void ConsoleHandler::AddCustomer()
{
	CustomersDB customersDB("C:\\_src\\x_temp_files\\customers.kmd");
	std::string name = ReadString("Please enter the customers name: ", 15);
	DateTime birthday =
	{
		ReadInt("Please enter the customers birthday day: ", 15),
		ReadInt("Please enter the customers birthday month: ", 15),
		ReadInt("Please enter the customers birthday year: ", 15),
		0,
		0
	};
	customersDB.Add(name, birthday);

	AddItemsMenu();
}

void ConsoleHandler::AddMovie()
{
	MoviesDB moviesDB("C:\\_src\\x_temp_files\\movies.kmd");
	std::string name = ReadString("Please enter the movies name: ", 15);
	std::string info = ReadString("Please enter the movies info: ", 15);
	moviesDB.Add(name, info);

	AddItemsMenu();
}

void ConsoleHandler::AddCinema()
{
	CinemasDB cinemasDB("C:\\_src\\x_temp_files\\cinemas.kmd");
	std::string name = ReadString("Please enter the cinemas name: ", 15);
	int rows = ReadInt("Please enter the number of rows the cinema has: ", 15);
	std::vector<int> seats;

	for (int i = 0; i < rows; i++) 
	{
		seats.push_back(ReadInt("Please enter the number of seats that row " + std::to_string(i + 1) + " has: ", 15));
	}

	cinemasDB.Add(name, seats);

	AddItemsMenu();
}