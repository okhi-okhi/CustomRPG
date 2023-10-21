#pragma once
#include "../../Screen.h"

class MainScreen final : public Screen
{
private:
	static void openSelectGame();
	static void openSetting();
	static void closeWindow();

public:
	MainScreen();
};

