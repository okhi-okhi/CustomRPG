#pragma once
#include <string>
#include <raylib-cpp.hpp>

#define BUTTON_STATE_NUMS 2

enum class buttonState
{
	IDLE = 0,
	HOVER
};

class Button
{
private:
	Texture2D spriteTexture;
	std::string i18nKey;
	Vector2 position;
	buttonState buttonState;

public:
	Button() = default;
	Button(const std::string& fileName, const std::string& i18nKey, Vector2 pos, float zoomPercent);

	void draw(const std::string& i18nPrefix) const;

	const Texture2D& getSpriteTexture() const { return this->spriteTexture; }
	const std::string& getI18nKey() const { return this->i18nKey; }
	const Vector2& getPosition() const { return this->position; }
	const enum buttonState& getButtonState() const { return this->buttonState; }
	float getButtonHeight() const { return static_cast<float>(this->spriteTexture.height) / BUTTON_STATE_NUMS; }
};

