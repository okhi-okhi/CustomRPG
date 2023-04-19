#include "ScreenManager.h"
#include "Screens/MainScreen.h"

void ScreenManager::init()
{
	this->allScreens.push_back(MainScreen().clone());
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

void ScreenManager::updateHitbox()
{
	for(int i=0; i < this->currentScreens.size(); i++)
	{
		for(int j=0; j < this->currentScreens[i]->getElements().size(); j++)
		{
			Element* element = this->currentScreens[i]->getElements()[j];
			if(element->getElementType() == elementTypes::BUTTON ||
				element->getElementType() == elementTypes::BUTTON_ARG)
			{
				for(int k = j; k < this->currentScreens[i]->getElements().size(); k++)
				{
					if(this->currentScreens[i]->getElements()[k]->getHitbox())
					{
						
					}
				}
			}
		}
	}
}
