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
	ScrollList(const std::string& background, Rectangle bounds,
		int itemCapacity, const std::string& itemTexture,
		const std::vector<Text>& itemsText,
		const std::string& scrollBar, const std::string& scrollBackground);

	void draw() override;
	ScrollList* clone() const override;
};

