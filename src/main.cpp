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

	Screen test("Screens/test.png", "screen.test");
	test.addButton(Button("Screens/basic_button.png", Vector2(0.5f, 0.2f), 0.1f, "screen.test.button1", 0.03f, textAlign::CENTER, BLACK, 0.0f));
	test.addButton(ButtonArg("Screens/basic_button.png", Vector2(0.5f, 0.8f), 0.1f, "screen.test.button2", { {"aa", &a}, {"bb", &b}, {"cc", &c} }, 0.03f, textAlign::CENTER, BLACK, 0.0f));
	// test.addButton(Button("Screens/basic_button.png", "button1", Vector2(0.5, 0.5), 0.1f, 45.0f, textAlign::CENTER, BLACK, 1.0f));
	// test.addButton(Button("Screens/basic_button.png", "button1", Vector2(0.5, 0.8), 0.1f, 45.0f, textAlign::RIGHT, BLACK, 1.0f));

	// Text text("screen.test.button1", Vector2(0.5f, 0.3f), 0.05f, textAlign::CENTER, BLACK, 0.0f);
	TextArg textArg("screen.test.text1", { {"aa", &a}, {"bb", &b}, {"cc", &c}}, Vector2(0.5f, 0.6f), 0.05f, textAlign::CENTER, BLACK, 0.0f);

	while (!window.ShouldClose())
	{
        window.BeginDrawing();
        {
			window.ClearBackground(WHITE);
			test.draw();
			textArg.draw();
			b++;
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