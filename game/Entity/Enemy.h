#pragma once
#include"Entity.h"
#include"../Utils/ChanceTable.h"

class Enemy : public Entity
{
private:
	int dropExp;
	int dropGold;

	ChanceTable attackTypes;
	ChanceTable skills;
	ChanceTable dropWeapons;
	ChanceTable dropArmors;

public:
	explicit Enemy(const std::string& fileName, int point=0);

	std::string getAsString()const;
	void debugPrint() const;

	std::string getAttackTypes() const { return this->attackTypes.getRandomItem(); }
	std::string getSkills() const { return this->skills.getRandomItem(); }
	std::set<std::string> getDropWeapons() const { return this->dropWeapons.drawItems(); }
	std::set<std::string> getDropArmors() const { return this->dropArmors.drawItems(); }

	const int& getDropExp()const { return this->dropExp; }
	const int& getDropGold()const { return this->dropGold; }
};

