#pragma once
#include "../Screen.h"

class SettingScreen final : public Screen
{
public:
	SettingScreen();

	static void openLanguage();
	static void closeSetting();
};

