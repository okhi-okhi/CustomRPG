#pragma once
#include"../Player/Player.h"
#include"Place.h"

class Event
{
public:
	static constexpr int EventNum = 3;

	static void generateEvent(Player& player, Place& place);

	static void enemyEncouter(Player& player, Place& place);
	static void shopEncouter(Player& player);
	static void scriptEncouter(Player& player, const Place& place);
};

