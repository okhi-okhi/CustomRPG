#pragma once
#include <functional>
#include <Sound.hpp>
#include "Picture.h"
#include "Text.h"
#include "../../System/PathProvider.h"

enum class buttonState
{
	IDLE = 0,
	HOVER
};

class Button : public Element
{
private:
	Text text;
protected:
	Picture texture;
	Sound clickSound;
	std::function<void()> clickFun;
	std::vector<raylib::Rectangle> reserveRec;

public:
	Button() = default;
	Button(const std::string& fileName, Vector2 position, float zoomPercent,
	       const std::string& i18nKey, float fontSize, textAlign textAlign,
	       raylib::Color textColor, float textSpacing, const std::function<void()>& function,
	       const std::string& clickSound = "button_click.wav");

	void draw() override;
	Button* clone() const override;

	void update();
	void checkCollision(raylib::Rectangle hitbox);
	void addReserveRec(raylib::Rectangle hitbox);

	Vector2 getTextPos(textAlign textAlign) const;
	const Picture& getTexture() const { return this->texture; }
	const Text& getI18nKey() const { return this->text; }
	buttonState getButtonState() const { return static_cast<buttonState>(this->texture.getCurrentFrame()); }
	float getButtonHeight() const { return this->texture.getHeight(); }
};

