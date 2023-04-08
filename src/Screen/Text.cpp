#include "Text.h"
#include "../I18n/FontProvider.h"
#include "../I18n/I18n.h"
#include "../Utils/RaylibUtils.h"

// Text::Text(const std::string& i18nKey, const float fontSize, const raylib::Color color, const float spacing)
// {
// 	this->text = I18n::instance().get(i18nKey);
//
// 	this->fontSize = fontSize * RaylibUtils::getWindowHeight();
// 	this->color = color;
// 	this->spacing = spacing;
//
// 	this->font = &FontProvider::instance().get(i18nKey);
//
// 	this->position = Vector2();
// }

Text::Text(const std::string& i18nKey, Vector2 pos, const float fontSize,
           const textAlign align, const raylib::Color color, const float spacing)
{
	this->text = I18n::instance().get(i18nKey);

	this->fontSize = fontSize * RaylibUtils::getWindowHeight();
	this->color = color;
	this->spacing = spacing;

	this->font = &FontProvider::instance().get(i18nKey);

	const Vector2 textSize = MeasureTextEx(*font, text.c_str(), this->fontSize, this->spacing);
	pos = Vector2(pos.x * RaylibUtils::getWindowWidth(), pos.y * RaylibUtils::getWindowHeight());
	const float posY = pos.y - textSize.y / 2;

	switch (align)
	{
	case textAlign::LEFT:
		this->position = Vector2(pos.x, posY);
		break;

	case textAlign::CENTER:
		this->position = Vector2(pos.x - textSize.x / 2, posY);
		break;

	case textAlign::RIGHT:
		this->position = Vector2(pos.x - textSize.x, posY);
		break;
	}
}

void Text::draw() const
{
	raylib::DrawTextEx(*font, text, this->position, this->fontSize, this->spacing, this->color);
}
