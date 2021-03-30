#include <fstream>
#include <vector>

#include "CustomersDB.h"

#include "StringTools.cpp"

CustomersDB::CustomersDB(std::string fullpathItemsDB)
{
	fullpath = fullpathItemsDB;
	Load();
}

void CustomersDB::Save()
{
	std::string data = "";
	for (int i = 0; i < customers.size(); i++)
	{
		data += std::to_string(customers[i].id) + ";";
		data += customers[i].name + ";";

		data += std::to_string(customers[i].birthday.day) + ",";
		data += std::to_string(customers[i].birthday.month) + ",";
		data += std::to_string(customers[i].birthday.year) + ";\n";
	}

	std::ofstream file(fullpath);
	file << data;
	file.close();
}

void CustomersDB::Load()
{
	std::ifstream file(fullpath);
	std::string line;

	while (std::getline(file, line))
	{
		std::vector<std::string> members = split(line, ';');
		std::vector<std::string> dateTime_members = split(members[2], ',');
		DateTime birthday = 
		{ 
			atoi(dateTime_members[0].c_str()),
			atoi(dateTime_members[1].c_str()),
			atoi(dateTime_members[2].c_str()),
			0,
			0
		};
		Customer customer = 
		{ 
			atoi(members[0].c_str()),
			members[1],
			birthday
		};
		customers.push_back(customer);
	}
	file.close();
}

void CustomersDB::Add(std::string name, DateTime birthday)
{
	customers.push_back({ (int)customers.size() + 0, name, birthday });
	Save();
}