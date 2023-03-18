#include "CraftArmor.h"
#include <iostream>
#include "Item.h"
#include "../System/Exceptions.hpp"
#include "../game/gameConfig.h"
#include "../Utils/Utilities.h"

CraftArmor::CraftArmor(const std::string& fileName) {
	using json = nlohmann::json;
	json j = Utils::readJsonFile("Items/CraftArmor/" + fileName);

	try {
		this->id = fileName;
		this->name = readString("name");
		this->description = readString("description");

		std::vector<std::string> armorPos = gameConfig::instance().getArmorSlots();
		if(std::find(armorPos.begin(), armorPos.end(), j["armorSlot"]) != armorPos.end()) {
			this->armorSlot = j["armorSlot"];
		} else {
			throw InvalidKeyException(j["armorSlot"]);
		}
	}
	catch (json::exception& e) {
		throw BadValueException(fileName, j, e.what());
	}
}

std::string CraftArmor::getArmorSlotName(const std::string& armorSlot)
{
	return I18n::instance().get("stat.armorSlotName." + armorSlot);
}

int CraftArmor::getArmorSlotIndex() const
{
	for(int i = 0; i < gameConfig::instance().getArmorSlots().size(); i++)
	{
		if(this->armorSlot == gameConfig::instance().getArmorSlots()[i]) {
			return i;
		}
	}
	return -1;
}


std::string CraftArmor::readString(const std::string& key) const
{
	return "dynamic.craftArmor." + this->id + "." + key;
}
