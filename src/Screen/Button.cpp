#include "Button.h"
#include <iostream>
#include "../I18n/I18n.h"
#include "../I18n/FontProvider.h"
#include "../System/PathProvider.h"
#include "../Utils/RaylibUtils.h"

Button::Button(const std::string& fileName, const std::string& i18nKey, const Vector2 pos, const float zoomPercent)
{
	raylib::Image image(PathProvider::instance().getResourcesPath() + fileName);
	const int btnWidth = static_cast<int>(RaylibUtils::getWindowWidth() * zoomPercent);
	image.Resize(btnWidth, btnWidth * (image.width / image.height));
	this->spriteTexture = image;

	this->i18nKey = i18nKey;

	this->position = Vector2(RaylibUtils::getWindowWidth() * pos.x - static_cast<float>(spriteTexture.width) / 2,
		RaylibUtils::getWindowHeight() * pos.y - this->getButtonHeight() / 2);

	buttonState = buttonState::IDLE;
}

void Button::draw(const std::string& i18nPrefix) const
{
	const raylib::Rectangle sourceRec(0, static_cast<float>(this->buttonState) * this->getButtonHeight(),
		static_cast<float>(this->spriteTexture.width), this->getButtonHeight());
	DrawTextureRec(this->spriteTexture, sourceRec, this->position, WHITE);

	std::string text = I18n::instance().get(i18nPrefix + "." + this->i18nKey);
	const raylib::Font *font = &FontProvider::instance().get(i18nPrefix + "." + this->i18nKey);

	RaylibUtils::drawTextBoxed(*font,
		I18n::instance().get(i18nPrefix + "." + this->i18nKey),
		Rectangle(this->position.x, this->position.y, static_cast<float>(this->spriteTexture.width), this->getButtonHeight()), 80, 0.0f, false, BLACK);
}
