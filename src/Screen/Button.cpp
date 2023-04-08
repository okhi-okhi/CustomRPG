#include "Button.h"
#include "../I18n/I18n.h"
#include "../I18n/FontProvider.h"
#include "../System/PathProvider.h"
#include "../Utils/RaylibUtils.h"

Button::Button(const Picture& texture, const std::string& i18nKey, const float fontSize,
			   const textAlign textAlign, const raylib::Color textColor, const float textSpacing)
{
	this->texture = texture;

	Vector2 textPos;
	const float textY = this->texture.getPosition().y + this->getButtonHeight() / 2;
	switch (textAlign)
	{
	case textAlign::LEFT:
		textPos = Vector2(this->texture.getPosition().x, textY);
		break;

	case textAlign::CENTER:
		textPos = Vector2(this->texture.getPosition().x + static_cast<float>(this->texture.getSpriteTexture().width) / 2, textY);
		break;

	case textAlign::RIGHT:
		textPos = Vector2(this->texture.getPosition().x + this->texture.getSpriteTexture().width, textY);
		break;
	}
	textPos = Vector2(textPos.x/RaylibUtils::getWindowWidth(), textPos.y/RaylibUtils::getWindowHeight());

	this->text = Text(i18nKey, textPos, fontSize, textAlign, textColor, textSpacing);
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
	this->text.draw();
}
