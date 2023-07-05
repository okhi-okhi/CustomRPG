#pragma once
#include "Slider.h"
#include "TextArg.h"
class SliderText final : public ElementGroup
{
private:
	shared_ptr<Slider> slider;
	shared_ptr<Text> name;
	shared_ptr<TextArg> value;

	const float spacing = 32;

public:
	SliderText() = default;
	SliderText(Vector2 position,const Slider& slider,
	           const Text& name, const TextArg& value);
	explicit SliderText(const SliderText& other);
	SliderText(SliderText&& other) noexcept : SliderText() { swap(*this, other); }
	~SliderText() override = default;

	SliderText& operator=(SliderText other);
	friend void swap(SliderText& first, SliderText& second) noexcept;

	void draw() override;
	void updatePosition() override;
	void updateChildren() override;

	const shared_ptr<Slider>& getSlider() const { return this->slider; }
	const shared_ptr<Text>& getName() const { return this->name; }
	const shared_ptr<TextArg>& getValue() const { return this->value; }
};

