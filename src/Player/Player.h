#pragma once
#include <vector>
#include "../System/GlobalVariable.h"
#include "Inventory.h"
#include "Team.h"

class Player
{
private:
	std::string name;
	int gold;
	int distance;
	int fame;
	Team team;
	std::vector<Ally> allAllys;
	Inventory inventory;
	//std::vector<Magic> allMagics;

public:
	Player() : gold(10), distance(0), fame(0){}
	explicit Player(std::string name) : name(std::move(name)), gold(10), distance(0), fame(0) {}

	void printStats() const;
	void printTeam() const { this->team.print(); }
	void printAllAllys() const;
	void printInventory() const { this->inventory.print(); }

	void addAlly(const Ally& ally) { this->allAllys.push_back(ally); }

	void gainDistance() { this->distance++; playerDistance++; }
	void gainGold(const int gold) { this->gold += gold; }
	void gainFame(const int fame) { this->fame += fame; playerFame += fame;}

	ordered_json getDataAsJson();
	ordered_json getAllysAsJson();
	ordered_json getInvAsJson() const;

	const std::string& getName() const { return this->name; }
	const int& getGold() const { return this->gold; }
	const int& getDistance() const { return this->distance; }
	const int& getFame() const { return this->fame; }

	Team& getTeam() { return this->team; }
	std::vector<Ally>& getAllAllys() { return this->allAllys; }
	Inventory& getInv() { return this->inventory; }
};

