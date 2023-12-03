#pragma once
#include <memory>
#include "Element.h"

class ElementGroup final : public Element
{
private:
	raylib::Vector2 oldPosition;
	vector<std::shared_ptr<Element>> elements;
public:
	ElementGroup() : Element(ElementType::ELEMENT_GROUP, 0) {}
	explicit ElementGroup(const std::vector<std::shared_ptr<Element>>& elements);

	void draw() override;
	void update() override;
	void updatePosition() override;

	void addElement(const std::shared_ptr<Element>& element);
};

