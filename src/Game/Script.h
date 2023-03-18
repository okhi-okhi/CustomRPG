#pragma once
#include <string>
#include <vector>

struct option {
	std::string text;
	std::string resultText;
	int exp = 0;
	int	gold = 0;
	int statPoint = 0;
};

class Script
{
private:
	std::string scnario;
	std::vector<option> options;

public:
	explicit Script(std::string fileName);
	std::string getAsString() const;

	const std::string& getResultText(const int option)const { return this->options[option].resultText; }
	const int& getExp(const int option)const { return this->options[option].exp; }
	const int& getGold(const int option)const { return this->options[option].gold; }
	const int& getStatPoint(const int option)const { return this->options[option].statPoint; }
};

