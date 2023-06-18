#pragma once
#include "Screen.h"
#include "../Utils/Singleton.h"

class ScreenManager : public Singleton<ScreenManager>
{
private:
	std::vector<shared_ptr<Screen>> allScreens;
	std::vector<shared_ptr<Screen>> currentScreens;
	bool needReload;

public:
	explicit ScreenManager(token) : needReload(false) {}

	void init();
	void loadAllScreen();
	void reloadAllScreen();
	void delayReload();

	void addScreen(const screenTypes& screen);
	void removeScreen(const screenTypes& screen);
	void clear();
		
	void draw();

	void updateHitbox() const;

	const std::vector<shared_ptr<Screen>>& getCurrentScreens() const { return this->currentScreens; }
};

