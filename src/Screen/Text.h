#pragma once
#include <Color.hpp>
#include <Font.hpp>
#include <map>

enum class textAlign
{
	LEFT = 0,
	CENTER,
	RIGHT
};

class Text
{
protected:
	std::string text;
	Vector2 position;

	float fontSize;
	raylib::Color color;
	float spacing;

	const raylib::Font* font;

public:
	Text() = default;
	explicit Text(const std::string& i18nKey, Vector2 pos, float fontSize = 0.03f,
		textAlign align = textAlign::LEFT, raylib::Color color = BLACK, float spacing = 1.0f);
	virtual ~Text() = default;

	virtual void draw();

	void setPosition(const Vector2 pos) { this->position = pos; }

	const std::string& getText() const { return this->text; }
	const Vector2& getPosition() const { return this->position; }
	const float& getFontSize() const { return this->fontSize; }
	const raylib::Color& getColor() const { return this->color; }
	const float& getSpacing() const { return this->spacing; }
};

