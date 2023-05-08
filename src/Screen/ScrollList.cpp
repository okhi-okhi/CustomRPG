#include "ScrollList.h"
#include "../Utils/RaylibUtils.h"

ScrollList::ScrollList(const std::string& background, const Rectangle bounds,
	const int itemCapacity, const std::string& itemTexture,
	const std::vector<Text>& itemsText,
	const std::string& scrollBar, const std::string& scrollBackground)
{
	constexpr int spacing = 16;
	constexpr float tileImageZoomPercent = 0.05f;
	this->currentIndex = 0;
	this->itemCapacity = itemCapacity;

	if(itemsText.size() < itemCapacity)
	{
		constexpr int scrollBarWidth = 32;
		this->hitbox = raylib::Rectangle(RaylibUtils::getWindowWidth()*bounds.x,
			RaylibUtils::getWindowHeight() * bounds.y,
			RaylibUtils::getWindowHeight() * bounds.width + scrollBarWidth,
			RaylibUtils::getWindowHeight() * bounds.height);
	} else {
		this->hitbox = raylib::Rectangle(RaylibUtils::getWindowWidth() * bounds.x,
			RaylibUtils::getWindowHeight() * bounds.y,
			RaylibUtils::getWindowHeight() * bounds.width,
			RaylibUtils::getWindowHeight() * bounds.height);
	}
	int buttonHeight = (this->hitbox.height - (this->itemCapacity + 1) * spacing) / this->itemCapacity;

	const int realTileWidth = static_cast<int>(RaylibUtils::getWindowWidth() * tileImageZoomPercent);
	// Vector2 backgroundTileNum(this->hitbox.width / realTileWidth,
	// 	this->hitbox.width / realTileWidth * );
	// this->background = Picture(background, Vector2(bounds.x, bounds.y), 1, tileImageZoomPercent, );

	int buttonY = this->hitbox.y;
	for (int i = 0; i < itemsText.size(); i++)
	{
		buttonY += spacing;
		//this->items.emplace(Vector2(this->hitbox.x + spacing, buttonY));
		buttonY += buttonHeight;
	}
	//TODO scrollBar and scrollBarBackground
}

void ScrollList::draw()
{
	//TODO draw background
	for (auto& item : this->items)
	{
		item.draw();
	}
	//TODO draw scrollBar and scrollBarBackground
}

ScrollList* ScrollList::clone() const
{
	return new ScrollList(*this);
}
