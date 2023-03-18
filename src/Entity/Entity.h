#pragma once
class Statu;
#include <json.hpp>
#include "../Statu/Statu.h"
#include "../System/I18n.h"
using ordered_json = nlohmann::ordered_json;
using json = nlohmann::json;
//#include"Magic/Magic.h"

enum class Faction { ALLY = 0, ENEMY};

class Entity
{
protected:
	Faction faction;
	std::string id;
	std::string name;
	int level;

	int hp;
	int hpMax;
	int mana;
	int manaMax;
	int atk;
	int defense;

	std::map<std::string, int> talents;

	std::vector<Statu> Status;

	virtual float readValue(const json& j) const = 0;
	virtual std::string readString(const std::string& key) const = 0;

public:
	Entity() : faction(Faction::ALLY), id("NONE"), level(0), hp(0), hpMax(0), mana(0),
	           manaMax(0), atk(0), defense(0){}
	Entity(const Faction& faction, std::string id, std::string name, const int& level,
			const int& hp, const int& mana, std::map<std::string, int> talents) :
		faction(faction), id(std::move(id)), name(std::move(name)), level(level),
		hp(hp), hpMax(hp), mana(mana), manaMax(mana), atk(0), defense(0), talents(std::move(talents)) {}
	virtual ~Entity() = default;

	void takeDamage(int damage);
	bool isAlive() const { return this->hp > 0; }

	virtual void print() const;
	virtual void debugPrint() const;

	static std::string getTalentName(const std::string& talent);

	void modifyStat(const std::string& key, const int& value);

	const std::string& getId() const { return this->id; }
	std::string getName() const { return I18n::instance().get(this->name); }
	const int& getLevel()const { return this->level; }
	const int& getHp()const { return this->hp; }
	const int& getHpMax()const { return this->hpMax; }
	const int& getMana()const { return this->mana; }
	const int& getManaMax()const { return this->manaMax; }
	const int& getAtk()const { return this->atk; }
	const int& getDefense()const { return this->defense; }

	const int& getTalent(const std::string& key) const;

	const Faction& getFraction()const { return this->faction; }
};

