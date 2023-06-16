#include "Element.h"
#include "ScreenManager.h"
#include "../Utils/RaylibUtils.h"

Element::Element(const elementTypes elementType, const raylib::Vector2 pos)
{
	this->elementType = elementType;
	this->position = RaylibUtils::getRealLength(pos);
}

void Element::updatePosition()
{
	ScreenManager::instance().updateHitbox();
}
