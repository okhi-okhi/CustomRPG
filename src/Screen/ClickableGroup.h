#pragma once
#include "Clickable.h"

class ClickableGroup : public Element
{
protected:
	std::vector<Clickable*> clickables;

public:
	void draw() override;
	ClickableGroup* clone() const override;
	void updatePosition() override;
	virtual void updateClickables();

	const std::vector<Clickable*>& getClickables() const { return this->clickables; }
};

