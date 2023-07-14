#include "ButtonHold.h"
#include "../Utils/RaylibUtils.h"

void ButtonHold::update()
{
	using RaylibUtils::checkCollisionPointRecs;
	if (checkCollisionPointRecs(GetMousePosition(), this->hitbox))
	{
		if (checkCollisionPointRecs(GetMousePosition(), this->reserveRec))
		{
			if (this->texture.getCurrentFrame() == static_cast<int>(ButtonState::HOVER))
			{
				this->texture.setCurrentFrame(static_cast<int>(ButtonState::IDLE));
			}
			return;
		}

		this->texture.setCurrentFrame(static_cast<int>(ButtonState::HOVER));
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			this->function();
		}
	}
	else if (this->texture.getCurrentFrame() == static_cast<int>(ButtonState::HOVER))
	{
		this->texture.setCurrentFrame(static_cast<int>(ButtonState::IDLE));
	}
}
