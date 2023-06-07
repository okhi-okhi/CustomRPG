#pragma once
#include "ButtonHold.h"
#include "ClickableGroup.h"

class Slider : public ClickableGroup
{
private:
	raylib::Rectangle bounds;
	ButtonHold* bar;
	Button* background;
	int* value;
	int minValue;
	int maxValue;
	bool horizontal;

	bool dragging;
	float displayValueSpacing;
	float valueSpacing;

	void barDrag();
	void backgroundClick();

public:
	Slider() : bar(nullptr), background(nullptr), value(nullptr), minValue(0), maxValue(0), horizontal(false), dragging(false), displayValueSpacing(0), valueSpacing(0) {}
	Slider(Rectangle bounds, const std::string& bar, const std::string& background,
		int barLength, int* value, int minValue, int maxValue, bool horizontal);

	void draw() override;
	Slider* clone() const override;

	const raylib::Rectangle& getBounds() const { return this->bounds; }
	const ButtonHold* getBar() const { return this->bar; }
	const Button* getBackground() const { return this->background; }
};