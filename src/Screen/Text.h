#pragma once
#include <Color.hpp>
#include <Font.hpp>
#include <map>
#include "Element.h"

enum class TextAlign
{
	LEFT = 0,
	CENTER,
	RIGHT
};

struct ColorText
{
	std::string text;
	raylib::Color color;
	ColorText(std::string text, const raylib::Color color) : text(std::move(text)), color(color) {}
};

class Text : public Element
{
protected:
	std::vector<ColorText> texts;

	float fontSize;
	TextAlign align;
	raylib::Color color;
	float spacing;

	const raylib::Font* font;

public:
	Text() : fontSize(0), align(), spacing(0), font(nullptr) {}
	explicit Text(const std::string& i18nKey, float fontSize,
		TextAlign align, raylib::Color color, float spacing);
	explicit Text(raylib::Vector2 pos, const std::string& i18nKey, float fontSize,
		TextAlign align, raylib::Color color, float spacing);
	explicit Text(const std::string& text, float fontSize,
		TextAlign align, raylib::Color color, float spacing, const raylib::Font* font);
	explicit Text(raylib::Vector2 pos, const std::string& text, float fontSize,
		TextAlign align, raylib::Color color, float spacing, const raylib::Font* font);

	void draw() override;
	void updatePosition() override;

	static std::vector<ColorText> str2ColorTexts(std::string str);
	static Color str2Color(const std::string& colorStr);
	void setAlign(const TextAlign align) { this->align = align; updatePosition(); }

	const std::vector<ColorText>& getTexts() const { return this->texts; }
	const float& getFontSize() const { return this->fontSize; }
	const TextAlign& getAlign() const { return this->align; }
	const raylib::Color& getColor() const { return this->color; }
	const float& getSpacing() const { return this->spacing; }
	const raylib::Font* getFont() const { return this->font; }
};

