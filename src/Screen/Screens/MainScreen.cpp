#include "MainScreen.h"
#include "../FullPicture.h"
#include "../ButtonArg.h"
#include "../TextArg.h"
#include "../../System/PathProvider.h"

MainScreen::MainScreen() : Screen("main")
{
	const std::string path = PathProvider::instance().getScreensPath() + "main/";
	addElement(FullPicture(path + "background.png", 1));
	addElement(Button(path + "basic_button.png", Vector2(0.5f, 0.2f), 0.1f, "screen.test.button1", 0.03f, textAlign::CENTER, BLACK, 0.0f));
}
