#pragma once
#include <string>
#include "../Utils/Singleton.h"

using std::string;

enum class ParentFolder
{
	AUTO = 0,
	SYSTEM,
	GAME,
	NONE
};

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
	const string configPath = "config.json";
	const string gamesPath = "games/";
	const string resourcesPath = "resources/";
	string currentGamePath;
	//Folders
	const string langsFolder = "langs/";
	const string fontsFolder = "fonts/";
	const string soundsFolder = "sounds/";
	const string texturesFolder = "textures/";

public:
	explicit PathProvider(token){}
	void setCurrentGamePath(const string& path) { this->currentGamePath = gamesPath + path + '/'; }

	string getFolder(resourcesFolder folder) const;
	string getFromSystem(resourcesFolder folder) const;
	string getFromGame(resourcesFolder folder) const;
	string get(ParentFolder parentFolder, resourcesFolder folder, const string& fileName) const;

	string getConfigPath() const { return this->configPath; }
	string getGamesPath() const { return this->gamesPath; }
	string getResourcesPath() const { return this->resourcesPath; }
	string getCurrentGamePath() const { return this->currentGamePath; }
};

