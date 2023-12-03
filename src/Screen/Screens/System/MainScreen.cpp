#include "MainScreen.h"
#include <iostream>
#include "../../FullPicture.h"
#include "../../ButtonText.h"
#include "../../ScreenManager.h"
#include "../../System/GlobalVariable.h"

MainScreen::MainScreen() : Screen(ScreenType::MAIN, "main")
{
	addElement(make_shared<FullPicture>(File("screens/main/background.png"), 1));
	addElement(make_shared<Picture>(Vector2{ 960, 108 }, File("screens/main/title.png"), 1, 960, ScaleMode::BICUBIC));

	const Picture buttonBg({ "screens/button_1.png" }, 2, 384);

	addElement(make_shared<ButtonText>(Vector2{ 960, 324 }, Button(buttonBg, openSelectGame), Text("screen.main.selectGame", TextAlign::CENTER, 0.0f)));
	addElement(make_shared<ButtonText>(Vector2{ 960, 540 }, Button(buttonBg, openSetting), Text("screen.main.setting", TextAlign::CENTER, 0.0f)));
	addElement(make_shared<ButtonText>(Vector2{ 960, 756 }, Button(buttonBg, closeWindow), Text("screen.main.quit", TextAlign::CENTER, 0.0f)));
}

void MainScreen::openSelectGame()
{
	ScreenManager::instance().showScreen(ScreenType::SELECT_GAME);
	ScreenManager::instance().hideScreen(ScreenType::MAIN);
}

void MainScreen::openSetting()
{
	ScreenManager::instance().showScreen(ScreenType::SETTING);
}

void MainScreen::closeWindow()
{
	running = false;
}
