#include "ScrollList.h"
#include <iostream>
#include "PictureTiled.h"
#include "../I18n/I18n.h"
#include "../I18n/FontProvider.h"
#include "../Utils/RaylibUtils.h"

ScrollList::ScrollList(const raylib::Rectangle bounds, const int itemCapacity, const int currentIndex,
	const std::vector<std::string>& itemsI18nKey, const float fontSize,
	const TextAlign textAlign, const raylib::Color textColor,
	const float textSpacing, const std::string& itemTexture, const std::string& sliderBar,
	const std::string& sliderBackground) :
	ScrollList(bounds, itemCapacity, currentIndex,
		[&]() {
			std::vector<std::string> texts;
			for (const auto& key : itemsI18nKey) {
				texts.push_back(I18n::instance().get(key));
			}
			return texts;
		}(),
		fontSize, textAlign, textColor, textSpacing,
		[&]() {
			std::vector<const raylib::Font*> fonts;
			for (const auto& key : itemsI18nKey) {
				fonts.push_back(&FontProvider::instance().get(key));
			}
			return fonts;
		}(),
		itemTexture, sliderBar, sliderBackground)
{

}

ScrollList::ScrollList(raylib::Rectangle bounds, const int itemCapacity, const int currentIndex,
	const std::vector<std::string>& itemsText, float fontSize, TextAlign textAlign, raylib::Color textColor,
	float textSpacing, const std::vector<const raylib::Font*>& itemsFont,
	const std::string& itemTexture, const std::string& sliderBar,
	const std::string& sliderBackground)
{
	using RaylibUtils::getRealLength;
	constexpr int tileImageWidth = 64;

	this->elementType = ElementType::SCROLL_LIST;
	this->position = getRealLength(bounds.GetPosition());
	this->bounds = getRealLength(Rectangle(bounds.x - bounds.width / 2, bounds.y - bounds.height / 2,
		bounds.width, bounds.height));
	this->startIndex = 0;
	this->currentIndex = currentIndex;
	this->itemCapacity = (itemsText.size() > itemCapacity) ? itemCapacity : static_cast<int>(itemsText.size());

	for (int i = 0; i < itemsText.size(); i++)
	{
		this->itemsText.emplace_back(Vector2(0, 0), itemsText[i], fontSize,
			textAlign, textSpacing, itemsFont[i]);
	}

	const float buttonHeight = bounds.height / static_cast<float>(itemCapacity);
	float buttonY = bounds.y - bounds.height/2 + static_cast<float>(buttonHeight)/2;
	const PictureTiled itemBg(itemTexture, 2, tileImageWidth, Vector2(bounds.width, buttonHeight));
	for (int i = 0; i < this->itemCapacity; i++)
	{
		this->items.push_back(std::make_shared<ButtonText>(Vector2(bounds.x, buttonY), Button(itemBg, [this, i] { select(i); }),
		                         Text(itemsText[i], fontSize, textAlign, textSpacing, itemsFont[i])));
		buttonY += buttonHeight;
	}

	if (itemsText.size() > this->itemCapacity)
	{
		this->scrollable = true;
		const float barHeight = bounds.height / static_cast<float>(itemsText.size()) * static_cast<float>(itemCapacity);
		this->slider = std::make_shared<Slider>(Vector2(bounds.x + bounds.width / 2 + this->scrollBarWidth / 2, bounds.y),
			PictureTiled(sliderBar, 2, tileImageWidth, Vector2(this->scrollBarWidth, barHeight)),
			PictureTiled(sliderBackground, 2, tileImageWidth, Vector2(this->scrollBarWidth, bounds.height)),
			&this->startIndex, 0, static_cast<int>(itemsText.size()) - itemCapacity, false);
	}
	else {
		this->scrollable = false;
	}

	updateChildren();
}

ScrollList::ScrollList(const ScrollList& other) : ElementGroup(other),
	itemCapacity(other.itemCapacity),
	scrollable(other.scrollable),
	startIndex(other.startIndex),
	currentIndex(other.currentIndex),
	itemsText(other.itemsText),
	items(other.items),
	slider(other.slider)
{
	updateChildren();
}

ScrollList& ScrollList::operator=(ScrollList other)
{
	swap(*this, other);
	return *this;
}

void ScrollList::updateChildren()
{
	ElementGroup::updateChildren();
	int index = 0;
	for (const auto& item : this->items)
	{
		this->children.push_back(item);
		item->getButton()->setFunction([this, index] { select(index); });
		for (auto& child : item->getChildren())
		{
			this->children.push_back(child);
		}
		index++;
	}
	if (this->scrollable)
	{
		this->children.push_back(this->slider);
		for (auto& item : this->slider->getChildren())
		{
			this->children.push_back(item);
		}
	}
}

void ScrollList::draw()
{
	const int wheelMove = static_cast<int>(GetMouseWheelMove());
	if (this->scrollable)
	{
		if (wheelMove != 0)
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
				if (this->startIndex + this->itemCapacity < static_cast<int>(this->itemsText.size()))
				{
					this->startIndex++;
				}
			}
			for (size_t i = 0; i < this->itemCapacity; i++)
			{
				this->items[i]->setText(this->itemsText[this->startIndex + i]);
			}
		}
	}
	const int index = this->currentIndex - this->startIndex;
	if (index >= 0 && index < this->itemCapacity)
	{
		this->items[index]->getButton()->setState(ButtonState::HOVER);
	}
}

void ScrollList::updatePosition()
{
	this->bounds.x = this->position.x - this->bounds.width / 2;
	this->bounds.y = this->position.y - this->bounds.height / 2;

	if (this->scrollable)
	{
		this->slider->setPosition(Vector2(this->bounds.x + this->bounds.width + scrollBarWidth / 2, this->position.y));
	}

	const float buttonHeight = this->items[0]->getButton()->getHitbox()[0].height;
	float buttonY = this->bounds.y + static_cast<float>(buttonHeight) / 2;
	for (int i = 0; i < this->itemCapacity; i++)
	{
		this->items[i]->setPosition(Vector2(this->position.x, buttonY));
		buttonY += buttonHeight;
	}
}

void ScrollList::select(const int index)
{
	this->currentIndex = this->startIndex + index;
}

void swap(ScrollList& first, ScrollList& second) noexcept
{
	using std::swap;
	swap(static_cast<ElementGroup&>(first), static_cast<ElementGroup&>(second));

	swap(first.bounds, second.bounds);
	swap(first.itemCapacity, second.itemCapacity);
	swap(first.scrollable, second.scrollable);
	swap(first.currentIndex, second.currentIndex);
	swap(first.startIndex, second.startIndex);
	swap(first.items, second.items);
	swap(first.itemsText, second.itemsText);
	swap(first.slider, second.slider);

	first.updateChildren();
}
