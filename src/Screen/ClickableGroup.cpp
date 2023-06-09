#include "ClickableGroup.h"

void ClickableGroup::draw()
{
}

void ClickableGroup::updatePosition()
{
	for (const auto& clickable : this->clickables)
	{
		clickable->updatePosition();
	}
}

void ClickableGroup::updateClickables()
{
	this->clickables.clear();
}
