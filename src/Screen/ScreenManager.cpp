#include "ScreenManager.h"
#include "Screens/System/MainScreen.h"
#include "Screens/System/SettingScreen.h"
#include "Screens/System/LanguageScreen.h"
#include "Screens/System/SelectGameScreen.h"
#include "../Utils/RaylibUtils.h"
#include "../System/GlobalVariable.h"

void ScreenManager::init()
{
	zoomPercent = static_cast<float>(RaylibUtils::getWindowWidth()) / 1920.0f;
	loadSystemScreens();
}

void ScreenManager::loadSystemScreens()
{
	this->allScreens.push_back(make_shared<MainScreen>());
	this->allScreens.push_back(make_shared<SettingScreen>());
	this->allScreens.push_back(make_shared<LanguageScreen>());
	this->allScreens.push_back(make_shared<SelectGameScreen>());
}

void ScreenManager::reloadAllScreen()
{
	this->allScreens.clear();
	loadSystemScreens();
	vector<shared_ptr<Screen>> newScreens;
	for (const auto& currentScreen : this->currentScreens)
	{
		for (const auto& storeScreen : this->allScreens)
		{
			if (currentScreen->getScreenType() == storeScreen->getScreenType())
			{
				newScreens.push_back(storeScreen);
			}
		}
	}
	this->currentScreens.clear();
	this->currentScreens = newScreens;
}

void ScreenManager::delayReload()
{
	this->needReload = true;
}

void ScreenManager::showScreen(const ScreenType& screen)
{
	for(const auto& currentScreen: this->currentScreens)
	{
		if(currentScreen->getScreenType() == screen)
		{
			return;
		}
	}
	for (const auto& storeScreen : this->allScreens)
	{
		if (storeScreen->getScreenType() == screen)
		{
			this->currentScreens.push_back(storeScreen);
			break;
		}
	}
}

void ScreenManager::hiddenScreen(const ScreenType& screen)
{
	for (int i = 0; i < this->currentScreens.size(); i++)
	{
		if (this->currentScreens[i]->getScreenType() == screen)
		{
			this->currentScreens.erase(currentScreens.begin() + i);
			break;
		}
	}
}

void ScreenManager::clear()
{
	this->currentScreens.clear();
}

void ScreenManager::draw()
{
	for(const auto& currentScreen: this->currentScreens)
	{
		currentScreen->draw();
	}
	if(this->needReload)
	{
		reloadAllScreen();
		needReload = false;
	}
}

void ScreenManager::update()
{
	this->clicked = false;
	for (int i = static_cast<int>(currentScreens.size()) - 1; i>=0; i--)
	{
		currentScreens[i]->update();
	}
}
