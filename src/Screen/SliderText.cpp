#include "SliderText.h"
#include "../Utils/RaylibUtils.h"

SliderText::SliderText(const Vector2 position, const Slider& slider,
	const Text& name, const TextArg& value)
{
	this->elementType = ElementType::SLIDER_TEXT;
	this->position = RaylibUtils::getRealLength(position);

	this->slider = slider;
	this->slider.setPosition(Vector2(this->position.x, this->position.y));

	this->name = name;
	this->name.setPosition(Vector2(this->slider.getBounds().x - this->spacing, this->position.y));
	this->name.setAlign(TextAlign::RIGHT);

	this->value = value;
	this->value.setPosition(Vector2(this->slider.getBounds().x + this->slider.getBounds().width + this->spacing, this->position.y));
	this->value.setAlign(TextAlign::LEFT);

}

void SliderText::draw()
{
	this->slider.draw();
	this->name.draw();
	this->value.draw();
}

void SliderText::update()
{
	this->value.update();
	this->name.update();
	this->slider.update();
}

void SliderText::updatePosition()
{
	this->slider.setPosition(this->position);
	this->name.setPosition(Vector2(this->slider.getBounds().x - this->spacing, this->position.y));
	this->value.setPosition(Vector2(this->slider.getBounds().x + this->slider.getBounds().width + this->spacing, this->position.y));
}
