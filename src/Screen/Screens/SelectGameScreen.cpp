#include "SelectGameScreen.h"
#include <filesystem>
#include "../FullPicture.h"
#include "../ScrollList.h"
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

	const auto gameList =
		make_shared<ScrollList>(Rectangle(300, 540, 500, 800), 8, -1, gameNames,
			48.0f, TextAlign::CENTER, 0.0f, fonts, "screens/button_tile_1.png", "screens/scroll_bar.png", "screens/button_tile_1.png", [this] { showGameInfo(); });
	addElement(gameList);
	this->selectedGameIndex = &gameList->getCurrentIndex();
}

void SelectGameScreen::showGameInfo()
{
	if(!this->isAnyGameSelected)
	{
		this->isAnyGameSelected = true;
		this->pictureGallery = make_shared<PictureGallery>(Rectangle(1150, 300, 640, 480), this->games[*this->selectedGameIndex].screenshots);
		addElement(this->pictureGallery);
		addElement(make_shared<Button>(Vector2(750, 300), Picture({ "screens/arrow_left.png" }, 2, 64), [this] { pictureGallery->previousPicture(); }));
		addElement(make_shared<Button>(Vector2(1550, 300), Picture({ "screens/arrow_right.png" }, 2, 64), [this] { pictureGallery->nextPicture(); }));

		std::string nameAndAuthor = I18n::instance().getSystemI18n().get("screen.selectGame.nameAndAuthor",
			{ {"name", this->games[*this->selectedGameIndex].name},
			  {"author", this->games[*this->selectedGameIndex].author} });
		this->info = make_shared<Text>(Vector2(800, 597), nameAndAuthor, 48.0f, TextAlign::LEFT, 1.0f, &this->games[*this->selectedGameIndex].font);
		addElement(this->info);

		std::string text = I18n::instance().getSystemI18n().get("screen.selectGame.dynamicDescription",
			{ {"description", this->games[*this->selectedGameIndex].description} });
		this->description = make_shared<TextBox>(Rectangle(1600, 1050, 800, 400), text, 48.0f, TextAlign::LEFT, 1.0f, &this->games[*this->selectedGameIndex].font);
		addElement(this->description);
	}
	else
	{
		this->pictureGallery->setPictures(this->games[*this->selectedGameIndex].screenshots);

		const std::string nameAndAuthor = I18n::instance().getSystemI18n().get("screen.selectGame.nameAndAuthor",
			{ {"name", this->games[*this->selectedGameIndex].name},
			  {"author", this->games[*this->selectedGameIndex].author} });
		this->info->setText(nameAndAuthor, &this->games[*this->selectedGameIndex].font);
		
		const std::string text = I18n::instance().getSystemI18n().get("screen.selectGame.dynamicDescription",
			{ {"description", this->games[*this->selectedGameIndex].description} });
		this->description->setText(text, &this->games[*this->selectedGameIndex].font);
	}
}

void SelectGameScreen::readGameInfo()
{
	namespace fs = std::filesystem;

	for (auto& game : fs::directory_iterator(PathProvider::instance().getGamesPath()))
	{
		fs::path systemCurrentLangFile = game.path();
		systemCurrentLangFile /= PathProvider::instance().getFolder(ResourcesFolder::LANGS);
		systemCurrentLangFile /= I18n::instance().getSystemI18n().getCurrentLanguage().info.id + ".json";
		if(exists(systemCurrentLangFile))
		{
			this->games.emplace_back(readGameInfoFromJson(game.path().string(), systemCurrentLangFile.string()));
			//TODO match language
		}
		else
		{
			fs::path systemDefaultLangFile = game.path();
			systemDefaultLangFile /= PathProvider::instance().getFolder(ResourcesFolder::LANGS);
			systemDefaultLangFile /= I18n::instance().getSystemI18n().getDefaultLanguage().info.id + ".json";
			if(exists(systemDefaultLangFile))
			{
				this->games.emplace_back(readGameInfoFromJson(game.path().string(), systemDefaultLangFile.string()));
			}
			else
			{
				fs::path gameConfigFile = game.path();
				gameConfigFile /= PathProvider::instance().getConfigPath();
				if (exists(gameConfigFile))
				{
					json j = Utils::readJsonFile(gameConfigFile.string(), false);
					std::string currentLang = j["currentLanguage"];

					fs::path gameCurrentLangFile = game.path();
					gameCurrentLangFile /= PathProvider::instance().getConfigPath();
					this->games.emplace_back(readGameInfoFromJson(game.path().string(), gameCurrentLangFile.string()));
				}
				else
				{
					std::cout<< "ERROR! No config file found in game " << game.path().string() << std::endl;
				}
			}
		}
	}
}

GameInfo SelectGameScreen::readGameInfoFromJson(const std::string& gamePath, const std::string& langFileName)
{
	namespace fs = std::filesystem;

	GameInfo gameInfo;
	json j = Utils::readJsonFile(langFileName, false);
	gameInfo.name = j["info"]["name"];
	gameInfo.description = j["info"]["description"];
	gameInfo.author = j["info"]["author"];

	const std::string textNeedFont = gameInfo.name + gameInfo.description + gameInfo.author;
	gameInfo.font = RaylibUtils::getContainTextFont(gamePath + '/' +
		PathProvider::instance().getFolder(ResourcesFolder::FONTS) + j["font"].get<string>(), textNeedFont);

	fs::path gameHighlightFolder = gamePath;
	gameHighlightFolder /= PathProvider::instance().getFolder(ResourcesFolder::HIGHLIGHT_SCREENSHOTS);
	for (const auto& highlightPic : fs::directory_iterator(gameHighlightFolder))
	{
		gameInfo.screenshots.emplace_back(FileSource::NONE, highlightPic.path().string());
	}

	return gameInfo;
}
