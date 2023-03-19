#pragma once
#include <json.hpp>
#include "../I18n/I18n.h"
using json = nlohmann::json;

class Race
{
private:
	std::string id;
	std::string name;
	std::string description;
	int hpMaxBase;
	int manaMaxBase;
	int luckBase;
	
	std::map<std::string, int> talents;

	//std::vector<Passive> passives

	static float readValue(const json& j);
	std::string readString(const std::string& key) const;

public:
	Race() : hpMaxBase(0), manaMaxBase(0), luckBase(0){}

	explicit Race(const std::string& fileName);
	void print() const;
	void debugPrint() const;

	void modifyStat(const std::string& key, const int& value);

	const std::string& getId() const { return this->id; }
	std::string getName() const { return I18n::instance().get(this->name); }
	std::string getDescription() const { return I18n::instance().get(this->description); }
	const int& getHpMaxBase()const { return this->hpMaxBase; }
	const int& getManaMaxBase()const { return this->manaMaxBase; }
	const int& getLuckBase()const { return this->luckBase; }
	const int& getTalent(const std::string& key) const;
	const std::map<std::string, int>& getTalents() const { return this->talents; };
};

