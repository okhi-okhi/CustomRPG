#pragma once
#include "Text.h"
#include "Button.h"
#include "ElementGroup.h"

class ButtonText final : public ElementGroup
{
private:
	shared_ptr<Button> button;
	shared_ptr<Text> text;
public:
	ButtonText() = default;
	ButtonText(Vector2 position, const Button& button, const Text& text);

	void draw() override;
	void updateChildren() override;

	void setText(const Text& _text);

	const shared_ptr<Button>& getButton() const { return this->button; }
	const shared_ptr<Text>& getText() const { return this->text; }
};

