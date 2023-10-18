#include "Material.h"
#include "../System/Exceptions.hpp"
#include "../Utils/ChanceTable.h"
#include "../Utils/JsonUtils.h"
#include "../Utils/Utilities.h"

CustomRPG::Material::Material(const std::string& fileName)
{
	using std::cout, std::endl;
	json j = Utils::loadJsonFile("Items/Materials/" + fileName);
	try {
		this->itemType = itemTypes::MATERIAL;
		this->id = fileName;
		this->rarity = readRarity(j["rarity"]);
		this->name = readString(j["name"], "name");
		this->buyPrice = static_cast<int>(readValue(j["buyPrice"]));
		this->sellPrice = static_cast<int>(readValue(j["sellPrice"]));
		this->stackable = true;

		this->description = readString(j["description"], "description");
	}
	catch (json::exception& e) {
		throw BadValueException(fileName, e.what());
	}
}

CustomRPG::Material* CustomRPG::Material::clone()const {
	return new Material(*this);
}

ordered_json CustomRPG::Material::getAsJson()const
{
	ordered_json j = Item::getAsJson();
	j["description"] = this->description;

	return j;
}

std::vector<std::string> CustomRPG::Material::getDataKey() const
{
	std::vector<std::string> dataKey = Item::getDataKey();

	dataKey.emplace_back("description");

	return dataKey;
}

std::map<std::string, std::string> CustomRPG::Material::getData() const
{
	std::map<std::string, std::string> data = Item::getData();

	data["description"] = this->description;

	return data;
}

void CustomRPG::Material::print()const
{
	using std::cout, std::endl;
	Item::print();
	const std::string prefix = "item.material.print.";
	cout << I18n::instance().get(prefix + "description", { {"description", this->getDescription()} }) << endl;
}

void CustomRPG::Material::debugPrint() const
{
	using std::cout, std::endl;
	Item::debugPrint();
	print();
}

float CustomRPG::Material::readValue(const json& j) const
{
	if (j.is_number()) {
		return JsonUtils::readValueFromNum(j);
	}
	if (j.is_string()) {
		return JsonUtils::readValueFromString(j);
	}
	if (JsonUtils::isRarityTable(j)) {
		return JsonUtils::readValueFromRarity(j, static_cast<int>(this->rarity));
	}
	throw NoReadFunctionException(j);
}

std::string CustomRPG::Material::readString(const json& j, const std::string& key) const
{
	const std::string prefix = "dynamic.material." + this->id + "." + key + ".";
	if (j.is_null()) {
		return prefix + "default";
	}
	if (j.is_string()) {
		return prefix + j.get<std::string>();
	}
	if (JsonUtils::isRarityTable(j)) {
		return prefix + j[std::to_string(static_cast<int>(this->rarity))].get<std::string>();
	}
	throw NoReadFunctionException(j);
}