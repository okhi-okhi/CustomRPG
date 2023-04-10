#pragma once
#include "Button.h"
#include "TextArg.h"

class ButtonArg final : public Button
{
private:
	TextArg text;
public:
	ButtonArg() = default;
	ButtonArg(const std::string& fileName, Vector2 position, float zoomPercent,
		const std::string& i18nKey, const std::map<std::string, argTypes>& args,
		float fontSize = 32.0f, textAlign textAlign = textAlign::LEFT,
		raylib::Color textColor = BLACK, float textSpacing = 1.0f);

	void draw() override;
	ButtonArg* clone() const override;

	const TextArg& getText() const { return this->text; }
};

