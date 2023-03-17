#pragma once
#include <json.hpp>
#include <set>
using json = nlohmann::json;

class ChanceTable
{
private:
	std::map<std::string, float> chanceTable;
	float chanceMax;

	float readValue(const json& j) const;

public:
	ChanceTable();
	explicit ChanceTable(std::string& fileName);
	explicit ChanceTable(const json& j);

	std::string getRandomItem() const;
	std::set<std::string> getRandomItems(const int& num) const;

	std::set<std::string> drawItems() const; //draw chanceTable's size times, and no guarantee.

	void removeItem(const std::string& key) { this->chanceMax -= this->chanceTable[key]; this->chanceTable.erase(key); }
	void debugPrint()const;

	std::map<std::string, float> getChanceTable() const { return this->chanceTable; }
	int getSize()const { return static_cast<int>(this->chanceTable.size()); }
};