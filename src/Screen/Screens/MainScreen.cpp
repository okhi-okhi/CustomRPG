#include "MainScreen.h"
#include <iostream>
#include "../FullPicture.h"
#include "../ButtonText.h"
#include "../TextArg.h"
#include "../ScrollList.h"
#include "../ScreenManager.h"
#include "../../System/GlobalVariable.h"

MainScreen::MainScreen() : Screen(screenTypes::MAIN, "main")
{
	addElement(make_shared<FullPicture>("screens/main/background.png", 1));
	addElement(make_shared<Picture>("screens/main/title.png", Vector2(960, 108), 1, 960));

	const Picture buttonBg("screens/button_1.png", 2, 384);
	addElementGroup(make_shared<ButtonText>(Vector2(960, 324), Button(buttonBg, test), Text("screen.main.button1", 48, textAlign::CENTER, WHITE, 0.0f)));
	addElementGroup(make_shared<ButtonText>(Vector2(960, 540), Button(buttonBg, openSetting), Text("screen.main.button2", 48, textAlign::CENTER, WHITE, 0.0f)));
	addElementGroup(make_shared<ButtonText>(Vector2(960, 756), Button(buttonBg, closeWindow), Text("screen.main.button3", 48, textAlign::CENTER, WHITE, 0.0f)));
	
	// std::vector<std::string> vt;
	// vt.emplace_back("screen.test.text1");
	// vt.emplace_back("screen.test.text2");
	// vt.emplace_back("screen.test.text3");
	// vt.emplace_back("screen.test.text4");
	// vt.emplace_back("screen.test.text5");
	//
	// auto* scrollList = new ScrollList(Rectangle(960, 540, 1000, 500), 2, vt,
	//                                   32, textAlign::CENTER, WHITE, 0, "screens/button_tile_1.png", "screens/scroll_bar.png", "screens/button_tile_1.png");
	// addElement(scrollList);
	//
	// addElement(new TextArg("screen.test.button2", { {"aa", &scrollList->getCurrentIndex()}}, Vector2(960, 324)));
}

void MainScreen::test()
{
	playerDistance++;
}

void MainScreen::openSetting()
{
	ScreenManager::instance().addScreen(screenTypes::SETTING);
}

void MainScreen::closeWindow()
{
	running = false;
}
