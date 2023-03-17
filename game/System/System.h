#pragma once
#include "../Utils/Singleton.h"
#include "../Player/Player.h"

class System : public Singleton<System>{
private:
	std::string configPath = "config.json";
	int choice;
	bool playing;

	int activePlayer;
	std::vector<Player> players;

public:
	explicit System(token) : choice(0), playing(true), activePlayer(0) {}

	void init();

	void systemMenu();
	void settingMenu();
	//Main Menu
	void createNewPlayer();
	void selectPlayer();
	void savePlayers();
	void loadPlayers();
	//Setting Menu
	void selectLanguage();

	const bool& getPlaying() const { return this->playing; }
	Player& getPlayer() { return this->players[activePlayer]; }
};

