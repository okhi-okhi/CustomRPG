#include "System/Exceptions.hpp"
#include "System/System.h"
#include "Game/Game.h"
#include "Screen/Screens/MainScreen.h"
#include "Screen/ButtonArg.h"
#include "Screen/TextArg.h"
#include "Utils/RaylibUtils.h"
#include "System/PathProvider.h"

int playerDistance = 0;
int playerFame = 0;
menuStatus menuStatu = menuStatus::SYSTEM;

void windowSetup(raylib::Window& window)
{
	window.SetSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
	window.ToggleFullscreen();

	const raylib::Image icon(PathProvider::instance().getResourcesPath() + "Images/Icons/icon_main.png");
	window.SetIcon(icon);

	window.SetTargetFPS(60);
}

int main()
{
	SetTraceLogLevel(LOG_ALL);
	raylib::Window window(1920, 1080, "CustomRPG");

	windowSetup(window);

	System::instance().init();
	std::string a = "asdv";
	float b = 87.0f;
	int c = 777;

	MainScreen mainScreen;

	while (!window.ShouldClose())
	{
        window.BeginDrawing();
        {
			window.ClearBackground(WHITE);
			mainScreen.draw();
        }
		window.EndDrawing();
	}

	window.Close();
	return 0;
}

// #include <windows.h>
// #include "System/System.h"
// #include "Game/Game.h"
//
// int playerDistance = 0;
// int playerFame = 0;
// menuStatus menuStatu = menuStatus::SYSTEM;
//
// int main()
// {
// 	SetConsoleOutputCP(65001);
// 	System::instance().init();
//
// 	while (System::instance().getPlaying())
// 	{
// 		switch (menuStatu)
// 		{
// 		case menuStatus::SYSTEM:
// 			System::instance().systemMenu();
// 			break;
// 		case menuStatus::SETTING:
// 			System::instance().settingMenu();
// 			break;
// 		case menuStatus::GAME:
// 			Game::instance().gameMenu();
// 			break;
// 		case menuStatus::ALLY:
// 			Game::instance().allyMenu();
// 			break;
// 		case menuStatus::TEAM:
// 			Game::instance().teamMenu();
// 			break;
// 		case menuStatus::INV:
// 			Game::instance().inventoryMenu();
// 			break;
// 		
// 		default:
// 			break;
// 		}
// 	}
// 	return 0;
// }