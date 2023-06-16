#include "Screen.h"

#include <iostream>

#include "../System/PathProvider.h"
#include "../Utils/RaylibUtils.h"

Screen::Screen(const screenTypes screenType, const std::string& i18nKey)
{
	this->screenType = screenType;
	this->i18nKey = "screen." + i18nKey;
}

void Screen::addElement(const shared_ptr<Element>& element)
{
	this->elements.push_back(element);
}

void Screen::addButton(const shared_ptr<Button>& button)
{
	this->elements.push_back(button);
	this->buttons.emplace_back(static_cast<int>(this->elements.size()) - 1, button);
}

void Screen::addElementGroup(const shared_ptr<ElementGroup>& elementGroup)
{
	this->elements.push_back(elementGroup);
	for(const auto& child : elementGroup->getChildren())
	{
		this->elements.push_back(child);
		if (child->getElementType() == elementTypes::BUTTON)
		{
			this->buttons.emplace_back(static_cast<int>(this->elements.size()) - 1, dynamic_pointer_cast<Button>(child));
		}
	}
}

void Screen::draw() const
{
	for(const auto& element : this->elements)
	{
		element->draw();
	}
}

