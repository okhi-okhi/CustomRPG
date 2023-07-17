#pragma once
#include <Font.hpp>
#include "../Screen.h"
#include "../PictureGallery.h"
#include "../TextBox.h"

struct GameInfo
{
	std::string name;
	std::string description;
	std::string author;
	raylib::Font font;
	std::vector<File> screenshots;
	bool matchCurrentLanguage;

	GameInfo() : matchCurrentLanguage(false) {}
	GameInfo(std::string name, std::string description, std::string author, raylib::Font font, std::vector<File> screenshots) :
		name(std::move(name)), description(std::move(description)), author(std::move(author)), font(std::move(font)), screenshots(std::move(screenshots)), matchCurrentLanguage(false) {}
};

class SelectGameScreen final : public Screen
{
private:
	std::vector<GameInfo> games;
	bool isAnyGameSelected;
	const int* selectedGameIndex;
	shared_ptr<PictureGallery> pictureGallery;
	shared_ptr<Text> info;
	shared_ptr<TextBox> description;

public:
	SelectGameScreen();

	void showGameInfo();

	void readGameInfo();
	GameInfo readGameInfoFromJson(const std::string& gamePath, const std::string& langFileName);
};

