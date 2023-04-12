#pragma once
#include <Vector2.hpp>

enum class elementTypes
{
	PICTURE = 0,
	FULL_PICTURE,
	TEXT,
	TEXT_ARG,
	BUTTON,
	BUTTON_ARG
};

class Element
{
protected:
	elementTypes elementType;
	raylib::Vector2 position;

public:
	Element() : elementType(elementTypes::PICTURE) {}
	explicit Element(elementTypes elementType, raylib::Vector2 pos);
	virtual ~Element() = default;

	virtual void draw() = 0;
	virtual Element* clone() const = 0;

	const elementTypes& getElementType() const { return this->elementType; }
	const raylib::Vector2& getPosition() const { return this->position; }
};

