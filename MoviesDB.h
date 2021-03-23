#pragma once

#include <string>
#include <vector>

struct Movie
{
	int id;
	std::string name;
	std::string info;
};

class MoviesDB
{
private:

	std::string fullpath;

public:

	std::vector<Movie> movies;

	MoviesDB(std::string);

	void Save();

	void Load();
};