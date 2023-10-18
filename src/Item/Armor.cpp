#include "Armor.h"

#include "CraftWeapon.h"
#include "../System/Exceptions.hpp"
#include "../Utils/ChanceTable.h"
#include "../Utils/JsonUtils.h"
#include "../Utils/Utilities.h"

Armor::Armor(const std::string& fileName)
{
	using std::cout, std::endl;
	json j = Utils::loadJsonFile("Items/Armors/" + fileName);
	try {
		this->itemType = itemTypes::ARMOR;
		this->id = fileName;
		this->rarity = readRarity(j["rarity"]);
		this->name = readString(j["name"], "name");
		this->level = static_cast<int>(readValue(j["level"]));
		this->buyPrice = static_cast<int>(readValue(j["buyPrice"]));
		this->sellPrice = static_cast<int>(readValue(j["sellPrice"]));
		this->stackable = false;

		this->armorType = CraftArmor(j["weaponType"]);
		this->atk = static_cast<int>(readValue(j["atk"]));
		this->defense = static_cast<int>(readValue(j["defense"]));
		this->durabilityMax = static_cast<int>(readValue(j["durabilityMax"]));
		this->durability = j["durability"] == -1 ? this->durabilityMax : static_cast<int>(readValue(j["durability"]));
	}
	catch (json::exception& e) {
		throw BadValueException(fileName, e.what());
	}
}

Armor* Armor::clone()const {
	return new Armor(*this);
}

ordered_json Armor::getAsJson()const
{
	ordered_json j = Item::getAsJson();
	j["armorType"] = this->armorType.getId();
	j["level"] = this->level;
	j["atk"] = this->atk;
	j["defense"] = this->defense;
	j["durability"] = this->durability;
	j["durabilityMax"] = this->durabilityMax;

	return j;
}

std::vector<std::string> Armor::getDataKey() const
{
	std::vector<std::string> dataKey = Item::getDataKey();

	dataKey.emplace_back("armorType");
	dataKey.emplace_back("level");
	dataKey.emplace_back("atk");
	dataKey.emplace_back("defense");
	dataKey.emplace_back("durability");

	return dataKey;
}

std::map<std::string, std::string> Armor::getData() const
{
	std::map<std::string, std::string> data = Item::getData();

	data["armorType"] = getArmorTypeName();
	data["level"] = std::to_string(this->level);
	data["atk"] = std::to_string(this->atk);
	data["defense"] = std::to_string(this->defense);
	data["durability"] = std::to_string(this->durability) + '/' + std::to_string(this->durabilityMax);

	return data;
}

void Armor::print() const
{
	Item::print();
	using std::cout, std::endl, std::to_string;
	const std::string prefix = "item.armor.print.";
	cout << I18n::instance().get(prefix + "armorType",{ {"armorType", getArmorTypeName()}}) << endl;
	cout << I18n::instance().get(prefix + "level",    { {"level", to_string(this->level)} }) << endl;
	cout << I18n::instance().get(prefix + "atk",      { {"atk", to_string(this->atk)} }) << endl;
	cout << I18n::instance().get(prefix + "defense",  { {"defense", to_string(this->defense)} }) << endl;
	cout << I18n::instance().get(prefix + "durability",
		{ {"durability",    std::to_string(this->durability)},
		  {"durabilityMax", std::to_string(this->durabilityMax)} }) << endl;
}

void Armor::debugPrint() const
{
	using std::cout, std::endl;
	Item::debugPrint();
	print();
}

std::string Armor::getArmorTypeName() const
{
	return I18n::instance().get("item.armor.weaponType",
		{ {"armorType", getRawArmorTypeName()},
		  {"armorSlot", getArmorSlot()} });
}

float Armor::readValue(const json& j) const
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

std::string Armor::readString(const json& j, const std::string& key) const
{
	const std::string prefix = "dynamic.armor." + this->id + "." + key + ".";
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