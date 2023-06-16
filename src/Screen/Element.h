#pragma once
#include <iostream>
#include <Rectangle.hpp>
#include <vector>

enum class elementTypes
{
	PICTURE = 0,
	FULL_PICTURE,
	TEXT,
	TEXT_ARG,
	BUTTON,
	BUTTON_TEXT,
	BUTTON_ARG,
	SCROLL_LIST,
	SLIDER
};

class Element
{
protected:
	elementTypes elementType;
	raylib::Vector2 position;
	raylib::Vector2 originPos;
	std::vector<raylib::Rectangle> hitbox;

public:
	Element() : elementType(elementTypes::PICTURE) {}
	explicit Element(elementTypes elementType, raylib::Vector2 pos);
	virtual ~Element() = default;

	virtual void draw() = 0;
	virtual void updatePosition();

	void setPosition(const raylib::Vector2 pos) {
		this->position = pos;
		updatePosition();
	}

	void setPositionX(const float posX) {
		this->position.x = posX;
		updatePosition();
	}

	void setPositionY(const float posY) {
		this->position.y = posY;
		updatePosition();
	}

	void addPosition(const raylib::Vector2 pos) {
		this->position += pos;
		updatePosition();
	}

	const elementTypes& getElementType() const { return this->elementType; }
	const raylib::Vector2& getPosition() const { return this->position; }
	const raylib::Vector2& getOriginPos() const { return this->originPos; }
	const std::vector<raylib::Rectangle>& getHitbox() const { return this->hitbox; }
};

