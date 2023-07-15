#pragma once
#include "TextBox.h"
#include "TextArg.h"

class TextArgBox final : public TextBox, public TextArg
{
public:
	TextArgBox() = default;
	TextArgBox(raylib::Rectangle bounds, const std::string& i18nKey,
		const std::map<std::string, argTypes>& args, float fontSize,
		TextAlign align, float spacing);

	void draw() override;
	void updatePosition() override;
};

