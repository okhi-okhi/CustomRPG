#include "Slider.h"

#include <iostream>

#include "../Utils/RaylibUtils.h"

Slider::Slider(const Rectangle bounds, const std::string& bar, const std::string& background,
               const int barLength, int* value, const int minValue, const int maxValue, const bool horizontal)
{
	using RaylibUtils::getRealLength;
	constexpr int tileWidth = 32;
	this->elementType = elementTypes::SLIDER;

	this->background = Button(Vector2(bounds.x, bounds.y),
		Picture(background, 2, tileWidth, Vector2(bounds.width, bounds.height)),
		[this] { backgroundClick(); });

	this->position = this->background.getPosition();
	this->bounds = this->background.getHitbox()[0];

	this->minValue = minValue;
	this->maxValue = maxValue;
	this->value = value;
	this->horizontal = horizontal;
	this->dragging = false;

	if (this->horizontal)
	{
		this->bar = ButtonHold(Vector2(this->bounds.x + static_cast<float>(barLength) / 2, bounds.y),
			Picture(bar, 2, tileWidth, Vector2(barLength, bounds.height)), [this] { barDrag(); });

		this->displayValueSpacing = (this->bounds.width - this->bar.getHitbox()[0].width) / static_cast<float>(this->maxValue - this->minValue);
		this->valueSpacing = this->bounds.width / static_cast<float>(this->maxValue - this->minValue + 1);
	}
	else
	{
		this->bar = ButtonHold(Vector2(bounds.x, this->bounds.y + static_cast<float>(barLength)/2),
			Picture(bar, 2, tileWidth, Vector2(bounds.width,barLength)), [this] { barDrag(); });

		this->displayValueSpacing = (this->bounds.height - this->bar.getHitbox()[0].height) / static_cast<float>(this->maxValue - this->minValue);
		this->valueSpacing = this->bounds.height / static_cast<float>(this->maxValue - this->minValue + 1);
	}
	updateClickables();
}

Slider::Slider(const Slider& other) : bounds(other.bounds), bar(other.bar),
	background(other.background), value(other.value),
	minValue(other.minValue), maxValue(other.maxValue),
	horizontal(other.horizontal), dragging(other.dragging),
	displayValueSpacing(other.displayValueSpacing), valueSpacing(other.valueSpacing)
{
	this->position = other.position;
	updateClickables();
}

Slider& Slider::operator=(Slider other)
{
	swap(*this, other);
	return *this;
}

void Slider::updateClickables()
{
	ClickableGroup::updateClickables();
	this->clickables.push_back(&this->background);
	this->clickables.push_back(&this->bar);
}

void Slider::draw()
{
	if(this->dragging)
	{
		if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			barDrag();
		}
		else
		{
			this->dragging = false;
		}
	}
	if (this->horizontal)
	{
		if (minValue <= *this->value && *this->value <= this->maxValue)
		{
			this->bar.setPositionX(this->bounds.x + this->bar.getHitbox()[0].width / 2 +
			(*this->value - this->minValue) * this->displayValueSpacing);
		}
	}
	else
	{
		if (minValue <= *this->value && *this->value <= this->maxValue)
		{
			this->bar.setPositionY(this->bounds.y + this->bar.getHitbox()[0].height / 2 +
				(*this->value - this->minValue) * this->displayValueSpacing);
		}
	}
}

Slider* Slider::clone() const
{
	return new Slider(*this);
}

void Slider::barDrag()
{
	this->dragging = true;
	if(this->horizontal)
	{
		if(GetMouseX() <= this->bounds.x)
		{
			*this->value = this->minValue;
		}
		else if(GetMouseX() >= this->bounds.x + this->bounds.width)
		{
			*this->value = this->maxValue;
		}
		else
		{
			*this->value = static_cast<int>((GetMouseX() - this->bounds.x) / this->valueSpacing);
		}
	}
	else
	{
		if (GetMouseY() <= this->bounds.y)
		{
			*this->value = this->minValue;
		}
		else if (GetMouseY() >= this->bounds.y + this->bounds.height)
		{
			*this->value = this->maxValue;
		}
		else
		{
			*this->value = static_cast<int>((GetMouseY() - this->bounds.y) / this->valueSpacing);
		}
	}
}

void Slider::backgroundClick() const
{
	using std::cout, std::endl;
	if (this->horizontal)
	{
		*this->value = this->minValue + static_cast<int>((GetMouseX() - this->bounds.x) / this->valueSpacing);
	}
	else
	{
		*this->value = this->minValue + static_cast<int>((GetMouseY() - this->bounds.y) / this->valueSpacing);
	}
}

void swap(Slider& first, Slider second) noexcept
{
	using std::swap;
	swap(first.position, second.position);
	swap(first.bounds, second.bounds);
	swap(first.background, second.background);
	swap(first.bar, second.bar);
	swap(first.value, second.value);
	swap(first.minValue, second.minValue);
	swap(first.maxValue, second.maxValue);
	swap(first.horizontal, second.horizontal);
	swap(first.dragging, second.dragging);
	swap(first.displayValueSpacing, second.displayValueSpacing);
	swap(first.valueSpacing, second.valueSpacing);
	first.updateClickables();
	first.bar.setFunction([&first] { first.barDrag(); });
	first.background.setFunction([&first] { first.backgroundClick(); });
}
