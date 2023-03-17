#pragma once
#include "../Player/Player.h"
#include "../Utils/Singleton.h"
#include <set>

class Game : public Singleton<Game>
{
private:
	int choice;
	Player* player{};

	std::string currentPlace;
	std::set<std::string> nextPlaces{};

public:
	explicit Game(token) : choice(0) {}

	void init(Player& player);

	void gameMenu();
	void allyMenu();
	void teamMenu();
	void inventoryMenu();
	//Game Menu
	void printStats() const;
	void adventure();
	//Ally Menu
	//Team Menu
	void editMember();
	void setOrder() const;
};

