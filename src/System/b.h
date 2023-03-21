#pragma once
#include <string>
#include "../Utils/Singleton.h"

class SystemConfig : public Singleton<SystemConfig>
{
private:
	//system
	std::string defaultLanguage;
	std::string currentLanguage;

public:
	explicit SystemConfig(token) : defaultLanguage("en_US"), currentLanguage("en_US") {}

	void load(const std::string& fileName);

	//system
	const std::string& getDefaultLanguage() const { return this->defaultLanguage; }
	const std::string& getCurrentLanguage() const { return this->currentLanguage; }

	void setCurrentLanguage(const std::string& lang) { this->currentLanguage = lang; }
};

