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
	addElement(Picture("screens/main/title.png", Vector2(0.5f, 0.1f), 1, 0.5f));
	addButton(Button("screens/button_1.png", Vector2(0.8f, 0.3f), 0.2f, test));
	addButton(ButtonText("screens/button_1.png", Vector2(0.5f, 0.3f), 0.2f, "screen.test.button1", 0.03f, textAlign::CENTER, WHITE, 0.0f, test));
	addButton(ButtonText("screens/button_1.png", Vector2(0.5f, 0.5f), 0.2f, "screen.test.button1", 0.03f, textAlign::CENTER, WHITE, 0.0f, test));
	addButton(ButtonText("screens/button_1.png", Vector2(0.5f, 0.7f), 0.2f, "screen.test.button1", 0.03f, textAlign::CENTER, WHITE, 0.0f, test));
}

Screen* MainScreen::clone() const
{
	return new MainScreen(*this);
}

void MainScreen::test()
{
	playerDistance++;
}
