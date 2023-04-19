#pragma once
#include <Rectangle.hpp>

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
	raylib::Rectangle hitbox;

public:
	Element() : elementType(elementTypes::PICTURE) {}
	explicit Element(elementTypes elementType, raylib::Vector2 pos);
	virtual ~Element() = default;

	virtual void draw() = 0;
	virtual Element* clone() const = 0;

	const elementTypes& getElementType() const { return this->elementType; }
	raylib::Vector2 getPosition() const { return Vector2(this->hitbox.x, hitbox.y); }
	const raylib::Rectangle& getHitbox() const { return this->hitbox; }
};

