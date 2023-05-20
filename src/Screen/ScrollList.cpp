#include "ScrollList.h"
#include "../Utils/RaylibUtils.h"

ScrollList::ScrollList(const Rectangle bounds, const int itemCapacity,
	const std::vector<Text>& itemsText,
	const std::string& itemTexture, const std::string& scrollBar,
	const std::string& scrollBackground)
{
	constexpr int tileImageWidth = 64;

	this->currentIndex = 0;
	this->itemCapacity = itemCapacity;

	//this->hitbox = RaylibUtils::getRealLength(Rectangle(bounds.x - bounds.width / 2, bounds.y - bounds.height / 2, bounds.width, bounds.height));

	if(itemsText.size() < itemCapacity)
	{
		constexpr int scrollBarWidth = 32;
		this->scrollable = true;
		//TODO scrollBar and scrollBarBackground

	} else {
		this->scrollable = false;
	}

	const int buttonHeight = bounds.height / this->itemCapacity;
	int buttonY = bounds.y - bounds.height/2 + static_cast<float>(buttonHeight) /2;
	for (int i = 0; i < itemsText.size(); i++)
	{
		this->items.emplace_back(itemTexture, Vector2(bounds.x, buttonY), tileImageWidth, 
			Vector2(bounds.width, buttonHeight), select);
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
