#pragma once

#include <string>
#include <vector>

#include "DateTime.h"

struct Customer
{
	int id;
	std::string name;
	DateTime birthday;
};

class CustomersDB
{
private:

	std::string fullpath;

public:

	std::vector<Customer> customers;

	CustomersDB(std::string);

	void Save();

	void Load();

	void Add(std::string, DateTime);

	void Delete(int id);
};