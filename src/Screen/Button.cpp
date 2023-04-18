#include "Button.h"
#include "../I18n/I18n.h"
#include "../I18n/FontProvider.h"
#include "../System/PathProvider.h"
#include "../Utils/RaylibUtils.h"

Button::Button(const std::string& fileName, const Vector2 position, const float zoomPercent,
	const std::string& i18nKey, const float fontSize, const textAlign textAlign,
	const raylib::Color textColor, const float textSpacing, const std::function<void()>& function)
{
	this->elementType = elementTypes::BUTTON;
	this->texture = Picture(fileName, position, 2, zoomPercent);
	this->text = Text(i18nKey, this->getTextPos(textAlign), fontSize, textAlign, textColor, textSpacing);
	this->clickFun = function;
}

void Button::draw()
{
	update();
	this->texture.draw();
	this->text.draw();
}

Button* Button::clone() const
{
	return new Button(*this);
}

void Button::update()
{
	if (CheckCollisionPointRec(GetMousePosition(), raylib::Rectangle(this->texture.getPosition().x, this->texture.getPosition().y, static_cast<float>(this->texture.getSpriteTexture().width), this->getButtonHeight())))
	{
		this->texture.setCurrentFrame(static_cast<int>(buttonState::HOVER));
		if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			this->clickFun();
		}
	}
	else if (this->texture.getCurrentFrame() == static_cast<int>(buttonState::HOVER))
	{
		this->texture.setCurrentFrame(static_cast<int>(buttonState::IDLE));
	}
}

Vector2 Button::getTextPos(const textAlign textAlign) const
{
	Vector2 textPos(0.0f, 0.0f);
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
	textPos = Vector2(textPos.x / RaylibUtils::getWindowWidth(), textPos.y / RaylibUtils::getWindowHeight());

	return textPos;
}
