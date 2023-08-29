#pragma once
#include <Color.hpp>
#include <Font.hpp>
#include "Element.h"

enum class TextAlign
{
	LEFT = 0,
	CENTER,
	RIGHT
};

struct TextBatchChar
{
	int codepoint;
	float width;
	TextBatchChar(const int codepoint, const float width) : codepoint(codepoint), width(width) {}
};

struct TextBatch
{
	std::vector<TextBatchChar> chars;
	float size;
	Color color;
	TextBatch() : size(32.0f), color(WHITE) {}
	TextBatch(std::vector<TextBatchChar> chars, const float size, const Color color) :
		chars(std::move(chars)), size(size), color(color) {}
};

struct TextLine
{
	float width;
	float height;
	int startBatch;
	int startBatchIndex;

	TextLine(const float width, const float height) : width(width), height(height), startBatch(0), startBatchIndex(0) {}
	TextLine(const float width, const float height, const int startBatch, const int startBatchIndex) :
		width(width), height(height), startBatch(startBatch), startBatchIndex(startBatchIndex) {}
};

class Text : public Element
{
protected:
	static constexpr float DEFAULT_LINE_SPACING = 1.0f;
	std::vector<TextBatch> textBatches;
	std::vector<TextLine> textLines;

	TextAlign align;
	float spacing;

	const raylib::Font* font;

public:
	Text() : align(), spacing(0), font(nullptr) {}
	explicit Text(const std::string& i18nKey, TextAlign align, float spacing);
	explicit Text(raylib::Vector2 pos, const std::string& i18nKey,
		TextAlign align, float spacing);
	explicit Text(const std::string& text, TextAlign align, float spacing,
		const raylib::Font* font);
	explicit Text(raylib::Vector2 pos, const std::string& text,
		TextAlign align, float spacing, const raylib::Font* font);

	void draw() override;
	void updatePosition() override;

	virtual void parseText(std::string str);
	virtual void setText(const std::string& text);
	void setFont(const raylib::Font* font) { this->font = font; }
	void setAlign(const TextAlign align) { this->align = align; updatePosition(); }

	static Color str2Color(const std::string& colorStr);

	const std::vector<TextBatch>& getTexts() const { return this->textBatches; }
	const TextAlign& getAlign() const { return this->align; }
	const float& getSpacing() const { return this->spacing; }
	const raylib::Font* getFont() const { return this->font; }
};

