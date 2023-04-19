#include "Element.h"
#include "../Utils/RaylibUtils.h"

Element::Element(const elementTypes elementType, const raylib::Vector2 pos)
{
	this->elementType = elementType;
	this->hitbox = Rectangle(pos.x * RaylibUtils::getWindowWidth(),
		pos.y * RaylibUtils::getWindowHeight(), 0, 0);
}
