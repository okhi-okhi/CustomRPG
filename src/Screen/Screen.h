#pragma once
#include <string>
#include <vector>
#include "Button.h"

class Screen
{
private:
	Texture2D backGround;
	std::string i18nKey;
	std::vector<Button> buttons;

public:
	Screen() = default;
	explicit Screen(const std::string& bgFileName, const std::string& i18nKey);

	void addButton(const Button& button);

	void draw();
};

