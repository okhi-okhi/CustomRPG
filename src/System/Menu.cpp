#include "Menu.h"
#include <iostream>
#include "Exceptions.hpp"
#include "../I18n/I18n.h"

void Menu::addDescription(const std::string& descKey)
{
	this->descriptions.push_back(I18n::instance().get(this->i18nKey + "." + descKey));
}

void Menu::addDescription(const std::string& descKey, const std::map<std::string, std::string>& args)
{
	this->descriptions.push_back(I18n::instance().get(this->i18nKey + "." + descKey, args));
}

void Menu::addButton(const std::string& descKey) {
	this->buttons.push_back(I18n::instance().get(this->i18nKey + "." + descKey));
}

void Menu::addButton(const std::string& descKey, const std::map<std::string, std::string>& args) {
	this->buttons.emplace_back(I18n::instance().get(this->i18nKey + "." + descKey, args));
}

void Menu::replaceButton(const std::string& descKey, const int index) {
	if (index < 0 || index >= this->buttons.size()) {
		throw OutOfRangeException(index, this->buttons.size());
	}
	this->buttons[index] = I18n::instance().get(this->i18nKey + "." + descKey);
}

void Menu::printTitle() const {
	using std::cout, std::cin, std::endl;
	cout << I18n::instance().get("menu.continue");
	cin.get();
	system("CLS");

	cout << I18n::instance().get(this->i18nKey+".title") << endl;
}

void Menu::printDescription() const
{
	using std::cout, std::cin, std::endl;
	for (const auto& description : this->descriptions) {
		cout << description << endl;
	}
}

void Menu::printButton() const {
	using std::cout, std::endl, std::to_string;
	for(int i = 0; i < this->buttons.size(); i++)
	{
		cout << I18n::instance().get("menu.button", 
			{ {"index", to_string(i)}, {"description", this->buttons[i]} }) << endl;
	}
	cout << endl;
}

void Menu::print() const
{
	printTitle();
	printDescription();
	printButton();
}

int Menu::getInput() const {
	return getInput(0, static_cast<int>(this->buttons.size()));
}

int Menu::getInput(const int min, const int max)
{
	using std::cout, std::cin, std::endl, std::to_string;
	int choice;
	cout << I18n::instance().get("menu.choose");
	cin >> choice;

	while (cin.fail() || choice > max || choice < min)
	{
		cout << I18n::instance().get("menu.faultyInput", { {"limit", to_string(max)} }) << endl;
		cin.clear();
		cin.ignore(100, '\n');
		cout << I18n::instance().get("menu.choose");
		cin >> choice;
	}
	cin.ignore(100, '\n');

	return choice;
}