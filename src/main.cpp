#include "System/System.h"
#include "Game/Game.h"
#include "Screen/ScreenManager.h"
#include "Utils/RaylibUtils.h"
#include "System/PathProvider.h"

int playerDistance = 0;
int playerFame = 0;
menuStatus menuStatu = menuStatus::SYSTEM;
float zoomPercent = 1.0f;
bool running = true;

void windowSetup(raylib::Window& window)
{
	window.SetSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
	window.ToggleFullscreen();

	const raylib::Image icon(PathProvider::instance().getResourcesPath() + "textures/icons/icon_main.png");
	window.SetIcon(icon);

	window.SetTargetFPS(60);
}

int main()
{
	SetTraceLogLevel(LOG_ALL);
	raylib::Window window(1920, 1080, "CustomRPG");
	InitAudioDevice();

	windowSetup(window);
	
	System::instance().init();
	ScreenManager::instance().addScreen(screenTypes::MAIN);

	while (!window.ShouldClose() && running)
	{
        window.BeginDrawing();
        {
			ScreenManager::instance().draw();
        }
		window.EndDrawing();
	}
	CloseAudioDevice();
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