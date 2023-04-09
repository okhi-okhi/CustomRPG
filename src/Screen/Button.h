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
	Text text;
protected:
	Picture texture;

public:
	Button() = default;
	Button(const std::string& fileName, Vector2 position, float zoomPercent,
		const std::string& i18nKey, float fontSize = 32.0f, textAlign textAlign = textAlign::LEFT,
		raylib::Color textColor = BLACK, float textSpacing = 1.0f);
	virtual ~Button() = default;

	virtual void draw();

	Vector2 getTextPos(textAlign textAlign) const;

	const Picture& getTexture() const { return this->texture; }
	const Text& getI18nKey() const { return this->text; }
	buttonState getButtonState() const { return static_cast<buttonState>(this->texture.getCurrentFrame()); }
	float getButtonHeight() const { return this->texture.getHeight(); }
};

