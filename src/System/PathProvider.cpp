#include "PathProvider.h"
#include <filesystem>
#include "Exceptions.hpp"

std::string PathProvider::getFolder(const resourcesFolder folder) const
{
	switch (folder)
	{
	case resourcesFolder::LANGS:
		return this->langsFolder;
	case resourcesFolder::FONTS:
		return this->fontsFolder;
	case resourcesFolder::SOUNDS:
		return this->soundsFolder;
	case resourcesFolder::TEXTURES:
		return this->texturesFolder;
	}
	return {};
}

std::string PathProvider::getFromSystem(const resourcesFolder folder) const
{
	return this->resourcesPath + getFolder(folder);
}

std::string PathProvider::getFromGame(const resourcesFolder folder) const
{
	return this->currentGamePath + getFolder(folder);
}

std::string PathProvider::get(const resourcesFolder folder, const std::string& fileName) const
{
	if(!currentGamePath.empty() && std::filesystem::exists(getFromGame(folder) + fileName))
	{
		return getFromGame(folder) + fileName;
	}
	if (std::filesystem::exists(getFromSystem(folder) + fileName))
	{
		return getFromSystem(folder) + fileName;
	}
	throw InvalidFileException(getFromSystem(folder) + fileName);
}
