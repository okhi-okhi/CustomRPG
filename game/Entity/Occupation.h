#pragma once
#include <json.hpp>
#include "../System/I18n.h"
using json = nlohmann::json;

class Occupation
{
private:
	std::string id;
	std::string name;
	std::string description;
	int hpMaxScale;
	int manaMaxScale;
	int luckScale;
	int talentPointScale;

	//std::vector<Passive> passives
	//std::vector<Magic> magics

	static float readValue(const json& j);
	std::string readString(const std::string& key) const;

public:
	Occupation() : hpMaxScale(0), manaMaxScale(0), luckScale(0), talentPointScale(0) {}

	explicit Occupation(const std::string& fileName);
	void print() const;
	void debugPrint() const;

	const std::string& getId() const { return this->id; }
	std::string getName() const { return I18n::instance().get(this->name); }
	std::string getDescription() const { return I18n::instance().get(this->description); }
	const int& getHpMaxScale()const { return this->hpMaxScale; }
	const int& getManaMaxScale()const { return this->manaMaxScale; }
	const int& getLuckScale()const { return this->luckScale; }
	const int& getTalentPointScale()const { return this->talentPointScale; }
};

