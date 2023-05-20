#include "Text.h"
#include "../I18n/FontProvider.h"
#include "../I18n/I18n.h"
#include "../Utils/RaylibUtils.h"

Text::Text(const std::string& i18nKey, const raylib::Vector2 pos, const float fontSize,
	const textAlign align, const raylib::Color color, const float spacing) :
	Text(I18n::instance().get(i18nKey), pos, fontSize, align, color, spacing, &FontProvider::instance().get(i18nKey))
{
	
}

Text::Text(const std::string& text, const raylib::Vector2 pos,
	const float fontSize, const textAlign align, const raylib::Color color,
	const float spacing, const raylib::Font* font) : Element(elementTypes::TEXT, pos)
{
	this->text = text;

	this->fontSize = RaylibUtils::getRealLength(fontSize);
	this->align = align;
	this->color = color;
	this->spacing = spacing;

	this->font = font;

	const Vector2 textSize = MeasureTextEx(*font, text.c_str(), this->fontSize, this->spacing);
	this->position.y -= textSize.y / 2;

	switch (this->align)
	{
	case textAlign::LEFT:
		break;

	case textAlign::CENTER:
		this->position.x -= textSize.x / 2;
		break;

	case textAlign::RIGHT:
		this->position.x -= textSize.x;
		break;
	}
}

void Text::draw()
{
	raylib::DrawTextEx(*this->font, this->text, this->position, this->fontSize, this->spacing, this->color);
}

Text* Text::clone() const
{
	return new Text(*this);
}
