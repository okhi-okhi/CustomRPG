#include "Element.h"
#include "ScreenManager.h"
#include "../Utils/RaylibUtils.h"

Element::Element(const ElementType elementType, const raylib::Vector2 pos)
{
	this->elementType = elementType;
	this->position = RaylibUtils::getRealLength(pos);
	this->canBlock = true;
}

void Element::update()
{
	using RaylibUtils::checkCollisionPointRecs;
	if (this->canBlock && checkCollisionPointRecs(GetMousePosition(), this->hitbox))
	{
		ScreenManager::instance().setClicked(true);
	}
}

void swap(Element& first, Element& second) noexcept
{
	using std::swap;
	swap(first.elementType, second.elementType);
	swap(first.position, second.position);
	swap(first.originPos, second.originPos);
	swap(first.hitbox, second.hitbox);
	swap(first.hidden, second.hidden);
	swap(first.canBlock, second.canBlock);
}
