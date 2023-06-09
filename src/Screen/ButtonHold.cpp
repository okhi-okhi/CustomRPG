#include "ButtonHold.h"

#include <iostream>

#include "../Utils/RaylibUtils.h"

void ButtonHold::draw()
{
	update();
	this->texture.draw();
}

void ButtonHold::update()
{
	using RaylibUtils::checkCollisionPointRecs;
	if (checkCollisionPointRecs(GetMousePosition(), this->hitbox))
	{
		if (checkCollisionPointRecs(GetMousePosition(), this->reserveRec))
		{
			if (this->texture.getCurrentFrame() == static_cast<int>(buttonState::HOVER))
			{
				this->texture.setCurrentFrame(static_cast<int>(buttonState::IDLE));
			}
			return;
		}

		this->texture.setCurrentFrame(static_cast<int>(buttonState::HOVER));
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			this->function();
		}
	}
	else if (this->texture.getCurrentFrame() == static_cast<int>(buttonState::HOVER))
	{
		this->texture.setCurrentFrame(static_cast<int>(buttonState::IDLE));
	}
}
