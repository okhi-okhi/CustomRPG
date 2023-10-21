#pragma once
#include <Sound.hpp>
#include "../../Screen.h"

class SettingScreen final : public Screen
{
private:
	raylib::Sound testSound;
	void changeMasterVolume();
	static void openLanguage();
	static void closeSetting();

public:
	SettingScreen();
};

