#include "SliderText.h"
#include "../Utils/RaylibUtils.h"

SliderText::SliderText(const Vector2 position, const Slider& slider,
	const Text& name, const TextArg& value)
{
	this->elementType = ElementType::SLIDER_TEXT;
	this->position = RaylibUtils::getRealLength(position);

	this->slider = std::make_shared<Slider>(slider);
	this->slider->setPosition(Vector2(this->position.x, this->position.y));

	this->name = std::make_shared<Text>(name);
	this->name->setPosition(Vector2(this->slider->getBounds().x - this->spacing, this->position.y));
	this->name->setAlign(textAlign::RIGHT);

	this->value = std::make_shared<TextArg>(value);
	this->value->setPosition(Vector2(this->slider->getBounds().x + this->slider->getBounds().width + this->spacing, this->position.y));
	this->value->setAlign(textAlign::LEFT);

	updateChildren();
}

SliderText::SliderText(const SliderText& other) :ElementGroup(other),
	slider(other.slider),
	name(other.name),
	value(other.value)
{
	updateChildren();
}

SliderText& SliderText::operator=(SliderText other)
{
	swap(*this, other);
	return *this;
}

void SliderText::draw()
{
}

void SliderText::updatePosition()
{
	this->slider->setPosition(this->position);
	this->name->setPosition(Vector2(this->slider->getBounds().x - this->spacing, this->position.y));
	this->value->setPosition(Vector2(this->slider->getBounds().x + this->slider->getBounds().width + this->spacing, this->position.y));
}

void SliderText::updateChildren()
{
	ElementGroup::updateChildren();
	this->children.push_back(this->slider);
	for (auto& item : this->slider->getChildren())
	{
		this->children.push_back(item);
	}

	this->children.push_back(this->name);
	this->children.push_back(this->value);
}

void swap(SliderText& first, SliderText& second) noexcept
{
	using std::swap;
	swap(static_cast<ElementGroup&>(first), static_cast<ElementGroup&>(second));

	swap(first.slider, second.slider);
	swap(first.name, second.name);
	swap(first.value, second.value);

	first.updateChildren();
}
