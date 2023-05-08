#include "Element.h"
#include "../Utils/RaylibUtils.h"

Element::Element(const elementTypes elementType, const raylib::Vector2 pos)
{
	this->elementType = elementType;
	this->hitbox = Rectangle(RaylibUtils::getRealLength(pos.x),
		RaylibUtils::getRealLength(pos.y), 0, 0);
}
