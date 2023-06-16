#include "ElementGroup.h"

void ElementGroup::updatePosition()
{
	for (const auto& child : this->children)
	{
		child->updatePosition();
	}
}

void ElementGroup::updateChildren()
{
	this->children.clear();
}
