#pragma once
#include <map>
#include <string>
#include <vector>
#include "../Utils/Singleton.h"

class GameConfig : public Singleton<GameConfig>
{
private:
	std::string defaultLanguage;
	std::string currentLanguage;

	int nextPlaceNum;
	int teamCapacity;
	int lineCapacity;
	//formula
	std::map<std::string, std::string> formulas;
	//talent
	std::vector<std::string> talents;
	//armorSlot
	std::vector<std::string> armorSlots;

public:
	explicit GameConfig(token) : defaultLanguage("en_US"), currentLanguage("en_US"), nextPlaceNum(3), teamCapacity(3), lineCapacity(3) {}

	void load(const std::string& fileName);

	const std::string& getDefaultLanguage() const { return this->defaultLanguage; }
	const std::string& getCurrentLanguage() const { return this->currentLanguage; }

	const int& getNextPlaceNum() const { return this->nextPlaceNum; }
	const int& getTeamCapacity() const { return this->teamCapacity; }
	const int& getLineCapacity() const { return this->lineCapacity; }

	const std::string& getFormula(const std::string& key) const;

	const std::vector<std::string>& getTalents() const { return this->talents; }

	const std::vector<std::string>& getArmorSlots() const { return this->armorSlots; }
};

