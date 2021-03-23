#pragma once
#include <string>

class ConsoleHandler
{
private:


public:

	void Write(std::string);

	void Write(std::string, bool);

	void Write(std::string, bool, int);

	void WritePredefined(int);
};