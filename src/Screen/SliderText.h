#pragma once
#include "Slider.h"
#include "TextArg.h"
class SliderText final : public Element
{
private:
	Slider slider;
	Text name;
	TextArg value;

	const float spacing = 32;

public:
	SliderText() = default;
	SliderText(Vector2 position, const Slider& slider,
	           const Text& name, const TextArg& value);

	void draw() override;
	void update() override;
	void updatePosition() override;

	const Slider& getSlider() const { return this->slider; }
	const Text& getName() const { return this->name; }
	const TextArg& getValue() const { return this->value; }
};

