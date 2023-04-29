#pragma once
#include "Text.h"
#include "Button.h"

class ButtonText : public Button
{
private:
	Text text;
public:
	ButtonText() = default;
	ButtonText(const std::string& fileName, Vector2 position, float zoomPercent,
		const std::string& i18nKey, float fontSize, textAlign textAlign,
		raylib::Color textColor, float textSpacing, const std::function<void()>& function,
		const std::string& clickSound = "button_click.wav");

	void draw() override;
	ButtonText* clone() const override;

	const Text& getText() const { return this->text; }
};

