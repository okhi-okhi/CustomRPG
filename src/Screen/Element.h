#pragma once
#include <memory>
#include <Rectangle.hpp>
#include <string>
#include <vector>

using std::string, std::vector;

enum class ElementType
{
	PICTURE = 0,
	FULL_PICTURE,
	PICTURE_TILED,
	PICTURE_GALLERY,
	PICTURE_BORDER,
	TEXT,
	TEXT_ARG,
	TEXT_BOX,
	TEXT_ARG_BOX,
	BUTTON,
	BUTTON_TEXT,
	SCROLL_LIST,
	SLIDER,
	SLIDER_TEXT,
	ELEMENT_GROUP,
	ELEMENT_SHEET
};

class Element
{
protected:
	ElementType elementType;
	raylib::Vector2 position;
	raylib::Vector2 originPos;
	vector<raylib::Rectangle> hitbox;
	bool hidden = false;
	bool canBlock;

public:
	Element() : elementType(ElementType::PICTURE), canBlock(false) {}
	explicit Element(ElementType elementType, raylib::Vector2 pos);
	Element(const Element& other) = default;
	Element(Element&& other) noexcept : Element() { swap(*this, other); }
	virtual ~Element() = default;

	Element& operator=(const Element& other) = default;
	Element& operator=(Element&& other) = default;
	friend void swap(Element& first, Element& second) noexcept;

	virtual void draw() = 0;
	virtual void update();
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
	void setHide(const bool hide) { this->hidden = hide; }
	void setCanBlock(const bool canBlock) { this->canBlock = canBlock; }

	void addPosition(const raylib::Vector2 pos) {
		this->position += pos;
		updatePosition();
	}

	const ElementType& getElementType() const { return this->elementType; }
	const raylib::Vector2& getPosition() const { return this->position; }
	const raylib::Vector2& getOriginPos() const { return this->originPos; }
	const std::vector<raylib::Rectangle>& getHitbox() const { return this->hitbox; }
	const bool& isHidden() const { return this->hidden; }
};

template <typename T>
class ElementBuilder
{
protected:
	raylib::Vector2 position = raylib::Vector2(0, 0);
	bool hidden = false;
	bool canBlock = true;

public:
	ElementBuilder() = default;
	virtual ~ElementBuilder() = default;

	T& setPosition(const raylib::Vector2 pos) { this->position = pos; return static_cast<T&>(*this); }
	T& setHide(const bool hide) { this->hidden = hide; return static_cast<T&>(*this); }
	T& setCanBlock(const bool canBlock) { this->canBlock = canBlock; return static_cast<T&>(*this); }

	virtual std::shared_ptr<Element> build() const = 0;
};