#include "MainScreen.h"
#include <iostream>
#include "../FullPicture.h"
#include "../ButtonArg.h"
#include "../ButtonText.h"
#include "../ButtonHold.h"
#include "../TextArg.h"
#include "../ScrollList.h"
#include "../../System/PathProvider.h"
#include "../../System/GlobalVariable.h"
#include "../../I18n/FontProvider.h"

MainScreen::MainScreen() : Screen(screenTypes::MAIN, "main")
{
	addElement(FullPicture("screens/main/background.png", 1));
	addElement(Picture("screens/main/title.png", Vector2(960, 108), 1, 960));

	Picture buttonBg("screens/button_1.png", 2, 384);
	addClickable(ButtonText(Vector2(960, 324), buttonBg, Text("screen.test.button1", 32, textAlign::CENTER, WHITE, 0.0f), test));
	addClickable(ButtonText(Vector2(960, 540), buttonBg, Text("screen.test.button1", 32, textAlign::CENTER, WHITE, 0.0f), test));
	addClickable(ButtonText(Vector2(960, 756), buttonBg, Text("screen.test.button1", 32, textAlign::CENTER, WHITE, 0.0f), test));

	// Picture buttonTile("screens/button_tile_1.png", 2, 64, Vector2(400, 500));
	// addClickable(Button(Vector2(960, 540), buttonTile, test));
	//addElement(TextArg("screen.test.button2", { {"aa", &playerDistance} }, Vector2(960, 324)));
	
	std::vector<std::string> vt;
	vt.emplace_back("screen.test.button1");
	vt.emplace_back("screen.test.button2");
	vt.emplace_back("screen.test.button3");
	vt.emplace_back("screen.test.button4");
	const std::vector<const raylib::Font*> vf = { &FontProvider::instance().get("screen.test.button2"), &FontProvider::instance().get("screen.test.button2"), &FontProvider::instance().get("screen.test.button2"), &FontProvider::instance().get("screen.test.button2") };
	
	addClickable(ScrollList(Rectangle(960, 540, 1000, 500), 2, vt,
		32, textAlign::CENTER, WHITE, 0, vf, "screens/button_tile_1.png", "screens/scroll_bar.png", "b"));

	//addClickable(ButtonHold(Vector2(960, 800), buttonBg, test));
}

Screen* MainScreen::clone() const
{
	return new MainScreen(*this);
}

void MainScreen::test()
{
	playerDistance++;
}
