#include "ScreenManager.h"
#include "Screens/MainScreen.h"
#include "../Utils/RaylibUtils.h"
#include "../System/GlobalVariable.h"

void ScreenManager::init()
{
	zoomPercent = static_cast<float>(RaylibUtils::getWindowWidth()) / 1920.0f;

	this->allScreens.push_back(new MainScreen());
	updateHitbox();
}

void ScreenManager::addScreen(const screenTypes& screen)
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
	updateHitbox();
}

void ScreenManager::removeScreen(const screenTypes& screen)
{
	for (int i = 0; i < this->currentScreens.size(); i++)
	{
		if (this->currentScreens[i]->getScreenType() == screen)
		{
			this->currentScreens.erase(currentScreens.begin() + i);
		}
	}
	updateHitbox();
}

void ScreenManager::clear()
{
	this->currentScreens.clear();
}

void ScreenManager::draw() const
{
	for(const auto& currentScreen: this->currentScreens)
	{
		currentScreen->draw();
	}
}

void ScreenManager::updateHitbox() const
{
	for(int i=0; i < this->currentScreens.size(); i++)
	{
		for(int j=0; j < this->currentScreens[i]->getClickableElements().size(); j++)
		{
			const auto [index, btn] = this->currentScreens[i]->getClickableElements()[j];
			btn->clearReserveRec();
			for(int k = index+1; k < this->currentScreens[i]->getElements().size(); k++)
			{
				btn->checkCollision(this->currentScreens[i]->getElements()[k]->getHitbox());
			}
			for(int l = i+1; l < this->currentScreens.size(); l++)
			{
				for (int m = 0; m < this->currentScreens[l]->getClickableElements().size(); m++)
				{
					btn->checkCollision(this->currentScreens[l]->getElements()[m]->getHitbox());
				}
			}
		}
	}
}
