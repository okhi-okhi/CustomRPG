#pragma once
#include <Vector2.hpp>

class Element
{
protected:
	raylib::Vector2 position;

public:
	Element() = default;
	explicit Element(raylib::Vector2 pos);
	virtual ~Element() = default;

	virtual void draw() = 0;
	virtual Element* clone() const = 0;

	const raylib::Vector2& getPosition() const { return this->position; }
};

