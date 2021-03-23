#pragma once

#include <string>
#include <vector>

#include "DateTime.h"

struct Show
{
	int id;
	int movieId;
	int cinemaId;
	DateTime startTime;
	std::vector<int> bookingIds;
};

class ShowsDB
{
private:

	std::string fullpath;

public:

	std::vector<Show> shows;

	ShowsDB(std::string);

	void Save();

	void Load();
};