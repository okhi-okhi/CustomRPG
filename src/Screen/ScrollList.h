#pragma once
#include <vector>
#include "Button.h"

class ScrollList : public Element
{
private:
	std::vector<Button> items;
	int itemCapacity;
	bool scrollable;
	int currentIndex;
	Button scrollBar;
	Button scrollBackground;

public:
	ScrollList() : itemCapacity(0), scrollable(false), currentIndex(-1) {}
	ScrollList(const std::string& itemTexture, const std::vector<Text>& itemsText, Vector2 position,
		int itemCapacity, const std::string& scrollBar, const std::string& scrollBackground);
};

