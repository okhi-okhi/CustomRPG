#include "SelectGameScreen.h"
#include "../FullPicture.h"

SelectGameScreen::SelectGameScreen() : Screen(ScreenType::SELECT_GAME, "selectGame")
{
	addElement(make_shared<FullPicture>("screens/main/background.png", 1));


}
