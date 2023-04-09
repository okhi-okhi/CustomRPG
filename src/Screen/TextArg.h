#pragma once
#include <variant>
#include "Text.h"

using argTypes = std::variant<int*, float*, std::string*>;
class TextArg final : public Text
{
private:
	std::string i18nKey;
	std::map<std::string, argTypes> args;
	textAlign align;

	Vector2 oldTextSize;

public:
	TextArg() = default;
	TextArg(const std::string& i18nKey, const std::map<std::string, argTypes>& args, Vector2 pos, float fontSize = 0.03f,
		textAlign align = textAlign::LEFT, raylib::Color color = BLACK, float spacing = 1.0f);

	void draw() const override;
};

