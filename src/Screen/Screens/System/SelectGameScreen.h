#pragma once
#include <filesystem>
#include <Font.hpp>
#include "../../Screen.h"
#include "../../PictureGallery.h"
#include "../../TextBox.h"

struct GameInfo
{
	std::string path;
	std::string name;
	std::string description;
	std::string author;
	raylib::Font font;
	std::vector<File> screenshots;
	bool isMatchCurrentLanguage;

	GameInfo() : isMatchCurrentLanguage(false) {}
	GameInfo(std::string name, std::string description, std::string author, raylib::Font font, std::vector<File> screenshots, bool isMatchCurrentLanguage) :
		name(std::move(name)), description(std::move(description)), author(std::move(author)), font(std::move(font)), screenshots(std::move(screenshots)), isMatchCurrentLanguage(isMatchCurrentLanguage) {}
};

class SelectGameScreen final : public Screen
{
private:
	std::vector<GameInfo> games;
	bool isAnyGameSelected;
	const int* selectedGameIndex;
	shared_ptr<PictureGallery> pictureGallery;
	shared_ptr<Text> info;
	shared_ptr<Text> matchLanguage;
	shared_ptr<TextBox> description;

	static void openMain();
	void showGameInfo();
	void startGame() const;

	void readGameInfo();
	static GameInfo readGameInfoFromLang(const std::filesystem::path& langFileName, bool isMatchLanguage);

public:
	SelectGameScreen();
};

