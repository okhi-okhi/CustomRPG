#include "MainScreen.h"
#include <iostream>
#include "../FullPicture.h"
#include "../ButtonArg.h"
#include "../ButtonText.h"
#include "../TextArg.h"
#include "../../System/PathProvider.h"
#include "../../System/GlobalVariable.h"

MainScreen::MainScreen() : Screen(screenTypes::MAIN, "main")
{
	addElement(FullPicture("screens/main/background.png", 1));
	addElement(Picture("screens/main/title.png", Vector2(960, 108), 1, 960));
	addButton(ButtonText("screens/button_1.png", Vector2(960, 324), 384, "screen.test.button1", 32, textAlign::CENTER, WHITE, 0.0f, test));
	addButton(ButtonText("screens/button_1.png", Vector2(960, 540), 384, "screen.test.button1", 32, textAlign::CENTER, WHITE, 0.0f, test));
	addButton(ButtonText("screens/button_1.png", Vector2(960, 864), 384, "screen.test.button1", 32, textAlign::CENTER, WHITE, 0.0f, test));
	addButton(Button("screens/button_tile_1.png", Vector2(960, 540), 196, Vector2(588, 392), test));
	//addElement(Text("screen.test.button1", Vector2(960, 100), 58, textAlign::CENTER, BLACK, 0.0f));
}

Screen* MainScreen::clone() const
{
	return new MainScreen(*this);
}

void MainScreen::test()
{
	playerDistance++;
}
