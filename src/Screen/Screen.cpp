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

void Screen::draw() const
{
	DrawTexture(this->backGround, 0, 0, WHITE);

	for(const auto& button : this->buttons)
	{
		button.draw();
	}
}

