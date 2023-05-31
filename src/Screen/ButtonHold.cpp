#include "ButtonHold.h"

#include <iostream>

#include "../Utils/RaylibUtils.h"

void ButtonHold::draw()
{
	update();
	this->texture.draw();
}

ButtonHold* ButtonHold::clone() const
{
	return new ButtonHold(*this);
}

void ButtonHold::update()
{
	using RaylibUtils::checkCollisionPointRecs;
	std::cout << "b";
	if (checkCollisionPointRecs(GetMousePosition(), this->hitbox))
	{
		std::cout << "c";
		if (checkCollisionPointRecs(GetMousePosition(), this->reserveRec))
		{
			std::cout << "d";
			if (this->texture.getCurrentFrame() == static_cast<int>(buttonState::HOVER))
			{
				this->texture.setCurrentFrame(static_cast<int>(buttonState::IDLE));
			}
			return;
		}

		this->texture.setCurrentFrame(static_cast<int>(buttonState::HOVER));
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			this->clickFun();
		}
	}
	else if (this->texture.getCurrentFrame() == static_cast<int>(buttonState::HOVER))
	{
		this->texture.setCurrentFrame(static_cast<int>(buttonState::IDLE));
	}
}
