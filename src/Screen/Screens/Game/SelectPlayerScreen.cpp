#include "SelectPlayerScreen.h"
#include "../../ElementGroup.h"
#include "../../ElementSheet.h"
#include "../../FullPicture.h"
#include "../../Picture.h"
#include "../../../System/PathProvider.h"
#include "../../../Utils/Utilities.h"

SelectPlayerScreen::SelectPlayerScreen() : Screen(ScreenType::SELECT_PLAYER, "selectPlayer")
{
	loadPlayerFile();

	vector<shared_ptr<Element>> playerList;
	vector<shared_ptr<Element>> block;
	int playerCount = 0;
	for(const auto& playerInfo : this->playersInfo)
	{
		block.emplace_back(make_shared<Picture>(File("screens/selectPlayer/block_background.png")));

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
	addElement(make_shared<ElementSheet>(raylib::Rectangle(960, 540, 1920, 1080), 1, 5, 64, 0, playerList));
}

void SelectPlayerScreen::loadPlayerFile()
{
	json playersFile = Utils::loadJsonFile(PathProvider::getCurrentGamePath() + PathProvider::getPlayerPath(), false);

	PlayerInfo playerInfo;
	for(const auto& player : playersFile.items())
	{
		playerInfo.name = player.value()["name"];
		playerInfo.gold = player.value()["gold"];
		playerInfo.distance = player.value()["distance"];
		playerInfo.fame = player.value()["fame"];

		this->playersInfo.push_back(playerInfo);
	}
}

