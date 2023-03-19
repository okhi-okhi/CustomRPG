#pragma once
#include <string>
#include "I18nProvider.h"
#include "../Utils/Singleton.h"

class I18n : public Singleton<I18n>
{
private:
	I18nProvider systemI18n;
	I18nProvider gameI18n;

public:
	explicit I18n(token){}
	void loadSystemI18n(const string& currentLanguage, const string& defaultLanguage);
	void loadGameI18n(const string& currentLanguage, const string& defaultLanguage);

	string get(const string& key) const;
	string get(const string& key, const std::map<string, string>& args) const;

	I18nProvider& getSystemI18n() { return this->systemI18n; }
	I18nProvider& getGameI18n() { return this->gameI18n; }
};

