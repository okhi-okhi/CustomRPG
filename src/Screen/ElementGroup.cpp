#include "ElementGroup.h"

#include <iostream>

ElementGroup::ElementGroup(const std::vector<std::shared_ptr<Element>>& elements) : Element(ElementType::ELEMENT_GROUP, 0)
{
	this->elements = elements;
	this->oldPosition = this->position;
}

void ElementGroup::draw()
{
	for (const auto& element : this->elements)
	{
		element->draw();
	}
}

void ElementGroup::update()
{
	for (const auto& element : this->elements)
	{
		element->update();
	}
}

void ElementGroup::updatePosition()
{
	for (const auto& element : this->elements)
	{
		element->setPosition(element->getPosition() - this->oldPosition + this->position);
	}
	this->oldPosition = this->position;
}

void ElementGroup::addElement(const std::shared_ptr<Element>& element)
{
	element->addPosition(this->position);
	this->elements.push_back(element);
}
