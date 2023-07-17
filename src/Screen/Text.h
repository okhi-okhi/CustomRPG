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

struct ColorChar
{
	int codepointByteCount;
	int codepoint;
	float width;
	Color color;
	ColorChar(const int codepointByteCount, const int codepoint, const float width, const Color color) :
		codepointByteCount(codepointByteCount), codepoint(codepoint), width(width), color(color) {}
};

struct TextLine
{
	float width;
	std::vector<ColorChar> text;
	TextLine(const float width, std::vector<ColorChar> text) : width(width), text(std::move(text)) {}
};

class Text : public Element
{
protected:
	std::vector<TextLine> textLines;

	float fontSize;
	TextAlign align;
	float spacing;

	const raylib::Font* font;

public:
	Text() : fontSize(0), align(), spacing(0), font(nullptr) {}
	explicit Text(const std::string& i18nKey, float fontSize,
		TextAlign align, float spacing);
	explicit Text(raylib::Vector2 pos, const std::string& i18nKey,
		float fontSize, TextAlign align, float spacing);
	explicit Text(const std::string& text, float fontSize,
		TextAlign align, float spacing, const raylib::Font* font);
	explicit Text(raylib::Vector2 pos, const std::string& text, float fontSize,
		TextAlign align, float spacing, const raylib::Font* font);

	void draw() override;
	void updatePosition() override;

	virtual std::vector<TextLine> str2TextLines(std::string str) const;
	static Color str2Color(const std::string& colorStr);

	virtual void setText(const std::string& text, const raylib::Font* font);
	void setAlign(const TextAlign align) { this->align = align; updatePosition(); }

	const std::vector<TextLine>& getTexts() const { return this->textLines; }
	const float& getFontSize() const { return this->fontSize; }
	const TextAlign& getAlign() const { return this->align; }
	const float& getSpacing() const { return this->spacing; }
	const raylib::Font* getFont() const { return this->font; }
};

