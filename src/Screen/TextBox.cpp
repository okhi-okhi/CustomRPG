#include "TextBox.h"
#include "../I18n/FontProvider.h"
#include "../I18n/I18n.h"
#include "../Utils/RaylibUtils.h"

TextBox::TextBox(const raylib::Rectangle bounds, const std::string& i18nKey, const TextAlign align, const float spacing) :
	TextBox(bounds, I18n::instance().get(i18nKey), align, spacing, &FontProvider::instance().get(i18nKey))
{
}

TextBox::TextBox(raylib::Rectangle bounds, const std::string& text,
                 const TextAlign align, const float spacing, const raylib::Font* font)
{
	this->elementType = ElementType::TEXT_BOX;
	this->position = RaylibUtils::getRealLength(bounds.GetPosition());
	this->bounds = RaylibUtils::getRealLength(Rectangle{ bounds.x - bounds.width / 2, bounds.y - bounds.height / 2,
		bounds.width, bounds.height });
	this->align = align;
	this->spacing = spacing;

	this->font = font;

	TextBox::parseText(text);
	this->startIndex = 0;
	calculateLineCapacity();
	this->scrollable = (this->textLines.size() > this->lineCapacity) ? true : false;
	TextBox::updatePosition();
}

void TextBox::draw()
{
	if (this->scrollable)
	{
		const int wheelMove = static_cast<int>(GetMouseWheelMove());
		if (wheelMove != 0)
		{
			if (wheelMove > 0)
			{
				if (this->startIndex > 0)
				{
					this->startIndex--;
					calculateLineCapacity();
				}
			}
			else
			{
				if (this->startIndex + this->lineCapacity < this->textLines.size())
				{
					this->startIndex++;
					calculateLineCapacity();
				}
			}
		}
	}
	float textOffsetX = 0;
	float textOffsetY = 0;
	int lineCount = 1;
	if (lineCount > this->lineCapacity)
	{
		return;
	}
	switch (this->align)
	{
	case TextAlign::LEFT:
		textOffsetX = 0;
		break;
	case TextAlign::CENTER:
		textOffsetX = -this->textLines[this->startIndex].width / 2;
		break;
	case TextAlign::RIGHT:
		textOffsetX = -this->textLines[this->startIndex].width;
		break;
	}

	const int startBatch = this->textLines[this->startIndex].startBatch;
	for (int i = this->textLines[this->startIndex].startBatchIndex; i < this->textBatches[startBatch].chars.size(); i++)
	{
		if (this->textBatches[startBatch].chars[i].codepoint == -1) // -1 == \n
		{
			textOffsetY += textLines[this->startIndex + lineCount-1].height * DEFAULT_LINE_SPACING;
			if(lineCount >= this->lineCapacity)
			{
				return;
			}
			lineCount++;
			if(this->startIndex + lineCount> this->textLines.size())
			{
				return;
			}
			switch (this->align)
			{
			case TextAlign::LEFT:
				textOffsetX = 0;
				break;
			case TextAlign::CENTER:
				textOffsetX = -this->textLines[this->startIndex + lineCount - 1].width / 2;
				break;
			case TextAlign::RIGHT:
				textOffsetX = -this->textLines[this->startIndex + lineCount - 1].width;
				break;
			}
		}
		else if((this->textBatches[startBatch].chars[i].codepoint != ' ') && (this->textBatches[startBatch].chars[i].codepoint != '\t'))
		{
			DrawTextCodepoint(*this->font, this->textBatches[startBatch].chars[i].codepoint,
				Vector2{ this->originPos.x + textOffsetX, this->originPos.y + textOffsetY + this->textLines[this->startIndex + lineCount-1].height - this->textBatches[startBatch].size },
				this->textBatches[startBatch].size, this->textBatches[startBatch].color);
		}
		textOffsetX += this->textBatches[startBatch].chars[i].width;
	}

	for (int i = startBatch + 1; i < textBatches.size(); i++)
	{
		for (const auto& c : this->textBatches[i].chars)
		{
			if (c.codepoint == -1) // -1 == \n
			{
				textOffsetY += textLines[this->startIndex + lineCount-1].height * DEFAULT_LINE_SPACING;
				if (lineCount >= this->lineCapacity)
				{
					return;
				}
				lineCount++;
				if (this->startIndex + lineCount > this->textLines.size())
				{
					return;
				}
				switch (this->align)
				{
				case TextAlign::LEFT:
					textOffsetX = 0;
					break;
				case TextAlign::CENTER:
					textOffsetX = -this->textLines[this->startIndex + lineCount - 1].width / 2;
					break;
				case TextAlign::RIGHT:
					textOffsetX = -this->textLines[this->startIndex + lineCount - 1].width;
					break;
				}
			}
			else if((c.codepoint != ' ') && (c.codepoint != '\t'))
			{
				DrawTextCodepoint(*this->font, c.codepoint, 
					Vector2{ this->originPos.x + textOffsetX, this->originPos.y + textOffsetY + this->textLines[this->startIndex + lineCount - 1].height - this->textBatches[i].size },
					this->textBatches[i].size, this->textBatches[i].color);
			}
			textOffsetX += c.width;
		}
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

void TextBox::calculateLineCapacity()
{
	int maxCapacity = 0;
	float totalHeight = 0;
	for(int i = this->startIndex; i < this->textLines.size(); i++)
	{
		const float lineHeight = this->textLines[i].height * DEFAULT_LINE_SPACING;
		if(totalHeight + lineHeight > this->bounds.height)
		{
			break;
		}
		totalHeight += lineHeight;
		maxCapacity++;
	}

	if (this->textLines.size() > maxCapacity)
	{
		this->lineCapacity = maxCapacity;
	}
	else
	{
		this->lineCapacity = static_cast<int>(this->textLines.size());
	}
}

void TextBox::parseText(std::string str)
{
	TextBatch currentBatch;
	float currentWidth = 0;
	float currentHeight = currentBatch.size;

	int currentTextLineBatch = 0;
	int currentTextLineBatchIndex = 0;

	this->textBatches.clear();
	this->textLines.clear();

	int codepointByteCount = 1;
	for (size_t i = 0; i < str.size(); i += codepointByteCount)
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
			else if (tagStr == "reset")
			{
				currentBatch = TextBatch();
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
			this->textLines.emplace_back(currentWidth, currentHeight, currentTextLineBatch, currentTextLineBatchIndex);
			currentWidth = 0;
			currentTextLineBatch = static_cast<int>(this->textBatches.size());
			currentTextLineBatchIndex = static_cast<int>(currentBatch.chars.size());
			codepointByteCount = 1;
		}
		else 
		{
			const int codepoint = GetCodepointNext(&str[i], &codepointByteCount);
			const int index = GetGlyphIndex(*this->font, codepoint);
			float charWidth;

			if (this->font->glyphs[index].advanceX == 0) {
				charWidth = this->font->recs[index].width * currentBatch.size / this->font->baseSize + this->spacing;
			}
			else {
				charWidth = static_cast<float>(this->font->glyphs[index].advanceX) * currentBatch.size / this->font->baseSize + this->spacing;
			}

			if (currentWidth + charWidth > this->bounds.width)
			{
				currentBatch.chars.emplace_back(-1, 0.0f);
				this->textLines.emplace_back(currentWidth, currentHeight, currentTextLineBatch, currentTextLineBatchIndex);
				currentWidth = 0;
				currentTextLineBatch = static_cast<int>(this->textBatches.size());
				currentTextLineBatchIndex = static_cast<int>(currentBatch.chars.size());
			}

			if (currentBatch.size > currentHeight)
			{
				currentHeight = currentBatch.size;
			}
			currentWidth += charWidth;
			currentBatch.chars.emplace_back(codepoint, charWidth);
		}
	}
	this->textBatches.push_back(currentBatch);
	this->textLines.emplace_back(currentWidth, currentHeight, currentTextLineBatch, currentTextLineBatchIndex);
}

void TextBox::setText(const std::string& text)
{
	this->startIndex = 0;
	parseText(text);
	calculateLineCapacity();
	this->scrollable = (this->textLines.size() > this->lineCapacity) ? true : false;

	TextBox::updatePosition();
}
