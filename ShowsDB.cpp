#include <fstream>
#include <vector>

#include "ShowsDB.h"

#include "StringTools.cpp"
#include "VectorTools.cpp"

ShowsDB::ShowsDB(std::string fullpathItemsDB)
{
	fullpath = fullpathItemsDB;
	Load();
}

void ShowsDB::Save()
{
	std::string data = "";
	for (int i = 0; i < shows.size(); i++)
	{
		data += std::to_string(shows[i].id) + ";";
		data += std::to_string(shows[i].movieId) + ";";
		data += std::to_string(shows[i].cinemaId) + ";";

		data += std::to_string(shows[i].startTime.day) + ",";
		data += std::to_string(shows[i].startTime.month) + ",";
		data += std::to_string(shows[i].startTime.year) + ",";
		data += std::to_string(shows[i].startTime.hours) + ",";
		data += std::to_string(shows[i].startTime.minutes) + ";";

		for (int e = 0; e < shows[i].bookingIds.size(); e++)
		{
			data += std::to_string(shows[i].bookingIds[e]) + (e != shows[i].bookingIds.size() - 1 ? "," : "");
		}
		data += ";\n";
	}

	std::ofstream file(fullpath);
	file << data;
	file.close();
}

void ShowsDB::Load()
{
	std::ifstream file(fullpath);
	std::string line;

	while (std::getline(file, line))
	{
		std::vector<std::string> members = split(line, ';');
		std::vector<std::string> dateTime_members = split(members[3], ',');
		std::vector<std::string> bookingids_members;
		if (members.size() > 4) bookingids_members = split(members[4], ',');
		DateTime startTime =
		{
			atoi(dateTime_members[0].c_str()), //D
			atoi(dateTime_members[1].c_str()), //M
			atoi(dateTime_members[2].c_str()), //Y
			atoi(dateTime_members[3].c_str()), //h
			atoi(dateTime_members[4].c_str())  //m
		};
		Show show =
		{
			atoi(members[0].c_str()),
			atoi(members[1].c_str()),
			atoi(members[2].c_str()),
			startTime,
			VecStrToVecInt(bookingids_members)
		};
		shows.push_back(show);
	}
	file.close();
}

void ShowsDB::Add(int movieId, int cinemaId, DateTime startTime)
{
	std::vector<int> bookingIds;
	shows.push_back({ shows[shows.size() - 1].id + 1, movieId, cinemaId, startTime, bookingIds });
	Save();
}

void ShowsDB::Delete(int id)
{

}