#include "Screen.h"
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
	if (element->getId() != "Invalid")
	{
		for (const auto& currentElement : this->elements)
		{
			if (element->getId() == currentElement->getId())
			{
				std::cout << "Element with id: " << element->getId() << " already exists" << std::endl;
				return;
			}
		}
	}
	this->elements.push_back(element);
}

void Screen::removeElement(const std::string& id)
{
	if (id == "Invalid")
	{
		std::cout << "Elements with no id set cannot be operated on" << std::endl;
		return;
	}
	for (int i = 0; i < this->elements.size(); i++)
	{
		if (this->elements[i]->getId() == id)
		{
			this->elements.erase(this->elements.begin() + i);
			return;
		}
	}
	std::cout << "Element with id: " << id << " not found" << std::endl;
}

void Screen::showElement(const std::string& id) const
{
	if (id == "Invalid")
	{
		std::cout << "Elements with no id set cannot be operated on" << std::endl;
		return;
	}
	for (const auto& element : this->elements)
	{
		if (element->getId() == id)
		{
			element->setHide(false);
			return;
		}
	}
	std::cout << "Element with id: " << id << " not found" << std::endl;
}

void Screen::hiddenElement(const std::string& id) const
{
	if (id == "Invalid") 
	{
		std::cout << "Elements with no id set cannot be operated on" << std::endl;
		return;
	}
	for (const auto& element : this->elements)
	{
		if (element->getId() == id)
		{
			element->setHide(true);
			return;
		}
	}
	std::cout << "Element with id: " << id << " not found" << std::endl;
}

void Screen::draw() const
{
	for (const auto& element : this->elements)
	{
		if(!element->isHidden())
		{
			element->draw();
		}
	}
}

void Screen::update() const
{
	for (int i = static_cast<int>(this->elements.size()) - 1; i >= 0; i--)
	{
		if (!this->elements[i]->isHidden())
		{
			this->elements[i]->update();
		}
	}
}

