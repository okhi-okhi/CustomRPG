#include "I18n.h"
#include <iostream>
#include "../System/PathProvider.h"

void I18n::loadSystemI18n(const string& currentLanguage, const string& defaultLanguage)
{
	systemI18n.init(PathProvider::instance().getResourcesPath(), currentLanguage, defaultLanguage);
}

void I18n::loadGameI18n(const string& currentLanguage, const string& defaultLanguage)
{
	gameI18n.init(PathProvider::instance().getCurrentGamePath(), currentLanguage, defaultLanguage);
}

string I18n::get(const string& key) const
{
	string gameResult = gameI18n.get(key);
	if(gameResult != "Invalid")
	{
		return gameResult;
	}
	string systemResult = systemI18n.get(key);
	if(systemResult == "Invalid")
	{
		std::cout << "ERROR! Invalid translate key: " << key << std::endl;
	}
	return systemResult;
}

string I18n::get(const string& key, const std::map<string, string>& args) const
{
	string gameResult = gameI18n.get(key, args);
	if (gameResult != "Invalid")
	{
		return gameResult;
	}
	string systemResult = systemI18n.get(key, args);
	if (systemResult == "Invalid")
	{
		std::cout << "ERROR! Invalid translate key: " << key << std::endl;
	}
	return systemResult;
}
