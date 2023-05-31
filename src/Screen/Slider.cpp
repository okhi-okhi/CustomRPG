#include "Slider.h"

#include <iostream>

#include "../Utils/RaylibUtils.h"

Slider::Slider(const Rectangle bounds, const std::string& bar, const std::string& background,
               const int barLength, const int minValue, const int maxValue, const bool horizontal)
{
	using RaylibUtils::getRealLength;
	constexpr int tileWidth = 32;

	this->position = getRealLength(Vector2(bounds.x, bounds.y));
	this->bounds = Rectangle(getRealLength(bounds.x - bounds.width / 2), getRealLength(bounds.y - bounds.height / 2),
		getRealLength(bounds.width), getRealLength(bounds.height));
	if(horizontal)
	{
		this->bar = ButtonHold(Vector2( this->bounds.x + static_cast<float>(barLength)/2, bounds.y ),
			Picture(bar, 2, tileWidth, Vector2( barLength, bounds.height)), [this] { barDrag(); });

		this->stepPerValue = this->bounds.width / static_cast<float>(this->maxValue - this->minValue);
	}
	else
	{
		this->bar = ButtonHold(Vector2(bounds.x, this->bounds.y + static_cast<float>(barLength)/2),
			Picture(bar, 2, tileWidth, Vector2(bounds.width,barLength)), [this] { barDrag(); });

		this->stepPerValue = this->bounds.height / static_cast<float>(this->maxValue - this->minValue);
	}
	this->background = Button(Vector2(bounds.x, bounds.y),
		Picture(background, 1, tileWidth, Vector2(bounds.width, bounds.height)),
		[this] { backgroundClick(); });

	this->minValue = minValue;
	this->maxValue = maxValue;
	this->horizontal = horizontal;

	//this->hitbox.
}

void Slider::draw()
{
	this->background.draw();
	this->bar.draw();
}

Slider* Slider::clone() const
{
	return new Slider(*this);
}


void Slider::barDrag()
{
	if(this->horizontal)
	{
		this->bar.setPositionX(GetMouseX());
	}
	else
	{
		this->bar.setPositionY(GetMouseY());
	}
}

void Slider::backgroundClick()
{
	std::cout << "a";
}