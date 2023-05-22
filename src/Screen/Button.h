#pragma once
#include <functional>
#include <Sound.hpp>
#include "Picture.h"
#include "Text.h"
#include "Clickable.h"

enum class buttonState
{
	IDLE = 0,
	HOVER
};

class Button : public Clickable
{
protected:
	Picture texture;
	Sound clickSound;
	std::function<void()> clickFun;

public:
	Button() : clickSound() {}
	Button(Vector2 position, const Picture& texture,
		const std::function<void()>& function,
		const std::string& clickSound = "button_click.wav");

	void draw() override;
	Button* clone() const override;
	void updatePosition() override;

	void update();

	// Vector2 getTextPos(textAlign textAlign) const;
	const Picture& getTexture() const { return this->texture; }
	buttonState getButtonState() const { return static_cast<buttonState>(this->texture.getCurrentFrame()); }
	float getButtonHeight() const { return this->texture.getHeight(); }
};

