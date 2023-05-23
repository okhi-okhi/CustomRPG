#include "ScrollList.h"

#include <iostream>

#include "../Utils/RaylibUtils.h"

ScrollList::ScrollList(const Rectangle bounds, const int itemCapacity,
	const std::vector<std::string>& itemsText, float fontSize, textAlign textAlign, raylib::Color textColor,
	float textSpacing, const std::vector<const raylib::Font*>& itemsFont,
	const std::string& itemTexture, const std::string& scrollBar,
	const std::string& scrollBackground)
{
	constexpr int tileImageWidth = 64;

	this->startIndex = 0;
	this->currentIndex = 0;
	this->itemCapacity = itemsText.size() < itemCapacity ? static_cast<int>(itemsText.size()) : itemCapacity;

	if(itemsText.size() > itemCapacity)
	{
		constexpr float scrollBarWidth = 32;

		this->scrollable = true;
		const float scrollBarHeight = bounds.height / static_cast<float>(itemsText.size()) * itemCapacity;
		this->scrollBar = Picture(scrollBar,
			Vector2(bounds.x + (bounds.width + scrollBarWidth)/2, bounds.y - bounds.height/2 + scrollBarHeight / 2),
			2, 32, Vector2(scrollBarWidth, scrollBarHeight));
		std::cout << this->scrollBar.getPosition().x<<" y : "<<this->scrollBar.getPosition().y<<std::endl;
		//TODO scrollBar and scrollBarBackground

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
	Picture itemBg(itemTexture, 2, tileImageWidth, Vector2(bounds.width, buttonHeight));
	for (int i = 0; i < this->itemCapacity; i++)
	{
		this->items.emplace_back(Vector2(bounds.x, buttonY), itemBg,
			Text(itemsText[i], fontSize, textAlign, textColor, textSpacing, itemsFont[i]), select);
		buttonY += buttonHeight;
	}

	for (const auto& item : this->items)
	{
		this->hitbox.insert(this->hitbox.begin(), item.getHitbox().begin(), item.getHitbox().end());
	}
}

void ScrollList::draw()
{
	for (auto& item : this->items)
	{
		item.draw();
	}

	const int wheelMove = static_cast<int>(GetMouseWheelMove());
	if(wheelMove != 0)
	{
		if(this->scrollable)
		{
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
			for(int i = 0; i<this->itemCapacity; i++)
			{
				this->items[i].setText(this->itemsText[this->startIndex+i]);
			}
		}
	}
	this->scrollBar.draw();
	//TODO draw scrollBar and scrollBarBackground
}

ScrollList* ScrollList::clone() const
{
	return new ScrollList(*this);
}

void ScrollList::select()
{
	int a = 0;
	a++;
}
