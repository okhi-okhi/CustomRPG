#pragma once
#include <json.hpp>
#include "../I18n/I18n.h"
using json = nlohmann::json;

class CraftArmor
{
private:
	std::string id;
	std::string name;
	std::string description;
	std::string armorSlot;

	//to do: recipe formula...
	//ChanceTable<passive> passives

	std::string readString(const std::string& key) const;

public:
	CraftArmor() = default;
	explicit CraftArmor(const std::string& fileName);

	static std::string getArmorSlotName(const std::string& armorSlot);

	const std::string& getId()const { return this->id; }
	std::string getName()const { return I18n::instance().get(this->name); }
	std::string getDescription()const { return I18n::instance().get(this->description); }
	std::string getArmorSlot()const { return I18n::instance().get(this->armorSlot); }
	int getArmorSlotIndex()const;
};


