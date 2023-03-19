#pragma once
#include <string>
#include <vector>
#include <map>

using std::string;

struct Language {
	string id;
	string name;
	Language() : id("NONE"), name("NONE") {}
	Language(string id, string name) : id(std::move(id)), name(std::move(name)) {}
};

class I18nProvider
{
private:
	string langsFilePaths;
	std::vector<Language> languages;

	Language defaultLanguage;
	Language currentLanguage;

	std::map<string, string> currentTranslation;
	std::map<string, string> defaultTranslation;

	string replaceKeyInString(string str) const;
	string replaceArgInString(string str, const std::map<string, string>& args) const;
	string getLanguageName(const string& fileName) const;

public:
	explicit I18nProvider() = default;
	void init(const string& langsFilePaths, const string& currentLanguage, const string& defaultLanguage);

	bool loadLanguage(const string& fileName);
	void loadDefaultLanguage(const string& fileName);

	string get(const string& key) const;
	string get(const string& key, const std::map<string, string>& args) const;

	string getFromDefault(const string& key) const;
	string getFromDefault(const string& key, const std::map<string, string>& args) const;

	const Language& getCurrentLanguage() const { return this->currentLanguage; }
	const std::vector<Language>& getLanguages() const { return this->languages; }
};

