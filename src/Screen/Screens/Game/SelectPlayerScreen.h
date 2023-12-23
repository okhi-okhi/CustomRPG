#pragma once
#include "../../Screen.h"

struct PlayerInfo
{
	int gold;
	int diamond;
	int distance;
	int fame;

	PlayerInfo() : gold(0), diamond(0), distance(0), fame(0) {}
};

class SelectPlayerScreen : public Screen
{
private:
	vector<PlayerInfo> playersInfo;

	void loadPlayerFile();

public:
	SelectPlayerScreen();
};

