#include "Button.h"
#include <iostream>
#include "ScreenManager.h"
#include "../Utils/RaylibUtils.h"	

Button::Button(const raylib::Vector2 pos, const Picture& texture,
	const std::function<void()>& function, const std::string& clickSound) : Element(ElementType::BUTTON, pos)
{
	this->texture = texture;
	this->texture.setPosition(this->position);
	this->function = function;
	if(clickSound != "none")
	{
		this->clickSound = LoadSound(PathProvider::get(FileSource::AUTO, ResourcesFolder::SOUNDS, clickSound).c_str());
	}
	else
	{
		this->clickSound = Sound();
	}

	this->hitbox.emplace_back(this->texture.getOriginPos().x, this->texture.getOriginPos().y, static_cast<float>(this->texture.getSpriteTexture().width), this->texture.getHeight());
	this->originPos = this->texture.getOriginPos();
}

Button::Button(const Picture& texture, const std::function<void()>& function, const std::string& clickSound) :
	Button(Vector2(0, 0), texture, function, clickSound)
{
}

void Button::draw()
{
	this->texture.draw();
	std::cout<< this->texture.getCurrentFrame() << std::endl;
}

void Button::update()
{
	using RaylibUtils::checkCollisionPointRecs;
	if (checkCollisionPointRecs(GetMousePosition(), this->hitbox) && !ScreenManager::instance().isClicked())
	{
		this->texture.setCurrentFrame(static_cast<int>(ButtonState::HOVER));
		ScreenManager::instance().setClicked(true);
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			PlaySound(this->clickSound);
			this->function();
		}
	}
	else if (this->texture.getCurrentFrame() == static_cast<int>(ButtonState::HOVER))
	{
		this->texture.setCurrentFrame(static_cast<int>(ButtonState::IDLE));
	}
}

void Button::updatePosition()
{
	this->texture.setPosition(this->position);
	this->originPos = this->texture.getOriginPos();
	this->hitbox.clear();
	this->hitbox.emplace_back(this->texture.getOriginPos().x, this->texture.getOriginPos().y, static_cast<float>(this->texture.getSpriteTexture().width), this->texture.getHeight());
}
