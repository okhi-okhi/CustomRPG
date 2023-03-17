#include "Player.h"
#include <iostream>
#include "../System/I18n.h"

void Player::printStats() const {
	using std::cout, std::endl, std::to_string;

	cout << I18n::instance().get("player.printStats.name", { {"name", this->name} }) << endl;
	cout << I18n::instance().get("player.printStats.gold", { {"gold", to_string(this->gold)} }) << endl;
	cout << I18n::instance().get("player.printStats.distance", { {"distance", to_string(this->distance)} }) << endl;
}

void Player::printAllAllys() const {
	using std::cout, std::endl, std::to_string;
	const int lineCapacity = Config::instance().getLineCapacity();
	const int lineAmount = static_cast<int>(std::ceil(static_cast<float>(this->allAllys.size()) / static_cast<float>(lineCapacity)));

	for (int i = 0; i < lineAmount; i++) {
		int itemRemain = static_cast<int>(this->allAllys.size()) - (lineCapacity * i);
		if (itemRemain > lineCapacity) {
			itemRemain = lineCapacity;
		}

		for (int j = 0; j < itemRemain; j++)
		{
			const int slot = j + (lineCapacity * i);
			cout << I18n::instance().get("player.printAllAllys.info", 
				{ {"slot", std::to_string(slot + 1)},
				  {"name", this->team[slot]->getName()},
				  {"level", std::to_string(this->team[slot]->getLevel())} });

			if (this->team[slot]->getInTeam()){
				cout << I18n::instance().get("player.printAllAllys.inTeam");
			}
			cout << " | ";
		}
		cout << endl;
	}
}

ordered_json Player::getDataAsJson() {
	ordered_json json;
	//json["gold"] = this->gold;
	json["distance"] = this->distance;

	for (int i = 0; i < 3; i++)
	{
		if (this->team[i]->getLevel() != 0)
			json["team"][i] = this->team[i]->getId();
	}
	return json;
}

ordered_json Player::getAllysAsJson() {
	ordered_json json;
	int i = 0;
	for (auto& ally : this->allAllys)
	{
		json["allAllys"][ally.getId()] = ally.getAsJson();
		i++;
	}
	return json;
}

ordered_json Player::getInvAsJson() const
{
	ordered_json json;
	int weaponIndex = 0, armorIndex = 0;
	for (int i = 0; i < this->inventory.getSize(); i++) {
		if (this->inventory[i].first->getItemType() == itemTypes::WEAPON) {
				json["inventory"]["weapon"][weaponIndex] = this->inventory[i].first->getAsJson();
				weaponIndex++;
		}
		else if (this->inventory[i].first->getItemType() == itemTypes::ARMOR) {
			json["inventory"]["armor"][armorIndex] = this->inventory[i].first->getAsJson();
			armorIndex++;
		}
	}
	return json;
}
