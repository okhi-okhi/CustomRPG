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
	TextBox(raylib::Rectangle bounds, const std::string& i18nKey,
		TextAlign align, float spacing);
	TextBox(raylib::Rectangle bounds, const std::string& text,
		TextAlign align, float spacing, const raylib::Font* font);

	void draw() override;
	void updatePosition() override;

	void parseText(std::string str) override;
	void setText(const std::string& text) override;

	void calculateLineCapacity();

	const raylib::Rectangle& getBounds() const { return bounds; }
	const int& getLineCapacity() const { return lineCapacity; }
	const int& getStartIndex() const { return startIndex; }
	const bool& isScrollable() const { return scrollable; }
};

