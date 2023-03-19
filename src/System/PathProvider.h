#pragma once
#include <string>
#include "../Utils/Singleton.h"

class PathProvider : public Singleton<PathProvider>
{
private:
	std::string currentGamePath;
	const std::string gamesPath = "games/";
	const std::string gameLangPath = gamesPath + "Langs/";

	const std::string resourcesPath = "resources/";
	const std::string systemLangPath = resourcesPath + "Langs/";

public:
	explicit PathProvider(token){}
	void setCurrentGamePath(const std::string& path) { this->currentGamePath = path; }

	std::string getCurrentGamePath() const { return this->currentGamePath; }
	std::string getGamesPath() const { return this->gamesPath; }
	std::string getGameLangPath() const { return this->gameLangPath; }

	std::string getResourcesPath() const { return this->resourcesPath; }
	std::string getSystemLangPath() const { return this->systemLangPath; }
};

