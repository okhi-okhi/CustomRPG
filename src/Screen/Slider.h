#pragma once
#include <functional>
#include "ButtonHold.h"
#include "ElementGroup.h"

class Slider final : public ElementGroup
{
private:
	raylib::Rectangle bounds;
	shared_ptr<ButtonHold> bar;
	shared_ptr<Button> background;
	int* value;
	int minValue;
	int maxValue;
	bool horizontal;
	std::function<void()> dragFunction;

	bool dragging;
	float displayValueSpacing;
	float valueSpacing;

	void barDrag();
	void backgroundClick();

public:
	Slider() : value(nullptr), minValue(0), maxValue(0), horizontal(false), dragging(false), displayValueSpacing(0), valueSpacing(0) {}
	Slider(const Picture& bar, const Picture& background,
		int* value, int minValue, int maxValue, bool horizontal,
		const std::function<void()>& dragFunction = std::function<void()>());
	Slider(Vector2 bounds, const Picture& bar, const Picture& background,
		int* value, int minValue, int maxValue, bool horizontal,
		const std::function<void()>& dragFunction = std::function<void()>());
	Slider(const Slider& other);
	Slider(Slider&& other) noexcept : Slider() { swap(*this, other); }
	~Slider() override = default;

	Slider& operator=(Slider other);
	friend void swap(Slider& first, Slider& second) noexcept;

	void draw() override;
	void updatePosition() override;
	void updateChildren() override;

	const raylib::Rectangle& getBounds() const { return this->bounds; }
	const shared_ptr<ButtonHold>& getBar() const { return this->bar; }
	const shared_ptr<Button>& getBackground() const { return this->background; }
};