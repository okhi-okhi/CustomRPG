#pragma once
#include <vector>
#include "Button.h"

class ScrollList final : public Clickable
{
private:
	int itemCapacity;
	bool scrollable;
	int currentIndex;
	std::vector<Button> items;
	Button scrollBar;
	Button scrollBackground;

public:
	ScrollList() : itemCapacity(0), scrollable(false), currentIndex(-1) {}
	ScrollList(Rectangle bounds, int itemCapacity, const std::vector<Text>& itemsText,
		const std::string& itemTexture, const std::string& scrollBar,
		const std::string& scrollBackground);

	void draw() override;
	ScrollList* clone() const override;

	static void select();
};

