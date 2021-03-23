#pragma once

#include <string>
#include <vector>

struct Booking
{
	int id;
	int customerId;
	int showId;
};

class BookingsDB
{
private:

	std::string fullpath;

public:

	std::vector<Booking> cinemas;

	BookingsDB(std::string);

	void Save();

	void Load();
};