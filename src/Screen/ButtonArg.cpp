#include "ButtonArg.h"
#include <Rectangle.hpp>

ButtonArg::ButtonArg(const std::string& fileName, const Vector2 position, const float zoomPercent,
	const std::string& i18nKey, const std::map<std::string, argTypes>& args,
	const float fontSize, const textAlign textAlign, const raylib::Color textColor, const float textSpacing)
{
	this->elementType = elementTypes::BUTTON_ARG;
	this->texture = Picture(fileName, position, 2, zoomPercent);

	this->text = TextArg(i18nKey, args, this->getTextPos(textAlign), fontSize, textAlign, textColor, textSpacing);
}

void ButtonArg::draw()
{
	if (CheckCollisionPointRec(GetMousePosition(), raylib::Rectangle(this->texture.getPosition().x, this->texture.getPosition().y, static_cast<float>(this->texture.getSpriteTexture().width), this->getButtonHeight())))
	{
		this->texture.setCurrentFrame(static_cast<int>(buttonState::HOVER));
	}
	else
	{
		this->texture.setCurrentFrame(static_cast<int>(buttonState::IDLE));
	}

	this->texture.draw();
	this->text.draw();
}

ButtonArg* ButtonArg::clone() const
{
	return new ButtonArg(*this);
}
