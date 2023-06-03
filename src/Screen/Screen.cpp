#include "Screen.h"

#include <iostream>

#include "../System/PathProvider.h"
#include "../Utils/RaylibUtils.h"

Screen::Screen(const screenTypes screenType, const std::string& i18nKey)
{
	this->screenType = screenType;
	this->i18nKey = "screen." + i18nKey;
}

void Screen::addElement(Element* element)
{
	this->elements.push_back(element);
}

void Screen::addElement(Clickable* clickable)
{
	this->elements.push_back(clickable);
	this->clickableElements.emplace_back(static_cast<int>(this->elements.size()) - 1, clickable);
}

void Screen::addElement(ClickableGroup* clickableGroup)
{
	this->elements.push_back(clickableGroup);
	for(const auto& clickable : clickableGroup->getClickables())
	{
		this->elements.push_back(clickable);
		this->clickableElements.emplace_back(static_cast<int>(this->elements.size()) - 1, clickable);
	}
}

void Screen::draw() const
{
	for(const auto& element : this->elements)
	{
		element->draw();
	}
}

