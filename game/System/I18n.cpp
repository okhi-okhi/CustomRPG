#include "I18n.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <json.hpp>
#include "../Utils/Utilities.h"

void I18n::init(const string& currentLanguage, const string& defaultLanguage) {
	namespace fs = std::filesystem;

	const string langDirectory = "Langs/";
	for (const auto& langFile : fs::directory_iterator(langDirectory)) {
		string id = langFile.path().stem().string();
		this->languages.emplace_back(id, getLanguageName(id));
	}

	loadDefaultLanguage(defaultLanguage);

	if (!loadLanguage(currentLanguage)) {
		std::cout << "Fallback to default language..." << std::endl;
		this->currentLanguage = this->defaultLanguage;
	}
}

string I18n::getLanguageName(const string& fileName)
{
	using json = nlohmann::json;
	json j = Utils::readJsonFile("Langs/" + fileName);
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

bool I18n::loadLanguage(string fileName) {
	using json = nlohmann::json;
	const string id = fileName;
	fileName = "Langs/" + fileName + ".json";
	std::ifstream inFile(fileName);
	if (!inFile.good()) {
		std::cout << "Can't find file:"  << fileName << std::endl;
		return false;
	}
	try {
		json j = json::parse(inFile);
		this->currentLanguage = Language(id, j["name"]);
		j = j.flatten();
		json j2;
		for (const auto& item : j.items())
		{
			std::string s = item.key();
			s.erase(0, 1);
			j2[s] = item.value();
		}
		this->translation = j2.get<std::map<string, string>>();
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

void I18n::loadDefaultLanguage(string fileName) {
	using json = nlohmann::json;
	const string id = fileName;
	fileName = "Langs/" + fileName + ".json";
	std::ifstream inFile(fileName);
	if (!inFile.good()) {
		std::cout << "Can't find file:" << fileName << std::endl;
		exit(1);
	}
	try {
		json j = json::parse(inFile);
		this->currentLanguage = Language(id, j["name"]);
		j = j.flatten();
		for (const auto& item : j.items())
		{
			std::string s = item.key();
			s.erase(0, 1);
			this->fallbackTranslation[s] = item.value();
		}
	}
	catch (json::exception& e)
	{
		std::cout << "ERROR! Conversion failed while reading " << fileName << std::endl;
		std::cout << e.what() << std::endl;
		inFile.close();
		exit(8);
	}
	inFile.close();
}

string I18n::replaceKeyInString(string str)const{
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

string I18n::get(const string& key) const {
	if (this->translation.contains(key)) {
		return replaceKeyInString(this->translation.find(key)->second);
	}
	std::cout << "ERROR! Invalid translate key: " << key << std::endl;
	return "Invalid";
}

string I18n::get(const string& key, const std::map<string, string>& args) const {
	if (this->translation.contains(key)) {
		string str = replaceKeyInString(this->translation.find(key)->second);
		for (const auto& [fst, snd] : args) {
			const size_t startPos = str.find('%' + fst + '%');
			if (startPos != std::string::npos) {
				str.replace(startPos, fst.length()+2, snd);
			}
			else {
				std::cout<< "ERROR! Can't find arg: %" << fst <<"% in "<< str << std::endl;
			}
		}
		return str;
	}
	std::cout << "ERROR! Invalid translate key: " << key << std::endl;
	return "Invalid";
}
