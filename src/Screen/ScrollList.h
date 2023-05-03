#pragma once
#include <vector>
#include "Button.h"

class ScrollList : public Element
{
private:
	int itemCapacity;
	std::vector<Button> items;
	Button scrollBar;
	Button scrollBackground;
	bool scrollable;
	int currentIndex;

public:
	ScrollList() : itemCapacity(0), scrollable(false), currentIndex(-1) {}
	ScrollList(const std::string& background, Rectangle backgroundBounds,
		const std::string& itemTexture, Vector2 bounds,
		const std::vector<Text>& itemsText, int itemCapacity,
		const std::string& scrollBar, const std::string& scrollBackground);
};

