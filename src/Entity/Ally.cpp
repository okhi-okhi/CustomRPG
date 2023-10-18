#include "Ally.h"
#include <queue>
#include "../game/GameConfig.h"
#include "../System/Exceptions.hpp"
#include "../Utils/ChanceTable.h"
#include "../Utils/JsonUtils.h"
#include "../Utils/Utilities.h"

Ally::Ally(const std::string& fileName) {
	json j = Utils::loadJsonFile("Entitys/Allys/" + fileName);
	try {
		this->faction = Faction::ALLY;
		this->id = fileName;
		this->name = readString("name");
		this->level = static_cast<int>(readValue(j["level"]));
		this->exp = 0;
		this->expNext = 0;
		this->talentPoint = 0;
		this->race = Race(j["race"]);
		this->occupation = Occupation(j["occupation"]);
		this->inTeam = false;

		std::queue<json> modifyJson;
		modifyJson.push(j["modifyValue"]);
		while (!modifyJson.empty())
		{
			for (auto modifyValue = modifyJson.front().begin(); modifyValue != modifyJson.front().end(); ++modifyValue) {
				if(modifyValue->is_structured())
				{
					modifyJson.push(*modifyValue);
				}
				else {
					this->race.modifyStat(modifyValue.key(), modifyValue.value());
				}
			}
			modifyJson.pop();
		}

		this->talents = race.getTalents();
	}
	catch (json::exception& e) {
		throw BadValueException(fileName, e.what());
	}
	updateStats();
}


void Ally::updateStats()
{
	this->expNext = static_cast<int>(JsonUtils::readValueFromString(GameConfig::instance().getFormula("entity.expNext"), { {"level", this->level} }));

	std::map <std::string, int> vars = this->talents;
	vars["level"] = this->level;

	this->hpMax = static_cast<int>(JsonUtils::readValueFromString(GameConfig::instance().getFormula("entity.hpMax"), vars))
	+ this->level * this->occupation.getHpMaxScale() + this->race.getHpMaxBase();
	this->hp = this->hpMax;

	this->manaMax = static_cast<int>(JsonUtils::readValueFromString(GameConfig::instance().getFormula("entity.manaMax"), vars))
		+ this->level * this->occupation.getManaMaxScale() + this->race.getManaMaxBase();
	this->mana = this->manaMax;

	this->atk = static_cast<int>(JsonUtils::readValueFromString(GameConfig::instance().getFormula("entity.atk"), vars));

	this->defense = static_cast<int>(JsonUtils::readValueFromString(GameConfig::instance().getFormula("entity.defense"), vars));

	this->luck = static_cast<int>(JsonUtils::readValueFromString(GameConfig::instance().getFormula("entity.luck"), vars))
		+ this->level * this->occupation.getLuckScale() + this->race.getLuckBase();
}

void Ally::CheckLevelUp() {
	using std::cout, std::endl, std::to_string;
	while (this->exp >= this->expNext) {
		this->exp -= this->expNext;
		this->level++;
		this->talentPoint += this->occupation.getTalentPointScale();

		cout << I18n::instance().get("entity.ally.checkLevelUp", 
			{ {"name", this->name},
			  {"level", to_string(this->level)},
			  {"talentPoint", to_string(this->talentPoint)} }) << endl;
	}
}

void Ally::allocateStat() {
	using std::cout, std::endl, std::cin;
	if (this->talentPoint > 0) {
		// int i;
		// cout << "你可以選擇升級一項能力!\n\n";
		// cout << "1) 力量: 顯著地影響攻擊,也會些微影響到血量, 目前: "<< this->strength <<endl;
		// cout << "2) 體力: 顯著地影響血量和防禦, 目前: " << this->vitality << endl;
		// cout << "3) 敏捷: 顯著地影響命中率、爆擊率和防禦 目前: " << this->dexterity << endl;
		// cout << "4) 智力: 顯著地影響魔力,但影響著許多要素, 目前: " << this->intelligence << endl;
		// cout << "選擇升級的數值: ";
		// cin >> i;
		//
		// while (cin.fail() || i > 4)
		// {
		// 	cout << "錯誤的輸入!" << endl;
		// 	cin.clear();
		// 	cin.ignore(100, '\n');
		//
		// 	cout << "選擇升級的數值: " << endl;
		// 	cin >> i;
		// }
		//
		// cin.ignore(100, '\n');
		// cout << endl;
		//
		// switch (i) {
		// case 1:
		// 	this->strength += 1;
		// 	cout << "力量增加! 目前力量:" << this->strength << endl;
		// 	break;
		// case 2:
		// 	this->vitality += 1;
		// 	cout << "體力增加! 目前體力:" << this->vitality << endl;
		// 	break;
		//
		// case 3:
		// 	this->dexterity += 1;
		// 	cout << "敏捷增加! 目前敏捷:" << this->dexterity << endl;
		// 	break;
		// case 4:
		// 	this->intelligence += 1;
		// 	cout << "智力增加! 目前智力:" << this->intelligence << endl;
		// 	break;
		// default:;
		// }
		// talentPoint--;
		//TODO move this to game.cpp
	}
	this->updateStats();
}

ordered_json Ally::getAsJson()
{
	ordered_json j;
	j["name"] = this->name;
	j["level"] = this->level;
	j["exp"] = this->exp;

	j["hp"] = this->hp;
	j["mana"] = this->mana;
	j["luck"] = this->luck;

	j["talentPoint"] = this->talentPoint;

	return j;
}

ordered_json Ally::getEquipAsJson() const
{
	ordered_json j, temp;
	int armorIndex = 0;

	// if (weapon.getRarity() >= 0) {
	// 	temp = this->weapon.getAsJson();
	// 	for (const auto& item : temp.items()) {
	// 		j["equipments"]["weapon"][item.key()] = item.value();
	// 	}
	// }
	//
	// temp = this->armor_head.getAsJson();
	// if (armor_head.getRarity() >= 0) {
	// 	for (const auto& item : temp.items()) {
	// 		j["equipments"]["armor"][armorIndex][item.key()] = item.value();
	// 	}
	// 	armorIndex++;
	// }
	//
	// temp = this->armor_chest.getAsJson();
	// if (armor_chest.getRarity() >= 0) {
	// 	for (const auto& item : temp.items()) {
	// 		j["equipments"]["armor"][armorIndex][item.key()] = item.value();
	// 	}
	// 	armorIndex++;
	// }
	//
	// temp = this->armor_legs.getAsJson();
	// if (armor_legs.getRarity() >= 0) {
	// 	for (const auto& item : temp.items()) {
	// 		j["equipments"]["armor"][armorIndex][item.key()] = item.value();
	// 	}
	// 	armorIndex++;
	// }
	//
	// temp = this->armor_boots.getAsJson();
	// if (armor_boots.getRarity() >= 0) {
	// 	for (const auto& item : temp.items()) {
	// 		j["equipments"]["armor"][armorIndex][item.key()] = item.value();
	// 	}
	// }

	return j;
}

void Ally::print() const
{
	using std::cout, std::endl, std::string, std::to_string;
	const std::string prefix = "entity.ally.print.";
	Entity::print();
	cout << I18n::instance().get(prefix + "exp",
		{ {"exp", to_string(this->exp)},
		  {"expNext", to_string(this->expNext)} }) << endl;
	cout << I18n::instance().get(prefix + "hp",
		{ {"hp", to_string(this->hp)},
		  {"hpMax", to_string(this->hpMax)} }) << endl;
	cout << I18n::instance().get(prefix + "mana",
		{ {"mana", to_string(this->mana)},
		  {"manaMax", to_string(this->manaMax)} }) << endl;
	cout << I18n::instance().get(prefix + "atk",
		{ {"atk", to_string(this->atk)},
		  {"weaponAtk", to_string(1)} }) << endl;
	cout << I18n::instance().get(prefix + "defense",
		{ {"defense", to_string(this->defense)},
		  {"armorDefense", to_string(this->getArmorDefense())} }) << endl;
	cout << I18n::instance().get(prefix + "luck", { {"luck", to_string(this->luck)} }) << endl;
	cout << endl;

	for (const auto& [fst, snd] : this->talents) {
		cout << I18n::instance().get("entity.ally.print.talent",
			{ {"talent", getTalentName(fst)},
			  {"value", to_string(snd)} }) << endl;
	}

	cout << endl;
	cout << I18n::instance().get(prefix + "equipment");
	// if
	// cout << "= 武器: " << this->weapon.getName()
	// 	<< " 等級: " << this->weapon.getLevel()
	// 	<< " 攻擊: " << this->weapon.getAtk() << endl;
	// cout << "= 頭盔: " << this->armor_head.getName()
	// 	<< " 等級: " << this->armor_head.getLevel()
	// 	<< " 防禦: " << this->armor_head.getDefense() << endl;
	// cout << "= 胸甲: " << this->armor_chest.getName()
	// 	<< " 等級: " << this->armor_chest.getLevel()
	// 	<< " 防禦: " << this->armor_chest.getDefense() << endl;
	// cout << "= 護腿: " << this->armor_legs.getName()
	// 	<< " 等級: " << this->armor_legs.getLevel()
	// 	<< " 防禦: " << this->armor_legs.getDefense() << endl;
	// cout << "= 鞋子: " << this->armor_boots.getName()
	// 	<< " 等級: " << this->armor_boots.getLevel()
	// 	<< " 防禦: " << this->armor_boots.getDefense() << endl << endl;
}

void Ally::debugPrint() const
{
}

float Ally::readValue(const json& j) const
{
	if (j.is_number()) {
		return JsonUtils::readValueFromNum(j);
	}
	if (j.is_string()) {
		return JsonUtils::readValueFromString(j);
	}
	throw NoReadFunctionException(j);
}

std::string Ally::readString(const std::string& key) const
{
	return "dynamic.ally." + this->id + "." + key;
}

void Ally::modifyStat(const std::string& key, const int& value) {
	const std::vector <std::string> modifyKeyMap = { "exp", "luck", "talentPoint" };
	const auto it = std::ranges::find(modifyKeyMap, key);
	if (it == modifyKeyMap.end()) {
		Entity::modifyStat(key, value);
		return;
	}
	switch (it - modifyKeyMap.begin()) {
	case 0:
		this->exp += value;
		if (this->exp < 0) this->exp = 0;
		CheckLevelUp();
		break;
	case 1:
		this->luck += value;
		if (this->luck < 0) this->luck = 0;
		break;
	case 2:
		this->talentPoint += value;
		if (this->talentPoint < 0) this->talentPoint = 0;
		break;
	default:
		throw InvalidKeyException(key);
	}
}

int Ally::getArmorDefense() const
{
	int sum = 0;
	for (const auto& armor : this->armors) {
		sum += armor.getDefense();
	}
	return sum;
}
