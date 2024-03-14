#include "SelectPlayerScreen.h"
#include "../../ScreenManager.h"
#include "../../Button.h"
#include "../../ElementGroup.h"
#include "../../ElementSheet.h"
#include "../../FullPicture.h"
#include "../../Picture.h"
#include "../../TextArg.h"
#include "../../../System/PathProvider.h"
#include "../../../Utils/Utilities.h"
#include "../../../I18n/I18n.h"

SelectPlayerScreen::SelectPlayerScreen() : Screen(ScreenType::SELECT_PLAYER, "selectPlayer")
{
	loadPlayerFile();

	vector<shared_ptr<Element>> playerList;
	vector<shared_ptr<Element>> block;
	int playerCount = 0;
	for(const auto& playerInfo : this->playersInfo)
	{
		block.emplace_back(make_shared<Picture>(File("screens/selectPlayer/block_background.png")));
		block.emplace_back(make_shared<Text>(raylib::Vector2(0, -330), "screen.selectPlayer.index",
			std::map<string, string>{ {"index", std::to_string(playerCount+1) } }, TextAlign::CENTER, 1.0f));
		block.emplace_back(make_shared<Picture>(raylib::Vector2(0, -270), File("misc/divider_1.png"), 1, 384));

		block.emplace_back(make_shared<Picture>(raylib::Vector2(-150, -230), File("icons/gold.png"), 1, 64));
		block.emplace_back(make_shared<Text>(raylib::Vector2(-100, -230), "screen.selectPlayer.gold",
			std::map<string, string>{ {"gold", std::to_string(playerInfo.gold) } }, TextAlign::LEFT, 1.0f));

		block.emplace_back(make_shared<Picture>(raylib::Vector2(-150, -150), File("icons/diamond.png"), 1, 64));
		block.emplace_back(make_shared<Text>(raylib::Vector2(-100, -150), "screen.selectPlayer.diamond",
			std::map<string, string>{ {"diamond", std::to_string(playerInfo.diamond) } }, TextAlign::LEFT, 1.0f));

		block.emplace_back(make_shared<Picture>(raylib::Vector2(-150, -70), File("icons/distance.png"), 1, 64));
		block.emplace_back(make_shared<Text>(raylib::Vector2(-100, -70), "screen.selectPlayer.distance",
			std::map<string, string>{ {"distance", std::to_string(playerInfo.distance) } }, TextAlign::LEFT, 1.0f));

		block.emplace_back(make_shared<Picture>(raylib::Vector2(-150, 10), File("icons/fame.png"), 1, 64));
		block.emplace_back(make_shared<Text>(raylib::Vector2(-100, 10), "screen.selectPlayer.fame",
			std::map<string, string>{ {"fame", std::to_string(playerInfo.fame) } }, TextAlign::LEFT, 1.0f));

		block.emplace_back(make_shared<Text>(raylib::Vector2(-180, 70), "screen.selectPlayer.lastUpdate",
			std::map<string, string>{ {"time", playerInfo.lastUpdate } }, TextAlign::LEFT, 1.0f));

		playerList.emplace_back(make_shared<ElementGroup>(block));
		playerCount++;
		block.clear();
	}
	while (playerCount < 4)
	{
		block.emplace_back(make_shared<Picture>(File("screens/selectPlayer/block_background.png")));

		playerList.emplace_back(make_shared<ElementGroup>(block));
		playerCount++;
		block.clear();
	}

	addElement(make_shared<FullPicture>(File("screens/main/background.png"), 1));
	addElement(make_shared<Button>(Vector2{ 72, 50 }, Picture(File("screens/return.png"), 2, 144), openSelectGame));
	addElement(make_shared<ElementSheet>(raylib::Rectangle(960, 540, 1920, 1080), 1, 4, 64, 0, playerList));
}

void SelectPlayerScreen::openSelectGame()
{
	ScreenManager::instance().showScreen(ScreenType::SELECT_GAME);
	ScreenManager::instance().hideScreen(ScreenType::SELECT_PLAYER);
}

void SelectPlayerScreen::loadPlayerFile()
{
	json playersFile = Utils::loadJsonFile(PathProvider::getCurrentGamePath() + PathProvider::getPlayerPath(), false);

	for(const auto& player : playersFile.items())
	{
		PlayerInfo playerInfo;
		playerInfo.gold = player.value()["gold"];
		playerInfo.diamond = player.value()["diamond"];
		playerInfo.distance = player.value()["distance"];
		playerInfo.fame = player.value()["fame"];
		playerInfo.lastUpdate = player.value()["lastUpdate"];

		this->playersInfo.push_back(playerInfo);
	}
}

