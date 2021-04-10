#include "ConsoleHandler.h"

#include <windows.h>
#include <iostream>
#include <conio.h>
#include <vector>

#include "CustomersDB.h"
#include "MoviesDB.h"
#include "CinemasDB.h"
#include "ShowsDB.h"
#include "BookingsDB.h"

#include "Coordinates.h"
#include "Colors.h"
#include "Keys.h"

#include "StringTools.cpp"

void ConsoleHandler::Clear() 
{
	system("cls");
}

void ConsoleHandler::Write(std::string string, bool endl = true, int color = Colors::WHITE)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); //inspiration from: https://www.daniweb.com/programming/software-development/code/216345/add-a-little-color-to-your-console-text
	std::cout << string << (endl ? "\n" : "");
}

std::string ConsoleHandler::ReadString(std::string string, int color = Colors::WHITE)
{
	Write(string, false, color);
	std::string input;
	std::getline(std::cin, input);
	return input;
}

int ConsoleHandler::ReadInt(std::string string, int color = Colors::WHITE)
{
	std::string input;
	do 
	{
		Write(string, false, color);
		std::getline(std::cin, input);
	} while (!isInt(input));
	return atoi(input.c_str());
}

int ConsoleHandler::ListSelection(std::string title, std::vector<std::string> items, int titleColor = Colors::WHITE)
{
	int ascii = 0;
	int selection = 0;
	do
	{
		Write(title + "\n", true, titleColor);

		for (int i = 0; i < items.size(); i++)
		{
			Write("[", false);
			Write(selection == i ? "@" : " ", false, Colors::LIGHTCYAN);
			Write("] : " + items[i]);
		}

		Write("\n[arrow_up]   : up     | [arrow_down]   : down\n[enter]      : select | [esc]          : back");

		ascii = (int)_getch();

		switch (ascii)
		{
		case Keys::UP:
			selection != 0 ? selection-- : 0;
			break;
		case Keys::DOWN:
			selection != items.size() - 1 ? selection++ : 0;
			break;
		case Keys::ESC:
			return -1;
			break;
		}

		Clear();

	} while (ascii != Keys::ENTER);

	return selection;
}

Coordinates ConsoleHandler::MatrixSelection(std::string title, std::vector<int> matrix, std::vector<Coordinates> blockedPoints = {}, int titleColor = Colors::WHITE)
{
	int ascii = 0;
	bool selectionBlocked = false;
	Coordinates selection = { 0, 0 };

	do
	{
		selectionBlocked = false;

		Write(title + "\n", true, titleColor);

		for (int y = 0; y < matrix.size(); y++)
		{
			Write(std::to_string(y) + " | ", false, Colors::YELLOW);
			for (int x = 0; x < matrix[y]; x++)
			{
				bool blockDrawing = false;
				for (int i = 0; i < blockedPoints.size(); i++) //Check if coordinate is blocked allready
				{
					if (x == blockedPoints[i].x && y == blockedPoints[i].y)
					{
						if (x == selection.x && y == selection.y) Write("@ ", false, Colors::LIGHTRED);
						else Write("X ", false, Colors::LIGHTMAGENTA);
						blockDrawing = true;
					}
					if (selection.x == blockedPoints[i].x && selection.y == blockedPoints[i].y) selectionBlocked = true;
				}
				if (x == selection.x && y == selection.y && !blockDrawing) Write("@ ", false, Colors::LIGHTCYAN);
				else if(!blockDrawing) Write("U ", false);
			}
			Write("");
		}
		Write("\nRow: " + std::to_string(selection.y) + ", Seat :" + std::to_string(selection.x), true, Colors::LIGHTCYAN);

		Write("\n[arrow_up]   : up     | [arrow_down]   : down\n[arrow_left] : left   | [arrow_rightn] : right\n[enter]      : select | [esc]          : back");

		ascii = (int)_getch();

		switch (ascii)
		{
		case Keys::UP:
			selection.y != 0 ? selection.y-- : 0;
			break;
		case Keys::DOWN:
			selection.y != matrix.size() - 1 ? selection.y++ : 0;
			break;
		case Keys::LEFT:
			selection.x != 0 ? selection.x-- : 0;
			break;
		case Keys::RIGHT:
			selection.x != matrix[selection.y] - 1 ? selection.x++ : 0;
			break;
		case Keys::ESC:
			return {-1, -1};
			break;
		}


		Clear();

		if (ascii == 27) return { -1, -1 };
		else if (selectionBlocked) ascii = 0; //overwrites ascii if selection is blocked, so enter dont escapes the loop

	} while (ascii != 13);

	return selection;
}

#pragma region main menues

void ConsoleHandler::MainMenu()
{
	int endManCon = false;
	do
	{
		Clear();
		const std::vector<std::string> mainMenuItems =
		{
			"Add items",
			"Show items",
			"Booking Wizard",
			"Delete items",
		};
		switch (ListSelection("Main menu\nPlease select an item:", mainMenuItems))
		{
		case -1:
			endManCon = true;
			break;
		case 0:
			AddItemsMenu();
			break;
		case 1:
			ShowItemsMenu();
			break;
		case 2:
			AddBooking();
			break;
		case 3:
			DeleteItemsMenu();
			break;
		}
	} while (!endManCon);
}

void ConsoleHandler::AddItemsMenu()
{
	int backToMainMenu = false;
	do
	{
		Clear();
		const std::vector<std::string> addItemsMenuItems =
		{
			"Customer",
			"Movie",
			"Cinema",
			"Show"
		};
		switch (ListSelection("Add item menu\nPlease select the item you want to add:", addItemsMenuItems))
		{
		case -1:
			backToMainMenu = true;
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
		case 3:
			AddShow();
			break;
		}
	} while (!backToMainMenu);
}

void ConsoleHandler::ShowItemsMenu()
{
	int backToMainMenu = false;
	do
	{
		Clear();
		const std::vector<std::string> showItemsMenuItems =
		{
			"Customer",
			"Movie",
			"Cinema",
			"Shows",
			"Bookings"
		};
		switch (ListSelection("Show items menu\nPlease select the item group you want to show:", showItemsMenuItems))
		{
		case -1:
			backToMainMenu = true;
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
		case 3:
			ShowShows();
			break;
		case 4:
			ShowBookings();
			break;
		}
	} while (!backToMainMenu);
}

void ConsoleHandler::DeleteItemsMenu()
{
	int backToMainMenu = false;
	do
	{
		Clear();
		const std::vector<std::string> deleteItemsMenuItems =
		{
			"Customer",
			"Movie",
			"Cinema",
			"Shows",
			"Bookings"
		};
		switch (ListSelection("Delete items menu\nPlease select the item group in which you want to delete an item:", deleteItemsMenuItems))
		{
		case -1:
			backToMainMenu = true;
			break;
		case 0:
			DeleteCustomer();
			break;
		case 1:
			DeleteMovie();
			break;
		case 2:
			DeleteCinema();
			break;
		case 3:
			DeleteShow();
			break;
		case 4:
			DeleteBooking();
			break;
		}
	} while (!backToMainMenu);
}

#pragma endregion

#pragma region adding items

void ConsoleHandler::AddCustomer()
{
	CustomersDB customersDB("C:\\x.temp\\customers.kmcf");
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
}

void ConsoleHandler::AddMovie()
{
	MoviesDB moviesDB("C:\\x.temp\\movies.kmcf");
	std::string name = ReadString("Please enter the movies name: ", Colors::WHITE);
	std::string info = ReadString("Please enter the movies info: ", Colors::WHITE);
	moviesDB.Add(name, info);
}

void ConsoleHandler::AddCinema()
{
	CinemasDB cinemasDB("C:\\x.temp\\cinemas.kmcf");
	std::string name = ReadString("Please enter the cinemas name: ", Colors::WHITE);
	int rows = ReadInt("Please enter the number of rows the cinema has: ", Colors::WHITE);
	std::vector<int> seats;

	for (int i = 0; i < rows; i++) 
	{
		seats.push_back(ReadInt("Please enter the number of seats that row " + std::to_string(i + 1) + " has: ", Colors::WHITE));
	}

	cinemasDB.Add(name, seats);
}

void ConsoleHandler::AddBooking()
{
	std::vector<std::string> listOfCustomers;
	std::vector<std::string> listOfShows;
	std::vector<std::string> listOfCinemas;

	ShowsDB showsDB("C:\\x.temp\\shows.kmcf");
	MoviesDB moviesDB("C:\\x.temp\\movies.kmcf");
	CinemasDB cinemasDB("C:\\x.temp\\cinemas.kmcf");
	BookingsDB bookingsDB("C:\\x.temp\\bookings.kmcf");
	CustomersDB customersDB("C:\\x.temp\\customers.kmcf");

	int customerId;
	int showId;
	int cinemaId;
	std::string cinemaName;
	std::vector<int> cinemaSeats;
	std::vector<Coordinates> blockedSeats;

	for (int i = 0; i < showsDB.shows.size(); i++)
	{
		std::string movieName;
		for (int e = 0; e < moviesDB.movies.size(); e++)
		{
			if (moviesDB.movies[e].id == showsDB.shows[i].movieId) movieName = moviesDB.movies[e].name;
		}

		for (int e = 0; e < cinemasDB.cinemas.size(); e++)
		{
			if (cinemasDB.cinemas[e].id == showsDB.shows[i].cinemaId)
			{
				cinemaId = cinemasDB.cinemas[e].id;
				cinemaName = cinemasDB.cinemas[e].name;
				cinemaSeats = cinemasDB.cinemas[e].seats;
			}
		}

		listOfShows.push_back(
			std::to_string(showsDB.shows[i].id) + ": [" +
			movieName + "; " +
			cinemaName + "; " +
			std::to_string(showsDB.shows[i].startTime.day) + "." +
			std::to_string(showsDB.shows[i].startTime.month) + "." +
			std::to_string(showsDB.shows[i].startTime.year) + " " +
			std::to_string(showsDB.shows[i].startTime.hours) + ":" +
			std::to_string(showsDB.shows[i].startTime.minutes) + "]"
		);
	}

	int selectedShow = ListSelection("Please select a show:", listOfShows);
	if (selectedShow == -1) return;

	showId = showsDB.shows[selectedShow].id;

	for (int i = 0; i < cinemasDB.cinemas.size(); i++)
	{
		if (cinemasDB.cinemas[i].id == showsDB.shows[selectedShow].cinemaId)
		{
			cinemaId = cinemasDB.cinemas[i].id;
			cinemaName = cinemasDB.cinemas[i].name;
			cinemaSeats = cinemasDB.cinemas[i].seats;
		}
	}

	for (int i = 0; i < bookingsDB.bookings.size(); i++)
	{
		if (bookingsDB.bookings[i].showId == showsDB.shows[selectedShow].id) blockedSeats.push_back(bookingsDB.bookings[i].seat);
	}

	for (int i = 0; i < customersDB.customers.size(); i++)
	{
		listOfCustomers.push_back(std::to_string(customersDB.customers[i].id) + ": " + customersDB.customers[i].name);
	}

	int selectedCustomer = ListSelection("Please select a customer:", listOfCustomers);
	if (selectedCustomer == -1) return;

	customerId = customersDB.customers[selectedCustomer].id;

	Coordinates seat = MatrixSelection(std::to_string(cinemaId) + " : " + cinemaName, cinemaSeats, blockedSeats);
	if (seat.x == -1) return;

	bookingsDB.Add(customerId, showId, seat);
}

void ConsoleHandler::AddShow()
{
	std::vector<std::string> listOfMovies;
	std::vector<std::string> listOfCinemas;

	ShowsDB showsDB("C:\\x.temp\\shows.kmcf");
	MoviesDB moviesDB("C:\\x.temp\\movies.kmcf");
	CinemasDB cinemasDB("C:\\x.temp\\cinemas.kmcf");

	int movieId;
	int cinemaId;

	for (int i = 0; i < moviesDB.movies.size(); i++) listOfMovies.push_back(moviesDB.movies[i].name);
	for (int i = 0; i < cinemasDB.cinemas.size(); i++) listOfCinemas.push_back(cinemasDB.cinemas[i].name);

	switch (int n = ListSelection("Please select a movie:", listOfMovies))
	{
	case -1:
		return;
		break;
	default:
		movieId = moviesDB.movies[n].id;
		break;
	}

	switch (int n = ListSelection("Please select a cinema:", listOfCinemas))
	{
	case -1:
		return;
		break;
	default:
		cinemaId = cinemasDB.cinemas[n].id;
		break;
	}

	DateTime startTime =
	{
		ReadInt("Please enter the day: ", Colors::WHITE),
		ReadInt("Please enter the month: ", Colors::WHITE),
		ReadInt("Please enter the year: ", Colors::WHITE),
		ReadInt("Please enter the hour: ", Colors::WHITE),
		ReadInt("Please enter the minute: ", Colors::WHITE)
	};

	showsDB.Add(movieId, cinemaId, startTime);
}

#pragma endregion

#pragma region showing items

void ConsoleHandler::ShowCustomers()
{
	Write("Customers", true, Colors::YELLOW);
	Write("ID: [Name; DD.MM.YYYY]\n", true, Colors::YELLOW);
	CustomersDB customersDB("C:\\x.temp\\customers.kmcf");
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
}

void ConsoleHandler::ShowMovies()
{
	Write("Movies", true, Colors::YELLOW);
	Write("ID: [Name; Info]\n", true, Colors::YELLOW);
	MoviesDB moviesDB("C:\\x.temp\\movies.kmcf");
	for (int i = 0; i < moviesDB.movies.size(); i++)
	{
		Write(
			std::to_string(moviesDB.movies[i].id) + ": [" +
			moviesDB.movies[i].name + "; " +
			moviesDB.movies[i].info + "]"
		);
	}
	_getch();
}

void ConsoleHandler::ShowCinemas()
{
	Write("Cinemas", true, Colors::YELLOW);
	Write("ID: [Name; Seats]\n", true, Colors::YELLOW);
	CinemasDB cinemasDB("C:\\x.temp\\cinemas.kmcf");
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
}

void ConsoleHandler::ShowBookings()
{
	Write("Bookings", true, Colors::YELLOW);
	Write("ID: [Customer; Movie; Row, Seat]\n", true, Colors::YELLOW);

	BookingsDB bookingsDB("C:\\x.temp\\bookings.kmcf");
	CustomersDB customersDB("C:\\x.temp\\customers.kmcf");
	ShowsDB showsDB("C:\\x.temp\\shows.kmcf");
	MoviesDB moviesDB("C:\\x.temp\\movies.kmcf");

	for (int i = 0; i < bookingsDB.bookings.size(); i++)
	{

		std::string customerName;
		std::string movieName;

		for (int e = 0; e < customersDB.customers.size(); e++)
		{
			if (customersDB.customers[e].id == bookingsDB.bookings[i].customerId) customerName = customersDB.customers[e].name;
		}

		for (int e = 0; e < showsDB.shows.size(); e++)
		{
			if (showsDB.shows[e].id == bookingsDB.bookings[i].showId)
			{
				for (int a = 0; a < moviesDB.movies.size(); a++)
				{
					if (moviesDB.movies[a].id == showsDB.shows[e].movieId) movieName = moviesDB.movies[a].name;
				}
			}
		}

		Write(
			std::to_string(bookingsDB.bookings[i].id) + ": [" +
			customerName + "; " +
			movieName + "; " +
			std::to_string(bookingsDB.bookings[i].seat.y) + ", " +
			std::to_string(bookingsDB.bookings[i].seat.x) + "]"
		);
	}
	_getch();
}

void ConsoleHandler::ShowShows()
{
	std::vector<std::string> listOfShows;

	ShowsDB showsDB("C:\\x.temp\\shows.kmcf");
	MoviesDB moviesDB("C:\\x.temp\\movies.kmcf");
	CinemasDB cinemasDB("C:\\x.temp\\cinemas.kmcf");

	for (int i = 0; i < showsDB.shows.size(); i++)
	{
		std::string movieName;
		for (int e = 0; e < moviesDB.movies.size(); e++)
		{
			if (moviesDB.movies[e].id == showsDB.shows[i].movieId) movieName = moviesDB.movies[e].name;
		}

		std::string cinemaName;
		for (int e = 0; e < cinemasDB.cinemas.size(); e++) 
		{
			if (cinemasDB.cinemas[e].id == showsDB.shows[i].cinemaId) cinemaName = cinemasDB.cinemas[e].name;
		}

		listOfShows.push_back(
			std::to_string(showsDB.shows[i].id) + ": [" +
			movieName + "; " +
			cinemaName + "; " +
			std::to_string(showsDB.shows[i].startTime.day) + "." +
			std::to_string(showsDB.shows[i].startTime.month) + "." +
			std::to_string(showsDB.shows[i].startTime.year) + " " +
			std::to_string(showsDB.shows[i].startTime.hours) + ":" +
			std::to_string(showsDB.shows[i].startTime.minutes) + "]"
			);
	}

	int n = ListSelection("Shows\nID: [Movie; Cinema; DD.MM.YYYY HH : mm]", listOfShows, Colors::YELLOW);
	//TODO: List selection for shows -> all bookings for this show
}

#pragma endregion

#pragma region deleting items
	
void ConsoleHandler::DeleteBooking() 
{

}

void ConsoleHandler::DeleteCinema()
{

}

void ConsoleHandler::DeleteCustomer()
{
	std::vector<std::string> listOfCustomers;

	CustomersDB customersDB("C:\\x.temp\\customers.kmcf");

	for (int i = 0; i < customersDB.customers.size(); i++)
	{
		listOfCustomers.push_back(
			std::to_string(customersDB.customers[i].id) + ": [" +
			customersDB.customers[i].name + "; " +
			std::to_string(customersDB.customers[i].birthday.day) + "." +
			std::to_string(customersDB.customers[i].birthday.month) + "." +
			std::to_string(customersDB.customers[i].birthday.year) + "]"
		);
	}
	
	int selectedCustomer = ListSelection("Delete Customer\nID: [Name; DD.MM.YYYY]\n", listOfCustomers, Colors::YELLOW);
	if (selectedCustomer == -1) return;

	customersDB.Delete(customersDB.customers[selectedCustomer].id);
}

void ConsoleHandler::DeleteMovie()
{
	std::vector<std::string> listOfMovies;

	MoviesDB moviesDB("C:\\x.temp\\movies.kmcf");
	for (int i = 0; i < moviesDB.movies.size(); i++)
	{
		listOfMovies.push_back(
			std::to_string(moviesDB.movies[i].id) + ": [" +
			moviesDB.movies[i].name + "; " +
			moviesDB.movies[i].info + "]"
		);
	}

	int selectedMovies = ListSelection("Movies\nID: [Name; Info]\n", listOfMovies, Colors::YELLOW);
	if (selectedMovies == -1) return;

	moviesDB.Delete(moviesDB.movies[selectedMovies].id);
}

void ConsoleHandler::DeleteShow()
{

}
	
#pragma endregion