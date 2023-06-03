#pragma once
#include "ButtonText.h"
#include "ClickableGroup.h"

class ScrollList final : public ClickableGroup
{
private:
	raylib::Rectangle bounds;
	int itemCapacity;
	bool scrollable;
	int startIndex;
	int currentIndex;
	std::vector<Text> itemsText;
	std::vector<ButtonText*> items;
	Picture scrollBar;
	Picture scrollBackground;

public:
	ScrollList() : itemCapacity(0), scrollable(false), startIndex(0), currentIndex(-1) {}
	ScrollList(Rectangle bounds, int itemCapacity,
		const std::vector<std::string>& itemsText,
		float fontSize, textAlign textAlign, raylib::Color textColor, float textSpacing,
		const std::vector<const raylib::Font*>& itemsFont,
		const std::string& itemTexture, const std::string& scrollBar,
		const std::string& scrollBackground);

	void draw() override;
	ScrollList* clone() const override;
	void updatePosition() override;

	static void select();
};

