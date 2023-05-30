#pragma once
#include "ButtonHold.h"

class Slider : public Clickable
{
private:
	raylib::Rectangle bounds;
	ButtonHold bar;
	Button background;
	int value;
	int minValue;
	int maxValue;
	bool horizontal;

	void barDrag();
	void backgroundClick();

public:
	Slider() : value(-1), minValue(0), maxValue(0), horizontal(false) {}
	Slider(Rectangle bounds, const std::string& bar, const std::string& background,
		int minValue, int maxValue, bool horizontal);
	Slider(Rectangle bounds, const std::string& bar, const std::string& background,
		int barLength, int minValue, int maxValue, bool horizontal);

	void draw() override;
	Slider* clone() const override;

	const int& getValue() const { return this->value; }
};