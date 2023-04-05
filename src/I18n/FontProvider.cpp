#include "FontProvider.h"
#include "../System/PathProvider.h"
#include "../System/Exceptions.hpp"
#include "../Utils/Utilities.h"
#include "../Utils/RaylibUtils.h"

void FontProvider::loadSystemFont()
{
	this->systemFont.defaultFont = loadFont(I18n::instance().getSystemI18n().getDefaultLanguage(), PathProvider::instance().getResourcesPath());
	this->systemFont.currentFont = loadFont(I18n::instance().getSystemI18n().getCurrentLanguage(), PathProvider::instance().getResourcesPath());
}

void FontProvider::loadGameFont()
{
	this->gameFont.defaultFont = loadFont(I18n::instance().getGameI18n().getDefaultLanguage(), PathProvider::instance().getCurrentGamePath());
	this->gameFont.currentFont = loadFont(I18n::instance().getGameI18n().getCurrentLanguage(), PathProvider::instance().getCurrentGamePath());
}

raylib::Font FontProvider::loadFont(const Language& lang, const std::string& rootPath)
{
	using nlohmann::json;

	string str;
	for (const auto& value : lang.translation | std::views::values)
	{
		str.append(value);
	}

	json j = Utils::readJsonFile(rootPath + PathProvider::instance().getLangsPath() + lang.info.id);
	try {
		return RaylibUtils::getContainTextFont(rootPath + PathProvider::instance().getFontsPath() + j["font"].get<string>(), str);
	}
	catch (json::exception& e)
	{
		throw BadValueException(lang.info.id, e.what());
	}
}

const raylib::Font& FontProvider::get(const std::string& key) const
{
	if(I18n::instance().getGameI18n().getCurrentLanguage().translation.contains(key))
	{
		return this->gameFont.currentFont;
	}
	if (I18n::instance().getGameI18n().getDefaultLanguage().translation.contains(key))
	{
		return this->gameFont.defaultFont;
	}
	if (I18n::instance().getSystemI18n().getCurrentLanguage().translation.contains(key))
	{
		return this->systemFont.currentFont;
	}
	if (I18n::instance().getSystemI18n().getDefaultLanguage().translation.contains(key))
	{
		return this->systemFont.defaultFont;
	}
	return this->defaultFont;
}
