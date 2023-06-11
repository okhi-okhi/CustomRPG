#include "Button.h"

#include <iostream>

#include "ScreenManager.h"
#include "../I18n/I18n.h"
#include "../I18n/FontProvider.h"
#include "../System/PathProvider.h"
#include "../Utils/RaylibUtils.h"

Button::Button(const Vector2 position, const Picture& texture,
	const std::function<void()>& function, const std::string& clickSound)
{
	this->elementType = elementTypes::BUTTON;
	this->position = RaylibUtils::getRealLength(position);
	this->texture = texture;
	this->texture.setPosition(this->position);
	this->function = function;
	this->clickSound = LoadSound(PathProvider::instance().get(resourcesFolder::SOUNDS, clickSound).c_str());
	this->lockState = false;

	this->hitbox = this->texture.getHitbox();
	this->originPos = this->texture.getOriginPos();
}

void Button::draw()
{
	this->texture.draw();
	if (!this->lockState)
	{
		update();
	}
}

void Button::updatePosition()
{
	this->texture.setPosition(this->position);
	this->originPos = this->texture.getOriginPos();
	this->hitbox = this->texture.getHitbox();
	Clickable::updatePosition();
}

void Button::update()
{
	using RaylibUtils::checkCollisionPointRecs, std::cout;
	if (checkCollisionPointRecs(GetMousePosition(), this->hitbox))
	{
		if(checkCollisionPointRecs(GetMousePosition(), this->reserveRec))
		{
			if (this->texture.getCurrentFrame() == static_cast<int>(buttonState::HOVER))
			{
				this->texture.setCurrentFrame(static_cast<int>(buttonState::IDLE));
			}
			return;
		}
		this->texture.setCurrentFrame(static_cast<int>(buttonState::HOVER));
		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			PlaySound(this->clickSound);
			this->function();
		}
	}
	else if (this->texture.getCurrentFrame() == static_cast<int>(buttonState::HOVER))
	{
		this->texture.setCurrentFrame(static_cast<int>(buttonState::IDLE));
	}
}


// Vector2 Button::getTextPos(const textAlign textAlign) const
// {
// 	Vector2 textPos(0.0f, 0.0f);
// 	const float textY = this->texture.getPosition().y + this->getButtonHeight() / 2;
// 	switch (textAlign)
// 	{
// 	case textAlign::LEFT:
// 		textPos = Vector2(this->texture.getPosition().x, textY);
// 		break;
//
// 	case textAlign::CENTER:
// 		textPos = Vector2(this->texture.getPosition().x + static_cast<float>(this->texture.getSpriteTexture().width) / 2, textY);
// 		break;
//
// 	case textAlign::RIGHT:
// 		textPos = Vector2(this->texture.getPosition().x + this->texture.getSpriteTexture().width, textY);
// 		break;
// 	}
//
// 	return textPos;
// }
