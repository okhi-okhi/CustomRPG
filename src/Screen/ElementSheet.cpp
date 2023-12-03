#include "ElementSheet.h"
#include "../Utils/RaylibUtils.h"

ElementSheet::ElementSheet(raylib::Rectangle bounds, const int row, const int column,
                           const int spacing, const int currentIndex, const vector<shared_ptr<Element>>& elements) :
	Element(ElementType::ELEMENT_SHEET, bounds.GetPosition())
{
	using RaylibUtils::getRealLength;

	this->bounds = getRealLength(raylib::Rectangle(bounds.x - bounds.width / 2,
		bounds.y - bounds.height / 2, bounds.width, bounds.height));
	this->row = row;
	this->column = column;
	this->spacing = spacing;
	this->startIndex = 0;
	this->currentIndex = currentIndex;
	this->elements = elements;

	ElementSheet::updatePosition();
}

void ElementSheet::draw()
{
	const int drawNum = this->row * this->column;

	for(int i = 0; i < drawNum; i++)
	{
		const int index = this->startIndex + i;
		if (index < this->elements.size())
		{
			this->elements[index]->draw();
		}
	}
}

void ElementSheet::update()
{
	for (const auto& element : this->elements)
	{
		element->update();
	}
}

void ElementSheet::updatePosition()
{
	const int gridWidth = static_cast<int>((this->bounds.width - (this->column - 1) * this->spacing) / this->column);
	const int gridHeight = static_cast<int>((this->bounds.height - (this->row - 1) * this->spacing) / this->row);
	float elementX;
	float elementY = this->bounds.y + static_cast<float>(gridHeight) / 2;
	for (int y = 0; y < this->row; y++)
	{
		elementX = this->bounds.x + static_cast<float>(gridWidth) /2;
		for (int x = 0; x < this->column; x++)
		{
			const int index = this->startIndex + y * this->column + x;
			if (index < this->elements.size())
			{
				this->elements[index]->setPosition(raylib::Vector2(elementX, elementY));
				elementX += gridWidth + this->spacing;
			}
		}
		elementY += gridHeight + this->spacing;
	}
}
