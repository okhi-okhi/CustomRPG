#pragma once
#include <string>
#include <vector>
#include <memory>
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
	string i18nKey;
	vector<shared_ptr<Element>> elements;

public:
	explicit Screen(ScreenType screenType, const string& i18nKey);

	void addElement(const shared_ptr<Element>& element);
	void removeElement(const std::string& id);
	void showElement(const std::string& id) const;
	void hiddenElement(const std::string& id) const;

	void draw() const;
	void update() const;

	const ScreenType& getScreenType() const { return this->screenType; }
	const string& getI18nKey() const { return this->i18nKey; }
	const vector<shared_ptr<Element>>& getElements() const { return this->elements; }
};

