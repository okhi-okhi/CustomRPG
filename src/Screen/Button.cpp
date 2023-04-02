#include "Button.h"
#include "../System/PathProvider.h"
#include "../Utils/RaylibUtils.h"

#define BUTTON_STATE_NUMS 2

Button::Button(const std::string& fileName, const std::string& i18nKey, const Vector2 pos, const float zoomPercent)
{
	raylib::Image image(PathProvider::instance().getResourcesPath() + fileName);
	const int btnWidth = RaylibUtils::getWindowWidth() * zoomPercent;
	image.Resize(btnWidth, btnWidth * (image.width / image.height));
	this->spriteTexture = image;

	this->i18nKey = i18nKey;

	const float buttonHeight = static_cast<float>(this->spriteTexture.height) / BUTTON_STATE_NUMS;
	this->pos = Vector2(RaylibUtils::getWindowWidth() * pos.x - spriteTexture.width / 2,
		RaylibUtils::getWindowHeight() * pos.y - buttonHeight / 2);

	buttonState = buttonState::IDLE;
}

void Button::draw() const
{
	const float buttonHeight = static_cast<float>(this->spriteTexture.height) / BUTTON_STATE_NUMS;
	const raylib::Rectangle sourceRec(0, static_cast<float>(this->buttonState) * buttonHeight,
		spriteTexture.width, buttonHeight);
	DrawTextureRec(this->spriteTexture, sourceRec, this->pos, WHITE);
}
