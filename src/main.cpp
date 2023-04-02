#include "System/System.h"
#include "Game/Game.h"
#include "Screen/Screen.h"
#include "Utils/RaylibUtils.h"

int playerDistance = 0;
int playerFame = 0;
menuStatus menuStatu = menuStatus::SYSTEM;

int main ()
{
	raylib::Window window(0, 0, "CustomRPG");

	window.SetSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
	window.ToggleFullscreen();
	window.SetTargetFPS(144);

	Screen test("Screens/test.png", "system.testScreen");
	test.addButton(Button("Screens/basic_button.png", "test", Vector2(0.5, 0.7), 0.3));
	
	while (!window.ShouldClose())
	{
        window.BeginDrawing();
        {
			window.ClearBackground(WHITE);
			test.draw();
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