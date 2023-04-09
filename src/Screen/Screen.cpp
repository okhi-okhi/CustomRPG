#include "Screen.h"
#include "../System/PathProvider.h"
#include "../Utils/RaylibUtils.h"

Screen::Screen(const std::string& bgFileName, const std::string& i18nKey)
{
	raylib::Image bgImage(PathProvider::instance().getResourcesPath() + bgFileName);
	bgImage.Resize(RaylibUtils::getWindowWidth(), RaylibUtils::getWindowHeight());
	this->backGround = bgImage;

	this->i18nKey = i18nKey;
}

void Screen::addButton(const Button& button)
{
	this->buttons.push_back(button);
}

void Screen::addButton(const ButtonArg& buttonArg)
{
	this->buttonArgs.push_back(buttonArg);
}

void Screen::draw()
{
	DrawTexture(this->backGround, 0, 0, WHITE);

	for(auto& button : this->buttons)
	{
		button.draw();
	}
	for(auto& buttonArg : this->buttonArgs)
	{
		buttonArg.draw();
	}
}

