#include <fstream>

#include "BookingsDB.h"

#include "StringTools.cpp"

BookingsDB::BookingsDB(std::string fullpathItemsDB)
{
	fullpath = fullpathItemsDB;
	Load();
}

void BookingsDB::Save()
{
	std::string data = "";
	for (int i = 0; i < bookings.size(); i++)
	{
		data += std::to_string(bookings[i].id) + ";";
		data += std::to_string(bookings[i].customerId) + ";";
		data += std::to_string(bookings[i].showId) + ";";
		data += std::to_string(bookings[i].seat.x) + ";";
		data += std::to_string(bookings[i].seat.y) + ";\n";
	}

	std::ofstream File(fullpath);
	File << data;
	File.close();

}

void BookingsDB::Load()
{
	std::ifstream file(fullpath);
	std::string line;

	while (std::getline(file, line))
	{
		std::vector<std::string> members;
		members = split(line, ';');
		Booking booking = 
		{ 
			atoi(members[0].c_str()),
			atoi(members[1].c_str()),
			atoi(members[2].c_str()),
			{
				atoi(members[3].c_str()),
				atoi(members[4].c_str())
			}
		};
		bookings.push_back(booking);
	}
	file.close();
}

void BookingsDB::Add(int customerId, int showId, Coordinates seat)
{
	if (bookings.size() == 0) bookings.push_back({ 1, customerId, showId, seat });
	else bookings.push_back({ bookings[bookings.size() - 1].id + 1, customerId, showId, seat});
	Save();
}

void BookingsDB::Delete(int id)
{
	std::vector<Booking> newBookings;
	for (int i = 0; i < bookings.size(); i++)
	{
		if (bookings[i].id != id) newBookings.push_back(bookings[i]);
	}
	bookings = newBookings;
	Save();
}