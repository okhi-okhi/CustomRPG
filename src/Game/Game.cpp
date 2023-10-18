#include "Game.h"
#include "Event.h"
#include "GameConfig.h"
#include "../I18n/FontProvider.h"
#include "../Item/Material.h"
#include "../Item/Prop.h"
#include "../System/Exceptions.hpp"
#include "../System/PathProvider.h"
#include "../System/Menu.h"
#include "../System/Sheet.h"
#include "../Utils/Utilities.h"

void Game::init(Player& player)
{
	using std::cout, std::endl;
	this->player = &player;

	PathProvider::setCurrentGamePath("FatefulAdventure");
	GameConfig::instance().load(PathProvider::getCurrentGamePath() + PathProvider::getConfigPath());
	I18n::instance().loadGameI18n(GameConfig::instance().getCurrentLanguage(), GameConfig::instance().getDefaultLanguage());
	FontProvider::instance().loadGameFont();
}

void Game::gameMenu() {
	using std::cout, std::endl, std::to_string;

	Menu gameMenu("game.gameMenu");

	gameMenu.addDescription("info",
		{ {"name", this->player->getName()},
		  {"gold", to_string(this->player->getGold())},
		  {"distance", to_string(this->player->getDistance())} });

	gameMenu.addButton("printStats");
	gameMenu.addButton("ally");
	gameMenu.addButton("team");
	gameMenu.addButton("inventory");
	gameMenu.addButton("adventure");
	gameMenu.addButton("quit");
	gameMenu.print();

	this->choice = gameMenu.getInput();
	
	switch (this->choice) {
	case 0:
		printStats();
		break;
	
	case 1:
		allyMenu();
		break;
	
	case 2:
		menuStatu = menuStatus::TEAM;
		teamMenu();
		break;
	
	case 3:
		inventoryMenu();
		break;
	
	case 4:
		adventure();
		break;
	
	case 5:
		menuStatu = menuStatus::SYSTEM;
		break;
	
	default:
		break;
	}
}

void Game::allyMenu()
{
}

void Game::teamMenu() {
	using std::cout, std::endl;

	Menu teamMenu("game.teamMenu");

	teamMenu.addDescription("yourTeam");

	teamMenu.addButton("editMember");
	teamMenu.addButton("setOrder");
	teamMenu.addButton("quit");

	teamMenu.printTitle();
	cout << endl;
	teamMenu.printDescription();
	this->player->getTeam().print();
	cout << endl;
	teamMenu.printButton();

	this->choice = teamMenu.getInput();
	
	switch (this->choice) {
	case 0:
		editMember();
		break;

	case 1:
		setOrder();
		break;

	case 2:
		this->player->getTeam().optimized();
		menuStatu = menuStatus::GAME;
		break;

	default:
		break;
	}
}

void Game::inventoryMenu()
{
}

void Game::printStats() const {
	using std::cout, std::cin, std::endl;

	cout << I18n::instance().get("game.printStats.title") << endl;
	this->player->printStats();
	cout << endl;
	cout << I18n::instance().get("game.printStats.team") << endl;
	this->player->printTeam();
	cout << endl;
	cout << I18n::instance().get("game.printStats.allys") << endl;
	this->player->printAllAllys();
	cout << endl;
	cout << I18n::instance().get("game.printStats.inventory") << endl;
	this->player->printInventory();
}

void Game::adventure() {
	// using std::cout, std::cin;
	// Place currentPlace(this->currentPlace);
	// cout << "你現在在: " << currentPlace.getName() << "\n";
	// if (this->player->getDistance() == 0) {
	// 	// this->currentPlace = Place("bar");
	// }
	// else {
	// 	int i = 1;
	// 	std::vector<Place> vp;
	// 	for (const auto& s : this->nextPlaces) {
	// 		Place p(s);
	// 		vp.push_back(p);
	// 		cout << i << ") " << p.getAsString();
	// 		i++;
	// 	}
	// 	cout << "你選擇去: ";
	// 	cin >> i;
	//
	// 	while (cin.fail())
	// 	{
	// 		cout << "錯誤的輸入!" << "\n";
	// 		cin.clear();
	// 		cin.ignore(100, '\n');
	//
	// 		cout << "你選擇去: ";
	// 		cin >> i;
	// 	}
	//
	// 	i--;
	// 	// this->currentPlace = vp[i];
	// }
	// Event::generateEvent(*this->player, currentPlace);
	//
	// this->player->gainDistance();
	// this->nextPlaces = currentPlace.getPlaces(Config::instance().getNextPlaceNum());
}

void Game::editMember()
{
	using std::cout, std::cin, std::endl, std::to_string;
	cout << endl;
	cout << I18n::instance().get("game.editMember.description") << endl;
	cout << endl;

	const int slot = Menu::getInput(0, GameConfig::instance().getTeamCapacity());

	cout << I18n::instance().get("game.editMember.allIdleAllys") << endl;

	const int lineCapacity = GameConfig::instance().getLineCapacity();
	const int lineAmount = static_cast<int>(std::ceil(static_cast<float>(this->player->getAllAllys().size()) / static_cast<float>(lineCapacity)));
	int selectIndex = 0;
	std::vector<int> indexes;
	for (int i = 0; i < lineAmount; i++) {
		int itemRemain = static_cast<int>(this->player->getAllAllys().size()) - (lineCapacity * i);
		if (itemRemain > lineCapacity) {
			itemRemain = lineCapacity;
		}
		for (int j = 0; j < itemRemain; j++)
		{
			int index = j + (lineCapacity * i);
			if (!this->player->getAllAllys()[index].getInTeam()) {
				cout << I18n::instance().get("player.printAllAllys.info",
					{ {"slot", to_string(selectIndex + 1)},
					  {"name", this->player->getAllAllys()[index].getName()},
					  {"level", to_string(this->player->getAllAllys()[index].getLevel())} }) << " | ";
				indexes.push_back(index);
				selectIndex++;
			}
		}
		cout << endl;
	}
	cout << endl;
	cout << I18n::instance().get("game.editMember.tips") << endl;
	cout << I18n::instance().get("game.editMember.inputAlly") << endl;
	this->choice = Menu::getInput(-1, selectIndex);
	if(choice == -1)
	{
		this->player->getTeam().removeMember(slot - 1);
		cout << I18n::instance().get("game.editMember.success") << endl;
	}
	else if(choice == 0)
	{
		cout << I18n::instance().get("game.editMember.cancel") << endl;
	}
	else
	{
		this->player->getTeam().replaceMember(this->player->getAllAllys()[indexes[this->choice - 1]], slot - 1);
		cout << I18n::instance().get("game.editMember.success") << endl;
	}
}

void Game::setOrder() const
{
	using std::cout, std::cin, std::endl;
	cout << endl;
	cout << I18n::instance().get("game.setOrder.description") << endl;
	cout << endl;

	std::string orderString;
	std::vector<int> indexList;

	getInput:
		indexList.clear();
		cout << I18n::instance().get("game.setOrder.inputOrder");
		cin >> orderString;
		cin.ignore(100, '\n');
		std::stringstream order(orderString);

		int index = 0;
		while (order.good())
		{
			string substr;
			getline(order, substr, ',');
			if(substr=="-") {
				indexList.push_back(index);
			}
			else {
				const int pushIndex = std::stoi(substr) - 1;
				if(pushIndex >= 0) {
					indexList.push_back(pushIndex);
				}
				else {
					cout << I18n::instance().get("game.setOrder.negativeIndex") << endl;
					goto getInput;
				}
			}
			index++;
		}
		if (indexList.size() > this->player->getTeam().getAllyNum()) {
			cout << I18n::instance().get("game.setOrder.outOfRange") << endl;
			goto getInput;
		}
		if (indexList.size() < this->player->getTeam().getAllyNum()) {
			for (int i = index; i < this->player->getTeam().getAllyNum(); i++) {
				indexList.push_back(i);
			}
		}
		for (int i = 0; i < indexList.size(); i++) {
			for (int j = i + 1; j < indexList.size(); j++) {
				if (indexList[i] == indexList[j]) {
					cout << I18n::instance().get("game.setOrder.sameIndex") << endl;
					goto getInput;
				}
			}
		}

	this->player->getTeam().setOrder(indexList);
	cout << I18n::instance().get("game.setOrder.success") << endl;
	this->player->getTeam().print();
}
