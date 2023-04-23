#pragma once
#include <string>
#include "../Utils/Singleton.h"

enum class resourcesFolder
{
	LANGS,
	FONTS,
	SOUNDS,
	TEXTURES,
};

class PathProvider : public Singleton<PathProvider>
{
private:
	//Global path
	const std::string configPath = "config.json";
	const std::string gamesPath = "games/";
	const std::string resourcesPath = "resources/";
	std::string currentGamePath;
	//Folders
	const std::string langsFolder = "langs/";
	const std::string fontsFolder = "fonts/";
	const std::string soundsFolder = "sounds/";
	const std::string texturesFolder = "textures/";

public:
	explicit PathProvider(token){}
	void setCurrentGamePath(const std::string& path) { this->currentGamePath = gamesPath + path + '/'; }

	std::string getFolder(resourcesFolder folder) const;
	std::string getFromSystem(resourcesFolder folder) const;
	std::string getFromGame(resourcesFolder folder) const;
	std::string get(resourcesFolder folder, const std::string& fileName) const;

	std::string getConfigPath() const { return this->configPath; }
	std::string getGamesPath() const { return this->gamesPath; }
	std::string getResourcesPath() const { return this->resourcesPath; }
	std::string getCurrentGamePath() const { return this->currentGamePath; }
};

