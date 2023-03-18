#include <windows.h>
#include "System/System.h"
#include "Game/Game.h"

int playerDistance = 0;
int playerFame = 0;
menuStatus menuStatu = menuStatus::SYSTEM;

int main()
{
	SetConsoleOutputCP(65001);
	System::instance().init();

	while (System::instance().getPlaying())
	{
		switch (menuStatu)
		{
		case menuStatus::SYSTEM:
			System::instance().systemMenu();
			break;
		case menuStatus::SETTING:
			System::instance().settingMenu();
			break;
		case menuStatus::GAME:
			Game::instance().gameMenu();
			break;
		case menuStatus::ALLY:
			Game::instance().allyMenu();
			break;
		case menuStatus::TEAM:
			Game::instance().teamMenu();
			break;
		case menuStatus::INV:
			Game::instance().inventoryMenu();
			break;
		
		default:
			break;
		}
	}
	return 0;
}