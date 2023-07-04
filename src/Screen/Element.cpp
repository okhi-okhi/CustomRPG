#include "Element.h"
#include "ScreenManager.h"
#include "../Utils/RaylibUtils.h"

Element::Element(const ElementType elementType, const raylib::Vector2 pos)
{
	this->elementType = elementType;
	this->position = RaylibUtils::getRealLength(pos);
}

void swap(Element& first, Element& second) noexcept
{
	using std::swap;
	swap(first.elementType, second.elementType);
	swap(first.position, second.position);
	swap(first.originPos, second.originPos);
	swap(first.hitbox, second.hitbox);
}
