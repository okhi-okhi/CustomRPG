#include "SettingScreen.h"
#include "../ScreenManager.h"
#include "../ButtonText.h"

SettingScreen::SettingScreen() : Screen(screenTypes::SETTING, "setting")
{
	addElement(new Picture("screens/setting/background.png", Vector2(960, 540), 1, 540));

	const Picture buttonBg("screens/button_1.png", 2, 384);
	addElement(new ButtonText(Vector2(960, 540), buttonBg, Text("screen.setting.button1", 48, textAlign::CENTER, WHITE, 0.0f), openLanguage));
	addElement(new ButtonText(Vector2(960, 720), buttonBg, Text("screen.setting.button2", 48, textAlign::CENTER, WHITE, 0.0f), closeSetting));
}

void SettingScreen::openLanguage()
{
	ScreenManager::instance().addScreen(screenTypes::LANGUAGE);
	ScreenManager::instance().removeScreen(screenTypes::SETTING);
}

void SettingScreen::closeSetting()
{
	ScreenManager::instance().removeScreen(screenTypes::SETTING);
}
