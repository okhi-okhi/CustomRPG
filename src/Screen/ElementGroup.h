#pragma once
#include <memory>
#include "Element.h"

using std::shared_ptr;
class ElementGroup : public Element
{
protected:
	std::vector<shared_ptr<Element>> children;

public:
	void updatePosition() override;
	virtual void updateChildren();

	const std::vector<shared_ptr<Element>>& getChildren() const { return this->children; }
};

