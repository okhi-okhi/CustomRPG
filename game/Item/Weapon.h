#pragma once
#include "Item.h"
#include "CraftWeapon.h"

class Weapon final : public Item{
private:
	CraftWeapon weaponType;
	int level;
	int atk;
	int defense;
	float critChance;
	float critDamage;
	int durability;
	int durabilityMax;

	bool isEquipped;

	//std::vector<Passive> passives

	virtual float readValue(const json& j) const override;
	virtual std::string readString(const json& j, const std::string& key) const override;

public:
	Weapon() : Item(), level(0), atk(0), defense(0),
		critChance(0), critDamage(0), durability(0),
		durabilityMax(0), isEquipped(false) { this->itemType = itemTypes::WEAPON; }

	Weapon(std::string id, std::string name, const int& buyPrice, const int& sellPrice,
		const enum rarity& rarity, const std::string& weaponType, const int& level, const int atk,
		const int defense, const float& critChance, const float& critDamage, const int& durability, const int& dM) :
		Item(itemTypes::WEAPON, std::move(id), std::move(name), buyPrice, sellPrice, rarity, false),
		weaponType(CraftWeapon(weaponType)), level(level), atk(atk), defense(defense),
		critChance(critChance), critDamage(critDamage), durability(durability),
		durabilityMax(dM), isEquipped(false) {}

	explicit Weapon(const std::string& fileName);

	Weapon* clone() const override;
	ordered_json getAsJson() const override;
	std::vector<std::string> getDataKey() const override;
	std::map<std::string, std::string> getData() const override;

	void print() const override;
	void debugPrint() const override;

	void addLevel() { this->level++; }

	const CraftWeapon& getWeaponType()const { return this->weaponType; }
	std::string getRawWeaponTypeName()const { return this->weaponType.getName(); }
	std::string getWeaponTypeName()const;
	const bool& getIsTwoHand()const { return this->weaponType.getIsTwoHand(); }
	const int& getLevel()const { return this->level; }
	const int& getAtk()const { return this->atk; }
	const int& getDefense()const { return this->defense; }
	const float& getCritChance()const { return this->critChance; }
	const float& getCritDamage()const { return this->critDamage; }
	const float& getComboRate()const { return this->weaponType.getComboRate(); }
	const int& getDurability()const { return this->durability; }
	const int& getDurabilityMax()const { return this->durabilityMax; }
	const bool& getIsEquipped()const { return this->isEquipped; }
};

