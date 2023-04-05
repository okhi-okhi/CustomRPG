#pragma once
#include <string>
#include <raylib-cpp.hpp>

#define BUTTON_STATE_NUMS 2

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
	Texture2D spriteTexture;
	std::string i18nKey;
	Vector2 buttonPosition;
	buttonState buttonState;

	float fontSize;
	textAlign textAlign;
	raylib::Color textColor;
	float textSpacing;

public:
	Button() = default;
	Button(const std::string& fileName, const std::string& i18nKey, Vector2 buttonPos, float zoomPercent, float fontSize = 32.0f, enum textAlign textAlign = textAlign::LEFT, raylib::Color textColor = BLACK, float textSpacing = 1.0f);

	void draw(const std::string& i18nPrefix);

	const Texture2D& getSpriteTexture() const { return this->spriteTexture; }
	const std::string& getI18nKey() const { return this->i18nKey; }
	const Vector2& getButtonPosition() const { return this->buttonPosition; }
	const enum buttonState& getButtonState() const { return this->buttonState; }
	float getButtonHeight() const { return static_cast<float>(this->spriteTexture.height) / BUTTON_STATE_NUMS; }

	const float& getFontSize() const { return this->fontSize; }
	const enum textAlign& getTextAlign() const { return this->textAlign; }
	const raylib::Color& getTextColor() const { return this->textColor; }
	const float& getTextSpacing() const { return this->textSpacing; }
};

