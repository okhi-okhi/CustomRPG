#pragma once
#include <string>
#include "../Utils/Singleton.h"

class PathProvider : public Singleton<PathProvider>
{
private:
	const std::string langsPath = "Langs/";
	const std::string fontsPath = "Fonts/";

	std::string currentGamePath;
	const std::string gamesPath = "games/";
	const std::string gameLangPath = currentGamePath + langsPath;
	const std::string gameFontPath = currentGamePath + fontsPath;

	const std::string resourcesPath = "resources/";
	const std::string systemLangPath = resourcesPath + langsPath;
	const std::string systemFontPath = resourcesPath + fontsPath;

public:
	explicit PathProvider(token){}
	void setCurrentGamePath(const std::string& path) { this->currentGamePath = path; }

	std::string getLangsPath() const { return this->langsPath; }
	std::string getFontsPath() const { return this->fontsPath; }

	std::string getCurrentGamePath() const { return this->currentGamePath; }
	std::string getGamesPath() const { return this->gamesPath; }
	std::string getGameLangPath() const { return this->gameLangPath; }
	std::string getGameFontPath() const { return this->gameFontPath; }

	std::string getResourcesPath() const { return this->resourcesPath; }
	std::string getSystemLangPath() const { return this->systemLangPath; }
	std::string getSystemFontPath() const { return this->systemFontPath; }
};

