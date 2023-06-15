#pragma once
#include "Item.h"
#include "CraftArmor.h"

class Armor final : public Item {
private:
	CraftArmor armorType;
	int level;
	int atk;
	int defense;
	int durability;
	int durabilityMax;

	bool isEquipped;

	//std::vector<Passive> passives

	virtual float readValue(const json& j) const override;
	virtual std::string readString(const json& j, const std::string& key) const override;

public:
	Armor() : level(0), atk(0), defense(0), durability(0),
		durabilityMax(0), isEquipped(false) { this->itemType = itemTypes::ARMOR; }
	Armor(const std::string& id, const std::string& name, const int& buyPrice,
	      const int& sellPrice, const enum rarity& rarity, const std::string& armorType,
	      const int& level, const int& atk, const int& defense, const int& durability, const int& dM) :
		Item(itemTypes::ARMOR, id, name, buyPrice, sellPrice, rarity, false),
		armorType(CraftArmor(armorType)), level(level), atk(atk),
		defense(defense), durability(durability), durabilityMax(dM), isEquipped(false) {}

	explicit Armor(const std::string& fileName);

	Armor* clone()const override;
	ordered_json getAsJson()const override;
	std::vector<std::string> getDataKey() const override;
	std::map<std::string, std::string> getData() const override;

	void print() const override;
	void debugPrint() const override;

	void addLevel() { this->level++; }

	const CraftArmor& getArmorType()const { return this->armorType; }
	std::string getRawArmorTypeName()const { return I18n::instance().get(this->armorType.getName()); }
	std::string getArmorTypeName()const;
	std::string getArmorSlot()const { return this->armorType.getArmorSlot(); }
	const int& getLevel()const { return this->level; }
	const int& getAtk()const { return this->atk; }
	const int& getDefense()const { return this->defense; }
	const int& getDurability()const { return this->durability; }
	const int& getDurabilityMax()const { return this->durabilityMax; }
	const bool& getIsEquipped()const { return this->isEquipped; }
};

