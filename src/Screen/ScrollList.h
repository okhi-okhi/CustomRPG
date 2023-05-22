#pragma once
#include <vector>
#include "ButtonText.h"

class ScrollList final : public Clickable
{
private:
	int itemCapacity;
	bool scrollable;
	int startIndex;
	int currentIndex;
	std::vector<Text> itemsText;
	std::vector<ButtonText> items;
	Button scrollBar;
	Button scrollBackground;

public:
	ScrollList() : itemCapacity(0), scrollable(false), currentIndex(-1) {}
	ScrollList(Rectangle bounds, int itemCapacity,
		const std::vector<std::string>& itemsText,
		float fontSize, textAlign textAlign, raylib::Color textColor, float textSpacing,
		const std::vector<const raylib::Font*>& itemsFont,
		const std::string& itemTexture, const std::string& scrollBar,
		const std::string& scrollBackground);

	void draw() override;
	ScrollList* clone() const override;

	static void select();
};

