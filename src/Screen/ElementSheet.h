#pragma once
#include <memory>
#include "Element.h"

using std::shared_ptr;

class ElementSheet final : public Element
{
private:
	raylib::Rectangle bounds;
	int row;
	int column;
	int spacing;
	int startIndex;
	int currentIndex;
	std::vector<std::shared_ptr<Element>> elements;

public:
	ElementSheet() : row(0), column(0), spacing(0), startIndex(0), currentIndex(0){}
	ElementSheet(raylib::Rectangle bounds, int row, int column, int spacing,
	             int currentIndex, const vector<shared_ptr<Element>>& elements);

	void draw() override;
	void update() override;
	void updatePosition() override;

	void setCurrentIndex(const int currentIndex)
	{
		this->currentIndex = currentIndex;
		this->updatePosition();
	}

	const raylib::Rectangle& getBounds() const { return this->bounds; }
	const int& getRow() const { return this->row; }
	const int& getColumn() const { return this->column; }
	const int& getSpacing() const { return this->spacing; }
	const int& getStartIndex() const { return this->startIndex; }
	const int& getCurrentIndex() const { return this->currentIndex; }
	const std::vector<std::shared_ptr<Element>>& getElements() const { return this->elements; }
};
