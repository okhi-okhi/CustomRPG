#include "CraftArmor.h"
#include <iostream>
#include "Item.h"
#include "../System/Exceptions.hpp"
#include "../game/gameConfig.h"
#include "../Utils/Utilities.h"

CraftArmor::CraftArmor(const string& fileName) {
	using json = nlohmann::json;
	json j = Utils::loadJsonFile("Items/CraftArmor/" + fileName);

	try {
		this->id = fileName;
		this->name = readString("name");
		this->description = readString("description");

		std::vector<string> armorPos = GameConfig::instance().getArmorSlots();

		if(std::ranges::find(armorPos, j["armorSlot"].get<string>()) != armorPos.end()) {
			this->armorSlot = j["armorSlot"];
		} else {
			throw InvalidKeyException(j["armorSlot"]);
		}
	}
	catch (json::exception& e) {
		throw BadValueException(fileName, e.what());
	}
}

string CraftArmor::getArmorSlotName(const std::string& armorSlot)
{
	return I18n::instance().get("stat.armorSlotName." + armorSlot);
}

int CraftArmor::getArmorSlotIndex() const
{
	for(int i = 0; i < GameConfig::instance().getArmorSlots().size(); i++)
	{
		if(this->armorSlot == GameConfig::instance().getArmorSlots()[i]) {
			return i;
		}
	}
	return -1;
}


string CraftArmor::readString(const string& key) const
{
	return "dynamic.craftArmor." + this->id + "." + key;
}
