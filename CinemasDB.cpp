#include <fstream>
#include <vector>

#include "CinemasDB.h"

#include "stringTools.cpp"
#include "VectorTools.cpp"

CinemasDB::CinemasDB(std::string fullpathItemsDB)
{
	fullpath = fullpathItemsDB;
	Load();
}

void CinemasDB::Save()
{
	std::string data = "";
	for (int i = 0; i < cinemas.size(); i++)
	{
		data += std::to_string(cinemas[i].id) + ";";
		data += cinemas[i].name + ";";
		
		for (int e = 0; e < cinemas[i].seats.size(); e++) 
		{
			data += std::to_string(cinemas[i].seats[e]) + (e == cinemas[i].seats.size() - 1 ? ";\n" : ",");
		}
	}

	std::ofstream file(fullpath);
	file << data;
	file.close();
}

void CinemasDB::Load()
{
	std::ifstream file(fullpath);
	std::string line;

	while (std::getline(file, line))
	{
		std::vector<std::string> members = split(line, ';');
		std::vector<std::string> seats_members = split(members[2], ',');
		
		Cinema cinema = 
		{ 
			atoi(members[0].c_str()),
			members[1],
			VecStrToVecInt(seats_members) 
		};
		cinemas.push_back(cinema);
	}
	file.close();
}