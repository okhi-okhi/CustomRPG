#include "ButtonHold.h"
#include "ScreenManager.h"
#include "../Utils/RaylibUtils.h"

void ButtonHold::update()
{
	using RaylibUtils::checkCollisionPointRecs;
	if (checkCollisionPointRecs(GetMousePosition(), this->hitbox) && !ScreenManager::instance().isClicked())
	{
		this->texture.setCurrentFrame(static_cast<int>(ButtonState::HOVER));
		ScreenManager::instance().setClicked(true);
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
