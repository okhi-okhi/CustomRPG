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

void Screen::addButton(const Button& button)
{
	Button* ptr = button.clone();
	this->buttons.emplace_back(this->elements.size(), ptr);
	this->elements.push_back(ptr);
}

void Screen::draw() const
{
	for(const auto& element : this->elements)
	{
		element->draw();
	}
}

