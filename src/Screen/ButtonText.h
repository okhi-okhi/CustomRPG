#pragma once
#include "Text.h"
#include "Button.h"

class ButtonText : public Button
{
private:
	Text text;
public:
	ButtonText() = default;
	ButtonText(Vector2 position, const Picture& texture, const Text& text,
		const std::function<void()>& function,
		const std::string& clickSound = "button_click.wav");

	void draw() override;

	void setText(const Text& text);

	const Text& getText() const { return this->text; }
};

