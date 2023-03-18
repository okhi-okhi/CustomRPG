#include "Entity.h"
#include "../System/Exceptions.hpp"
#include "../Utils/JsonUtils.h"

void Entity::takeDamage(const int damage)
{
	this->hp -= damage;

	if (this->hp <= 0)
		this->hp = 0;
}

void Entity::print() const {
	using std::cout, std::endl, std::to_string;
	const std::string prefix = "entity.entity.print.";
	cout << I18n::instance().get(prefix + "name",  { {"name"  , this->getName()} }) << endl;
	cout << I18n::instance().get(prefix + "level", { {"level", to_string(this->level)}}) << endl;
}

void Entity::debugPrint() const {
	using std::cout, std::endl, std::to_string;
	const std::string prefix = "entity.entity.debugPrint.";
	cout << I18n::instance().get(prefix + "id", { {"id", this->id} }) << endl;
	print();
}

std::string Entity::getTalentName(const std::string& talent)
{
	return I18n::instance().get("stat.talentName." + talent);
}

void Entity::modifyStat(const std::string& key, const int& value)
{
	std::vector <std::string> modifyKeyMap = 
		{ "level", "hp", "hpMax", "mana", "manaMax", "atk", "defense"};

	for (const auto& talentName : this->talents | std::views::keys) {
		modifyKeyMap.push_back(talentName);
	}

	const auto it = std::ranges::find(modifyKeyMap, key);
	if(it == modifyKeyMap.end()) {
		throw InvalidKeyException(key);
	}
	switch(const auto index = it - modifyKeyMap.begin()) {
	case 0:
		this->level += value;
		if (this->level < 0) this->level = 0;
		break;
	case 1:
		this->hp += value;
		if (this->hp < 0) this->hp = 0;
		break;
	case 2:
		this->hpMax += value;
		if (this->hpMax < 0) this->hpMax = 0;
		break;
	case 3:
		this->mana += value;
		if (this->mana < 0) this->mana = 0;
		break;
	case 4:
		this->manaMax += value;
		if (this->manaMax < 0) this->manaMax = 0;
		break;
	case 5:
		this->atk += value;
		if (this->atk < 0) this->atk = 0;
		break;
	case 6:
		this->defense += value;
		if (this->defense < 0) this->defense = 0;
		break;
	default:
		this->talents[modifyKeyMap[index]] += value;
		if (this->talents[modifyKeyMap[index]] < 0) this->talents[modifyKeyMap[index]] = 0;
	}
}

const int& Entity::getTalent(const std::string& key) const
{
	if (this->talents.contains(key)) {
		return this->talents.find(key)->second;
	}
	throw InvalidKeyException(key);
}