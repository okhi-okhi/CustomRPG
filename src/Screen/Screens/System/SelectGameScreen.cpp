#include "SelectGameScreen.h"
#include <filesystem>
#include "../../FullPicture.h"
#include "../../ScrollList.h"
#include "../../PictureBorder.h"
#include "../../../I18n/FontProvider.h"
#include "../../../Utils/Utilities.h"
#include "../../../Utils/RaylibUtils.h"

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
		this->pictureGallery = make_shared<PictureGallery>(Rectangle{ 1300, 300, 640, 480 }, this->games[*this->selectedGameIndex].screenshots);
		addElement(this->pictureGallery);
		addElement(make_shared<Button>(Vector2{ 850, 300 }, Picture({ "screens/arrow_left.png" }, 2, 64), [this] { pictureGallery->previousPicture(); }));
		addElement(make_shared<Button>(Vector2{ 1700, 300 }, Picture({ "screens/arrow_right.png" }, 2, 64), [this] { pictureGallery->nextPicture(); }));

		const std::string nameAndAuthor = I18n::instance().getSystemI18n().get("screen.selectGame.nameAndAuthor",
			{ {"name", this->games[*this->selectedGameIndex].name},
			  {"author", this->games[*this->selectedGameIndex].author}});
		this->info = make_shared<Text>(Vector2{ 700, 600 }, nameAndAuthor, TextAlign::LEFT, 1.0f, &this->games[*this->selectedGameIndex].font);
		addElement(this->info);

		const std::string matchLanguageI18nKey = this->games[*this->selectedGameIndex].isMatchCurrentLanguage ?
			"screen.selectGame.isMatchLanguage" : "screen.selectGame.notMatchLanguage";
		this->matchLanguage = make_shared<Text>(Vector2{ 700, 820 }, matchLanguageI18nKey, TextAlign::LEFT, 1.0f);
		addElement(this->matchLanguage);

		std::string text = I18n::instance().getSystemI18n().get("screen.selectGame.dynamicDescription",
			{ {"description", this->games[*this->selectedGameIndex].description} });

		this->description = make_shared<TextBox>(Rectangle{ 1500, 790, 700, 450 }, text, TextAlign::LEFT, 1.0f, &this->games[*this->selectedGameIndex].font);
		addElement(this->description);

		addElement(make_shared<ButtonText>(Vector2{ 850, 900 }, Button(Picture({ "screens/button_1.png" }, 2, 300), [this] { startGame(); }), Text("screen.selectGame.startGame", TextAlign::CENTER, 1.0f)));
	}
	else
	{
		this->pictureGallery->setPictures(this->games[*this->selectedGameIndex].screenshots);

		const std::string nameAndAuthor = I18n::instance().getSystemI18n().get("screen.selectGame.nameAndAuthor",
			{ {"name", this->games[*this->selectedGameIndex].name},
			  {"author", this->games[*this->selectedGameIndex].author} });
		this->info->setFont(&this->games[*this->selectedGameIndex].font);
		this->info->setText(nameAndAuthor);

		const std::string matchLanguageStr = this->games[*this->selectedGameIndex].isMatchCurrentLanguage ?
			I18n::instance().getSystemI18n().get("screen.selectGame.isMatchLanguage") : I18n::instance().getSystemI18n().get("screen.selectGame.notMatchLanguage");
		this->matchLanguage->setText(matchLanguageStr);
		
		const std::string text = I18n::instance().getSystemI18n().get("screen.selectGame.dynamicDescription",
			{ {"description", this->games[*this->selectedGameIndex].description} });
		this->description->setFont(&this->games[*this->selectedGameIndex].font);
		this->description->setText(text);
	}
}

void SelectGameScreen::startGame() const
{
	PathProvider::setCurrentGamePath(this->games[*this->selectedGameIndex].path);
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

				fs::path gameCurrentLangFile = game.path() / 
					(PathProvider::getFolder(ResourcesFolder::LANGS) +
					 currentLang + ".json");
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

	GameInfo gameInfo;
	gameInfo.path = langFileName.parent_path().parent_path().string();
	json j = Utils::loadJsonFile(langFileName.string(), false);
	gameInfo.name = j["info"]["name"];
	gameInfo.description = j["info"]["description"];
	gameInfo.author = j["info"]["author"];
	gameInfo.isMatchCurrentLanguage = isMatchLanguage;

	const std::string textNeedFont = gameInfo.name + gameInfo.description + gameInfo.author;
	gameInfo.font = RaylibUtils::getContainTextFont(gameInfo.path + '/' +
		PathProvider::getFolder(ResourcesFolder::FONTS) + j["font"].get<string>(), textNeedFont);

	const fs::path gameHighlightFolder = gameInfo.path + '/' + PathProvider::getFolder(ResourcesFolder::HIGHLIGHT_SCREENSHOTS);
	for (const auto& highlightPic : fs::directory_iterator(gameHighlightFolder))
	{
		gameInfo.screenshots.emplace_back(FileSource::NONE, highlightPic.path().string());
	}

	return gameInfo;
}
