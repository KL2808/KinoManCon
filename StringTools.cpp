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