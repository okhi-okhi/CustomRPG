#include "MainScreen.h"
#include <iostream>
#include "../FullPicture.h"
#include "../ButtonArg.h"
#include "../ButtonText.h"
#include "../ButtonHold.h"
#include "../TextArg.h"
#include "../ScrollList.h"
#include "../Slider.h"
#include "../ScreenManager.h"
#include "../../System/PathProvider.h"
#include "../../System/GlobalVariable.h"
#include "../../I18n/FontProvider.h"

MainScreen::MainScreen() : Screen(screenTypes::MAIN, "main")
{
	addElement(new FullPicture("screens/main/background.png", 1));
	addElement(new Picture("screens/main/title.png", Vector2(960, 108), 1, 960));

	const Picture buttonBg("screens/button_1.png", 2, 384);
	addElement(new ButtonText(Vector2(960, 324), buttonBg, Text("screen.main.button1", 48, textAlign::CENTER, WHITE, 0.0f), test));
	addElement(new ButtonText(Vector2(960, 540), buttonBg, Text("screen.main.button2", 48, textAlign::CENTER, WHITE, 0.0f), openSetting));
	addElement(new ButtonText(Vector2(960, 756), buttonBg, Text("screen.main.button3", 48, textAlign::CENTER, WHITE, 0.0f), CloseWindow));
	
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

// MainScreen::~MainScreen()
// {
// 	for (auto& element : this->elements)
// 	{
// 		delete element;
// 	}
// }

void MainScreen::test()
{
	playerDistance++;
}

void MainScreen::openSetting()
{
	ScreenManager::instance().addScreen(screenTypes::SETTING);
}
