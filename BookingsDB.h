 #pragma once

#include <string>
#include <vector>

struct Booking
{
	int id;
	int customerId;
	int showId;
	int row; 
	int seat;
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

	void Add();
};