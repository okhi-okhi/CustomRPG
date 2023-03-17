#pragma once
#include "../System/GlobalVariable.h"
#include "../Utils/ChanceTable.h"

class EnemyGroup
{
private:
	int spawnNum;
	ChanceTable randomEnemies;
	std::vector<std::string> certainEnemies;

	static float readValue(const json& j);

public:
	EnemyGroup();
	explicit EnemyGroup(const std::string& fileName);

	void debugPrint() const;
	std::vector<std::string> getEnemies() const;
};

