#pragma once
#include <variant>
#include "Text.h"

using argTypes = std::variant<int*, float*, std::string*>;
class TextArg final : public Text
{
private:
	std::string i18nKey;
	std::map<std::string, argTypes> args;
	raylib::Vector2 startPos;

public:
	TextArg() = default;
	TextArg(const std::string& i18nKey, const std::map<std::string, argTypes>& args,
		raylib::Vector2 pos, float fontSize = 0.03f, textAlign align = textAlign::LEFT,
		raylib::Color color = BLACK, float spacing = 1.0f);

	void draw() override;
	TextArg* clone() const override;

	const std::string& getI18nKey() const { return this->i18nKey; }
	const std::map<std::string, argTypes>& getArgs() const { return this->args; }
	const raylib::Vector2& getStartPos() const { return this->startPos; }
};

