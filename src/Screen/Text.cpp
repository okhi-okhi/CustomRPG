#include "Text.h"
#include "../I18n/FontProvider.h"
#include "../I18n/I18n.h"
#include "../Utils/RaylibUtils.h"

Text::Text(const std::string& i18nKey, const raylib::Vector2 pos,
	const float fontSize, const textAlign align, const raylib::Color color,
	const float spacing) : Element(elementTypes::TEXT, pos)
{
	this->text = I18n::instance().get(i18nKey);

	this->fontSize = fontSize * static_cast<float>(RaylibUtils::getWindowHeight());
	this->align = align;
	this->color = color;
	this->spacing = spacing;

	this->font = &FontProvider::instance().get(i18nKey);

	const Vector2 textSize = MeasureTextEx(*font, text.c_str(), this->fontSize, this->spacing);
	const float posY = this->position.y - textSize.y / 2;

	switch (this->align)
	{
	case textAlign::LEFT:
		this->position = Vector2(this->position.x, posY);
		break;

	case textAlign::CENTER:
		this->position = Vector2(this->position.x - textSize.x / 2, posY);
		break;

	case textAlign::RIGHT:
		this->position = Vector2(this->position.x - textSize.x, posY);
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
