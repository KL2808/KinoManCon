#pragma once

#include <string>
#include <vector>

struct Cinema
{
	int id;
	std::string name;
	std::vector<int> seats;
};

class CinemasDB
{
private:

	std::string fullpath;

public:

	std::vector<Cinema> cinemas;

	CinemasDB(std::string);

	void Save();

	void Load();

	void Add(std::string, std::vector<int>);

	void Delete(int id);
};