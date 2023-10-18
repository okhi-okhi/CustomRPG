#pragma once
#include "ButtonText.h"
#include "Slider.h"

class ScrollList final : public Element
{
private:
	inline static const float scrollBarWidth = 32;
	raylib::Rectangle bounds;
	int itemCapacity;
	bool scrollable;
	int startIndex;
	int currentIndex;
	std::vector<Text> itemsText{};
	std::vector<ButtonText> items{};
	Slider slider;
	std::function<void()> function;

public:
	ScrollList() : itemCapacity(0), scrollable(false), startIndex(0), currentIndex(-1){}
	ScrollList(raylib::Rectangle bounds, int itemCapacity, int currentIndex,
		const std::vector<std::string>& itemsI18nKey, TextAlign textAlign, float textSpacing,
		const std::string& itemTexture, const std::string& sliderBar,
		const std::string& sliderBackground, const std::function<void()>& function);
	ScrollList(raylib::Rectangle bounds, int itemCapacity, int currentIndex,
		const std::vector<std::string>& itemsText, TextAlign textAlign, float textSpacing,
		const std::vector<const raylib::Font*>& itemsFont,
		const std::string& itemTexture, const std::string& sliderBar,
		const std::string& sliderBackground, const std::function<void()>& function);
	ScrollList(const ScrollList& other);
	ScrollList(ScrollList&& other) noexcept : ScrollList() { swap(*this, other); }
	~ScrollList() override = default;

	ScrollList& operator=(ScrollList other);
	friend void swap(ScrollList& first, ScrollList& second) noexcept;

	void draw() override;
	void update() override;
	void updatePosition() override;

	void updateChildren();
	void select(int index);

	const raylib::Rectangle& getBounds() const { return this->bounds; }
	const int& getItemCapacity() const { return this->itemCapacity; }
	const bool& isScrollable() const { return this->scrollable; }
	const int& getStartIndex() const { return this->startIndex; }
	const int& getCurrentIndex() const { return this->currentIndex; }
	const std::vector<Text>& getItemsText() { return this->itemsText; }
	const std::vector<ButtonText>& getItems() { return this->items; }
	const Slider& getSlider() const { return this->slider; }
};

