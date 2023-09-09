#include "TextArgBox.h"
#include "../I18n/FontProvider.h"
#include "../I18n/I18n.h"

TextArgBox::TextArgBox(const raylib::Rectangle bounds, const std::string& i18nKey,
	const std::map<std::string, argTypes>& args,
	const TextAlign align, const float spacing)
{
	this->elementType = ElementType::TEXT_ARG_BOX;
	this->bounds = RaylibUtils::getRealLength(Rectangle{ bounds.x - bounds.width / 2, bounds.y - bounds.height / 2,
		bounds.width, bounds.height });
	this->position = this->bounds.GetPosition();
	this->i18nKey = i18nKey;
	this->args = args;

	this->align = align;
	this->spacing = spacing;

	this->font = &FontProvider::instance().get(i18nKey);

	TextArg::update();
	this->startIndex = 0;
	calculateLineCapacity();
	this->scrollable = (this->textLines.size() > this->lineCapacity) ? true : false;
	TextBox::updatePosition();
}

void TextArgBox::draw()
{
	TextBox::draw();
}

void TextArgBox::updatePosition()
{
	TextBox::updatePosition();
}
