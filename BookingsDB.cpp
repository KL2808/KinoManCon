#include <fstream>

#include "BookingsDB.h"

BookingsDB::BookingsDB(std::string fullpathItemsDB) //constructor
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

	std::ofstream File;
	File.open(fullpath);
	File << data;
	File.close();

}

void BookingsDB::Load()
{
	//TODO: Load cinemas
}