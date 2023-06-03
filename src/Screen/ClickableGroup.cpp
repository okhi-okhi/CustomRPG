#include "ClickableGroup.h"

void ClickableGroup::draw()
{
}

ClickableGroup* ClickableGroup::clone() const
{
	return new ClickableGroup(*this);
}

void ClickableGroup::updatePosition()
{
	for (const auto& clickable : this->clickables)
	{
		clickable->updatePosition();
	}
}