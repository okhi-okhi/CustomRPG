#include "EnemyGroup.h"
#include <iostream>
#include "../System/Exceptions.hpp"
#include "../Utils/JsonUtils.h"
#include "../Utils/Utilities.h"

EnemyGroup::EnemyGroup(const std::string& fileName)
{
	json j = Utils::readJsonFile("Games/EnemyGroups/" + fileName);

	try {
		this->spawnNum = static_cast<int>(readValue(j["spawnNum"]));

		this->randomEnemies = ChanceTable(j["randomEnemies"]);

		for (const auto& enemy : j["certainEnemies"].items())
		{
			for (int i=0; i < static_cast<int>(readValue(enemy.value())) ; i++) {
				this->certainEnemies.push_back(enemy.key());
			}
		}
	}
	catch (json::type_error& e) {
		throw BadValueException(fileName, e.what());
	}
}

void EnemyGroup::debugPrint() const {
	std::cout << "  隨機敵人數量: " << this->spawnNum << std::endl;
	std::cout << "  隨機敵人: " << std::endl;
	this->randomEnemies.debugPrint();
	std::cout << "  必定出現敵人:" << std::endl;
	for (const auto& enemy : this->certainEnemies) {
		std::cout << "  - "<< enemy << std::endl;
	}
}


std::vector<std::string> EnemyGroup::getEnemies() const
{
	std::vector<std::string> enemies = this->certainEnemies;
	for (int i = 0; i < this->spawnNum;i++) {
		enemies.push_back(this->randomEnemies.getRandomItem());
	}
	return enemies;
}

float EnemyGroup::readValue(const json& j)
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
