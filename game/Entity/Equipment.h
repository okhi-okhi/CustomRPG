#pragma once
#include "../Item/Armor.h"
#include "../Item/Weapon.h"
#include "../System/Config.h"

class Equipment
{
private:
	const int weaponCapacity = 2;
	const int armorCapacity = static_cast<int>(Config::instance().getArmorSlots().size());
	std::vector<Weapon*> weapons;
	std::vector<Armor*> armors;

public:
	Equipment();
	Equipment(std::vector<Weapon*> weapons, std::vector<Armor*> armors) :
		weapons(std::move(weapons)), armors(std::move(armors)) {}

	void replaceEquipment(Weapon& weapon, int index);
	void replaceEquipment(Armor& armor, int index);

	void removeWeapon(int index);

	void print() const;

	const std::vector<Weapon*>& getWeapons()const { return this->weapons; }
	const std::vector<Armor*>& getArmors()const { return this->armors; }
};

