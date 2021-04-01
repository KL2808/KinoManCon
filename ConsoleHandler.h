#pragma once
#include <string>
#include <vector>

static class ConsoleHandler
{
private:


public:

	void Clear();

	void Write(std::string);

	void Write(std::string, bool);

	void Write(std::string, bool, int);

	std::string ReadString(std::string, int);

	int ReadInt(std::string, int);

	int ListSelection(std::string title, std::vector<std::string> items);

	void MainMenu();

	void AddItemsMenu();

	void ShowItemsMenu();

	void BookingWizard();
	
	void ShowWizard();

	void AddCustomer();

	void AddMovie();

	void AddCinema();

	void ShowCustomers();

	void ShowMovies();

	void ShowCinemas();
};