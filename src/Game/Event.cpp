#include "Event.h"
#include <iostream>
#include "../Entity/Enemy.h"
#include "Script.h"

void Event::generateEvent(Player& player, Place& place)
{
	const std::string event = place.getEvent();

	std::cout << "\n" << place.getOpening() << "\n" << "\n";
	if(event =="enemy")
		enemyEncouter(player, place);
	else if(event =="shop")
		shopEncouter(player);
	else
		scriptEncouter(player, place);
}

void Event::enemyEncouter(Player& player, Place& place) {

}

void Event::shopEncouter(Player& player){

}

void Event::scriptEncouter(Player& player, const Place& place) {
	int userAns;

	const Script script(place.getScripts());
	std::cout<<script.getAsString();
	std::cout << "\n你的選擇: ";
	std::cin >> userAns;

	while (std::cin.fail())
	{
		std::cout << "錯誤的輸入!" << "\n";
		std::cin.clear();
		std::cin.ignore(100, '\n');

		std::cout << "\n你的選擇: ";
		std::cin >> userAns;
	}

	std::cin.ignore(100, '\n');
	std::cout << "\n";

	userAns--;
	std::cout<< script.getResultText(userAns)<<"\n";

	const int exp = script.getExp(userAns);
	const int gold = script.getGold(userAns);

}
