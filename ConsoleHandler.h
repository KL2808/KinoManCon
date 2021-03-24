#pragma once
#include <string>
#include <vector>

static class ConsoleHandler
{
private:


public:

	void Clear();

	void Write(std::string);

	void Write(std::string, bool);

	void Write(std::string, bool, int);

	void WritePredefined(int);

	int ListSelection(std::string title, std::vector<std::string> items);
};