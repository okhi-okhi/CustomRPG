#pragma once
#include <map>
#include <string>
#include <vector>
#include "../Utils/Singleton.h"

class GameConfig : public Singleton<GameConfig>
{
private:
	//game
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
	GameConfig(token) : nextPlaceNum(3), teamCapacity(3), lineCapacity(3) {}

	void load(const std::string& fileName);

	//game
	const int& getNextPlaceNum() const { return this->nextPlaceNum; }
	const int& getTeamCapacity() const { return this->teamCapacity; }
	const int& getLineCapacity() const { return this->lineCapacity; }

	const std::string& getFormula(const std::string& key) const;

	const std::vector<std::string>& getTalents() const { return this->talents; }

	const std::vector<std::string>& getArmorSlots() const { return this->armorSlots; }
};

