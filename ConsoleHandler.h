#pragma once
#include <string>
#include <vector>

#include "Coordinates.h"

static class ConsoleHandler
{
private:


public:

	void Clear();

	void Write(std::string string, bool endl, int color);

	std::string ReadString(std::string string , int color);

	int ReadInt(std::string string, int color);

	int ListSelection(std::string title, std::vector<std::string> items, int titleColor);

	Coordinates MatrixSelection(std::string title, std::vector<int> matrix, std::vector<Coordinates> blockedPoints, int titleColor);

	void MainMenu();

	void AddItemsMenu();

	void ShowItemsMenu();

	void DeleteItemsMenu();

	void AddCustomer();

	void AddMovie();

	void AddCinema();

	void AddBooking();

	void AddShow();

	void ShowCustomers();

	void ShowMovies();

	void ShowCinemas();

	void ShowBookings();

	void ShowShows();

	void DeleteBooking();

	void DeleteCinema();

	void DeleteCustomer();

	void DeleteMovie();

	void DeleteShow();
};