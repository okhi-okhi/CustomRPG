#include "MainScreen.h"
#include <iostream>
#include "../FullPicture.h"
#include "../ButtonArg.h"
#include "../ButtonText.h"
#include "../ButtonHold.h"
#include "../TextArg.h"
#include "../ScrollList.h"
#include "../Slider.h"
#include "../../System/PathProvider.h"
#include "../../System/GlobalVariable.h"
#include "../../I18n/FontProvider.h"

MainScreen::MainScreen() : Screen(screenTypes::MAIN, "main")
{
	addElement(new FullPicture("screens/main/background.png", 1));
	addElement(new Picture("screens/main/title.png", Vector2(960, 108), 1, 960));

	const Picture buttonBg("screens/button_1.png", 2, 384);
	addElement(new ButtonText(Vector2(960, 324), buttonBg, Text("screen.test.button1", 32, textAlign::CENTER, WHITE, 0.0f), test));
	addElement(new ButtonText(Vector2(960, 540), buttonBg, Text("screen.test.button1", 32, textAlign::CENTER, WHITE, 0.0f), test));
	addElement(new ButtonText(Vector2(960, 756), buttonBg, Text("screen.test.button1", 32, textAlign::CENTER, WHITE, 0.0f), test));
	
	std::vector<std::string> vt;
	vt.emplace_back("screen.test.button1");
	vt.emplace_back("screen.test.button2");
	vt.emplace_back("screen.test.button3");
	vt.emplace_back("screen.test.button4");
	vt.emplace_back("addas");
	const std::vector<const raylib::Font*> vf = { &FontProvider::instance().get("screen.test.button2"), &FontProvider::instance().get("screen.test.button2"), &FontProvider::instance().get("screen.test.button2"), &FontProvider::instance().get("screen.test.button2"), &FontProvider::instance().get("screen.test.button2") };

	auto* scrollList = new ScrollList(Rectangle(960, 540, 1000, 500), 2, vt,
	                                  32, textAlign::CENTER, WHITE, 0, vf, "screens/button_tile_1.png", "screens/scroll_bar.png", "screens/button_tile_1.png");
	addElement(scrollList);

	// Slider* slider = new Slider(Rectangle(960, 540, 500, 32), "screens/scroll_bar.png", "screens/button_tile_1.png", 64, &playerDistance, 0, 10, true);
	// addElement(slider);
	// addElement(new TextArg("screen.test.button2", { {"aa", &playerDistance} }, Vector2(960, 324)));
}

void MainScreen::test()
{
	playerDistance++;
}
