#pragma once
#include "../Screen.h"

class MainScreen final : public Screen
{
public:
	MainScreen();

	static void openSelectGame();
	static void openSetting();
	static void closeWindow();
};

