#pragma once
#include <functional>
#include <Sound.hpp>
#include "Picture.h"
#include "Text.h"

enum class buttonState
{
	IDLE = 0,
	HOVER
};

class Button : public Element
{
protected:
	Picture texture;
	Sound clickSound;
	std::function<void()> clickFun;
	std::vector<raylib::Rectangle> reserveRec{};

public:
	Button() : clickSound() {}
	Button(const std::string& fileName, Vector2 position, float zoomPercent,
		const std::function<void()>& function,
		const std::string& clickSound = "button_click.wav");

	void draw() override;
	Button* clone() const override;

	void update();
	void checkCollision(raylib::Rectangle hitbox);
	void addReserveRec(raylib::Rectangle hitbox);

	Vector2 getTextPos(textAlign textAlign) const;
	const Picture& getTexture() const { return this->texture; }
	buttonState getButtonState() const { return static_cast<buttonState>(this->texture.getCurrentFrame()); }
	float getButtonHeight() const { return this->texture.getHeight(); }
};

