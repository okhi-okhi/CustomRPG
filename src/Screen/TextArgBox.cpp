#include "TextArgBox.h"
#include "../I18n/FontProvider.h"
#include "../I18n/I18n.h"
#include "../Utils/RaylibUtils.h"

TextArgBox::TextArgBox(const raylib::Rectangle bounds, const std::string& i18nKey,
	const std::map<std::string, argTypes>& args, const float fontSize,
	const TextAlign align, const float spacing)
{
	this->elementType = ElementType::TEXT_ARG_BOX;
	this->bounds = RaylibUtils::getRealLength(Rectangle(bounds.x - bounds.width / 2, bounds.y - bounds.height / 2,
		bounds.width, bounds.height));
	this->position = this->bounds.GetPosition();
	this->i18nKey = i18nKey;
	this->args = args;

	this->fontSize = RaylibUtils::getRealLength(fontSize);
	this->align = align;
	this->spacing = spacing;

	this->font = &FontProvider::instance().get(i18nKey);

	update();

	const int maxCapacity = static_cast<int>(this->bounds.height / this->fontSize);
	this->lineCapacity = (this->textLines.size() > maxCapacity) ? maxCapacity : static_cast<int>(this->textLines.size());
	this->startIndex = 0;
	this->scrollable = (this->textLines.size() > this->lineCapacity) ? true : false;

	TextArgBox::updatePosition();
}

void TextArgBox::draw()
{
	update();
	TextBox::draw();
}

void TextArgBox::updatePosition()
{
	TextBox::updatePosition();
}
