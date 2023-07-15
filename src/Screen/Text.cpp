#include "Text.h"
#include "../I18n/FontProvider.h"
#include "../I18n/I18n.h"
#include "../Utils/RaylibUtils.h"

Text::Text(const std::string& i18nKey, const float fontSize, const TextAlign align,
           const float spacing) :
	Text(Vector2(0, 0), i18nKey, fontSize, align, spacing)
{
}

Text::Text(const raylib::Vector2 pos, const std::string& i18nKey, const float fontSize,
           const TextAlign align, const float spacing) :
	Text(pos, I18n::instance().get(i18nKey), fontSize, align, spacing, &FontProvider::instance().get(i18nKey))
{
}

Text::Text(const std::string& text, const float fontSize, const TextAlign align,
		   const float spacing, const raylib::Font* font) :
	Text(Vector2(0, 0), text, fontSize, align, spacing, font)
{
}

Text::Text(const raylib::Vector2 pos, const std::string& text,
           const float fontSize, const TextAlign align,
           const float spacing, const raylib::Font* font) : Element(ElementType::TEXT, pos)
{
	this->fontSize = RaylibUtils::getRealLength(fontSize);
	this->align = align;
	this->spacing = spacing;

	this->font = font;

	this->textLines = Text::str2TextLines(text);

	Text::updatePosition();
}

void Text::draw()
{
	float textOffsetX = 0;
	float textOffsetY = 0;

	for (const auto& text : this->textLines)
	{
		switch (this->align)
		{
		case TextAlign::LEFT:
			textOffsetX = 0;
			break;
		case TextAlign::CENTER:
			textOffsetX = - text.width / 2;
			break;
		case TextAlign::RIGHT:
			textOffsetX = - text.width;
			break;
		}

		for (const auto& colorChar : text.text)
		{
			DrawTextCodepoint(*this->font, colorChar.codepoint, Vector2(this->originPos.x + textOffsetX, this->originPos.y + textOffsetY), this->fontSize, colorChar.color);
			textOffsetX += colorChar.width;
		}
		textOffsetY += this->fontSize;
	}
}

void Text::updatePosition()
{
	this->originPos.x = this->position.x;
	this->originPos.y = this->position.y - (this->fontSize * textLines.size() / 2);
}

std::vector<TextLine> Text::str2TextLines(std::string str) const
{
	std::vector<TextLine> textLines;
	float currentWidth = 0;
	auto currentColor = WHITE;
	std::vector<ColorChar> currentText;

	for(size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == '<') {
			const size_t colorEnd = str.find('>', i);
			std::string colorStr = str.substr(i + 1, colorEnd - i - 1);
			if(!colorStr.empty())
			{
				currentColor = str2Color(colorStr);
				i = colorEnd;
			}
		}
		else if (str[i] == '\n')
		{
			textLines.emplace_back(currentWidth, currentText);
			currentText.clear();
			currentWidth = 0;
		}
		else {
			int codepointByteCount;
			const int codepoint = GetCodepointNext(&str[i], &codepointByteCount);
			const int index = GetGlyphIndex(*this->font, codepoint);
			float charWidth;

			if (codepoint == 0x3f) codepointByteCount = 1;
			if (this->font->glyphs[index].advanceX == 0) {
				charWidth = this->font->recs[index].width * this->fontSize / this->font->baseSize + this->spacing;
			}
			else {
				charWidth = static_cast<float>(this->font->glyphs[index].advanceX) * this->fontSize / this->font->baseSize + this->spacing;
			}
			currentWidth += charWidth;
			currentText.emplace_back(codepointByteCount, codepoint, charWidth, currentColor);
			i += codepointByteCount - 1;
		}
	}
	textLines.emplace_back(currentWidth, currentText);

	return textLines;
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
		const auto rgb = RaylibUtils::hexDecode(colorStr);
		currentColor = Color(rgb[0], rgb[1], rgb[2], 255);
	}
	return currentColor;
}
