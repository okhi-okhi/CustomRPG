#include "SettingScreen.h"
#include <fstream>
#include <json.hpp>
#include "../../System/PathProvider.h"
#include "../../System/GlobalVariable.h"
#include "../ScreenManager.h"
#include "../ButtonText.h"
#include "../SliderText.h"
#include "../TextArg.h"
#include "../../System/SystemConfig.h"

SettingScreen::SettingScreen() : Screen(screenTypes::SETTING, "setting")
{
	this->testSound.Load(PathProvider::instance().getFromSystem(resourcesFolder::SOUNDS) + "button_click.wav");

	addElement(make_shared<Picture>("screens/setting/background.png", Vector2(960, 540), 1, 540));

	addElementGroup(make_shared<SliderText>(Vector2(1000, 320), 
		Slider(
			Picture("screens/slider_bar.png", 2, 12),
			Picture("screens/slider_background_horizontal.png", 2, 32, Vector2(250, 32)),
			&SystemConfig::instance().getMasterVolume(), 0, 100, true, [this] { changeMasterVolume(); }
		),
		Text("screen.setting.masterVolume", 48, textAlign::CENTER, WHITE, 1.0f),
		TextArg("screen.setting.currentMasterVolume", std::map<std::string, argTypes>{ {"volume", & SystemConfig::instance().getMasterVolume()} }, Vector2(1170, 325), 48, textAlign::CENTER, WHITE, 1.0f)
	));

	const Picture buttonBg("screens/button_1.png", 2, 384);
	addElementGroup(make_shared<ButtonText>(Vector2(960, 540), Button(buttonBg, openLanguage), Text("screen.setting.button1", 48, textAlign::CENTER, WHITE, 0.0f)));
	addElementGroup(make_shared<ButtonText>(Vector2(960, 720), Button(buttonBg, closeSetting), Text("screen.setting.button2", 48, textAlign::CENTER, WHITE, 0.0f)));
}

void SettingScreen::changeMasterVolume()
{
	using nlohmann::json;
	SetMasterVolume(static_cast<float>(SystemConfig::instance().getMasterVolume()) / 100);
	this->testSound.Play();
	try {
		std::ifstream inFile(PathProvider::instance().getConfigPath());
		json j = json::parse(inFile);
		nlohmann::ordered_json j2;
		j2["masterVolume"] = SystemConfig::instance().getMasterVolume();
		j.update(j2, true);
		inFile.close();
		std::ofstream outFile(PathProvider::instance().getConfigPath());
		outFile << j.dump(4);
		outFile.close();
	}
	catch (json::exception& e)
	{
		std::cout << e.what();
	}
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
