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
	std::function<void()> function;

public:
	Button() : clickSound() {}
	Button(Vector2 position, const Picture& texture,
		const std::function<void()>& function,
		const std::string& clickSound = "button_click.wav");

	void draw() override;
	Button* clone() const override;
	void updatePosition() override;

	virtual void update();

	void setState(buttonState buttonState) { this->texture.setCurrentFrame(static_cast<int>(buttonState)); }
	void setFunction(const std::function<void()>& function) { this->function = function; }

	const Picture& getTexture() const { return this->texture; }
	buttonState getButtonState() const { return static_cast<buttonState>(this->texture.getCurrentFrame()); }
	float getButtonHeight() const { return this->texture.getHeight(); }
};

