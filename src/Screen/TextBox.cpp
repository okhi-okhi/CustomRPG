#include "TextBox.h"
#include "../I18n/FontProvider.h"
#include "../I18n/I18n.h"
#include "../Utils/RaylibUtils.h"

TextBox::TextBox(const raylib::Rectangle bounds, const std::string& i18nKey, const TextAlign align, const float spacing) :
	TextBox(bounds, I18n::instance().get(i18nKey), align, spacing, &FontProvider::instance().get(i18nKey))
{
}

TextBox::TextBox(const raylib::Rectangle bounds, const std::string& text,
                 const TextAlign align, const float spacing, const raylib::Font* font)
{
	this->elementType = ElementType::TEXT_BOX;
	this->bounds = RaylibUtils::getRealLength(Rectangle{ bounds.x - bounds.width / 2, bounds.y - bounds.height / 2,
		bounds.width, bounds.height });
	this->position = this->bounds.GetPosition();
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
					calculateLineCapacity();
					std::cout << "startIndex: " << this->startIndex << " lineCap: " << this->lineCapacity << std::endl;
				}
			}
			else
			{
				if (this->startIndex + this->lineCapacity < this->textLines.size())
				{
					this->startIndex++;
					calculateLineCapacity();
					std::cout << "startIndex: " << this->startIndex << " lineCap: " << this->lineCapacity << std::endl;
				}
			}
		}
	}
	float textOffsetX = 0;
	float textOffsetY = 0;
	int lineCount = 0;

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

	for(int i = this->textLines[this->startIndex].startBatch; i < textBatches.size(); i++)
	{
		if(i == this->textLines[this->startIndex].startBatch)
		{
			for(int j = this->textLines[this->startIndex].startBatchIndex; j<this->textBatches[i].chars.size(); j++)
			{
				if (this->textBatches[i].chars[j].codepoint == -1) // -1 == \n
				{
					textOffsetY += textLines[i].height * DEFAULT_LINE_SPACING;
					lineCount++;
					if(lineCount >= this->lineCapacity)
					{
						return;
					}
					switch (this->align)
					{
					case TextAlign::LEFT:
						textOffsetX = 0;
						break;
					case TextAlign::CENTER:
						textOffsetX = -this->textLines[this->startIndex + lineCount + 1].width / 2;
						break;
					case TextAlign::RIGHT:
						textOffsetX = -this->textLines[this->startIndex + lineCount + 1].width;
						break;
					}
				}
				else if((this->textBatches[i].chars[j].codepoint != ' ') && (this->textBatches[i].chars[j].codepoint != '\t'))
				{
					DrawTextCodepoint(*this->font, this->textBatches[i].chars[j].codepoint, Vector2{ this->originPos.x + textOffsetX, this->originPos.y + textOffsetY }, this->textBatches[i].size, this->textBatches[i].color);
				}
				textOffsetX += this->textBatches[i].chars[j].width;
			}
		}
		else
		{
			for (const auto& c : this->textBatches[i].chars)
			{
				if (c.codepoint == -1) // -1 == \n
				{
					textOffsetY += textLines[i].height * DEFAULT_LINE_SPACING;
					lineCount++;
					if (lineCount >= this->lineCapacity)
					{
						return;
					}
					switch (this->align)
					{
					case TextAlign::LEFT:
						textOffsetX = 0;
						break;
					case TextAlign::CENTER:
						textOffsetX = -this->textLines[this->startIndex + lineCount+1].width / 2;
						break;
					case TextAlign::RIGHT:
						textOffsetX = -this->textLines[this->startIndex + lineCount+1].width;
						break;
					}
				}
				else if((c.codepoint != ' ') && (c.codepoint != '\t'))
				{
					DrawTextCodepoint(*this->font, c.codepoint, Vector2{ this->originPos.x + textOffsetX, this->originPos.y + textOffsetY }, this->textBatches[i].size, this->textBatches[i].color);
				}
				textOffsetX += c.width;
			}
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
	int i = this->startIndex, maxCapacity = 0;
	float totalHeight = 0;
	float lineHeight = this->textLines[i].height * DEFAULT_LINE_SPACING;
	while (totalHeight + lineHeight < this->bounds.height)
	{
		totalHeight += lineHeight;
		i++;
		maxCapacity++;
		lineHeight = this->textLines[i].height * DEFAULT_LINE_SPACING;
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
			else
			{
				std::cout << "WARN! Unknown text tag: " << tagStr << std::endl;
			}
			i = tagEnd;
		}
		else if (str[i] == '\n')
		{
			currentBatch.chars.emplace_back(-1, 0.0f);
			this->textLines.emplace_back(currentWidth, currentHeight, this->textBatches.size(), currentBatch.chars.size() - 1);
			currentWidth = 0;
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
				this->textLines.emplace_back(currentWidth, currentHeight);
				currentWidth = 0;
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
	this->textLines.emplace_back(currentWidth, currentHeight, this->textBatches.size(), currentBatch.chars.size() - 1);
}

void TextBox::setText(const std::string& text)
{
	this->startIndex = 0;
	parseText(text);
	calculateLineCapacity();
	this->scrollable = (this->textLines.size() > this->lineCapacity) ? true : false;

	TextBox::updatePosition();
}
