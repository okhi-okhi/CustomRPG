#include "FontProvider.h"
#include "I18n.h"
#include "../System/PathProvider.h"
#include "../System/Exceptions.hpp"
#include "../Utils/Utilities.h"
#include "../Utils/RaylibUtils.h"

void FontProvider::loadSystemFont(const std::string& currentLanguage, const std::string& defaultLanguage)
{
	using nlohmann::json;

	string str;
	for (const auto& value : I18n::instance().getSystemI18n().getDefaultLanguage().translation | std::views::values)
	{
		str.append(value);
	}

	json j = Utils::readJsonFile(PathProvider::instance().getSystemLangPath() + defaultLanguage);
	try {
		this->systemFont.defaultFont = RaylibUtils::getContainTextFont(
			PathProvider::instance().getSystemFontPath() + j["font"].get<string>(), str);
	}
	catch (json::exception& e)
	{
		throw BadValueException(defaultLanguage, e.what());
	}

	str = "";
	for (const auto& value : I18n::instance().getSystemI18n().getCurrentLanguage().translation | std::views::values)
	{
		str.append(value);
	}

	j = Utils::readJsonFile(PathProvider::instance().getSystemLangPath() + currentLanguage);
	try {
		this->systemFont.currentFont = RaylibUtils::getContainTextFont(
			PathProvider::instance().getSystemFontPath() + j["font"].get<string>(), str);
	}
	catch (json::exception& e)
	{
		throw BadValueException(defaultLanguage, e.what());
	}
}

void FontProvider::loadGameFont(const std::string& currentLanguage, const std::string& defaultLanguage)
{

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
