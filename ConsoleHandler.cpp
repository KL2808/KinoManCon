#include "ConsoleHandler.h"

#include <windows.h>
#include <iostream>
#include <conio.h>
#include <vector>

#include "CustomersDB.h"
#include "MoviesDB.h"
#include "CinemasDB.h"

#include "Colors.h"

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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),Colors::WHITE); //inspiration from: https://www.daniweb.com/programming/software-development/code/216345/add-a-little-color-to-your-console-text
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
			Write(res == i ? "@" : " ", false, Colors::LIGHTCYAN);
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
	Clear();
	const std::vector<std::string> addItemsMenuItems =
	{
		"Customer",
		"Movie",
		"Cinema"
	};
	switch (ListSelection("Show items menu\nPlease select the item-group you want to show:", addItemsMenuItems))
	{
	case -1:
		MainMenu();
		break;
	case 0:
		ShowCustomers();
		break;
	case 1:
		ShowMovies();
		break;
	case 2:
		ShowCinemas();
		break;
	}
}

void ConsoleHandler::BookingWizard()
{

}

void ConsoleHandler::ShowWizard()
{

}

void ConsoleHandler::AddCustomer()
{
	CustomersDB customersDB("C:\\x.temp\\customers.kmd");
	std::string name = ReadString("Please enter the customers name: ", Colors::WHITE);
	DateTime birthday =
	{
		ReadInt("Please enter the customers birthday day: ", Colors::WHITE),
		ReadInt("Please enter the customers birthday month: ", Colors::WHITE),
		ReadInt("Please enter the customers birthday year: ", Colors::WHITE),
		0,
		0
	};
	customersDB.Add(name, birthday);

	AddItemsMenu();
}

void ConsoleHandler::AddMovie()
{
	MoviesDB moviesDB("C:\\x.temp\\movies.kmd");
	std::string name = ReadString("Please enter the movies name: ", Colors::WHITE);
	std::string info = ReadString("Please enter the movies info: ", Colors::WHITE);
	moviesDB.Add(name, info);

	AddItemsMenu();
}

void ConsoleHandler::AddCinema()
{
	CinemasDB cinemasDB("C:\\x.temp\\cinemas.kmd");
	std::string name = ReadString("Please enter the cinemas name: ", Colors::WHITE);
	int rows = ReadInt("Please enter the number of rows the cinema has: ", Colors::WHITE);
	std::vector<int> seats;

	for (int i = 0; i < rows; i++) 
	{
		seats.push_back(ReadInt("Please enter the number of seats that row " + std::to_string(i + 1) + " has: ", Colors::WHITE));
	}

	cinemasDB.Add(name, seats);

	AddItemsMenu();
}

void ConsoleHandler::ShowCustomers()
{
	Write("Customers", true, Colors::LIGHTGREEN);
	Write("ID: [Name; DD.MM.YYYY]\n", true, Colors::LIGHTGREEN);
	CustomersDB customersDB("C:\\x.temp\\customers.kmd");
	for (int i = 0; i < customersDB.customers.size(); i++)
	{
		Write(
			std::to_string(customersDB.customers[i].id) + ": [" +
			customersDB.customers[i].name + "; " + 
			std::to_string(customersDB.customers[i].birthday.day) + "." +
			std::to_string(customersDB.customers[i].birthday.month) + "." +
			std::to_string(customersDB.customers[i].birthday.year) + "]"
		);
	}
	_getch();
	ShowItemsMenu();
}

void ConsoleHandler::ShowMovies()
{
	Write("Movies", true, Colors::LIGHTGREEN);
	Write("ID: [Name; Info]\n", true, Colors::LIGHTGREEN);
	MoviesDB moviesDB("C:\\x.temp\\movies.kmd");
	for (int i = 0; i < moviesDB.movies.size(); i++)
	{
		Write(
			std::to_string(moviesDB.movies[i].id) + ": [" +
			moviesDB.movies[i].name + "; " +
			moviesDB.movies[i].info + "]"
		);
	}
	_getch();
	ShowItemsMenu();
}

void ConsoleHandler::ShowCinemas()
{
	Write("Cinemas", true, Colors::LIGHTGREEN);
	Write("ID: [Name; Seats]\n", true, Colors::LIGHTGREEN);
	CinemasDB cinemasDB("C:\\x.temp\\cinemas.kmd");
	for (int i = 0; i < cinemasDB.cinemas.size(); i++)
	{
		int seats = 0;
		for (int e = 0; e < cinemasDB.cinemas[i].seats.size(); e++) seats += cinemasDB.cinemas[i].seats[e];
		Write(
			std::to_string(cinemasDB.cinemas[i].id) + ": [" +
			cinemasDB.cinemas[i].name + "; " +
			std::to_string(seats) + "]"
		);
	}
	_getch();
	ShowItemsMenu();
}