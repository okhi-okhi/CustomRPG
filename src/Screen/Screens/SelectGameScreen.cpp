#include "SelectGameScreen.h"
#include <filesystem>
#include "../FullPicture.h"
#include "../ScrollList.h"
#include "../PictureBorder.h"
#include "../../I18n/FontProvider.h"
#include "../../Utils/Utilities.h"
#include "../../Utils/RaylibUtils.h"

SelectGameScreen::SelectGameScreen() : Screen(ScreenType::SELECT_GAME, "selectGame")
{
	this->isAnyGameSelected = false;
	readGameInfo();

	std::vector<std::string> gameNames;
	std::vector<const raylib::Font*> fonts;
	for (const auto& gameInfo : this->games)
	{
		gameNames.push_back(gameInfo.name);
		fonts.push_back(&gameInfo.font);
	}

	addElement(make_shared<FullPicture>(File("screens/main/background.png"), 1));
	addElement(make_shared<PictureBorder>(Vector2{ 300, 540 }, File("screens/selectGame/border_corner.png"),
		File("screens/selectGame/border_side.png"), File("screens/selectGame/border_padding.png"), 1, 64, Vector2{ 512, 1024 }));

	const auto gameList =
		make_shared<ScrollList>(Rectangle{ 300, 540, 300, 800 }, 8, -1, gameNames,
			TextAlign::CENTER, 0.0f, fonts, "screens/button_tile_1.png", "screens/scroll_bar.png", "screens/button_tile_1.png", [this] { showGameInfo(); });
	addElement(gameList);
	this->selectedGameIndex = &gameList->getCurrentIndex();
}

void SelectGameScreen::showGameInfo()
{
	if (!this->isAnyGameSelected)
	{
		this->isAnyGameSelected = true;
		addElement(make_shared<PictureBorder>(Vector2{ 1250, 540 }, File("screens/selectGame/border_corner.png"),
			File("screens/selectGame/border_side.png"), File("screens/selectGame/border_padding.png"), 1, 64, Vector2{ 1280, 1024 }));
		this->pictureGallery = make_shared<PictureGallery>(Rectangle{ 1150, 300, 640, 480 }, this->games[*this->selectedGameIndex].screenshots);
		addElement(this->pictureGallery);
		addElement(make_shared<Button>(Vector2{ 750, 300 }, Picture({ "screens/arrow_left.png" }, 2, 64), [this] { pictureGallery->previousPicture(); }));
		addElement(make_shared<Button>(Vector2{ 1550, 300 }, Picture({ "screens/arrow_right.png" }, 2, 64), [this] { pictureGallery->nextPicture(); }));

		std::string author = I18n::instance().getSystemI18n().get("screen.selectGame.author",
			{ {"author", this->games[*this->selectedGameIndex].author} });
		this->info = make_shared<Text>(Vector2{ 750, 570 }, author, TextAlign::LEFT, 1.0f, &this->games[*this->selectedGameIndex].font);
		addElement(this->info);

		std::string text = I18n::instance().getSystemI18n().get("screen.selectGame.dynamicDescription",
			{ {"description", this->games[*this->selectedGameIndex].description} });
		this->description = make_shared<TextBox>(Rectangle{ 1150, 810, 800, 420 }, text, TextAlign::LEFT, 1.0f, &this->games[*this->selectedGameIndex].font);
		addElement(this->description);
	}
	else
	{
		this->pictureGallery->setPictures(this->games[*this->selectedGameIndex].screenshots);

		const std::string author = I18n::instance().getSystemI18n().get("screen.selectGame.author",
			{ {"author", this->games[*this->selectedGameIndex].author} });
		this->info->setFont(&this->games[*this->selectedGameIndex].font);
		this->info->setText(author);
		
		const std::string text = I18n::instance().getSystemI18n().get("screen.selectGame.dynamicDescription",
			{ {"description", this->games[*this->selectedGameIndex].description} });
		this->description->setFont(&this->games[*this->selectedGameIndex].font);
		this->description->setText(text);
	}
}

void SelectGameScreen::readGameInfo()
{
	namespace fs = std::filesystem;

	for (auto& game : fs::directory_iterator(PathProvider::getGamesPath()))
	{
		fs::path systemCurrentLangFile = game.path() /
			(PathProvider::getFolder(ResourcesFolder::LANGS) +
			I18n::instance().getSystemI18n().getCurrentLanguage().info.id + ".json");
		if(exists(systemCurrentLangFile))
		{
			this->games.emplace_back(readGameInfoFromLang(systemCurrentLangFile, true));
		}
		else
		{
			fs::path gameConfigFile = game.path() / PathProvider::getConfigPath();
			if (exists(gameConfigFile))
			{
				json j = Utils::loadJsonFile(gameConfigFile.string(), false);
				std::string currentLang = j["currentLanguage"];

				fs::path gameCurrentLangFile = game.path() / PathProvider::getConfigPath();
				this->games.emplace_back(readGameInfoFromLang(gameCurrentLangFile, false));
			}
			else
			{
				std::cout << "ERROR! No config file found in game " << game.path().string() << std::endl;
			}
		}
	}
}

GameInfo SelectGameScreen::readGameInfoFromLang(const std::filesystem::path & langFileName, bool isMatchLanguage)
{
	namespace fs = std::filesystem;

	fs::path gameFolder = langFileName.parent_path().parent_path();
	GameInfo gameInfo;
	json j = Utils::loadJsonFile(langFileName.string(), false);
	gameInfo.name = j["info"]["name"];
	gameInfo.description = j["info"]["description"];
	gameInfo.author = j["info"]["author"];
	gameInfo.isMatchCurrentLanguage = isMatchLanguage;

	const std::string textNeedFont = gameInfo.name + gameInfo.description + gameInfo.author;
	gameInfo.font = RaylibUtils::getContainTextFont(gameFolder.string() + '/' +
		PathProvider::getFolder(ResourcesFolder::FONTS) + j["font"].get<string>(), textNeedFont);

	const fs::path gameHighlightFolder = gameFolder / PathProvider::getFolder(ResourcesFolder::HIGHLIGHT_SCREENSHOTS);
	for (const auto& highlightPic : fs::directory_iterator(gameHighlightFolder))
	{
		gameInfo.screenshots.emplace_back(FileSource::NONE, highlightPic.path().string());
	}

	return gameInfo;
}
