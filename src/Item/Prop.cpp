#include "Prop.h"
#include "../System/Exceptions.hpp"
#include "../Utils/ChanceTable.h"
#include "../Utils/JsonUtils.h"
#include "../Utils/Utilities.h"

Prop::Prop(const std::string& fileName)
{
	using std::cout, std::endl;
	json j = Utils::readJsonFile("Items/Props/" + fileName);
	try {
		this->itemType = itemTypes::PROP;
		this->id = fileName;
		this->rarity = readRarity(j["rarity"]);
		this->name = readString(j["name"], "name");
		this->buyPrice = static_cast<int>(readValue(j["buyPrice"]));
		this->sellPrice = static_cast<int>(readValue(j["sellPrice"]));
		this->stackable = true;

		this->description = readString(j["description"], "description");
	}
	catch (json::exception& e) {
		throw BadValueException(fileName, j, e.what());
	}
}

Prop* Prop::clone()const {
	return new Prop(*this);
}

ordered_json Prop::getAsJson()const
{
	ordered_json j = Item::getAsJson();
	j["description"] = this->description;

	return j;
}

std::vector<std::string> Prop::getDataKey() const
{
	std::vector<std::string> dataKey = Item::getDataKey();

	dataKey.emplace_back("description");

	return dataKey;
}

std::map<std::string, std::string> Prop::getData() const
{
	std::map<std::string, std::string> data = Item::getData();

	data["description"] = this->description;

	return data;
}

void Prop::print()const
{
	using std::cout, std::endl;
	Item::print();
	const std::string prefix = "item.prop.print.";
	cout << I18n::instance().get(prefix + "description", { {"description", this->getDescription()} }) << endl;
}

void Prop::debugPrint() const
{
	using std::cout, std::endl;
	Item::debugPrint();
	print();
}

void Prop::onUse() const
{
}

float Prop::readValue(const json& j) const
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

std::string Prop::readString(const json& j, const std::string& key) const
{
	const std::string prefix = "dynamic.prop." + this->id + "." + key + ".";
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