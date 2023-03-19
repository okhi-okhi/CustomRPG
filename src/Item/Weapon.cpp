#include "Weapon.h"
#include "../System/Exceptions.hpp"
#include "../Utils/ChanceTable.h"
#include "../Utils/JsonUtils.h"
#include "../Utils/Utilities.h"

Weapon::Weapon(const std::string& fileName)
{
	json j = Utils::readJsonFile("Items/Weapons/" + fileName );
	try {
		this->itemType = itemTypes::WEAPON;
		this->id = fileName;
		this->rarity = readRarity(j["rarity"]);
		this->name = readString(j["name"], "name");
		this->level = static_cast<int>(readValue(j["level"]));
		this->buyPrice = static_cast<int>(readValue(j["buyPrice"]));
		this->sellPrice = static_cast<int>(readValue(j["sellPrice"]));
		this->stackable = false;

		this->weaponType = CraftWeapon(j["weaponType"]);
		this->atk = static_cast<int>(readValue(j["atk"]));
		this->defense = static_cast<int>(readValue(j["defense"]));
		this->critChance = readValue(j["critChance"]);
		this->critDamage = readValue(j["critDamage"]);
		this->durabilityMax = static_cast<int>(readValue(j["durabilityMax"]));
		this->durability = j["durability"] == -1 ? this->durabilityMax : static_cast<int>(readValue(j["durability"]));
	}
	catch (json::exception& e) {
		throw BadValueException(fileName, e.what());
	}
}

Weapon* Weapon::clone()const {
	return new Weapon(*this);
}

ordered_json Weapon::getAsJson()const
{
	ordered_json j = Item::getAsJson();
	j["weaponType"] = this->weaponType.getId();
	j["level"] = this->level;
	j["atk"] = this->atk;
	j["defense"] = this->defense;
	j["critChance"] = this->critChance;
	j["critDamage"] = this->critDamage;
	j["durability"] = this->durability;
	j["durabilityMax"] = this->durabilityMax;

	return j;
}

std::vector<std::string> Weapon::getDataKey() const
{
	std::vector<std::string> dataKey = Item::getDataKey();

	dataKey.emplace_back("weaponType");
	dataKey.emplace_back("level");
	dataKey.emplace_back("atk");
	dataKey.emplace_back("defense");
	dataKey.emplace_back("critChance");
	dataKey.emplace_back("critDamage");
	dataKey.emplace_back("durability");
	
	return dataKey;
}

std::map<std::string, std::string> Weapon::getData() const
{
	std::map<std::string, std::string> data = Item::getData();

	data["weaponType"] = getWeaponTypeName();
	data["level"] = std::to_string(this->level);
	data["atk"] = std::to_string(this->atk);
	data["defense"] = std::to_string(this->defense);
	data["critChance"] = Utils::floatToPercent(this->critChance);
	data["critDamage"] = Utils::floatToPercent(this->critDamage);
	data["durability"] = std::to_string(this->durability) + '/' + std::to_string(this->durabilityMax);

	return data;
}

void Weapon::print()const
{
	using std::cout, std::endl, std::to_string;
	Item::print();
	const std::string prefix = "item.weapon.print.";
	cout << I18n::instance().get(prefix + "weaponType",{ {"weaponType", getWeaponTypeName()} }) << endl;
	cout << I18n::instance().get(prefix + "level",     { {"level", to_string(this->level)} }) << endl;
	cout << I18n::instance().get(prefix + "atk",       { {"atk", to_string(this->atk)} }) << endl;
	cout << I18n::instance().get(prefix + "defense",   { {"defense", to_string(this->defense)} }) << endl;
	cout << I18n::instance().get(prefix + "comboRate", { {"comboRate", Utils::floatToPercent(this->weaponType.getComboRate())} }) << endl;
	cout << I18n::instance().get(prefix + "critChance",{ {"critChance", Utils::floatToPercent(this->critChance)} }) << endl;
	cout << I18n::instance().get(prefix + "critDamage",{ {"critDamage", Utils::floatToPercent(this->critDamage)} }) << endl;
	cout << I18n::instance().get(prefix + "durability",
		{ {"durability",    to_string(this->durability)},
		  {"durabilityMax", to_string(this->durabilityMax)} }) << endl;
}

void Weapon::debugPrint() const
{
	using std::cout, std::endl;
	print();
	Item::debugPrint();
}

std::string Weapon::getWeaponTypeName() const
{
	return I18n::instance().get("item.weapon.weaponType",
		{ {"weaponType", getRawWeaponTypeName()},
		  {"isTwoHand", CraftWeapon::getIsTwoHandName(getIsTwoHand())} });
}

float Weapon::readValue(const json& j) const
{
	std::map<std::string, int> vars;
	vars["level"] = this->level;
	if (j.is_number()) {
		return JsonUtils::readValueFromNum(j);
	}
	if (j.is_string()) {
		return JsonUtils::readValueFromString(j, vars);
	}
	if (j.contains("min") && j.contains("max")) {
		return JsonUtils::readValueFromRange(j, vars);
	}
	if (j.contains("expect") && j.contains("floatingRange")) {
		return JsonUtils::readValueFromExpect(j, vars);
	}
	if (JsonUtils::isRarityTable(j)) {
		return JsonUtils::readValueFromRarity(j, static_cast<int>(this->rarity), vars);
	}
	throw NoReadFunctionException(j);
}

std::string Weapon::readString(const json& j, const std::string& key) const
{
	const std::string prefix = "dynamic.weapon." + this->id + "." + key + ".";
	if (j.is_null()) {
		return prefix + "default";
	}
	if (j.is_string()) {
		return prefix + j.get<std::string>();
	}
	if (JsonUtils::isRarityTable(j)) {
		return prefix + j[std::to_string(static_cast<int>(this->rarity))].get<std::string>();
	}
	if (j.is_object()) {
		return prefix + ChanceTable(j).getRandomItem();
	}
	throw NoReadFunctionException(j);
}