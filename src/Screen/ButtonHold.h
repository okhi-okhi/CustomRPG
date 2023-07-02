#pragma once
#include "Button.h"

class ButtonHold : public Button
{
public:
	ButtonHold() = default;
	ButtonHold(const Vector2 position, const Picture& texture,
		const std::function<void()>& function) :
		Button(position, texture, function, "none") {}
	ButtonHold(const Picture& texture, const std::function<void()>& function) :
		Button(texture, function, "none") {}

	void update() override;
};

