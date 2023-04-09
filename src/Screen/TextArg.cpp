#include "TextArg.h"

#include <iostream>

#include "../I18n/FontProvider.h"
#include "../I18n/I18n.h"
#include "../Utils/LambdaUtil.hpp"
#include "../Utils/RaylibUtils.h"

TextArg::TextArg(const std::string& i18nKey, const std::map<std::string, argTypes>& args, Vector2 pos, const float fontSize,
                 const textAlign align, const raylib::Color color, const float spacing)
{
	this->i18nKey = i18nKey;
	this->args = args;
	this->position = Vector2(pos.x * RaylibUtils::getWindowWidth(), pos.y * RaylibUtils::getWindowHeight());

	this->fontSize = fontSize * RaylibUtils::getWindowHeight();
	this->align = align;
	this->color = color;
	this->spacing = spacing;

	this->font = &FontProvider::instance().get(i18nKey);

	this->oldTextSize = Vector2(0.0f, 0.0f);
}

void TextArg::draw() const
{
	std::map<std::string, std::string> newArgs;
	for (const auto& [fst, snd] : args)
	{
		if(snd.index() == 2)
		{
			newArgs.emplace(fst, *std::get<std::string*>(snd));
		}
		else if(snd.index() == 1)
		{
			newArgs.emplace(fst, std::to_string(*std::get<float*>(snd)));
		}
		else
		{
			newArgs.emplace(fst, std::to_string(*std::get<int*>(snd)));
		}
	}

	const std::string text = I18n::instance().get(i18nKey, newArgs);
	const Vector2 textSize = MeasureTextEx(*font, text.c_str(), this->fontSize, this->spacing);
	const float posY = this->position.y - textSize.y / 2;

	Vector2 startPos;
	switch (align)
	{
	case textAlign::LEFT:
		startPos = Vector2(this->position.x, posY);
		break;

	case textAlign::CENTER:
		startPos = Vector2(this->position.x - textSize.x / 2, posY);
		break;

	case textAlign::RIGHT:
		startPos = Vector2(this->position.x - textSize.x, posY);
		break;
	}
	raylib::DrawTextEx(*this->font, text, startPos, this->fontSize, this->spacing, this->color);
}
