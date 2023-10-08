#include "Text.h"
#include <iostream>
#include "../I18n/FontProvider.h"
#include "../I18n/I18n.h"

Text::Text(const std::string& i18nKey, const TextAlign align, const float spacing) :
	Text(Vector2{ 0, 0 }, i18nKey, align, spacing)
{
}

Text::Text(const raylib::Vector2 pos, const std::string& i18nKey, const TextAlign align,
		   const float spacing) :
	Text(pos, I18n::instance().get(i18nKey), align, spacing, &FontProvider::instance().get(i18nKey))
{
}

Text::Text(const std::string& text, const TextAlign align, const float spacing,
		   const raylib::Font* font) :
	Text(Vector2{ 0, 0 }, text, align, spacing, font)
{
}

Text::Text(const raylib::Vector2 pos, const std::string& text, const TextAlign align,
           const float spacing, const raylib::Font* font) : Element(ElementType::TEXT, pos)
{
	this->align = align;
	this->spacing = spacing;

	this->font = font;

	Text::parseText(text);

	Text::updatePosition();
}

void Text::draw()
{
	float textOffsetX = 0;
	float textOffsetY = 0;
	int line = 0;

	switch (this->align)
	{
	case TextAlign::LEFT:
		textOffsetX = 0;
		break;
	case TextAlign::CENTER:
		textOffsetX = -textLines[line].width / 2;
		break;
	case TextAlign::RIGHT:
		textOffsetX = -textLines[line].width;
		break;
	}

	for (const auto& text : this->textBatches)
	{
		for (const auto& c : text.chars)
		{
			if (c.codepoint == -1) // -1 == \n
			{
				textOffsetY += this->textLines[line].height * DEFAULT_LINE_SPACING;
				line++;
				switch (this->align)
				{
				case TextAlign::LEFT:
					textOffsetX = 0;
					break;
				case TextAlign::CENTER:
					textOffsetX = -this->textLines[line].width / 2;
					break;
				case TextAlign::RIGHT:
					textOffsetX = -this->textLines[line].width;
					break;
				}
			}
			else if ((c.codepoint != ' ') && (c.codepoint != '\t'))
			{
				DrawTextCodepoint(*this->font, c.codepoint, Vector2{ this->originPos.x + textOffsetX, this->originPos.y + textOffsetY + this->textLines[line].height - text.size }, text.size, text.color);
			}
			textOffsetX += c.width;
		}
	}
}

void Text::updatePosition()
{
	this->originPos.x = this->position.x;
	float totalHeight = 0;
	for (const auto& textLine : this->textLines)
	{
		totalHeight += textLine.height;
	}
	this->originPos.y = this->position.y - totalHeight / 2;
}

void Text::parseText(std::string str)
{
	TextBatch currentBatch;
	float currentWidth = 0;
	float currentHeight = currentBatch.size;

	this->textBatches.clear();
	this->textLines.clear();

	int codepointByteCount = 1;
	for(size_t i = 0; i < str.size(); i += codepointByteCount)
	{
		if (str[i] == '<')
		{
			if (!currentBatch.chars.empty())
			{
				this->textBatches.push_back(currentBatch);
				currentBatch.chars.clear();
			}

			const size_t tagEnd = str.find('>', i);
			std::string tagStr = str.substr(i + 1, tagEnd - i - 1);
			if (tagStr.find("color=") == 0)
			{
				currentBatch.color = str2Color(tagStr.substr(6));
			}
			else if (tagStr.find("size=") == 0)
			{
				currentBatch.size = RaylibUtils::getRealLength(std::stoi(tagStr.substr(5)));
			}
			else
			{
				std::cout << "WARN! Unknown text tag: " << tagStr << std::endl;
			}
			codepointByteCount = 1;
			i = tagEnd;
		}
		else if (str[i] == '\n')
		{
			currentBatch.chars.emplace_back(-1, 0.0f);
			this->textLines.emplace_back(currentWidth, currentHeight);
			currentWidth = 0;
			codepointByteCount = 1;
		}
		else
		{
			const int codepoint = GetCodepointNext(&str[i], &codepointByteCount);
			const int index = GetGlyphIndex(*this->font, codepoint);
			float charWidth;

			if (codepoint == 0x3f) codepointByteCount = 1;
			if (this->font->glyphs[index].advanceX == 0) {
				charWidth = this->font->recs[index].width * currentBatch.size / this->font->baseSize + this->spacing;
			}
			else {
				charWidth = static_cast<float>(this->font->glyphs[index].advanceX) * currentBatch.size / this->font->baseSize + this->spacing;
			}

			if(currentBatch.size > currentHeight)
			{
				currentHeight = currentBatch.size;
			}
			currentWidth += charWidth;
			currentBatch.chars.emplace_back(codepoint, charWidth);
		}
	}
	this->textBatches.push_back(currentBatch);
	this->textLines.emplace_back(currentWidth, currentHeight);
}

Color Text::str2Color(const std::string& colorStr)
{
	Color currentColor;
	if (colorStr == "red") {
		currentColor = RED;
	}
	else if (colorStr == "blue") {
		currentColor = BLUE;
	}
	else if (colorStr == "green") {
		currentColor = GREEN;
	}
	else if (colorStr == "yellow") {
		currentColor = YELLOW;
	}
	else if (colorStr == "orange") {
		currentColor = ORANGE;
	}
	else if (colorStr == "purple") {
		currentColor = PURPLE;
	}
	else if (colorStr == "brown") {
		currentColor = BROWN;
	}
	else if (colorStr == "white") {
		currentColor = WHITE;
	}
	else if (colorStr == "black") {
		currentColor = BLACK;
	}
	else if (colorStr == "blank") {
		currentColor = BLANK;
	}
	else if (colorStr == "gold") {
		currentColor = GOLD;
	}
	else if (colorStr == "gray") {
		currentColor = GRAY;
	}
	else if (colorStr == "lime") {
		currentColor = LIME;
	}
	else if (colorStr == "skyblue") {
		currentColor = SKYBLUE;
	}
	else if (colorStr == "violet") {
		currentColor = VIOLET;
	}
	else if (colorStr == "pink") {
		currentColor = PINK;
	}
	else if (colorStr == "beige") {
		currentColor = BEIGE;
	}
	else {
		const std::vector<int> rgb = RaylibUtils::hexDecode(colorStr);
		currentColor = Color{ static_cast<unsigned char>(rgb[0]), static_cast<unsigned char>(rgb[1]), static_cast<unsigned char>(rgb[2]), 255 };
	}
	return currentColor;
}

void Text::setText(const std::string& text)
{
	parseText(text);
	Text::updatePosition();
}
