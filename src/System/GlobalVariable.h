#pragma once
enum class menuStatus {
	SYSTEM = 0,
	SETTING,
	GAME,
	ALLY,
	TEAM,
	INV,
};
extern int playerDistance;
extern int playerFame;
extern menuStatus menuStatu;
extern float zoomPercent;
extern bool running;