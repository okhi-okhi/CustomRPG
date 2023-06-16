#include "Clickable.h"
#include "ScreenManager.h"

void Clickable::draw()
{
}

void Clickable::updatePosition()
{
	ScreenManager::instance().updateHitbox();
}
