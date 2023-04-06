#include "Button.h"
#include <iostream>
#include "../I18n/I18n.h"
#include "../I18n/FontProvider.h"
#include "../System/PathProvider.h"
#include "../Utils/RaylibUtils.h"

Button::Button(const Picture& texture, const std::string& i18nKey, const float fontSize, const enum textAlign textAlign, const raylib::Color textColor, const float textSpacing)
{
	this->texture = texture;

	this->i18nKey = i18nKey;

	this->fontSize = fontSize;
	this->textAlign = textAlign;
	this->textColor = textColor;
	this->textSpacing = textSpacing;
}

void Button::draw(const std::string& i18nPrefix)
{
	if (CheckCollisionPointRec(GetMousePosition(), raylib::Rectangle(this->texture.getPosition().x, this->texture.getPosition().y, static_cast<float>(this->texture.getSpriteTexture().width), this->getButtonHeight())))
	{
		this->texture.setCurrentFrame(static_cast<int>(buttonState::HOVER));
	}
	else
	{
		this->texture.setCurrentFrame(static_cast<int>(buttonState::IDLE));
	}

	this->texture.draw();

	const std::string text = I18n::instance().get(i18nPrefix + "." + this->i18nKey);
	const raylib::Font *font = &FontProvider::instance().get(i18nPrefix + "." + this->i18nKey);

	Vector2 textPosition;
	const Vector2 textSize = MeasureTextEx(*font, text.c_str(), this->fontSize, this->textSpacing);
	const float textY = this->texture.getPosition().y + (this->getButtonHeight() - textSize.y) / 2;
	switch (this->textAlign)
	{
	case textAlign::LEFT:
		textPosition = Vector2(this->texture.getPosition().x, textY);
		break;

	case textAlign::CENTER:
		textPosition = Vector2(this->texture.getPosition().x + (this->texture.getSpriteTexture().width - textSize.x) / 2, textY);
		break;

	case textAlign::RIGHT:
		textPosition = Vector2(this->texture.getPosition().x + this->texture.getSpriteTexture().width - textSize.x, textY);
		break;
	}
	raylib::DrawTextEx(*font, text, textPosition, this->fontSize, this->textSpacing, this->textColor);
}
