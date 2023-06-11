#include "ScrollList.h"

#include <iostream>
#include "../I18n/I18n.h"
#include "../I18n/FontProvider.h"
#include "../Utils/RaylibUtils.h"

ScrollList::ScrollList(const Rectangle bounds, const int itemCapacity, const int currentIndex,
	const std::vector<std::string>& itemsI18nKey, const float fontSize,
	const textAlign textAlign, const raylib::Color textColor,
	const float textSpacing, const std::string& itemTexture, const std::string& sliderBar,
	const std::string& sliderBackground) :
	ScrollList(bounds, itemCapacity, currentIndex,
		[&]() {
			std::vector<std::string> texts;
			for (const auto& key : itemsI18nKey) {
				texts.push_back(I18n::instance().get(key));
			}
			return texts;}(),
			fontSize, textAlign, textColor, textSpacing,
			[&]() {
			std::vector<const raylib::Font*> fonts;
			for (const auto& key : itemsI18nKey) {
				fonts.push_back(&FontProvider::instance().get(key));
			}
			return fonts;}(),
			itemTexture, sliderBar, sliderBackground)
{

}

ScrollList::ScrollList(const Rectangle bounds, const int itemCapacity, const int currentIndex,
	const std::vector<std::string>& itemsText, float fontSize, textAlign textAlign, raylib::Color textColor,
	float textSpacing, const std::vector<const raylib::Font*>& itemsFont,
	const std::string& itemTexture, const std::string& sliderBar,
	const std::string& sliderBackground)
{
	using RaylibUtils::getRealLength;
	constexpr int tileImageWidth = 64;

	this->elementType = elementTypes::SCROLL_LIST;
	this->position = getRealLength(Vector2(bounds.x, bounds.y));
	this->bounds = Rectangle(getRealLength(bounds.x - bounds.width/2), getRealLength(bounds.y - bounds.height / 2),
		getRealLength(bounds.width), getRealLength(bounds.height));
	this->startIndex = 0;
	this->currentIndex = currentIndex;
	this->itemCapacity = itemsText.size() < itemCapacity ? static_cast<int>(itemsText.size()) : itemCapacity;

	if(itemsText.size() > itemCapacity)
	{
		constexpr float scrollBarWidth = 32;

		this->scrollable = true;
		const int barHeight = static_cast<int>(bounds.height / static_cast<float>(itemsText.size()) * static_cast<float>(itemCapacity));
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

	const float buttonHeight = bounds.height / static_cast<float>(itemCapacity);
	float buttonY = bounds.y - bounds.height/2 + static_cast<float>(buttonHeight)/2;
	const Picture itemBg(itemTexture, 2, tileImageWidth, Vector2(bounds.width, buttonHeight));
	for (int i = 0; i < this->itemCapacity; i++)
	{
		this->items.emplace_back(Vector2(bounds.x, buttonY), itemBg,
		                         Text(itemsText[i], fontSize, textAlign, textColor, textSpacing, itemsFont[i]), [this, i] { select(i); });
		buttonY += buttonHeight;
	}
	updateClickables();
}

ScrollList::ScrollList(const ScrollList& other) : ClickableGroup(other),
	itemCapacity(other.itemCapacity),
	scrollable(other.scrollable),
	startIndex(other.startIndex),
	currentIndex(other.currentIndex),
	itemsText(other.itemsText),
	items(other.items),
	slider(other.slider)
{
	updateClickables();
}

ScrollList& ScrollList::operator=(ScrollList other)
{
	swap(*this, other);
	return *this;
}

void ScrollList::updateClickables()
{
	ClickableGroup::updateClickables();
	int index = 0;
	for (auto& item : this->items)
	{
		item.setFunction([this, index] { select(index); });
		this->clickables.push_back(&item);
		index++;
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
	const int index = this->currentIndex - this->startIndex;
	if(index >= 0 && index < this->itemCapacity)
	{
		this->items[index].setState(buttonState::HOVER);
	}
}

void ScrollList::updatePosition()
{
	for (auto& item : this->items)
	{
		item.updatePosition();
	}
}

void ScrollList::select(const int index)
{
	this->currentIndex = this->startIndex + index;
}

void swap(ScrollList& first, ScrollList& second) noexcept
{
	using std::swap;
	swap(static_cast<ClickableGroup&>(first), static_cast<ClickableGroup&>(second));

	swap(first.bounds, second.bounds);
	swap(first.itemCapacity, second.itemCapacity);
	swap(first.scrollable, second.scrollable);
	swap(first.currentIndex, second.currentIndex);
	swap(first.startIndex, second.startIndex);
	swap(first.items, second.items);
	swap(first.itemsText, second.itemsText);
	swap(first.slider, second.slider);

	first.updateClickables();
}
