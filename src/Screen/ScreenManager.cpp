#include "ScreenManager.h"
#include "Screens/MainScreen.h"
#include "Screens/SettingScreen.h"
#include "Screens/LanguageScreen.h"
#include "Screens/SelectGameScreen.h"
#include "../Utils/RaylibUtils.h"
#include "../System/GlobalVariable.h"

void ScreenManager::init()
{
	zoomPercent = static_cast<float>(RaylibUtils::getWindowWidth()) / 1920.0f;
	loadAllScreen();
}

void ScreenManager::loadAllScreen()
{
	this->allScreens.push_back(make_shared<MainScreen>());
	this->allScreens.push_back(make_shared<SettingScreen>());
	this->allScreens.push_back(make_shared<LanguageScreen>());
	this->allScreens.push_back(make_shared<SelectGameScreen>());
}

void ScreenManager::reloadAllScreen()
{
	this->allScreens.clear();
	loadAllScreen();
	std::vector<shared_ptr<Screen>> newScreens;
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

void ScreenManager::addScreen(const ScreenType& screen)
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
		}
	}
}

void ScreenManager::removeScreen(const ScreenType& screen)
{
	for (int i = 0; i < this->currentScreens.size(); i++)
	{
		if (this->currentScreens[i]->getScreenType() == screen)
		{
			std::cout<<"erase screen: "<< this->currentScreens[i] <<std::endl;
			this->currentScreens.erase(currentScreens.begin() + i);
			std::cout << "success" << std::endl;
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
