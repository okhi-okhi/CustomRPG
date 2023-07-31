#pragma once
#include "Text.h"
#include "Button.h"

class ButtonText final : public Element
{
private:
	Button button;
	Text text;

public:
	ButtonText() = default;
	ButtonText(Vector2 pos, const Button& button, const Text& text);

	void draw() override;
	void update() override;
	void updatePosition() override;

	void setText(const Text& _text);

	Button& getButton() { return this->button; }
	Text& getText() { return this->text; }
};

