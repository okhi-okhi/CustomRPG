#include "MainScreen.h"
#include <iostream>
#include "../FullPicture.h"
#include "../ButtonArg.h"
#include "../TextArg.h"
#include "../../System/PathProvider.h"
#include "../../System/GlobalVariable.h"

MainScreen::MainScreen() : Screen(screenTypes::MAIN, "main")
{
	addElement(FullPicture("screens/main/background.png", 1));
	addButton(Button("screens/button_1.png", Vector2(0.5f, 0.2f), 0.2f, "screen.test.button1", 0.03f, textAlign::CENTER, BLACK, 0.0f, test));
	addButton(ButtonArg("screens/button_1.png", Vector2(0.5f, 0.5f), 0.2f, "screen.test.button2", { {"aa", &playerDistance} }, 0.03f, textAlign::CENTER, BLACK, 0.0f, test));
	// addElement(Picture("screens/button_1.png", Vector2(0.55f, 0.15f), 2, 0.1f));
	// addElement(Picture("screens/button_1.png", Vector2(0.45f, 0.25f), 2, 0.1f));
	addButton(Button("screens/button_1.png", Vector2(0.1f, 0.2f), 0.2f, "screen.test.button1", 0.03f, textAlign::CENTER, BLACK, 0.0f, test));
}

Screen* MainScreen::clone() const
{
	return new MainScreen(*this);
}

void MainScreen::test()
{
	playerDistance++;
}
