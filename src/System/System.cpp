#include "System.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <json.hpp>
#include "PathProvider.h"
#include "SystemConfig.h"
#include "Menu.h"
#include "../Game/Game.h"
#include "../Game/GameConfig.h"
#include "../I18n/I18n.h"
#include "../I18n/FontProvider.h"

void System::init() {
	SystemConfig::instance().load(PathProvider::instance().getConfigPath());
	I18n::instance().loadSystemI18n(SystemConfig::instance().getCurrentLanguage(), SystemConfig::instance().getDefaultLanguage());
	FontProvider::instance().loadSystemFont();
	// createNewPlayer();
}

void System::systemMenu() {
	using std::cout, std::endl;

	Menu systemMenu("system.systemMenu");

	systemMenu.addDescription("activePlayer", { {"name", getPlayer().getName()} });

	systemMenu.addButton("startGame");
	systemMenu.addButton("createNewPlayer");
	systemMenu.addButton("selectPlayer");
	systemMenu.addButton("savePlayers");
	systemMenu.addButton("loadPlayers");
	systemMenu.addButton("setting");
	systemMenu.addButton("quit");
	systemMenu.print();

	this->choice = systemMenu.getInput();
	
	switch (this->choice) {
	case 0:
		menuStatu = menuStatus::GAME;
		Game::instance().init(getPlayer());
		break;
	
	case 1:
		createNewPlayer();
		break;
	
	case 2:
		selectPlayer();
		break;
	
	case 3:
		savePlayers();
		break;
	
	case 4:
		loadPlayers();
		break;
	
	case 5:
		menuStatu = menuStatus::SETTING;
		settingMenu();
		break;
	
	case 6:
		playing = false;
		break;
	
	default:
		break;
	}
}

void System::settingMenu() {
	using std::cout, std::endl;

	Menu settingMenu("system.settingMenu");
	settingMenu.addButton("selectLanguage", { {"language", I18n::instance().getSystemI18n().getCurrentLanguage().info.name} });
	settingMenu.addButton("quit");
	settingMenu.print();

	this->choice = settingMenu.getInput();

	switch (this->choice) {
	case 0:
		selectLanguage();
		break;

	case 1:
		menuStatu = menuStatus::SYSTEM;
		break;

	default:
		break;
	}
}


void System::createNewPlayer() {
	string name;
	std::cout << I18n::instance().get("system.createNewPlayer.inputName");
	getline(std::cin, name);

	players.emplace_back(name);
	activePlayer = static_cast<int>(players.size() - 1);
}

void System::selectPlayer() {
	using std::cout, std::cin;
	cout << "選擇檔案: " << "\n\n";
	int n = 1;
	for (size_t i = 0; i < this->players.size(); i++)
	{
		cout << n + i << ") 金錢: " << this->players[i].getGold() << " 已前進距離: " << this->players[i].getDistance() << "\n";
	}
	cout << "\n";
	cout << "你要選擇的檔案: ";
	cin >> this->choice;

	while (cin.fail() || this->choice > this->players.size() || this->choice < 1)
	{
		cout << "錯誤的輸入!" << "\n";
		cin.clear();
		cin.ignore(100, '\n');

		cout << "你要選擇的檔案: ";
		cin >> this->choice;
	}
	cin.ignore(100, '\n');
	cout << "\n";
	this->choice--;

	this->activePlayer = this->choice;
	playerDistance = this->players[activePlayer].getDistance();
	playerFame = this->players[activePlayer].getFame();

	cout << choice + 1 << "號檔案被選擇了!" << "\n\n";
}

void System::savePlayers() {
	std::ofstream outFile("a");
	if (outFile.is_open()) {
		ordered_json j, temp;

		for (size_t i = 0; i < this->players.size(); i++) {
			j[i]["gold"] = this->players[i].getGold();
			temp = this->players[i].getDataAsJson();
			j[i].insert(temp.begin(), temp.end());

			temp = this->players[i].getAllysAsJson();
			if (!temp.empty())
				j[i].insert(temp.begin(), temp.end());

			temp = this->players[i].getInvAsJson();
			if (!temp.empty())
				j[i].insert(temp.begin(), temp.end());
		}

		outFile << j.dump(4);
	}
	outFile.close();
}

void System::loadPlayers()
{
	// using std::string;
	// using json = nlohmann::json;
	//
	// std::ifstream inFile(Config::instance().getPlayerFilePath());
	// if (!inFile.good()) {
	// 	const std::map<string, string> args = { {"file", Config::instance().getPlayerFilePath()} };
	// 	std::cout << I18n::instance().get("exception.invalidFile", args) << std::endl;
	// 	return;
	// }
	// json j = json::parse(inFile);
	// if (!j[0].contains("gold")) {
	// 	std::cout << "檔案 players.json 有問題! 請將檔案刪除之後儲存再讀取!" << std::endl;
	// 	return;
	// }
	//
	// this->players.clear();
	//
	// int gold;
	// int distance;
	// std::array<Ally, 3> team;
	// std::vector<Ally> allAllys;
	// Inventory tempItems;
	//
	// string id;
	// string name;
	// int level;
	// int exp;
	//
	// int hp;
	// int mana;
	// int luck;
	// int talentPoint;
	//
	// int strength;
	// int vitality;
	// int dexterity;
	// int intelligence;
	//
	// int buyPrice;
	// int sellPrice;
	// int rarity;
	// int type;
	// int defense;
	// int atk;

	//for (const auto& player : j.items()) {
	//	gold = player.value()["gold"];
	//	distance = player.value()["distance"];

	//	for (const auto& ally : player.value()["allAllys"].items()) {
	//		id = ally.value();
	//		name = ally.value()["name"];
	//		level = ally.value()["level"];
	//		exp = ally.value()["exp"];

	//		hp = ally.value()["hp"];
	//		mana = ally.value()["mana"];
	//		luck = ally.value()["luck"];

	//		talentPoint = ally.value()["talentPoint"];

	//		strength = ally.value()["stats"]["strength"];
	//		vitality = ally.value()["stats"]["vitality"];
	//		dexterity = ally.value()["stats"]["dexterity"];
	//		intelligence = ally.value()["stats"]["intelligence"];

	//		Ally temp(id, name, level, exp, hp, mana, luck,
	//			talentPoint, strength, vitality, dexterity, intelligence);

	//		name = ally.value()["equipments"]["weapon"]["name"];
	//		level = ally.value()["equipments"]["weapon"]["level"];
	//		buyPrice = ally.value()["equipments"]["weapon"]["buyPrice"];
	//		sellPrice = ally.value()["equipments"]["weapon"]["sellPrice"];
	//		rarity = ally.value()["equipments"]["weapon"]["rarity"];
	//		atk = ally.value()["equipments"]["weapon"]["atk"];
	//		//id need to correct
	//		Weapon weapon(id, name, level, buyPrice, sellPrice, rarity, atk);
	//		temp.setWeapon(weapon);

	//		for (const auto& ar : ally.value()["equipments"]["armor"].items())
	//		{
	//			name = ar.value()["name"];
	//			level = ar.value()["level"];
	//			buyPrice = ar.value()["buyPrice"];
	//			sellPrice = ar.value()["sellPrice"];
	//			rarity = ar.value()["rarity"];
	//			type = ar.value()["type"];
	//			defense = ar.value()["defense"];

	//			switch (type) {
	//			case 0: {
	//				Armor armor_head(name, level, buyPrice, sellPrice, rarity, type, defense);
	//				temp.setArmorHead(armor_head);
	//				break; }
	//			case 1: {
	//				Armor armor_chest(name, level, buyPrice, sellPrice, rarity, type, defense);
	//				temp.setArmorChest(armor_chest);
	//				break; }
	//			case 2: {
	//				Armor armor_legs(name, level, buyPrice, sellPrice, rarity, type, defense);
	//				temp.setArmorLegs(armor_legs);
	//				break; }
	//			case 3: {
	//				Armor armor_boots(name, level, buyPrice, sellPrice, rarity, type, defense);
	//				temp.setArmorBoots(armor_boots);
	//				break; }
	//			}
	//		}
	//		for (const auto& item : ch.value()["inventory"]["weapon"].items())
	//		{
	//			name = item.value()["name"];
	//			level = item.value()["level"];
	//			buyPrice = item.value()["buyPrice"];
	//			sellPrice = item.value()["sellPrice"];
	//			rarity = item.value()["rarity"];
	//			atk = item.value()["atk"];
	//			temp.addItem(Weapon(name, level, buyPrice, sellPrice, rarity, atk));
	//		}
	//		for (const auto& item : ch.value()["inventory"]["armor"].items())
	//		{
	//			name = item.value()["name"];
	//			level = item.value()["level"];
	//			buyPrice = item.value()["buyPrice"];
	//			sellPrice = item.value()["sellPrice"];
	//			rarity = item.value()["rarity"];
	//			type = item.value()["type"];
	//			defense = item.value()["defense"];
	//			temp.addItem(Armor(name, level, buyPrice, sellPrice, rarity, type, defense));
	//		}
	//		this->characters.push_back(Character(temp));
	//		cout << "角色 " << temp.getName() << " 讀取!\n";
	//	}
	//}
}

void System::selectLanguage() {
	using std::cout, std::cin, std::endl;
	using json = nlohmann::json;
	Menu selectLanguage("system.selectLanguage");

	for (const auto& language : I18n::instance().getSystemI18n().getLanguages())
	{
		selectLanguage.addButton("language", { {"language", language.name} });
	}
	selectLanguage.addButton("quit");

	selectLanguage.printTitle();
	selectLanguage.printButton();

	this->choice = selectLanguage.getInput();

	if (choice != static_cast<int>(I18n::instance().getSystemI18n().getLanguages().size())) {
		const string language = I18n::instance().getSystemI18n().getLanguages()[choice].id;
		I18n::instance().getSystemI18n().loadLanguage(language);
		SystemConfig::instance().setCurrentLanguage(language);
		//update config
		try {
			std::ifstream inFile(PathProvider::instance().getConfigPath());
			json j = json::parse(inFile);
			ordered_json j2;
			j2["system"]["currentLanguage"] = language;
			j.update(j2, true);
			inFile.close();
			std::ofstream outFile(PathProvider::instance().getConfigPath());
			outFile << j.dump(4);
			outFile.close();
		}
		catch (json::exception& e)
		{
			std::cout << e.what();
		}

		std::cout << I18n::instance().get("system.selectLanguage.success",
			{ {"language", I18n::instance().getSystemI18n().getCurrentLanguage().info.name} }) << std::endl;
	}
}