#include "Race.h"
#include "../System/Config.h"
#include "../System/Exceptions.hpp"
#include "../Utils/ChanceTable.h"
#include "../Utils/JsonUtils.h"
#include "../Utils/Utilities.h"
 
Race::Race(const std::string& fileName)
{
	using json = nlohmann::json;
	json j = Utils::readJsonFile("Entitys/Races/" + fileName);

	try {
		this->id = fileName;
		this->name = readString("name");
		this->description = readString("description");
		this->hpMaxBase = static_cast<int>(readValue(j["hpMaxBase"]));
		this->manaMaxBase = static_cast<int>(readValue(j["manaMaxBase"]));
		this->luckBase = static_cast<int>(readValue(j["luckBase"]));

		for(const std::string& talent : Config::instance().getTalents()) {
			this->talents[talent] = static_cast<int>(readValue(j["talents"][talent]));
		}
	}
	catch (json::exception& e) {
		throw BadValueException(fileName, j, e.what());
	}
}

void Race::print() const
{
	using std::cout, std::endl, std::to_string;
	const std::string prefix = "entity.race.print.";
	cout << I18n::instance().get(prefix + "name",        { {"name", this->getName()} }) << endl;
	cout << I18n::instance().get(prefix + "description", { {"description", this->getDescription()} }) << endl;

	for (const auto& [key, value] : this->talents) {
		cout << I18n::instance().get(prefix + key, { {key, to_string(value)} }) << endl;
	}
}

void Race::debugPrint() const
{
	using std::cout, std::endl, std::to_string;
	const std::string prefix = "entity.race.debugPrint.";
	cout << I18n::instance().get(prefix + "id",          { {"id", this->id} }) << endl;
	print();
	cout << I18n::instance().get(prefix + "hpMaxBase",   { {"hpMaxBase", to_string(this->hpMaxBase)} }) << endl;
	cout << I18n::instance().get(prefix + "manaMaxBase", { {"manaMaxBase", to_string(this->manaMaxBase)} }) << endl;
	cout << I18n::instance().get(prefix + "luckBase",    { {"luckBase", to_string(this->luckBase)} }) << endl;
}

void Race::modifyStat(const std::string& key, const int& value)
{
	std::vector <std::string> modifyKeyMap = { "hpMax", "manaMax", "luck"};

	for (const auto& talentName : this->talents | std::views::keys) {
		modifyKeyMap.push_back(talentName);
	}

	const auto it = std::ranges::find(modifyKeyMap, key);
	if (it == modifyKeyMap.end()) {
		throw InvalidKeyException(key);
	}
	switch (const auto index = it - modifyKeyMap.begin()) {
	case 0:
		this->hpMaxBase += value;
		if (this->hpMaxBase < 0) this->hpMaxBase = 0;
		break;
	case 1:
		this->manaMaxBase += value;
		if (this->manaMaxBase < 0) this->manaMaxBase = 0;
		break;
	case 2:
		this->luckBase += value;
		if (this->luckBase < 0) this->luckBase = 0;
		break;
	default:
		this->talents[modifyKeyMap[index]] += value;
		if (this->talents[modifyKeyMap[index]] < 0) this->talents[modifyKeyMap[index]] = 0;
	}
}

const int& Race::getTalent(const std::string& key) const
{
	if(this->talents.contains(key)) {
		return this->talents.find(key)->second;
	}
	throw InvalidKeyException(key);
}

float Race::readValue(const json& j)
{
	if (j.is_number()) {
		return JsonUtils::readValueFromNum(j);
	}
	throw NoReadFunctionException(j);
}

std::string Race::readString(const std::string& key) const
{
	return "dynamic.race." + this->id + "." + key;
}