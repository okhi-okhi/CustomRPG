#include "Place.h"
#include <iostream>
#include "EnemyGroup.h"
#include "../System/GlobalVariable.h"
#include "../System/Exceptions.hpp"
#include "../Utils/JsonUtils.h"
#include "../Utils/Utilities.h"

Place::Place(const std::string& fileName)
{
	json j = Utils::readJsonFile("Games/Places/" + fileName);

	try {
		this->id = fileName;
		this->name = readString(j["name"], "name");
		this->minDistance = static_cast<int>(readValue(j["minDistance"]));
		this->description = readString(j["description"], "description");
		this->opening = readString(j["opening"], "opening");
		this->neighbours = ChanceTable(j["neighbours"]);
		this->events = ChanceTable(j["events"]);
		this->scripts = ChanceTable(j["scripts"]);
		this->enemyGroups = ChanceTable(j["enemyGroups"]);

		bool canModify = false;
		json lastGroup;
		for(const auto& modifyGroup : j["modifyGroups"].items())
		{
			if(playerFame > modifyGroup.value()["fameCondition"] && playerDistance > modifyGroup.value()["distanceCondition"])
			{
				lastGroup = modifyGroup.value();
				canModify = true;
			}
		}
		if(canModify)
		{
			if (lastGroup.contains("opening"))
				this->opening = readString(lastGroup["opening"], "opening");
			if (lastGroup.contains("neighbours"))
				this->neighbours = ChanceTable(lastGroup["neighbours"]);
			if (lastGroup.contains("events"))
				this->events = ChanceTable(lastGroup["events"]);
			if (lastGroup.contains("scripts"))
				this->scripts = ChanceTable(lastGroup["scripts"]);
			if (lastGroup.contains("enemyGroups"))
				this->enemyGroups = ChanceTable(lastGroup["enemyGroups"]);
		}
	}
	catch (json::exception& e) {
		throw BadValueException(fileName, e.what());
	}
}

void Place::debugPrint() const
{
	std::cout << "名字: " << this->name << "\n";
	std::cout << "最小距離: " << this->minDistance << "\n";
	std::cout << "敘述: " << this->description << "\n";
	std::cout << "開場白: " << this->opening << "\n";
	std::cout << "鄰近地點:\n";
	this->neighbours.debugPrint();
	std::cout << "事件:\n";
	this->events.debugPrint();
	std::cout << "劇本:\n";
	this->scripts.debugPrint();
	std::cout << "敵人群:\n";
	this->enemyGroups.debugPrint();
	std::cout << "敵人群詳細資訊:\n";
	for (const auto& [fst, snd] : this->enemyGroups.getChanceTable()) {
		EnemyGroup(fst).debugPrint();
	}
}

std::string Place::getAsString() const
{
	return this->name + " : " + this->description + "\n";
}

std::set<std::string> Place::getPlaces(const int& num)
{
	for (const auto& [fst, snd] : this->neighbours.getChanceTable()) {
		Place p(fst);
		if (p.getMinDistance() > playerDistance) {
			this->neighbours.removeItem(fst);
		}
	}

	if (this->neighbours.getSize() == 0) {
		std::cout << "沒有可前進的地點! 將把你傳回初始地點" << std::endl;
		std::set<std::string> places;
		places.insert("bar");
		return places;
	}

	return this->neighbours.getRandomItems(num);
}

std::vector<std::string> Place::getEnemies() const
{
	return EnemyGroup(this->enemyGroups.getRandomItem()).getEnemies();
}

float Place::readValue(const json& j)
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

std::string Place::readString(const json& j, const std::string& key) const
{
	const std::string prefix = "dynamic.place." + this->id + "." + key;
	if (j.is_null()) {
		return prefix + ".default";
	}
	if (j.is_string()) {
		return prefix + j.get<std::string>();
	}
	if (j.is_object()) {
		return prefix + ChanceTable(j).getRandomItem();
	}
	throw NoReadFunctionException(j);
}
