#pragma once
#include <string>
#include <vector>
#include "Button.h"
#include "ElementGroup.h"

enum class screenTypes
{
	MAIN = 0,
	SETTING,
	LANGUAGE,
};

class Screen
{
protected:
	screenTypes screenType;
	std::string i18nKey;
	std::vector<shared_ptr<Element>> elements;
	std::vector<std::pair<int, Clickable*>> clickableElements;

public:
	Screen() = default;
	explicit Screen(screenTypes screenType, const std::string& i18nKey);
	virtual ~Screen() = default;

	void addElement(Element* element);
	void addElement(Button* button);
	void addElement(ElementGroup* elementGroup);

	void draw() const;

	const screenTypes& getScreenType() const { return this->screenType; }
	const std::string& getI18nKey() const { return this->i18nKey; }
	const std::vector<Element*>& getElements() const { return this->elements; }
	const std::vector<std::pair<int, Clickable*>>& getClickableElements() const { return this->clickableElements; }
};

