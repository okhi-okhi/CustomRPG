#pragma once
#include "../Screen.h"

class SettingScreen final : public Screen
{
private:
	raylib::Sound testSound;
public:
	SettingScreen();

	void changeMasterVolume();
	static void openLanguage();
	static void closeSetting();
};

