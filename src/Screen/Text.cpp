#include "Text.h"
#include "../I18n/FontProvider.h"
#include "../I18n/I18n.h"
#include "../Utils/RaylibUtils.h"

Text::Text(const std::string& i18nKey, const float fontSize, const TextAlign align,
           const raylib::Color color, const float spacing) :
	Text(Vector2(0, 0), i18nKey, fontSize, align, color, spacing)
{
}

Text::Text(const raylib::Vector2 pos, const std::string& i18nKey, const float fontSize,
           const TextAlign align, const raylib::Color color, const float spacing) :
	Text(pos, I18n::instance().get(i18nKey), fontSize, align, color, spacing, &FontProvider::instance().get(i18nKey))
{
}

Text::Text(const std::string& text, const float fontSize, const TextAlign align,
           const raylib::Color color, const float spacing, const raylib::Font* font) :
	Text(Vector2(0, 0), text, fontSize, align, color, spacing, font)
{
}

Text::Text(const raylib::Vector2 pos, const std::string& text,
           const float fontSize, const TextAlign align, const raylib::Color color,
           const float spacing, const raylib::Font* font) : Element(ElementType::TEXT, pos)
{
	this->texts = str2ColorTexts(text);

	this->fontSize = RaylibUtils::getRealLength(fontSize);
	this->align = align;
	this->color = color;
	this->spacing = spacing;

	this->font = font;

	this->lineNums = 1;
	for(const auto& c : text)
	{
		if (c == '\n')
		{
			this->lineNums++;
		}
	}

	Text::updatePosition();
}

void Text::draw()
{
	int textOffsetY = 0;
	float textOffsetX = 0.0f;

	const float scaleFactor = this->fontSize / this->font->baseSize;

	struct Char
	{
		int codepoint;
		float width;
		Color color;
	};
	float width;
	std::vector<Char> currentLine;

	for (const auto& colorText : this->texts) {
		const int size = TextLength(colorText.text.c_str());
		for (int i = 0; i < size;)
		{
			int codepointByteCount = 0;
			const int codepoint = GetCodepointNext(&colorText.text[i], &codepointByteCount);
			const int index = GetGlyphIndex(*this->font, codepoint);

			if (codepoint == 0x3f) codepointByteCount = 1;
			switch (this->align)
			{
				case TextAlign::LEFT:
					if (codepoint == '\n')
					{
						textOffsetY += static_cast<int>(this->fontSize);
						textOffsetX = 0.0f;

					}
					else
					{
						if ((codepoint != ' ') && (codepoint != '\t'))
						{
							DrawTextCodepoint(*this->font, codepoint, Vector2(this->originPos.x + textOffsetX, this->originPos.y + textOffsetY), this->fontSize, colorText.color);
						}

						if (this->font->glyphs[index].advanceX == 0) {
							textOffsetX += this->font->recs[index].width * scaleFactor + this->spacing;
						}
						else {
							textOffsetX += static_cast<float>(this->font->glyphs[index].advanceX) * scaleFactor + this->spacing;
						}
					}
					break;

				case TextAlign::CENTER:
					if (codepoint == '\n')
					{
						//std::cout << "x: " << this->originPos.x + textOffsetX << " y: " << this->originPos.y + textOffsetY << std::endl;
						for (const auto& [currentCodepoint, currentWidth, currentColor] : currentLine) {
							DrawTextCodepoint(*this->font, currentCodepoint, Vector2(this->originPos.x + textOffsetX, this->originPos.y + textOffsetY), this->fontSize, currentColor);
							textOffsetX += currentWidth;
						}
						textOffsetY += static_cast<int>(this->fontSize);
						textOffsetX = 0.0f;
						currentLine.clear();
					}
					else
					{
						if (this->font->glyphs[index].advanceX == 0) {
							width = this->font->recs[index].width * scaleFactor + this->spacing;
						}
						else {
							width = static_cast<float>(this->font->glyphs[index].advanceX) * scaleFactor + this->spacing;
						}
						currentLine.emplace_back(codepoint, width, colorText.color);
						textOffsetX -= width / 2;
					}
					break;

				case TextAlign::RIGHT:
					if (codepoint == '\n')
					{
						//std::cout << "x: " << this->originPos.x + textOffsetX << " y: " << this->originPos.y + textOffsetY << std::endl;
						for (const auto& [currentCodepoint, currentWidth, currentColor] : currentLine) {
							DrawTextCodepoint(*this->font, currentCodepoint, Vector2(this->originPos.x + textOffsetX, this->originPos.y + textOffsetY), this->fontSize, currentColor);
							textOffsetX += currentWidth;
						}
						textOffsetY += static_cast<int>(this->fontSize);
						textOffsetX = 0.0f;
						currentLine.clear();
					}
					else
					{
						if (this->font->glyphs[index].advanceX == 0) {
							width = this->font->recs[index].width * scaleFactor + this->spacing;
						}
						else {
							width = static_cast<float>(this->font->glyphs[index].advanceX) * scaleFactor + this->spacing;
						}
						currentLine.emplace_back(codepoint, width, colorText.color);
						textOffsetX -= width;
					}
					break;
			}

			i += codepointByteCount;
			}
		}

	if (align == TextAlign::CENTER || align == TextAlign::RIGHT) {
		for (const auto& [currentCodepoint, currentWidth, currentColor] : currentLine) {
			DrawTextCodepoint(*this->font, currentCodepoint, Vector2(this->originPos.x + textOffsetX, this->originPos.y + textOffsetY), this->fontSize, currentColor);
			textOffsetX += currentWidth;
		}
	}
}

void Text::updatePosition()
{
	this->originPos.y = this->position.y - (this->fontSize * this->lineNums / 2);
	this->originPos.x = this->position.x;
}

std::vector<ColorText> Text::str2ColorTexts(std::string str)
{
	std::vector<ColorText> colorTexts;
	std::vector<std::pair<std::string, std::string>> result;

	std::size_t start = 0;
	while (start < str.size()) {
		const std::size_t color_start = str.find('<', start);
		if (color_start == std::string::npos) {
			colorTexts.emplace_back(str.substr(start), str2Color("white"));
			break;
		}

		if (color_start > start) {
			colorTexts.emplace_back(str.substr(start, color_start - start), str2Color("white"));
		}
		const std::size_t color_end = str.find('>', color_start);
		if (color_end == std::string::npos) {
			break;
		}

		const std::size_t text_start = color_end + 1;
		const std::size_t text_end = str.find('<', text_start);
		if (text_end == std::string::npos) {
			std::string text = str.substr(text_start);
			if (!text.empty()) {
				colorTexts.emplace_back(text, str2Color(str.substr(color_start + 1, color_end - color_start - 1)));
			}
			break;
		}

		std::string text = str.substr(text_start, text_end - text_start);
		if (!text.empty()) {
			colorTexts.emplace_back(text, str2Color(str.substr(color_start + 1, color_end - color_start - 1)));
		}
		start = text_end;
	}

	return colorTexts;
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
