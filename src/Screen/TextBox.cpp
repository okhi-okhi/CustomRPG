#include "TextBox.h"
#include "../I18n/FontProvider.h"
#include "../I18n/I18n.h"
#include "../Utils/RaylibUtils.h"

TextBox::TextBox(const raylib::Rectangle bounds, const std::string& i18nKey, const float fontSize, const TextAlign align, const float spacing) :
	TextBox(bounds, I18n::instance().get(i18nKey), fontSize, align, spacing, &FontProvider::instance().get(i18nKey))
{
}

TextBox::TextBox(const raylib::Rectangle bounds, const std::string& text, const float fontSize,
                 const TextAlign align, const float spacing, const raylib::Font* font)
{
	this->elementType = ElementType::TEXT_BOX;
	this->bounds = RaylibUtils::getRealLength(Rectangle(bounds.x - bounds.width / 2, bounds.y - bounds.height / 2,
		bounds.width, bounds.height));
	this->position = this->bounds.GetPosition();
	this->fontSize = RaylibUtils::getRealLength(fontSize);
	this->align = align;
	this->spacing = spacing;

	this->font = font;

	this->textLines = TextBox::str2TextLines(text);
	const int maxCapacity = static_cast<int>(this->bounds.height / this->fontSize);
	this->lineCapacity = (this->textLines.size() > maxCapacity) ? maxCapacity : static_cast<int>(this->textLines.size());
	this->startIndex = 0;
	this->scrollable = (this->textLines.size() > this->lineCapacity) ? true : false;
	TextBox::updatePosition();
}

void TextBox::draw()
{
	if(this->scrollable)
	{
		const int wheelMove = static_cast<int>(GetMouseWheelMove());
		if (wheelMove != 0)
		{
			if (wheelMove > 0)
			{
				if (this->startIndex > 0)
				{
					this->startIndex--;
				}
			}
			else
			{
				if (this->startIndex + this->lineCapacity < this->textLines.size())
				{
					this->startIndex++;
				}
			}
		}
	}
	float textOffsetX = 0;
	float textOffsetY = 0;
	for (int i = 0; i < this->lineCapacity; i++)
	{

		switch (this->align)
		{
		case TextAlign::LEFT:
			textOffsetX = 0;
			break;
		case TextAlign::CENTER:
			textOffsetX = -this->textLines[i + this->startIndex].width / 2;
			break;
		case TextAlign::RIGHT:
			textOffsetX = -this->textLines[i + this->startIndex].width;
			break;
		}

		for (const auto& colorChar : this->textLines[i + this->startIndex].text)
		{
			DrawTextCodepoint(*this->font, colorChar.codepoint, Vector2(this->originPos.x + textOffsetX, this->originPos.y + textOffsetY), this->fontSize, colorChar.color);
			textOffsetX += colorChar.width;
		}
		textOffsetY += this->fontSize;
	}
}

void TextBox::updatePosition()
{
	this->bounds.x = this->position.x - this->bounds.width / 2;
	this->bounds.y = this->position.y - this->bounds.height / 2;

	switch (this->align)
	{
	case TextAlign::LEFT:
		this->originPos.x = this->bounds.x;
		break;
	case TextAlign::CENTER:
		this->originPos.x = this->position.x;
		break;
	case TextAlign::RIGHT:
		this->originPos.x = this->bounds.x + this->bounds.width;
		break;
	}

	this->originPos.y = this->bounds.y;
}

std::vector<TextLine> TextBox::str2TextLines(std::string str) const
{
	float currentWidth = 0;
	std::vector<TextLine> textLines;
	auto currentColor = WHITE;
	std::vector<ColorChar> currentText;

	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == '<') {
			const size_t colorEnd = str.find('>', i);
			std::string colorStr = str.substr(i + 1, colorEnd - i - 1);
			if (!colorStr.empty())
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

			if(currentWidth > this->bounds.width)
			{
				textLines.emplace_back(currentWidth, currentText);
				currentText.clear();
				currentWidth = 0;
			}
		}
	}
	textLines.emplace_back(currentWidth, currentText);

	return textLines;
}
