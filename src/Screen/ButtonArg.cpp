#include "ButtonArg.h"
#include <Rectangle.hpp>

ButtonArg::ButtonArg(const std::string& fileName, const Vector2 position, const float zoomPercent,
	const std::string& i18nKey, const std::map<std::string, argTypes>& args,
	const float fontSize, const textAlign textAlign, const raylib::Color textColor,
	const float textSpacing, const std::function<void()>& function, const std::string& clickSound)
{
	this->elementType = elementTypes::BUTTON_ARG;
	this->texture = Picture(fileName, position, 2, zoomPercent);
	this->text = TextArg(i18nKey, args, this->getTextPos(textAlign), fontSize, textAlign, textColor, textSpacing);
	this->clickFun = function;
	this->hitbox = this->texture.getHitbox();
	this->clickSound = LoadSound(PathProvider::instance().get(resourcesFolder::SOUNDS, clickSound).c_str());
}

void ButtonArg::draw()
{
	update();
	this->texture.draw();
	this->text.draw();
}

ButtonArg* ButtonArg::clone() const
{
	return new ButtonArg(*this);
}
