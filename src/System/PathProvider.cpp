#include "PathProvider.h"
#include <filesystem>
#include "Exceptions.hpp"

std::string PathProvider::getFolder(const ResourcesFolder folder) const
{
	switch (folder)
	{
	case ResourcesFolder::LANGS:
		return this->langsFolder;
	case ResourcesFolder::FONTS:
		return this->fontsFolder;
	case ResourcesFolder::SOUNDS:
		return this->soundsFolder;
	case ResourcesFolder::TEXTURES:
		return this->texturesFolder;
	case ResourcesFolder::HIGHLIGHT_SCREENSHOTS:
		return this->highlightScreenshotsFolder;
	}
	return {};
}

std::string PathProvider::getFromSystem(const ResourcesFolder folder) const
{
	return this->resourcesPath + getFolder(folder);
}

std::string PathProvider::getFromGame(const ResourcesFolder folder) const
{
	return this->currentGamePath + getFolder(folder);
}

std::string PathProvider::get(const FileSource parentFolder, const ResourcesFolder folder, const std::string& fileName) const
{
	switch (parentFolder)
	{
		case FileSource::AUTO:
			if (!currentGamePath.empty() && std::filesystem::exists(getFromGame(folder) + fileName))
			{
				return getFromGame(folder) + fileName;
			}
			if (std::filesystem::exists(getFromSystem(folder) + fileName))
			{
				return getFromSystem(folder) + fileName;
			}
			throw InvalidFileException(getFromSystem(folder) + fileName);

		case FileSource::SYSTEM:
			return getFromSystem(folder) + fileName;

		case FileSource::GAME:
			return getFromGame(folder) + fileName;

		case FileSource::NONE:
			return fileName;
	}
	return {};
}

string PathProvider::get(const File& file, const ResourcesFolder folder) const
{
	return get(file.src, folder, file.name);
}
