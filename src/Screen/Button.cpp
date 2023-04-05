#include "Button.h"
#include <iostream>
#include "../I18n/I18n.h"
#include "../I18n/FontProvider.h"
#include "../System/PathProvider.h"
#include "../Utils/RaylibUtils.h"

Button::Button(const std::string& fileName, const std::string& i18nKey, const Vector2 buttonPos, const float zoomPercent, const float fontSize, const enum textAlign textAlign, const raylib::Color textColor, const float textSpacing)
{
	raylib::Image image(PathProvider::instance().getResourcesPath() + fileName);
	const int btnWidth = static_cast<int>(RaylibUtils::getWindowWidth() * zoomPercent);
	image.Resize(btnWidth, btnWidth * (image.width / image.height));
	this->spriteTexture = image;

	this->i18nKey = i18nKey;

	this->buttonPosition = Vector2(RaylibUtils::getWindowWidth() * buttonPos.x - static_cast<float>(spriteTexture.width) / 2,
		RaylibUtils::getWindowHeight() * buttonPos.y - this->getButtonHeight() / 2);

	this->buttonState = buttonState::IDLE;

	this->fontSize = fontSize;
	this->textAlign = textAlign;
	this->textColor = textColor;
	this->textSpacing = textSpacing;
}

void Button::draw(const std::string& i18nPrefix)
{
	if (CheckCollisionPointRec(GetMousePosition(), raylib::Rectangle(this->buttonPosition.x, this->buttonPosition.y, this->spriteTexture.width, this->getButtonHeight())))
	{
		this->buttonState = buttonState::HOVER;
	}
	else
	{
		this->buttonState = buttonState::IDLE;
	}

	const raylib::Rectangle sourceRec(0, static_cast<float>(this->buttonState) * this->getButtonHeight(),
		static_cast<float>(this->spriteTexture.width), this->getButtonHeight());
	DrawTextureRec(this->spriteTexture, sourceRec, this->buttonPosition, WHITE);

	const std::string text = I18n::instance().get(i18nPrefix + "." + this->i18nKey);
	const raylib::Font *font = &FontProvider::instance().get(i18nPrefix + "." + this->i18nKey);

	Vector2 textPosition;
	const Vector2 textSize = MeasureTextEx(*font, text.c_str(), this->fontSize, this->textSpacing);
	const float textY = this->buttonPosition.y + (this->getButtonHeight() - textSize.y) / 2;
	switch (this->textAlign)
	{
	case textAlign::LEFT:
		textPosition = Vector2(this->buttonPosition.x, textY);
		break;

	case textAlign::CENTER:
		textPosition = Vector2(this->buttonPosition.x + (this->spriteTexture.width - textSize.x) / 2, textY);
		break;

	case textAlign::RIGHT:
		textPosition = Vector2(this->buttonPosition.x + this->spriteTexture.width - textSize.x, textY);
		break;
	}
	raylib::DrawTextEx(*font, text, textPosition, this->fontSize, this->textSpacing, this->textColor);
}
