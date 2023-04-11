#include "MainScreen.h"
#include "../Picture.h"
#include "../../System/PathProvider.h"

MainScreen::MainScreen() : Screen("main")
{
	const std::string path = PathProvider::instance().getSystemScreensPath() + "main/";
	addElement(Picture(path + "background", 0, 0))
}
