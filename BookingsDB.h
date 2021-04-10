#pragma once

#include <string>
#include <vector>

#include "Coordinates.h"

struct Booking
{
	int id;
	int customerId;
	int showId;
	Coordinates seat;
};

class BookingsDB
{
private:

	std::string fullpath;

public:

	std::vector<Booking> bookings;

	BookingsDB(std::string);

	void Save();

	void Load();

	void Add(int, int, Coordinates);
};