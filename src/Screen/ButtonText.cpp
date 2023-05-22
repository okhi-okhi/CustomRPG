#include "ButtonText.h"
#include "../Utils/RaylibUtils.h"

ButtonText::ButtonText(const Vector2 position, const Picture& texture, const Text& text,
	const std::function<void()>& function, const std::string& clickSound) :
	Button(position, texture, function, clickSound)
{
	this->elementType = elementTypes::BUTTON_TEXT;
	this->text = text;
	this->text.setPosition(RaylibUtils::getRealLength(position));
}

void ButtonText::draw()
{
	Button::draw();
	this->text.draw();
}

ButtonText* ButtonText::clone() const
{
	return new ButtonText(*this);
}

void ButtonText::setText(const Text& text)
{
	const Vector2 position = this->text.getPosition();
	this->text = text;
	this->text.setPosition(position);
}
