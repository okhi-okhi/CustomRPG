#pragma once
#include "ButtonText.h"
#include "Slider.h"

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
	Slider* slider;

public:
	ScrollList() : itemCapacity(0), scrollable(false), startIndex(0), currentIndex(-1), slider(nullptr) {}
	ScrollList(Rectangle bounds, int itemCapacity,
		const std::vector<std::string>& itemsText,
		float fontSize, textAlign textAlign, raylib::Color textColor, float textSpacing,
		const std::vector<const raylib::Font*>& itemsFont,
		const std::string& itemTexture, const std::string& sliderBar,
		const std::string& sliderBackground);

	void draw() override;
	ScrollList* clone() const override;
	void updatePosition() override;

	static void select();

	const Slider* getSlider() const { return this->slider; }
};

