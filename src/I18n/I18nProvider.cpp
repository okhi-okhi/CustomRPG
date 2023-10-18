#include "I18nProvider.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <json.hpp>
#include <regex>
#include "../System/PathProvider.h"
#include "../Utils/RaylibUtils.h"

void I18nProvider::init(const string& resourceFolder, const string& currentLanguage, const string& defaultLanguage)
{
	namespace fs = std::filesystem;

	this->langsFolder = resourceFolder + PathProvider::getFolder(ResourcesFolder::LANGS);
	this->fontsFolder = resourceFolder + PathProvider::getFolder(ResourcesFolder::FONTS);
	for (const auto& langFile : fs::directory_iterator(this->langsFolder))
	{
		string id = langFile.path().stem().string();
		this->languages.emplace_back(getLanguageInfo(id));
	}
	if (!loadLanguage(currentLanguage)) {
		std::cout << "Can't load language: " << currentLanguage << std::endl;
		std::cout << "Fallback to default language: "<< this->defaultLanguage.info.name << std::endl;
		this->currentLanguage = std::move(this->defaultLanguage);
	}
	loadDefaultLanguage(defaultLanguage);
}

LanguageInfo I18nProvider::getLanguageInfo(const string& fileName) const
{
	using json = nlohmann::json;

	std::ifstream inFile(this->langsFolder + fileName + ".json");
	if (!inFile.good())
	{
		std::cout << "Can't find file:" << this->langsFolder
			<< fileName << ".json" << std::endl;
		exit(1);
	}
	json j = json::parse(inFile);
	try {
		return {fileName, j["name"],
			RaylibUtils::getContainTextFont(
				this->fontsFolder + j["font"].get<string>(), j["name"])};
	}
	catch (json::exception& e)
	{
		std::cout << "ERROR! Conversion failed while reading " << fileName << std::endl;
		std::cout << e.what() << std::endl;
		return { "Invalid", "Invalid", raylib::Font()};
	}
}

bool I18nProvider::loadLanguage(const string& fileName)
{
	using json = nlohmann::json;

	std::ifstream inFile(this->langsFolder + fileName + ".json");
	if (!inFile.good()) 
	{
		std::cout << "Can't find file:" << this->langsFolder
			<< fileName << ".json" << std::endl;
		return false;
	}
	json j = json::parse(inFile);
	try {
		this->currentLanguage.info = LanguageInfo(fileName, j["name"],
			RaylibUtils::getContainTextFont(this->fontsFolder + j["font"].get<string>(), j["name"]));

		j = j.flatten();
		json j2;
		for (const auto& item : j.items())
		{
			std::string s = item.key();
			s.erase(0, 1);
			j2[s] = item.value();
		}
		this->currentLanguage.translation = j2.get<std::map<string, string>>();
	}
	catch (json::exception& e)
	{
		std::cout << "ERROR! Conversion failed while reading " << fileName << std::endl;
		std::cout << e.what() << std::endl;
		inFile.close();
		return false;
	}
	inFile.close();

	string str;
	for(const auto& value : this->currentLanguage.translation | std::views::values)
	{
		str.append(value);
	}

	return true;
}

void I18nProvider::loadDefaultLanguage(const string& fileName)
{
	using json = nlohmann::json;
	std::ifstream inFile(this->langsFolder + fileName + ".json");
	if (!inFile.good())
	{
		std::cout << "Can't find file:" << this->langsFolder
			<< fileName << ".json" << std::endl;
		exit(1);
	}
	try {
		json j = json::parse(inFile);
		this->defaultLanguage.info = LanguageInfo(fileName, j["name"],
			RaylibUtils::getContainTextFont(this->fontsFolder + j["font"].get<string>(), j["name"]));
		j = j.flatten();
		for (const auto& item : j.items())
		{
			std::string s = item.key();
			s.erase(0, 1);
			this->defaultLanguage.translation[s] = item.value();
		}
	}
	catch (json::exception& e)
	{
		std::cout << "ERROR! Conversion failed while reading default language: " << fileName << std::endl;
		std::cout << e.what() << std::endl;
		inFile.close();
		exit(8);
	}
	inFile.close();
}

string I18nProvider::replaceKeyInString(string str) const
{
	const std::regex pattern(R"(\|(.+?)\|)");
	std::smatch match;
	while (std::regex_search(str, match, pattern)) {
		std::string s = get(match[1]);
		str.replace(match.position(), match.length(), s);
	}
	return str;
}

string I18nProvider::replaceArgInString(string str, const std::map<string, string>& args) const
{
	for (const auto& [fst, snd] : args) {
		const size_t startPos = str.find('%' + fst + '%');
		if (startPos != std::string::npos) {
			str.replace(startPos, fst.length() + 2, snd);
		}
		else {
			std::cout << "ERROR! Can't find arg: %" << fst << "% in " << str << std::endl;
		}
	}
	return str;
}

string I18nProvider::get(const string& key) const
{
	if (this->currentLanguage.translation.contains(key))
	{
		return replaceKeyInString(this->currentLanguage.translation.find(key)->second);
	}
	// std::cout << "ERROR! Invalid translate key: " << key << std::endl
	// 	<< "Fallback to default language.";
	return getFromDefault(key);
}

string I18nProvider::get(const string& key, const std::map<string, string>& args) const
{
	if (this->currentLanguage.translation.contains(key))
	{
		return replaceArgInString(replaceKeyInString(this->currentLanguage.translation.find(key)->second), args);
	}
	// std::cout << "ERROR! Invalid translate key: " << key << std::endl
	// 	<< "Fallback to default language.";
	return getFromDefault(key, args);
}

string I18nProvider::getFromDefault(const string& key) const
{
	if (this->defaultLanguage.translation.contains(key)) {
		return replaceKeyInString(this->defaultLanguage.translation.find(key)->second);
	}
	// std::cout << "ERROR! Invalid translate in default language, key: " << key << std::endl;
	return "Invalid";
}

string I18nProvider::getFromDefault(const string& key, const std::map<string, string>& args) const
{
	if (this->defaultLanguage.translation.contains(key))
	{
		return replaceArgInString(replaceKeyInString(this->defaultLanguage.translation.find(key)->second), args);
	}
	// std::cout << "ERROR! Invalid translate in default language, key: " << key << std::endl;
	return "Invalid";
}
