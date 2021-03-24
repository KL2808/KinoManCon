#include <fstream>
#include <vector>

#include "MoviesDB.h"

#include "StringTools.cpp"

MoviesDB::MoviesDB(std::string fullpathItemsDB) //constructor
{
	fullpath = fullpathItemsDB;
	Load();
}

void MoviesDB::Save()
{
	std::string data = "";
	for (int i = 0; i < movies.size(); i++)
	{
		data += std::to_string(movies[i].id) + ";";
		data += movies[i].name + ";";
		data += movies[i].info + ";\n";
	}

	std::ofstream file(fullpath);
	file << data;
	file.close();
}

void MoviesDB::Load()
{
	std::ifstream file(fullpath);
	std::string line;

	while (std::getline(file, line))
	{
		std::vector<std::string> members;
		members = split(line, ';');
		Movie movie = {atoi(members[0].c_str()), members[1], members[2] };
		movies.push_back(movie);
	}
	file.close();
}