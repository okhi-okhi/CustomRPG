#pragma once
#include <string>
#include "../Utils/Singleton.h"

using std::string;

enum class FileSource
{
	AUTO = 0,
	SYSTEM,
	GAME,
	NONE
};

enum class ResourcesFolder
{
	LANGS,
	FONTS,
	SOUNDS,
	TEXTURES,
	HIGHLIGHT_SCREENSHOTS
};

struct File
{
	FileSource src;
	string name;

	File() : src(FileSource::AUTO) {}
	File(string name) : src(FileSource::AUTO), name(std::move(name)) {}
	File(const FileSource src, string name) : src(src), name(std::move(name)) {}
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
	const string highlightScreenshotsFolder = "highlight_screenshots/";

public:
	explicit PathProvider(token){}
	void setCurrentGamePath(const string& path) { this->currentGamePath = gamesPath + path + '/'; }

	string getFolder(ResourcesFolder folder) const;
	string getFromSystem(ResourcesFolder folder) const;
	string getFromGame(ResourcesFolder folder) const;
	string get(FileSource parentFolder, ResourcesFolder folder, const string& fileName) const;
	string get(const File& file, ResourcesFolder folder) const;

	string getConfigPath() const { return this->configPath; }
	string getGamesPath() const { return this->gamesPath; }
	string getResourcesPath() const { return this->resourcesPath; }
	string getCurrentGamePath() const { return this->currentGamePath; }
};

