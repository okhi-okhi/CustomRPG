#pragma once
#include <json.hpp>
#include "../I18n/I18n.h"
using json = nlohmann::json;

class CraftWeapon
{
private:
	std::string id;
	std::string name;
	std::string description;
	float comboRate;
	bool isTwoHand;
	//to do: recipe formula...
	//ChanceTable<passive> passives

	std::string readString(const json& j, const std::string& key) const;

public:
	CraftWeapon() : comboRate(0.0), isTwoHand(false) {}
	explicit CraftWeapon(const std::string& fileName);

	static std::string getIsTwoHandName(const bool& isTwoHand);

	const std::string& getId()const { return this->id; }
	std::string getName()const { return I18n::instance().get(this->name); }
	std::string getDescription()const { return I18n::instance().get(this->description); }
	const float& getComboRate()const { return this->comboRate; }
	const bool& getIsTwoHand()const { return this->isTwoHand; }
};

