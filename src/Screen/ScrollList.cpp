#include "ScrollList.h"

#include <iostream>

#include "../Utils/RaylibUtils.h"

ScrollList::ScrollList(const Rectangle bounds, const int itemCapacity,
	const std::vector<std::string>& itemsText, float fontSize, textAlign textAlign, raylib::Color textColor,
	float textSpacing, const std::vector<const raylib::Font*>& itemsFont,
	const std::string& itemTexture, const std::string& sliderBar,
	const std::string& sliderBackground)
{
	using RaylibUtils::getRealLength;
	constexpr int tileImageWidth = 64;

	this->position = getRealLength(Vector2(bounds.x, bounds.y));
	this->bounds = Rectangle(getRealLength(bounds.x - bounds.width/2), getRealLength(bounds.y - bounds.height / 2),
		getRealLength(bounds.width), getRealLength(bounds.height));
	this->startIndex = 0;
	this->currentIndex = 0;
	this->itemCapacity = itemsText.size() < itemCapacity ? static_cast<int>(itemsText.size()) : itemCapacity;

	if(itemsText.size() > itemCapacity)
	{
		constexpr float scrollBarWidth = 32;

		this->scrollable = true;
		const int barHeight = bounds.height / static_cast<float>(itemsText.size()) * itemCapacity;
		this->slider = Slider(Rectangle(bounds.x + bounds.width / 2 + scrollBarWidth / 2, bounds.y, scrollBarWidth, bounds.height),
			sliderBar, sliderBackground, barHeight, &this->startIndex, 0, static_cast<int>(itemsText.size()) - itemCapacity, false);

	} else {
		this->scrollable = false;
	}

	for (int i = 0; i < itemsText.size(); i++)
	{
		this->itemsText.emplace_back(itemsText[i], Vector2(0, 0), fontSize,
			textAlign, textColor, textSpacing, itemsFont[i]);
	}

	const float buttonHeight = bounds.height / static_cast<float>(this->itemCapacity);
	float buttonY = bounds.y - bounds.height/2 + static_cast<float>(buttonHeight)/2;
	const Picture itemBg(itemTexture, 2, tileImageWidth, Vector2(bounds.width, buttonHeight));
	for (int i = 0; i < this->itemCapacity; i++)
	{
		this->items.emplace_back(Vector2(bounds.x, buttonY), itemBg,
		                         Text(itemsText[i], fontSize, textAlign, textColor, textSpacing, itemsFont[i]), select);
		buttonY += buttonHeight;
	}
	updateClickables();
}

void ScrollList::updateClickables()
{
	ClickableGroup::updateClickables();
	for (auto& item : this->items)
	{
		this->clickables.push_back(&item);
	}
	for (auto& item : this->slider.getClickables())
	{
		this->clickables.push_back(item);
	}
}

void ScrollList::draw()
{
	const int wheelMove = static_cast<int>(GetMouseWheelMove());
	if(wheelMove != 0)
	{
		if(this->scrollable)
		{
			int moveY = 0;
			if(wheelMove > 0)
			{
				if(this->startIndex > 0)
				{
					this->startIndex--;
				}
			}
			else
			{
				if(this->startIndex + this->itemCapacity < this->itemsText.size())
				{
					this->startIndex++;
				}
			}
		}
	}
	for (int i = 0; i < this->itemCapacity; i++)
	{
		this->items[i].setText(this->itemsText[this->startIndex + i]);
	}
	if(this->scrollable)
	{
		this->slider.draw();
	}
}

void ScrollList::updatePosition()
{
	for (auto& item : this->items)
	{
		item.updatePosition();
	}
}

void ScrollList::select()
{
	int a = 0;
}
