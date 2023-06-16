#include "ButtonText.h"
#include "../Utils/RaylibUtils.h"

ButtonText::ButtonText(Vector2 position, const Button& button, const Text& text)
{
	this->elementType = elementTypes::BUTTON_TEXT;
	this->position = RaylibUtils::getRealLength(position);
	this->button = std::make_shared<Button>(button);
	this->button->setPosition(this->position);
	this->text = std::make_shared<Text>(text);
	this->text->setPosition(this->position);

	updateChildren();
	this->children.push_back(this->button);
	this->children.push_back(this->text);
}

void ButtonText::draw()
{
	this->button->draw();
	this->text->draw();
}

void ButtonText::updateChildren()
{
	ElementGroup::updateChildren();
}

void ButtonText::setText(const Text& _text)
{
	const Vector2 position = this->text->getPosition();
	this->text = std::make_shared<Text>(_text);
	this->text->setPosition(position);
}
