#include "MainScreen.h"
#include <iostream>
#include "../FullPicture.h"
#include "../ButtonText.h"
#include "../TextArg.h"
#include "../TextBox.h"
#include "../ScrollList.h"
#include "../ScreenManager.h"
# include "../../System/GlobalVariable.h"

MainScreen::MainScreen() : Screen(ScreenType::MAIN, "main")
{
	addElement(make_shared<FullPicture>(File("screens/main/background.png"), 1));
	addElement(make_shared<Picture>(Vector2(960, 108), File("screens/main/title.png"), 1, 960, ScaleMode::BICUBIC));

	const Picture buttonBg({ "screens/button_1.png" }, 2, 384);
	addElementGroup(make_shared<ButtonText>(Vector2(960, 324), Button(buttonBg, openSelectGame), Text("screen.main.button1", 48, TextAlign::CENTER, 0.0f)));
	addElementGroup(make_shared<ButtonText>(Vector2(960, 540), Button(buttonBg, openSetting), Text("screen.main.button2", 48, TextAlign::CENTER, 0.0f)));
	addElementGroup(make_shared<ButtonText>(Vector2(960, 756), Button(buttonBg, closeWindow), Text("screen.main.button3", 48, TextAlign::CENTER, 0.0f)));

	addElement(make_shared<TextBox>(Rectangle(400, 756, 200, 100), "screen.main.button4", 48, TextAlign::LEFT, 0.0f));
}

void MainScreen::openSelectGame()
{
	ScreenManager::instance().addScreen(ScreenType::SELECT_GAME);
	ScreenManager::instance().removeScreen(ScreenType::MAIN);
}

void MainScreen::openSetting()
{
	ScreenManager::instance().addScreen(ScreenType::SETTING);
}

void MainScreen::closeWindow()
{
	running = false;
}
