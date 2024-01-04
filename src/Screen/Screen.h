#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Element.h"

enum class ScreenType
{
	//System
	MAIN = 0,
	SETTING,
	LANGUAGE,
	SELECT_GAME,
	//Game
	SELECT_PLAYER,
	GAME_MAIN,
	PLAYER_INFO,
};

struct DisplayElement
{
	int order;
	shared_ptr<Element> element;

	DisplayElement(const int order, const shared_ptr<Element>& element) : order(order), element(element) {}
};

class Screen
{
protected:
	ScreenType screenType;
	string i18nKey;
	vector<DisplayElement> elements;

public:
	explicit Screen(ScreenType screenType, const string& i18nKey);

	void addElement(const shared_ptr<Element>& element);
	void removeElement(const shared_ptr<Element>& element);
	void setOrder(const shared_ptr<Element>& element, int order);

	void sortElements();
	void draw() const;
	void update() const;

	const ScreenType& getScreenType() const { return this->screenType; }
	const string& getI18nKey() const { return this->i18nKey; }
	const vector<DisplayElement>& getElements() const { return this->elements; }
};

