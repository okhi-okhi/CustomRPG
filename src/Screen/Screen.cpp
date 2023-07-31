#include "Screen.h"

#include <iostream>

#include "ScreenManager.h"
#include "../System/PathProvider.h"
#include "../Utils/RaylibUtils.h"

Screen::Screen(const ScreenType screenType, const std::string& i18nKey)
{
	this->screenType = screenType;
	this->i18nKey = "screen." + i18nKey;
}

void Screen::addElement(const std::shared_ptr<Element>& element)
{
	this->elements.push_back(element);
}

void Screen::draw() const
{
	for (const auto& element : this->elements)
	{
		element->draw();
	}
}

void Screen::update() const
{
	for (int i = static_cast<int>(this->elements.size()) - 1; i >= 0; i--)
	{
		this->elements[i]->update();
	}
}

