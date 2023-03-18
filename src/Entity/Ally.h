#pragma once
#include <utility>
#include "Entity.h"
#include "Race.h"
#include "Occupation.h"
#include "Equipment.h"

class Ally final : public Entity{
private:
	std::vector<Weapon> weapons;
	std::vector<Armor> armors;
	
	int exp;
	int expNext;

	int luck;
	int talentPoint;

	Race race;
	Occupation occupation;

	bool inTeam;

	virtual float readValue(const json& j) const override;
	virtual std::string readString(const std::string& key) const override;

public:
	Ally() : Entity(), exp(0), expNext(0), luck(0), talentPoint(0), inTeam(false) {}
	Ally(std::string id, std::string name, const int& level, const int& exp,
		const int& hp, const int& mana, const int& luck, const int& talentPoint,
		std::map<std::string, int> talents, const std::string& race) :
		Entity(Faction::ALLY, std::move(id), std::move(name), level, hp, mana, std::move(talents)),
		exp(exp), luck(luck), talentPoint(talentPoint), inTeam(false)
	{
		this->race = Race(race);
		this->updateStats();
	}

	explicit Ally(const std::string& fileName);

	//Functions
	void updateStats();
	void CheckLevelUp();
	void allocateStat();
	ordered_json getAsJson();
	ordered_json getEquipAsJson() const;

	void print() const override;
	void debugPrint() const override;

	//Modifiers
	void modifyStat(const std::string& key, const int& value);

	void setInTeam(const bool& inTeam) { this->inTeam = inTeam; }
	bool addWeapon(const Weapon& weapon);
	bool addArmor(const Armor& armor);

	//Accessors
	const int& getExp() const { return this->exp; }
	const int& getExpNext() const { return this->expNext; }

	const int& getLuck() const { return this->luck; }
	const int& getTalentPoint() const { return this->talentPoint; }
	const bool& getInTeam() const { return this->inTeam; }

	const std::vector<Weapon>& getWeapons() const { return this->weapons; }
	const std::vector<Armor>& getArmors() const { return this->armors; }

	int getArmorDefense() const ;
};
