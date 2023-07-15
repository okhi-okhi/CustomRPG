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
	ButtonText(Vector2 pos, const Button& button, const Text& text);
	ButtonText(const ButtonText& other) = default;
	ButtonText(ButtonText&& other) noexcept : ButtonText() { swap(*this, other); }
	~ButtonText() override = default;

	ButtonText& operator=(ButtonText other);
	friend void swap(ButtonText& first, ButtonText& second) noexcept;

	void draw() override;
	void updatePosition() override;
	void updateChildren() override;

	void setText(const Text& _text);

	const shared_ptr<Button>& getButton() const { return this->button; }
	const shared_ptr<Text>& getText() const { return this->text; }
};

