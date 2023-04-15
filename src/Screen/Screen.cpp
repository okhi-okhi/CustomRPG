#include "Screen.h"

#include <iostream>

#include "../System/PathProvider.h"
#include "../Utils/RaylibUtils.h"

Screen::Screen(const std::string& i18nKey)
{
	this->i18nKey = "screen." + i18nKey;
}

void Screen::addElement(const Element& element)
{
	this->elements.push_back(element.clone());
}

void Screen::draw() const
{
	for(const auto& element : this->elements)
	{
		element->draw();
	}
}

