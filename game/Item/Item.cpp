#include "Item.h"
#include "../System/Exceptions.hpp"
#include "../System/GlobalVariable.h"
#include "../Utils/ChanceTable.h"
#include "../Utils/JsonUtils.h"
#include "../Utils/Utilities.h"

ordered_json Item::getAsJson()const {
	ordered_json j;
	j["id"] = this->id;
	j["name"] = this->name;
	j["buyPrice"] = this->buyPrice;
	j["sellPrice"] = this->sellPrice;
	j["rarity"] = this->rarity;

	return j;
}

std::vector<std::string> Item::getDataKey() const
{
	std::vector<std::string> dataKey;
	dataKey.emplace_back("name");

	return dataKey;
}

std::map<std::string, std::string> Item::getData() const
{
	std::map<std::string, std::string> data;
	data["name"] = getName();

	return data;
}

void Item::print() const {
	using std::cout, std::endl;
	const std::string prefix = "item.item.print.";
	cout << I18n::instance().get(prefix + "name",
		{ {"name"  , getRawName()},
		  {"rarity", getRarityName(getRarity())} }) << endl;
	//cout << I18n::instance().get(prefix + "rarity", { {"rarity", getRarityName(getRarity())} }) << endl;
}

void Item::debugPrint() const
{
	using std::cout, std::endl, std::to_string;
	const std::string prefix = "item.item.debugPrint.";
	cout << I18n::instance().get(prefix + "itemType",  { {"itemType", to_string(static_cast<int>(this->itemType))} }) << endl;
	cout << I18n::instance().get(prefix + "id",        { {"id",this->id} }) << endl;
	cout << I18n::instance().get(prefix + "buyPrice",  { {"buyPrice",  to_string(this->buyPrice)} }) << endl;
	cout << I18n::instance().get(prefix + "sellPrice", { {"sellPrice", to_string(this->sellPrice)} }) << endl;
	cout << I18n::instance().get(prefix + "stackable", { {"stackable", Utils::boolToString(this->stackable)} }) << endl;
}

std::string Item::getRarityName(const enum rarity& rarity)
{
	switch (rarity) {
	case rarity::COMMON:
		return I18n::instance().get("stat.rarityName.common");
	case rarity::UNCOMMON:
		return I18n::instance().get("stat.rarityName.uncommon");
	case rarity::RARE:
		return I18n::instance().get("stat.rarityName.rare");
	case rarity::EPIC:
		return I18n::instance().get("stat.rarityName.epic");
	case rarity::LEGENDARY:
		return I18n::instance().get("stat.rarityName.legendary");
	}
	return "";
}

std::string Item::getName() const
{
	return I18n::instance().get("item.item.name",
		{ {"rarity", getRarityName(this->rarity)},
		  {"name", I18n::instance().get(this->name)} });
}

float Item::readValue(const json& j) const
{
	if (j.is_number()) {
		return JsonUtils::readValueFromNum(j);
	}
	if (j.is_string()) {
		return JsonUtils::readValueFromString(j);
	}
	if (j.contains("min") && j.contains("max")) {
		return JsonUtils::readValueFromRange(j);
	}
	if (j.contains("expect") && j.contains("floatingRange")) {
		return JsonUtils::readValueFromExpect(j);
	}
	throw NoReadFunctionException(j);
}

rarity Item::readRarity(const json& j)
{
	if (j.is_number()) {
		return static_cast<enum rarity>(JsonUtils::readValueFromNum(j));
	}
	if (j.is_string()) {
		return static_cast<enum rarity>(JsonUtils::readValueFromString(j));
	}
	if (j.contains("min") && j.contains("max")) {
		return static_cast<enum rarity>(JsonUtils::readValueFromRange(j));
	}
	if (j.contains("expect") && j.contains("floatingRange")) {
		return static_cast<enum rarity>(JsonUtils::readValueFromExpect(j));
	}
	if (j.is_object()) {
		return static_cast<enum rarity>(std::stoi(ChanceTable(j).getRandomItem()));
	}
	throw NoReadFunctionException(j);
}
