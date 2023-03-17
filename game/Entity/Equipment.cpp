#include "Equipment.h"
#include "../System/Config.h"
#include "../System/Exceptions.hpp"

Equipment::Equipment()
{
	this->weapons.clear();
	this->armors.clear();

	for (int i = 0; i < this->weaponCapacity; i++) {
		this->weapons.push_back(nullptr);
	}

	for (int i = 0; i < Config::instance().getArmorSlots().size(); i++) {
		this->armors.push_back(nullptr);
	}
}

void Equipment::replaceEquipment(Weapon& weapon, const int index)
{
	if (index < 0 || index >= this->weaponCapacity) {
		throw OutOfRangeException(index, this->weaponCapacity);
	}
	if(weapon.getIsTwoHand()) {
		removeWeapon(0);
		removeWeapon(1);
		this->weapons[0] = &weapon;
	}
	else
	{
		this->weapons[index] = &weapon;
	}
}

void Equipment::replaceEquipment(Armor& armor, const int index) {
	if (index < 0 || index >= this->armorCapacity) {
		throw OutOfRangeException(index, this->armorCapacity);
	}
	this->armors[index] = &armor;
}

void Equipment::removeWeapon(int index)
{
	if (index < 0 || index >= weaponCapacity + armorCapacity) {
		throw OutOfRangeException(index, weaponCapacity + armorCapacity);
	}
	if(index < weaponCapacity) {
		this->weapons[index] = nullptr;
	}
	else {
		this->armors[index - weaponCapacity] = nullptr;
	}
}

void Equipment::print() const
{
}
