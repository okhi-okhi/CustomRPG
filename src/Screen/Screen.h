#pragma once
#include <vector>
#include "ButtonArg.h"

class Screen
{
private:
	Texture2D backGround;
	std::string i18nKey;
	std::vector<Button> buttons;
	std::vector<ButtonArg> buttonArgs;

public:
	Screen() = default;
	explicit Screen(const std::string& bgFileName, const std::string& i18nKey);

	void addButton(const Button& button);
	void addButton(const ButtonArg& buttonArg);

	void draw();
};

