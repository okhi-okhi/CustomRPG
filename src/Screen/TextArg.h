#pragma once
#include <map>
#include <variant>
#include "Text.h"

using argTypes = std::variant<const int*, const float*, const std::string*>;
class TextArg : virtual public Text
{
protected:
	std::string i18nKey;
	std::map<std::string, argTypes> args;
	std::string text;

public:
	TextArg() = default;
	TextArg(raylib::Vector2 pos, const std::string& i18nKey,
		const std::map<std::string, argTypes>& args,
		TextAlign align, float spacing);

	void draw() override;
	void update() override;
	void updatePosition() override;

	const std::string& getI18nKey() const { return this->i18nKey; }
	const std::map<std::string, argTypes>& getArgs() const { return this->args; }
};

