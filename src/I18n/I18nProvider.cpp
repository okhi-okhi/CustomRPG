#include "I18nProvider.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <json.hpp>
#include "../Utils/Utilities.h"

void I18nProvider::init(const string& langsFilePaths, const string& currentLanguage, const string& defaultLanguage) {
	namespace fs = std::filesystem;

	this->langsFilePaths = langsFilePaths;
	for (const auto& langFile : fs::directory_iterator(this->langsFilePaths))
	{
		string id = langFile.path().stem().string();
		this->languages.emplace_back(id, getLanguageName(id));
	}
	if (!loadLanguage(currentLanguage)) {
		std::cout << "Fallback to default language: "<< this->defaultLanguage.name << std::endl;
		this->currentLanguage = this->defaultLanguage;
	}
	loadDefaultLanguage(defaultLanguage);
}

string I18nProvider::getLanguageName(const string& fileName) const
{
	using json = nlohmann::json;

	json j = Utils::readJsonFile(this->langsFilePaths + fileName);
	try {
		return j["name"];
	}
	catch (json::exception& e)
	{
		std::cout << "ERROR! Conversion failed while reading " << fileName << std::endl;
		std::cout << e.what() << std::endl;
		return "Invalid";
	}
}

bool I18nProvider::loadLanguage(const string& fileName) {
	using json = nlohmann::json;

	std::ifstream inFile(this->langsFilePaths + fileName + ".json");
	if (!inFile.good()) 
	{
		std::cout << "Couldn't find file:" << this->langsFilePaths
			<< fileName << ".json" << std::endl;
		return false;
	}
	json j = json::parse(inFile);
	try {
		this->currentLanguage = Language(fileName, j["name"]);

		j = j.flatten();
		json j2;
		for (const auto& item : j.items())
		{
			std::string s = item.key();
			s.erase(0, 1);
			j2[s] = item.value();
		}
		this->currentTranslation = j2.get<std::map<string, string>>();
	}
	catch (json::exception& e)
	{
		std::cout << "ERROR! Conversion failed while reading " << fileName << std::endl;
		std::cout << e.what() << std::endl;
		inFile.close();
		return false;
	}
	inFile.close();
	return true;
}

void I18nProvider::loadDefaultLanguage(const string& fileName) {
	using json = nlohmann::json;
	std::ifstream inFile(this->langsFilePaths + fileName + ".json");
	if (!inFile.good())
	{
		std::cout << "Couldn't find file:" << this->langsFilePaths
			<< fileName << ".json" << std::endl;
		exit(1);
	}
	try {
		json j = json::parse(inFile);
		this->defaultLanguage = Language(fileName, j["name"]);
		j = j.flatten();
		for (const auto& item : j.items())
		{
			std::string s = item.key();
			s.erase(0, 1);
			this->defaultTranslation[s] = item.value();
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
	using std::cout, std::endl;
	std::size_t first = 0;
	std::size_t n = 0;
	for (std::size_t i = 0; i < str.length(); i++) {
		if (str[i] == '|') {
			n++;
			if (n == 1) {
				first = i;
			}
			else if (n == 2) {
				const std::size_t second = i;
				string s = get(str.substr(first + 1, second - first - 1));
				str.replace(first, second - first + 1, s);
				i = i - second + first + s.length() - 1;
			}
			else {
				n = 1;
				first = i;
			}
		}
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

string I18nProvider::get(const string& key) const {
	if (this->currentTranslation.contains(key))
	{
		return replaceKeyInString(this->currentTranslation.find(key)->second);
	}
	// std::cout << "ERROR! Invalid translate key: " << key << std::endl
	// 	<< "Fallback to default language.";
	return getFromDefault(key);
}

string I18nProvider::get(const string& key, const std::map<string, string>& args) const {
	if (this->currentTranslation.contains(key)) 
	{
		return replaceArgInString(replaceKeyInString(this->currentTranslation.find(key)->second), args);
	}
	// std::cout << "ERROR! Invalid translate key: " << key << std::endl
	// 	<< "Fallback to default language.";
	return getFromDefault(key, args);
}

string I18nProvider::getFromDefault(const string& key) const
{
	if (this->defaultTranslation.contains(key)) {
		return replaceKeyInString(this->defaultTranslation.find(key)->second);
	}
	// std::cout << "ERROR! Invalid translate in default language, key: " << key << std::endl;
	return "Invalid";
}

string I18nProvider::getFromDefault(const string& key, const std::map<string, string>& args) const
{
	if (this->defaultTranslation.contains(key))
	{
		return replaceArgInString(replaceKeyInString(this->defaultTranslation.find(key)->second), args);
	}
	// std::cout << "ERROR! Invalid translate in default language, key: " << key << std::endl;
	return "Invalid";
}
