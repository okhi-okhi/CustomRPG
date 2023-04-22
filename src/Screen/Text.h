#pragma once
#include <Color.hpp>
#include <Font.hpp>
#include <map>
#include "Element.h"

enum class textAlign
{
	LEFT = 0,
	CENTER,
	RIGHT
};

class Text : public Element
{
protected:
	std::string text;

	float fontSize;
	textAlign align;
	raylib::Color color;
	float spacing;

	const raylib::Font* font;

public:
	Text() : fontSize(0), align(), spacing(0), font(nullptr) {}
	explicit Text(const std::string& i18nKey, raylib::Vector2 pos, float fontSize = 0.03f,
		textAlign align = textAlign::LEFT, raylib::Color color = BLACK, float spacing = 1.0f);

	void draw() override;
	Text* clone() const override;

	void setPosition(const raylib::Vector2 pos) { this->hitbox.x = pos.x; this->hitbox.y = pos.y; }

	const std::string& getText() const { return this->text; }
	const float& getFontSize() const { return this->fontSize; }
	const textAlign& getAlign() const { return this->align; }
	const raylib::Color& getColor() const { return this->color; }
	const float& getSpacing() const { return this->spacing; }
};

