#include "ElementGroup.h"
#include "ScreenManager.h"

void ElementGroup::updateChildren()
{
	this->children.clear();
}

void swap(ElementGroup& first, ElementGroup& second) noexcept
{
	using std::swap;
	swap(static_cast<Element&>(first), static_cast<Element&>(second));
	swap(first.children, second.children);
}
