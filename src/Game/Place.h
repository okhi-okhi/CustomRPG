#pragma once
#include <vector>
#include "../System/GlobalVariable.h"
#include "../System/I18n.h"
#include "../Utils/ChanceTable.h"

using json = nlohmann::json;
class Place
{
private:
	std::string id;
	std::string name;
	int minDistance;
	std::string description;
	std::string opening;
	ChanceTable neighbours;
	ChanceTable events;
	ChanceTable scripts;
	ChanceTable enemyGroups;

	static float readValue(const json& j);
	std::string readString(const json& j, const std::string& key) const;

public:
	Place() : minDistance(0) {}
	explicit Place(const std::string& fileName);

	void debugPrint() const;
	std::string getAsString() const;
	std::set<std::string> getPlaces(const int& num);
	std::string getEvent() const { return this->events.getRandomItem(); }
	std::string getScripts() const { return this->scripts.getRandomItem(); }
	std::vector<std::string> getEnemies() const;

	const std::string& getId() const { return this->id; }
	std::string getName() const { return I18n::instance().get(this->name); }
	const int& getMinDistance() const { return this->minDistance; }
	std::string getDescription() const { return I18n::instance().get(this->description); }
	std::string getOpening() const { return I18n::instance().get(this->opening); }
};

