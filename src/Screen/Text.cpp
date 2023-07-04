#include "Text.h"
#include "../I18n/FontProvider.h"
#include "../I18n/I18n.h"
#include "../Utils/RaylibUtils.h"

Text::Text(const std::string& i18nKey, const float fontSize, const textAlign align,
           const raylib::Color color, const float spacing) :
	Text(Vector2(0, 0), i18nKey, fontSize, align, color, spacing)
{
}

Text::Text(const raylib::Vector2 pos, const std::string& i18nKey, const float fontSize,
           const textAlign align, const raylib::Color color, const float spacing) :
	Text(pos, I18n::instance().get(i18nKey), fontSize, align, color, spacing, &FontProvider::instance().get(i18nKey))
{
}

Text::Text(const std::string& text, const float fontSize, const textAlign align,
           const raylib::Color color, const float spacing, const raylib::Font* font) :
	Text(Vector2(0, 0), text, fontSize, align, color, spacing, font)
{
}

Text::Text(const raylib::Vector2 pos, const std::string& text,
           const float fontSize, const textAlign align, const raylib::Color color,
           const float spacing, const raylib::Font* font) : Element(ElementType::TEXT, pos)
{
	this->text = text;

	this->fontSize = RaylibUtils::getRealLength(fontSize);
	this->align = align;
	this->color = color;
	this->spacing = spacing;

	this->font = font;

	Text::updatePosition();
}

void Text::draw()
{
	raylib::DrawTextEx(*this->font, this->text, this->originPos, this->fontSize, this->spacing, this->color);
}

void Text::updatePosition()
{
	const Vector2 textSize = MeasureTextEx(*this->font, this->text.c_str(), this->fontSize, this->spacing);

	this->originPos.y = this->position.y - textSize.y / 2;
	switch (this->align)
	{
	case textAlign::LEFT:
		this->originPos.x = this->position.x;
		break;
	case textAlign::CENTER:
		this->originPos.x = this->position.x - textSize.x / 2;
		break;
	case textAlign::RIGHT:
		this->originPos.x = this->position.x - textSize.x;
		break;
	}
}
