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
		float fontSize, textAlign textAlign, raylib::Color textColor,
		float textSpacing, const std::function<void()>& function,
		const std::string& clickSound = "button_click.wav");

	void draw() override;
	ButtonArg* clone() const override;

	const TextArg& getText() const { return this->text; }
};

