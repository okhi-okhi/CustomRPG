#pragma once
#include <string>
#include <vector>
#include <map>
#include "../Utils/Singleton.h"

using std::string;

struct Language {
	string id;
	string name;
	Language() : id("NONE"), name("NONE") {}
	Language(string id, string name) : id(std::move(id)), name(std::move(name)) {}
};

class I18n : public Singleton<I18n>
{
private:
	std::vector<Language> languages;

	Language defaultLanguage;
	Language currentLanguage;

	std::map<string, string> translation;
	std::map<string, string> fallbackTranslation;

	string replaceKeyInString(string str) const;
	static string getLanguageName(const string& fileName);

public:
	explicit I18n(token){}
	void init(const string& currentLanguage, const string& defaultLanguage);
	bool loadLanguage(string fileName);
	void loadDefaultLanguage(string fileName);

	string get(const string& key) const;
	string get(const string& key, const std::map<string, string>& args) const;

	const Language& getCurrentLanguage() const { return this->currentLanguage; }
	const std::vector<Language>& getLanguage() const { return this->languages; }
};

