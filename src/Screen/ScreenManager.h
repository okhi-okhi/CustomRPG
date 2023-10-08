#pragma once
#include "Screen.h"
#include "../Utils/Singleton.h"

class ScreenManager : public Singleton<ScreenManager>
{
private:
	vector<shared_ptr<Screen>> allScreens;
	vector<shared_ptr<Screen>> currentScreens;
	bool needReload;
	bool clicked;

public:
	explicit ScreenManager(token) : needReload(false), clicked(false) {}

	void init();
	void loadAllScreen();
	void reloadAllScreen();
	void delayReload();

	void showScreen(const ScreenType& screen);
	void hiddenScreen(const ScreenType& screen);
	void clear();
		
	void draw();
	void update();

	void setClicked(const bool& clicked) { this->clicked = clicked; }

	const std::vector<shared_ptr<Screen>>& getCurrentScreens() const { return this->currentScreens; }
	const bool& isNeedReload() const { return this->needReload; }
	const bool& isClicked() const { return this->clicked; }
};

