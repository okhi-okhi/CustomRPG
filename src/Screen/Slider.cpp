#include "Slider.h"

#include <iostream>

#include "../Utils/RaylibUtils.h"

Slider::Slider(const Rectangle bounds, const std::string& bar, const std::string& background,
               const int barLength, int* value, const int minValue, const int maxValue, const bool horizontal)
{
	using RaylibUtils::getRealLength;
	constexpr int tileWidth = 32;
	this->elementType = elementTypes::SLIDER;

	this->background = new Button(Vector2(bounds.x, bounds.y),
		Picture(background, 2, tileWidth, Vector2(bounds.width, bounds.height)),
		[this] { backgroundClick(); });

	this->position = this->background->getPosition();
	this->bounds = this->background->getHitbox()[0];

	this->minValue = minValue;
	this->maxValue = maxValue;
	this->value = value;
	this->horizontal = horizontal;
	this->dragging = false;

	if (this->horizontal)
	{
		this->bar = new ButtonHold(Vector2(this->bounds.x + static_cast<float>(barLength) / 2, bounds.y),
			Picture(bar, 2, tileWidth, Vector2(barLength, bounds.height)), [this] { barDrag(); });

		this->displayValueSpacing = (this->bounds.width - this->bar->getHitbox()[0].width) / static_cast<float>(this->maxValue - this->minValue);
		this->valueSpacing = this->bounds.width / static_cast<float>(this->maxValue - this->minValue + 1);
	}
	else
	{
		this->bar = new ButtonHold(Vector2(bounds.x, this->bounds.y + static_cast<float>(barLength)/2),
			Picture(bar, 2, tileWidth, Vector2(bounds.width,barLength)), [this] { barDrag(); });

		this->displayValueSpacing = (this->bounds.height - this->bar->getHitbox()[0].height) / static_cast<float>(this->maxValue - this->minValue);
		this->valueSpacing = this->bounds.height / static_cast<float>(this->maxValue - this->minValue + 1);
	}

	this->clickables.push_back(this->background);
	this->clickables.push_back(this->bar);
}

void Slider::draw()
{
	if(this->dragging)
	{
		if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			//this->bar.setState(buttonState::HOVER);
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
			this->bar->setPositionX(this->bounds.x + this->bar->getHitbox()[0].width / 2 +
			(*this->value - this->minValue) * this->displayValueSpacing);
		}
	}
	else
	{
		if (minValue <= *this->value && *this->value <= this->maxValue)
		{
			this->bar->setPositionY(this->bounds.y + this->bar->getHitbox()[0].height / 2 +
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

void Slider::backgroundClick()
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