#include "Enemy.h"
#include "../Utils/Utilities.h"
#include "../System/Exceptions.hpp"

Enemy::Enemy(const std::string& fileName, const int point) 
{
	using Utils::checkInRange, Utils::getFromFormula;
	json j = Utils::loadJsonFile("Entitys/Enemys/" + fileName);

	try {
		this->name = j["name"];
		this->level = checkInRange(point, j["level"]["min"], j["level"]["max"]);
		this->hpMax = getFromFormula(j["hpMax"], this->level);
		this->hp = this->hpMax;
		this->manaMax = getFromFormula(j["manaMax"], this->level);
		this->mana = this->manaMax;
		this->atk = getFromFormula(j["atk"], this->level);
		this->defense = getFromFormula(j["defense"], this->level);

		// this->strength = getFromFormula(j["talents"]["strength"], this->level);
		// this->vitality = getFromFormula(j["talents"]["vitality"], this->level);
		// this->dexterity = getFromFormula(j["talents"]["dexterity"], this->level);
		// this->intelligence = getFromFormula(j["talents"]["intelligence"], this->level);

		this->dropExp = getFromFormula(j["dropExp"], this->level);
		this->dropGold = getFromFormula(j["dropGold"], this->level);

		this->attackTypes = ChanceTable(j["attackTypes"]);
		this->skills = ChanceTable(j["skills"]);
		this->dropWeapons = ChanceTable(j["dropItems"]["weapon"]);
		this->dropArmors = ChanceTable(j["dropItems"]["armor"]);

		this->faction = Faction::ENEMY;
	}
	catch (json::type_error& e) {
		throw BadValueException(fileName, e.what());
	}
}

std::string Enemy::getAsString()const{
	return "等級: " + std::to_string(this->level) + "\n" +
		"血量: " + std::to_string(this->hp) + " / " + std::to_string(this->hpMax) + "\n" +
		"魔力: " + std::to_string(this->mana) + " / " + std::to_string(this->manaMax) + "\n" +
		"攻擊: " + std::to_string(this->atk) + "\n" +
		"防禦: " + std::to_string(this->defense) + "\n" +
		// "力量: " + std::to_string(this->strength) + "\n" +
		// "體力: " + std::to_string(this->vitality) + "\n" +
		// "敏捷: " + std::to_string(this->dexterity) + "\n" +
		// "智力: " + std::to_string(this->intelligence) + "\n" +
		"掉落經驗: " + std::to_string(this->dropExp) + "\n" +
		"掉落金錢: " + std::to_string(this->dropGold) + "\n";
}

void Enemy::debugPrint() const {
	using Utils::printMap;
	std::cout << "名字: " << this->name << "\n";
	std::cout << "等級: " << this->level << "\n";
	std::cout << "血量: " << this->hp << "\n";
	std::cout << "魔力: " << this->mana << "\n";
	std::cout << "攻擊: " << this->atk << "\n";
	std::cout << "防禦: " << this->defense << "\n";
	// std::cout << "力量: " << this->strength << "\n";
	// std::cout << "體力: " << this->vitality << "\n";
	// std::cout << "敏捷: " << this->dexterity << "\n";
	// std::cout << "智力: " << this->intelligence << "\n";
	std::cout << "掉落經驗: " << this->dropExp << "\n";
	std::cout << "掉落金錢: " << this->dropGold << "\n";
	std::cout << "攻擊類型:\n";
	this->attackTypes.debugPrint();
	std::cout << "技能:\n";
	this->skills.debugPrint();
	std::cout << "掉落武器:\n";
	this->dropWeapons.debugPrint();
	std::cout << "掉落盔甲:\n";
	this->dropArmors.debugPrint();
}
