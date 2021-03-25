#include <vector>
#include <string>

inline std::vector<int> VecStrToVecInt(std::vector<std::string> vecStr)
{
	std::vector<int> vecInt;

	for (int i = 0; i < vecStr.size(); i++) 
	{
		vecInt.push_back(atoi(vecStr[i].c_str()));
	}

	return vecInt;
}