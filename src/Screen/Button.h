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
	Button(const std::string& fileName, Vector2 position, int width,
		const std::function<void()>& function,
		const std::string& clickSound = "button_click.wav");

	Button(const std::string& tileImage, Vector2 position, int tileWidth,
		Vector2 tiledBounds, const std::function<void()>& function,
		const std::string& clickSound = "button_click.wav");

	void draw() override;
	Button* clone() const override;

	void update();

	// Vector2 getTextPos(textAlign textAlign) const;
	const Picture& getTexture() const { return this->texture; }
	buttonState getButtonState() const { return static_cast<buttonState>(this->texture.getCurrentFrame()); }
	float getButtonHeight() const { return this->texture.getHeight(); }
};

