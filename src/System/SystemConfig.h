#pragma once
#include <string>
#include "../Utils/Singleton.h"

class SystemConfig : public Singleton<SystemConfig>
{
private:
	int masterVolume;
	std::string defaultLanguage;
	std::string currentLanguage;

public:
	explicit SystemConfig(token) : masterVolume(100), defaultLanguage("en_US"), currentLanguage("en_US") {}

	void load(const std::string& fileName);

	int& getMasterVolume() { return this->masterVolume; }
	const std::string& getDefaultLanguage() const { return this->defaultLanguage; }
	const std::string& getCurrentLanguage() const { return this->currentLanguage; }

	void setMasterVolume(const float& volume) { this->masterVolume = volume; }
	void setCurrentLanguage(const std::string& lang) { this->currentLanguage = lang; }
};

