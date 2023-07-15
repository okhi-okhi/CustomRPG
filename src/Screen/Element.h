#pragma once
#include <iostream>
#include <Rectangle.hpp>
#include <vector>

enum class ElementType
{
	PICTURE = 0,
	FULL_PICTURE,
	PICTURE_TILED,
	PICTURE_GALLERY,
	TEXT,
	TEXT_ARG,
	TEXT_BOX,
	TEXT_ARG_BOX,
	BUTTON,
	BUTTON_TEXT,
	SCROLL_LIST,
	SLIDER,
	SLIDER_TEXT
};

class Element
{
protected:
	ElementType elementType;
	raylib::Vector2 position;
	raylib::Vector2 originPos;
	std::vector<raylib::Rectangle> hitbox;

public:
	Element() : elementType(ElementType::PICTURE) {}
	explicit Element(ElementType elementType, raylib::Vector2 pos);
	Element(const Element& other) = default;
	Element(Element&& other) noexcept : Element() { swap(*this, other); }
	virtual ~Element() = default;

	Element& operator=(const Element& other) = default;
	Element& operator=(Element&& other) = default;
	friend void swap(Element& first, Element& second) noexcept;

	virtual void draw() = 0;
	virtual void updatePosition() = 0;

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

	const ElementType& getElementType() const { return this->elementType; }
	const raylib::Vector2& getPosition() const { return this->position; }
	const raylib::Vector2& getOriginPos() const { return this->originPos; }
	const std::vector<raylib::Rectangle>& getHitbox() const { return this->hitbox; }
};

