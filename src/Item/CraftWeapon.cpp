#include "CraftWeapon.h"
#include <iostream>
#include "../System/Exceptions.hpp"
#include "../Utils/Utilities.h"

CraftWeapon::CraftWeapon(const std::string& fileName) {
	using json = nlohmann::json;
	json j = Utils::readJsonFile("Items/CraftWeapon/" + fileName);

	try {
		this->id = fileName;
		this->name = readString(j["name"], "name");
		this->description = readString(j["description"], "description");
		this->comboRate = j["comboRate"];
		this->isTwoHand = j["isTwoHand"];
	}
	catch (json::exception& e) {
		throw BadValueException(fileName, j, e.what());
	}
}

std::string CraftWeapon::getIsTwoHandName(const bool& isTwoHand)
{
	if(isTwoHand) {
		return I18n::instance().get("stat.handName.twoHand");
	}
	return I18n::instance().get("stat.handName.oneHand");
}

std::string CraftWeapon::readString(const json& j, const std::string& key) const
{
	if (j.is_null()) {
		return "dynamic.craftWeapon." + this->id + "." + key + ".default";
	}
	if (j.is_string()) {
		return "dynamic.craftWeapon." + this->id + "." + key + "." + j.get<std::string>();
	}
	throw NoReadFunctionException(j);
}
