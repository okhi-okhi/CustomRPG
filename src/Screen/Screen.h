#pragma once
#include <string>
#include <vector>
#include "Element.h"

class Screen
{
protected:
	std::string i18nKey;
	std::vector<Element*> elements;

public:
	Screen() = default;
	explicit Screen(const std::string& i18nKey);

	void addElement(const Element& element);

	void draw() const;
};

