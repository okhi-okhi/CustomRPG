#include "Occupation.h"
#include "../System/Exceptions.hpp"
#include "../Utils/ChanceTable.h"
#include "../Utils/JsonUtils.h"
#include "../Utils/Utilities.h"

Occupation::Occupation(const std::string& fileName)
{
	using std::cout, std::endl;
	json j = Utils::readJsonFile("Entitys/Occupations/" + fileName);
	try {
		this->id = fileName;
		this->name = readString("name");
		this->description = readString("description");
		this->hpMaxScale = static_cast<int>(readValue(j["hpMaxScale"]));
		this->manaMaxScale = static_cast<int>(readValue(j["manaMaxScale"]));
		this->luckScale = static_cast<int>(readValue(j["luckScale"]));
		this->talentPointScale = static_cast<int>(readValue(j["talentPointScale"]));
	}
	catch (json::exception& e) {
		throw BadValueException(fileName, j, e.what());
	}
}

void Occupation::print() const
{
	using std::cout, std::endl;
	const std::string prefix = "entity.occupation.print.";
	cout << I18n::instance().get(prefix + "name",             { {"name", this->getName()} }) << endl;
	cout << I18n::instance().get(prefix + "description",      { {"description", this->getDescription()} }) << endl;
	cout << I18n::instance().get(prefix + "talentPointScale", { {"talentPointScale", std::to_string(this->talentPointScale)} }) << endl;
}

void Occupation::debugPrint() const
{
	using std::cout, std::endl, std::to_string;
	const std::string prefix = "entity.occupation.debugPrint.";
	cout << I18n::instance().get(prefix + "id",           { {"id", this->id} }) << endl;
	print();
	cout << I18n::instance().get(prefix + "hpMaxScale",   { {"hpMaxScale", to_string(this->hpMaxScale)} }) << endl;
	cout << I18n::instance().get(prefix + "manaMaxScale", { {"manaMaxScale", to_string(this->manaMaxScale)} }) << endl;
	cout << I18n::instance().get(prefix + "luckScale",    { {"luckScale", to_string(this->luckScale)} }) << endl;
}

float Occupation::readValue(const json& j)
{
	if (j.is_number()) {
		return JsonUtils::readValueFromNum(j);
	}
	throw NoReadFunctionException(j);
}

std::string Occupation::readString(const std::string& key) const
{
	return "dynamic.occupation." + this->id + "." + key;
}