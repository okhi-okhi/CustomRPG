#include "Screen.h"
#include <algorithm>
#include <iostream>
#include "ScreenManager.h"
#include "../System/PathProvider.h"
#include "../Utils/RaylibUtils.h"

Screen::Screen(const ScreenType screenType, const string& i18nKey)
{
	this->screenType = screenType;
	this->i18nKey = "screen." + i18nKey;
}

void Screen::addElement(const shared_ptr<Element>& element)
{
	int max = 0;
	for (const auto& displayElement : this->elements)
	{
		if (displayElement.order > max)
		{
			max = displayElement.order;
		}
	}
	this->elements.emplace_back(max + 1, element);
}

void Screen::removeElement(const shared_ptr<Element>& element)
{
	for (int i = 0; i < this->elements.size(); i++)
	{
		if (this->elements[i].element == element)
		{
			this->elements.erase(this->elements.begin() + i);
			return;
		}
	}
}

void Screen::setOrder(const shared_ptr<Element>& element, const int order)
{
	for (auto& displayElement : this->elements)
	{
		if (displayElement.element == element)
		{
			displayElement.order = order;
			sortElements();
			return;
		}
	}
}

void Screen::sortElements()
{
	std::ranges::sort(this->elements, [](const DisplayElement& a, const DisplayElement& b) -> bool
	{
		return a.order < b.order;
	});
}

void Screen::draw() const
{
	for (const auto& displayElement : this->elements)
	{
		if(!displayElement.element->isHidden())
		{
			displayElement.element->draw();
		}
	}
}

void Screen::update() const
{
	for (int i = static_cast<int>(this->elements.size()) - 1; i >= 0; i--)
	{
		if (!this->elements[i].element->isHidden())
		{
			this->elements[i].element->update();
		}
	}
}

