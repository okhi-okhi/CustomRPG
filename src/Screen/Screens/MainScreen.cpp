#include "MainScreen.h"
#include <iostream>
#include "../FullPicture.h"
#include "../ButtonArg.h"
#include "../TextArg.h"
#include "../../System/PathProvider.h"
#include "../../System/GlobalVariable.h"

MainScreen::MainScreen() : Screen(screenTypes::MAIN, "main")
{
	const std::string path = PathProvider::instance().getScreensPath() + "main/";
	addElement(FullPicture(path + "background.png", 1));
	addButton(Button(path + "basic_button.png", Vector2(0.5f, 0.2f), 0.1f, "screen.test.button1", 0.03f, textAlign::CENTER, BLACK, 0.0f, test));
	addButton(ButtonArg(path + "basic_button.png", Vector2(0.5f, 0.5f), 0.1f, "screen.test.button2", { {"aa", &playerDistance} }, 0.03f, textAlign::CENTER, BLACK, 0.0f));
	addElement(Picture(path + "basic_button.png", Vector2(0.55f, 0.15f), 2, 0.1f));
	addElement(Picture(path + "basic_button.png", Vector2(0.45f, 0.25f), 2, 0.1f));
}

Screen* MainScreen::clone() const
{
	return new MainScreen(*this);
}

void MainScreen::test()
{
	playerDistance++;
}
