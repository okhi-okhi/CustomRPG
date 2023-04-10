#include "Element.h"
#include "../Utils/RaylibUtils.h"

Element::Element(const raylib::Vector2 pos)
{
	this->position = Vector2(pos.x * RaylibUtils::getWindowWidth(),
		pos.y * RaylibUtils::getWindowHeight());
}
