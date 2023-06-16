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

	this->children.push_back(this->button);
	this->children.push_back(this->text);
}

ButtonText& ButtonText::operator=(ButtonText other)
{
	swap(*this, other);
	return *this;
}

void ButtonText::draw()
{
	this->button->draw();
	this->text->draw();
}

void ButtonText::updatePosition()
{
	this->button->setPosition(this->position);
	this->text->setPosition(this->position);
}

void ButtonText::updateChildren()
{
	ElementGroup::updateChildren();
	this->children.push_back(this->button);
	this->children.push_back(this->text);
}

void ButtonText::setText(const Text& _text)
{
	const Vector2 position = this->text->getPosition();
	this->text = std::make_shared<Text>(_text);
	this->text->setPosition(position);
}

void swap(ButtonText& first, ButtonText& second) noexcept
{
	using std::swap;
	swap(static_cast<ElementGroup&>(first), static_cast<ElementGroup&>(second));

	swap(first.button, second.button);
	swap(first.text, second.text);
}
