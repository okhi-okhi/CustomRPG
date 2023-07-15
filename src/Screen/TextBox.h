#pragma once
#include "Text.h"

class TextBox : virtual public Text
{
protected:
	raylib::Rectangle bounds;
	int lineCapacity;
	int startIndex;
	bool scrollable;

public:
	TextBox() : lineCapacity(0), startIndex(0), scrollable(false) {}
	TextBox(raylib::Rectangle bounds, const std::string& i18nKey, float fontSize,
		TextAlign align, float spacing);
	TextBox(raylib::Rectangle bounds, const std::string& text, float fontSize,
		TextAlign align, float spacing, const raylib::Font* font);

	void draw() override;
	void updatePosition() override;

	std::vector<TextLine> str2TextLines(std::string str) const override;

	const raylib::Rectangle& getBounds() const { return bounds; }
	const int& getLineCapacity() const { return lineCapacity; }
	const int& getStartIndex() const { return startIndex; }
	const bool& isScrollable() const { return scrollable; }
};

