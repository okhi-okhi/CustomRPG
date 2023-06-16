#pragma once
#include <vector>
#include "Element.h"

class Clickable : public Element
{
protected:
	std::vector<raylib::Rectangle> reserveRec{};

public:
	void draw() override;
	void updatePosition() override;
};

