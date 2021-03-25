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
		data += std::to_string(bookings[i].row) + ";";
		data += std::to_string(bookings[i].seat) + ";\n";
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
			atoi(members[3].c_str()),
			atoi(members[4].c_str())
		};
		bookings.push_back(booking);
	}
	file.close();
}