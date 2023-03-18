#pragma once
#include <string>
#include <vector>
#include <map>

class Menu
{
private:
	std::string i18nKey;
	std::vector<std::string> descriptions;
	std::vector<std::string> buttons;

public:
	Menu() = default;
	explicit Menu(std::string i18nKey) : i18nKey(std::move(i18nKey)) {};

	void addDescription(const std::string& descKey);
	void addDescription(const std::string& descKey, const std::map<std::string, std::string>& args);

	void addButton(const std::string& descKey);
	void addButton(const std::string& descKey, const std::map<std::string, std::string>& args);

	void replaceButton(const std::string& descKey, int index);

	void printTitle() const;
	void printDescription() const;
	void printButton() const;
	void print() const;

	int getInput() const;
	static int getInput(int min, int max);
};
