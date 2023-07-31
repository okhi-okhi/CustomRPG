#include "ButtonText.h"
#include "../Utils/RaylibUtils.h"

ButtonText::ButtonText(const Vector2 pos, const Button& button, const Text& text)
{
	this->elementType = ElementType::BUTTON_TEXT;
	this->position = RaylibUtils::getRealLength(pos);
	this->button = button;
	this->button.setPosition(this->position);
	this->text = text;
	this->text.setPosition(this->position);
}

void ButtonText::draw()
{
	this->button.draw();
	this->text.draw();
}

void ButtonText::update()
{
	this->button.update();
	this->text.update();
}

void ButtonText::updatePosition()
{
	this->button.setPosition(this->position);
	this->text.setPosition(this->position);
}

void ButtonText::setText(const Text& _text)
{
	const Vector2 position = this->text.getPosition();
	this->text = _text;
	this->text.setPosition(position);
}
