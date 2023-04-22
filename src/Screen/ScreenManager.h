#pragma once
#include "Screen.h"
#include "../Utils/Singleton.h"

class ScreenManager : public Singleton<ScreenManager>
{
private:
	std::vector<Screen*> allScreens;
	std::vector<Screen*> currentScreens;
public:
	explicit ScreenManager(token) {}

	void init();

	void addScreen(const screenTypes& screen);
	void removeScreen(const screenTypes& screen);
	void clear();

	void draw() const;

	void updateHitbox() const;

	const std::vector<Screen*>& getCurrentScreens() const { return this->currentScreens; }
};

