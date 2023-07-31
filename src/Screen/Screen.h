#pragma once
#include <string>
#include <vector>
#include "Element.h"

using std::shared_ptr, std::make_shared;

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

public:
	Screen() = default;
	explicit Screen(ScreenType screenType, const std::string& i18nKey);
	virtual ~Screen() = default;

	void addElement(const shared_ptr<Element>& element);

	void draw() const;
	void update() const;

	const ScreenType& getScreenType() const { return this->screenType; }
	const std::string& getI18nKey() const { return this->i18nKey; }
	const std::vector<shared_ptr<Element>>& getElements() const { return this->elements; }
};

