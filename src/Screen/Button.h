#pragma once
#include <functional>
#include <Sound.hpp>
#include "Picture.h"

enum class ButtonState
{
	IDLE = 0,
	HOVER
};

class Button : public Element
{
protected:
	Picture texture;
	Sound clickSound;
	std::function<void()> function;

public:
	Button() : clickSound() {}
	Button(raylib::Vector2 pos, const Picture& texture,
		const std::function<void()>& function,
		const std::string& clickSound = "button_click.wav");
	Button(const Picture& texture, const std::function<void()>& function,
		const std::string& clickSound = "button_click.wav");

	void draw() override;
	void update() override;
	void updatePosition() override;

	void setState(ButtonState buttonState) { this->texture.setCurrentFrame(static_cast<int>(buttonState)); }
	void setFunction(const std::function<void()>& _function) { this->function = _function; }

	const Picture& getTexture() const { return this->texture; }
	ButtonState getButtonState() const { return static_cast<ButtonState>(this->texture.getCurrentFrame()); }
	float getButtonHeight() const { return this->texture.getHeight(); }
};

