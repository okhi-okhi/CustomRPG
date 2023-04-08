#include "System/Exceptions.hpp"
#include "System/System.h"
#include "Game/Game.h"
#include "Screen/Screen.h"
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

	window.SetTargetFPS(144);
}

int main()
{
	SetTraceLogLevel(LOG_ALL);
	raylib::Window window(1920, 1080, "CustomRPG");

	windowSetup(window);

	System::instance().init();
	Screen test("Screens/test.png", "screen.test");
	test.addButton(Button(Picture("Screens/basic_button.png", Vector2(0.5f, 0.2f), 2, 0.1f), "screen.test.button1", 0.03f, textAlign::RIGHT, BLACK, 0.0f));
	// test.addButton(Button("Screens/basic_button.png", "button1", Vector2(0.5, 0.5), 0.1f, 45.0f, textAlign::CENTER, BLACK, 1.0f));
	// test.addButton(Button("Screens/basic_button.png", "button1", Vector2(0.5, 0.8), 0.1f, 45.0f, textAlign::RIGHT, BLACK, 1.0f));

	Text text("screen.test.button1", Vector2(0.5f, 0.3f), 0.05f, textAlign::CENTER, BLACK, 0.0f);

	while (!window.ShouldClose())
	{
        window.BeginDrawing();
        {
			window.ClearBackground(WHITE);
			test.draw();
			text.draw();
        }
		window.EndDrawing();
	}

	window.Close();
	return 0;
}

// #include <windows.h>
// #include "System/System.h"
// #include "Game/Game.h"

// int playerDistance = 0;
// int playerFame = 0;
// menuStatus menuStatu = menuStatus::SYSTEM;

// int main()
// {
// 	SetConsoleOutputCP(65001);
// 	System::instance().init();

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
		
// 		default:
// 			break;
// 		}
// 	}
// 	return 0;
// }