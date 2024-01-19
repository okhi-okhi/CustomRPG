#pragma once
#include <string>

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

	File() : src(FileSource::AUTO), name("Invalid") {}
	File(string name) : src(FileSource::AUTO), name(std::move(name)) {}
	File(const FileSource src, string name) : src(src), name(std::move(name)) {}
};

class PathProvider
{
private:
	//Global path
	inline static const string configPath = "config.json";
	inline static const string playerPath = "players.json";
	inline static const string gamesPath = "games/";
	inline static const string resourcesPath = "resources/";
	inline static string currentGamePath;
	//Folders
	inline static const string langsFolder = "langs/";
	inline static const string fontsFolder = "fonts/";
	inline static const string soundsFolder = "sounds/";
	inline static const string texturesFolder = "textures/";
	inline static const string highlightScreenshotsFolder = "highlight_screenshots/";

	PathProvider() = default;

public:
	static void setCurrentGamePath(const string& path) { currentGamePath = path; }

	static string getFolder(ResourcesFolder folder);
	static string getFromSystem(ResourcesFolder folder);
	static string getFromGame(ResourcesFolder folder);
	static string get(FileSource parentFolder, ResourcesFolder folder, const string& fileName);
	static string get(const File& file, ResourcesFolder folder);

	static string getConfigPath() { return configPath; }
	static string getPlayerPath() { return playerPath; }
	static string getGamesPath() { return gamesPath; }
	static string getResourcesPath() { return resourcesPath; }
	static string getCurrentGamePath() { return currentGamePath; }
};

