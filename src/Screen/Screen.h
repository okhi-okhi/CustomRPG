#pragma once
#include <string>
#include <vector>
#include "Element.h"

enum class screenTypes
{
	MAIN = 0,
};

class Screen
{
protected:
	screenTypes screenType;
	std::string i18nKey;
	std::vector<Element*> elements;

public:
	Screen() = default;
	explicit Screen(screenTypes screenType, const std::string& i18nKey);
	virtual ~Screen() = default;

	void addElement(const Element& element);

	void draw() const;
	virtual Screen* clone() const = 0;

	const screenTypes& getScreenType() const { return this->screenType; }
	const std::string& getI18nKey() const { return this->i18nKey; }
	const std::vector<Element*>& getElements() const { return this->elements; }
};

