#include <vector>
#include <string>

inline std::vector<std::string> split(std::string subject, char delimiter)
{
	std::vector<std::string> result = { "" };
	bool isDel = false;

	for (int i = 0; i < subject.length(); i++)
	{
		if (isDel) result.push_back("");
		subject[i] == delimiter ? isDel = true : isDel = false;
		if (!isDel) result[result.size() - 1] += subject[i];
	}

	return result;
}

inline bool isInt(std::string string) //TODO: debug this function, there seems to be a litle bug
{
	for (int i = 0; i < string.size(); i++) if (string.c_str()[i] < 48 || string.c_str()[i] > 57) return false;
	return true;
}