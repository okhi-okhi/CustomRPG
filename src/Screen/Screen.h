#pragma once
#include <vector>
#include "ButtonArg.h"

class Screen
{
private:
	Texture2D backGround;
	std::string i18nKey;
	std::vector<Element*> elements;

public:
	Screen() = default;
	explicit Screen(const std::string& bgFileName, const std::string& i18nKey);

	void addElement(const Element& element);

	void draw() const;
};

