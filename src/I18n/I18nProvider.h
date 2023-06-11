#pragma once
#include <Font.hpp>
#include <string>
#include <vector>
#include <map>

using std::string;

struct LanguageInfo {
	string id;
	string name;
	raylib::Font font;
	LanguageInfo() = default;
	LanguageInfo(string id, string name, raylib::Font font) : id(std::move(id)), name(std::move(name)), font(std::move(font)) {}
};

struct Language {
	LanguageInfo info;
	std::map<string, string> translation;
	Language() = default;
	Language(LanguageInfo lang, std::map<string, string> translation) :
		info(std::move(lang)), translation(std::move(translation)) {}
};

class I18nProvider
{
private:
	string langsFolder;
	string fontsFolder;
	std::vector<LanguageInfo> languages;

	Language defaultLanguage;
	Language currentLanguage;

	string replaceKeyInString(string str) const;
	string replaceArgInString(string str, const std::map<string, string>& args) const;
	LanguageInfo getLanguageInfo(const string& fileName) const;

public:
	explicit I18nProvider() = default;
	void init(const string& resourceFolder, const string& currentLanguage, const string& defaultLanguage);

	bool loadLanguage(const string& fileName);
	void loadDefaultLanguage(const string& fileName);

	string get(const string& key) const;
	string get(const string& key, const std::map<string, string>& args) const;

	string getFromDefault(const string& key) const;
	string getFromDefault(const string& key, const std::map<string, string>& args) const;

	const Language& getDefaultLanguage() const { return this->defaultLanguage; }
	const Language& getCurrentLanguage() const { return this->currentLanguage; }
	const std::vector<LanguageInfo>& getLanguages() const { return this->languages; }
};

