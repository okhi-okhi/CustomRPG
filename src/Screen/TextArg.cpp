#include "TextArg.h"
#include "../I18n/FontProvider.h"
#include "../I18n/I18n.h"
#include "../Utils/RaylibUtils.h"

TextArg::TextArg(const std::string& i18nKey, const std::map<std::string, argTypes>& args,
	const raylib::Vector2 pos, const float fontSize,
	const textAlign align, const raylib::Color color, const float spacing)
{
	this->elementType = elementTypes::TEXT_ARG;
	this->i18nKey = i18nKey;
	this->args = args;
	this->position = RaylibUtils::getRealLength(pos);

	this->fontSize = RaylibUtils::getRealLength(fontSize);
	this->align = align;
	this->color = color;
	this->spacing = spacing;

	this->font = &FontProvider::instance().get(i18nKey);

	update();
}

void TextArg::draw()
{
	update();
	raylib::DrawTextEx(*this->font, text, this->position, this->fontSize, this->spacing, this->color);
}

TextArg* TextArg::clone() const
{
	return new TextArg(*this);
}

void TextArg::update()
{
	std::map<std::string, std::string> newArgs;
	for (const auto& [fst, snd] : args)
	{
		if (snd.index() == 2)
		{
			newArgs.emplace(fst, *std::get<std::string*>(snd));
		}
		else if (snd.index() == 1)
		{
			newArgs.emplace(fst, std::to_string(*std::get<float*>(snd)));
		}
		else
		{
			newArgs.emplace(fst, std::to_string(*std::get<int*>(snd)));
		}
	}
	const std::string newText = I18n::instance().get(i18nKey, newArgs);

	if (this->text != newText)
	{
		this->text = newText;
		const Vector2 textSize = MeasureTextEx(*font, text.c_str(), this->fontSize, this->spacing);
		this->position.y -= textSize.y / 2;

		switch (align)
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
}
