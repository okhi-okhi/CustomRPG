#pragma once
#include "Picture.h"
#include "Text.h"

enum class buttonState
{
	IDLE = 0,
	HOVER
};

class Button
{
private:
	Picture texture;
	Text text;

public:
	Button() = default;
	Button(const Picture& texture, const std::string& i18nKey, float fontSize = 32.0f, enum textAlign textAlign = textAlign::LEFT, raylib::Color textColor = BLACK, float textSpacing = 1.0f);

	void draw(const std::string& i18nPrefix);

	const Picture& getTexture() const { return this->texture; }
	const Text& getI18nKey() const { return this->text; }
	buttonState getButtonState() const { return static_cast<buttonState>(this->texture.getCurrentFrame()); }
	float getButtonHeight() const { return this->texture.getHeight(); }
};

