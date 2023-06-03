#pragma once
#include "ButtonHold.h"
#include "ClickableGroup.h"

class Slider : public ClickableGroup
{
private:
	raylib::Rectangle bounds;
	ButtonHold* bar;
	Button* background;
	int value;
	int minValue;
	int maxValue;
	bool horizontal;

	float stepPerValue;

	void barDrag();
	void backgroundClick();

public:
	Slider() : bar(nullptr), background(nullptr), value(-1), minValue(0), maxValue(0), horizontal(false), stepPerValue(0) {}
	Slider(Rectangle bounds, const std::string& bar, const std::string& background,
		int barLength, int minValue, int maxValue, bool horizontal);

	void draw() override;
	Slider* clone() const override;

	const ButtonHold* getBar() const { return this->bar; }
	const int& getValue() const { return this->value; }
};