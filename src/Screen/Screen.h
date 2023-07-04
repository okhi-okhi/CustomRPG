#pragma once
#include <string>
#include <vector>
#include "Button.h"
#include "ElementGroup.h"

enum class ScreenType
{
	MAIN = 0,
	SETTING,
	LANGUAGE,
	SELECT_GAME,
};

class Screen
{
protected:
	ScreenType screenType;
	std::string i18nKey;
	std::vector<shared_ptr<Element>> elements;
	std::vector<std::pair<int, shared_ptr<Button>>> buttons;

public:
	Screen() = default;
	explicit Screen(ScreenType screenType, const std::string& i18nKey);
	virtual ~Screen() = default;

	void addElement(const shared_ptr<Element>& element);
	void addButton(const shared_ptr<Button>& button);
	void addElementGroup(const shared_ptr<ElementGroup>& elementGroup);

	void draw() const;

	const ScreenType& getScreenType() const { return this->screenType; }
	const std::string& getI18nKey() const { return this->i18nKey; }
	const std::vector<shared_ptr<Element>>& getElements() const { return this->elements; }
	const std::vector<std::pair<int, shared_ptr<Button>>>& getButtons() const { return this->buttons; }
};

