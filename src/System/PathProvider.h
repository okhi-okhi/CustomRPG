#pragma once
#include <string>
#include "../Utils/Singleton.h"

class PathProvider : public Singleton<PathProvider>
{
private:
	const std::string configPath = "config.json";
	const std::string langsPath = "Langs/";
	const std::string fontsPath = "Fonts/";
	const std::string screensPath = "Screens/";

	std::string currentGamePath;
	const std::string gamesPath = "games/";
	const std::string gameLangPath = currentGamePath + langsPath;
	const std::string gameFontPath = currentGamePath + fontsPath;

	const std::string resourcesPath = "resources/";
	const std::string systemLangPath = resourcesPath + langsPath;
	const std::string systemFontPath = resourcesPath + fontsPath;
	const std::string systemScreensPath = resourcesPath + screensPath;

public:
	explicit PathProvider(token){}
	void setCurrentGamePath(const std::string& path) { this->currentGamePath = gamesPath + path + '/'; }

	std::string getConfigPath() const { return this->configPath; }
	std::string getLangsPath() const { return this->langsPath; }
	std::string getFontsPath() const { return this->fontsPath; }
	std::string getScreensPath() const { return this->screensPath; }

	std::string getCurrentGamePath() const { return this->currentGamePath; }
	std::string getGamesPath() const { return this->gamesPath; }
	std::string getGameLangPath() const { return this->gameLangPath; }
	std::string getGameFontPath() const { return this->gameFontPath; }

	std::string getResourcesPath() const { return this->resourcesPath; }
	std::string getSystemLangPath() const { return this->systemLangPath; }
	std::string getSystemFontPath() const { return this->systemFontPath; }
	std::string getSystemScreensPath() const { return this->systemScreensPath; }
};

