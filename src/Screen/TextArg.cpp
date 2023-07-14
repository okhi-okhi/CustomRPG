#include "TextArg.h"
#include "../I18n/FontProvider.h"
#include "../I18n/I18n.h"
#include "../Utils/RaylibUtils.h"

TextArg::TextArg(const raylib::Vector2 pos, const std::string& i18nKey,
	const std::map<std::string, argTypes>& args, const float fontSize,
	const TextAlign align, const float spacing)
{
	this->elementType = ElementType::TEXT_ARG;
	this->i18nKey = i18nKey;
	this->args = args;
	this->position = RaylibUtils::getRealLength(pos);

	this->fontSize = RaylibUtils::getRealLength(fontSize);
	this->align = align;
	this->spacing = spacing;

	this->font = &FontProvider::instance().get(i18nKey);

	update();
}

void TextArg::draw()
{
	update();
	Text::draw();
}

void TextArg::updatePosition()
{
	Text::updatePosition();
}

void TextArg::update()
{
	std::map<std::string, std::string> newArgs;
	for (const auto& [fst, snd] : this->args)
	{
		if (snd.index() == 2)
		{
			newArgs.emplace(fst, *std::get<const std::string*>(snd));
		}
		else if (snd.index() == 1)
		{
			newArgs.emplace(fst, std::to_string(*std::get<const float*>(snd)));
		}
		else
		{
			newArgs.emplace(fst, std::to_string(*std::get<const int*>(snd)));
		}
	}
	const std::string newText = I18n::instance().get(this->i18nKey, newArgs);

	if (this->text != newText)
	{
		this->text = newText;
		this->textLines = str2TextLines(newText);
		updatePosition();
	}
}
