#include "MainScreen.h"
#include <iostream>
#include "../FullPicture.h"
#include "../ButtonArg.h"
#include "../ButtonText.h"
#include "../TextArg.h"
#include "../ScrollList.h"
#include "../../System/PathProvider.h"
#include "../../System/GlobalVariable.h"

MainScreen::MainScreen() : Screen(screenTypes::MAIN, "main")
{
	addElement(FullPicture("screens/main/background.png", 1));
	addElement(Picture("screens/main/title.png", Vector2(960, 108), 1, 960));
	addClickable(ButtonText("screens/button_1.png", Vector2(960, 324), 384, "screen.test.button1", 32, textAlign::CENTER, WHITE, 0.0f, test));
	addClickable(ButtonText("screens/button_1.png", Vector2(960, 540), 384, "screen.test.button1", 32, textAlign::CENTER, WHITE, 0.0f, test));
	addClickable(ButtonText("screens/button_1.png", Vector2(960, 756), 384, "screen.test.button1", 32, textAlign::CENTER, WHITE, 0.0f, test));
	addClickable(Button("screens/button_tile_1.png", Vector2(960, 540), 196, Vector2(588, 392), test));

	Text t("screen.test.button2", Vector2(960, 540), 32, textAlign::CENTER, BLACK, 1.0f);
	std::vector<Text> vt;
	vt.push_back(t);
	vt.push_back(t);
	addClickable(ScrollList(Rectangle(960, 540, 1000, 500), 2, vt, "screens/button_tile_1.png", "a", "b"));
}

Screen* MainScreen::clone() const
{
	return new MainScreen(*this);
}

void MainScreen::test()
{
	playerDistance++;
}
