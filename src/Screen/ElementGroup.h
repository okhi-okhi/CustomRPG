#pragma once
#include <memory>
#include "Element.h"

using std::shared_ptr, std::make_shared;;
class ElementGroup : public Element
{
protected:
	std::vector<shared_ptr<Element>> children;

public:
	virtual void updateChildren();

	friend void swap(ElementGroup& first, ElementGroup& second) noexcept;

	const std::vector<shared_ptr<Element>>& getChildren() const { return this->children; }
};

