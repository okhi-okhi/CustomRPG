#include "SelectGameScreen.h"
#include <filesystem>
#include "../FullPicture.h"
#include "../PictureGallery.h"

SelectGameScreen::SelectGameScreen() : Screen(ScreenType::SELECT_GAME, "selectGame")
{
	namespace fs = std::filesystem;
	addElement(make_shared<FullPicture>(File("screens/main/background.png"), 1));

	std::vector<File> files;
	for(auto& game : fs::directory_iterator(PathProvider::instance().getGamesPath()))
	{
		auto gameHighlightFolder = game.path();
		gameHighlightFolder += '/';
		gameHighlightFolder += PathProvider::instance().getFolder(ResourcesFolder::HIGHLIGHT_SCREENSHOTS);
		for (const auto& highlightPic : fs::directory_iterator(gameHighlightFolder))
		{
			files.emplace_back(FileSource::NONE, highlightPic.path().string());
		}
	}
	auto gallery = make_shared<PictureGallery>(Rectangle(960, 540, 640, 360), files);
	addElement(gallery);

	addButton(make_shared<Button>(Vector2(640, 540), Picture({ "screens/arrow_left.png" }, 2, 64), [gallery] { gallery->previousPicture(); }));
	addButton(make_shared<Button>(Vector2(1280, 540), Picture({ "screens/arrow_right.png" }, 2, 64), [gallery] { gallery->nextPicture(); }));
}