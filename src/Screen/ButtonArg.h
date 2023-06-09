#pragma once
#include "Button.h"
#include "TextArg.h"

class ButtonArg final : public Button
{
private:
	TextArg text;

public:
	ButtonArg() = default;
	ButtonArg(Vector2 position, const Picture& texture, const TextArg& text,
		const std::function<void()>& function,
		const std::string& clickSound = "button_click.wav");

	void draw() override;

	const TextArg& getText() const { return this->text; }
};

