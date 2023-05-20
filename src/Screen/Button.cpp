#include "Button.h"
#include "ScreenManager.h"
#include "../I18n/I18n.h"
#include "../I18n/FontProvider.h"
#include "../System/PathProvider.h"
#include "../Utils/RaylibUtils.h"

Button::Button(const std::string& fileName, const Vector2 position, const int width,
	const std::function<void()>& function, const std::string& clickSound)
{
	this->elementType = elementTypes::BUTTON;
	this->texture = Picture(fileName, position, 2, width);
	this->clickFun = function;
	this->hitbox = this->texture.getHitbox();
	this->clickSound = LoadSound(PathProvider::instance().get(resourcesFolder::SOUNDS, clickSound).c_str());
}

Button::Button(const std::string& tileImage, const Vector2 position, const int tileWidth, const Vector2 tiledBounds,
	const std::function<void()>& function, const std::string& clickSound)
{
	this->elementType = elementTypes::BUTTON;
	this->texture = Picture(tileImage, position, 2, tileWidth, tiledBounds);
	this->clickFun = function;
	this->hitbox = this->texture.getHitbox();
	this->clickSound = LoadSound(PathProvider::instance().get(resourcesFolder::SOUNDS, clickSound).c_str());
}

void Button::draw()
{
	update();
	this->texture.draw();
}

Button* Button::clone() const
{
	return new Button(*this);
}

void Button::update()
{
	using RaylibUtils::checkCollisionPointRecs;
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
			this->clickFun();
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
