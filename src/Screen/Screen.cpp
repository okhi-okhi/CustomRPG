#include "Screen.h"
#include "../System/PathProvider.h"
#include "../Utils/RaylibUtils.h"

Screen::Screen(const screenTypes screenType, const std::string& i18nKey)
{
	this->screenType = screenType;
	this->i18nKey = "screen." + i18nKey;
}

void Screen::addElement(const Element& element)
{
	this->elements.push_back(element.clone());
}

void Screen::addClickable(const Clickable& clickable)
{
	Clickable* ptr = clickable.clone();
	this->clickableElements.emplace_back(static_cast<int>(this->elements.size()), ptr);
	this->elements.push_back(ptr);
}

void Screen::draw() const
{
	for(const auto& element : this->elements)
	{
		element->draw();
	}
}

