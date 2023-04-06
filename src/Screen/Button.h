#pragma once
#include <string>
#include <raylib-cpp.hpp>
#include "Picture.h"

enum class buttonState
{
	IDLE = 0,
	HOVER
};

enum class textAlign
{
	LEFT = 0,
	CENTER,
	RIGHT
};

class Button
{
private:
	Picture texture;
	std::string i18nKey;

	float fontSize;
	textAlign textAlign;
	raylib::Color textColor;
	float textSpacing;

public:
	Button() = default;
	Button(const Picture& texture, const std::string& i18nKey, float fontSize = 32.0f, enum textAlign textAlign = textAlign::LEFT, raylib::Color textColor = BLACK, float textSpacing = 1.0f);

	void draw(const std::string& i18nPrefix);

	const Picture& getTexture() const { return this->texture; }
	const std::string& getI18nKey() const { return this->i18nKey; }
	buttonState getButtonState() const { return static_cast<buttonState>(this->texture.getCurrentFrame()); }
	float getButtonHeight() const { return this->texture.getHeight(); }

	const float& getFontSize() const { return this->fontSize; }
	const enum textAlign& getTextAlign() const { return this->textAlign; }
	const raylib::Color& getTextColor() const { return this->textColor; }
	const float& getTextSpacing() const { return this->textSpacing; }
};

