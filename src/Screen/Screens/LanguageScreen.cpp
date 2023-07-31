#include "LanguageScreen.h"
#include <fstream>
#include "../ScreenManager.h"
#include "../ScrollList.h"
#include "../../I18n/I18n.h"
#include "../../I18n/FontProvider.h"
#include "../../System/PathProvider.h"
#include "../../System/SystemConfig.h"
#include "../../Utils/Utilities.h"
#include "../../Utils/RaylibUtils.h"

LanguageScreen::LanguageScreen() : Screen(ScreenType::LANGUAGE, "language")
{
	addElement(make_shared<Picture>(Vector2(960, 540), File("screens/setting/background.png"), 1, 540));
	
	int idx = 0;
	int currentLangIdx = 0;
	std::vector<std::string> languages;
	std::vector<const raylib::Font*> fonts;
	for (const auto& language : I18n::instance().getSystemI18n().getLanguages())
	{
		languages.push_back(I18n::instance().get("screen.language.language", { {"language", language.name} }));
		fonts.push_back(&language.font);
		if(language.id == I18n::instance().getSystemI18n().getCurrentLanguage().info.id)
		{
			currentLangIdx = idx;
		}
		idx++;
	}
	const auto languageList =
		make_shared<ScrollList>(Rectangle(960, 540, 400, 600), 8, currentLangIdx, languages,
			32.0f, TextAlign::CENTER, 0.0f, fonts, "screens/button_tile_1.png", "screens/scroll_bar.png", "screens/button_tile_1.png", [this] { changeLanguage(); });
	addElement(languageList);
	this->selectedLangIndex = &languageList->getCurrentIndex();

	addElement(make_shared<ButtonText>(Vector2(960, 770),
		Button(Picture({ "screens/button_1.png" }, 2, 384), closeLanguage),
		Text("screen.language.button1", 48, TextAlign::CENTER, 0.0f)));
}

void LanguageScreen::changeLanguage() const
{
	closeLanguage();
	const string selectLanguage = I18n::instance().getSystemI18n().getLanguages()[*this->selectedLangIndex].id;
	if(I18n::instance().getSystemI18n().getCurrentLanguage().info.id != selectLanguage)
	{
		I18n::instance().getSystemI18n().loadLanguage(selectLanguage);
		SystemConfig::instance().setCurrentLanguage(selectLanguage);
		FontProvider::instance().loadSystemFont();
		ScreenManager::instance().delayReload();
		try {
			std::ifstream inFile(PathProvider::instance().getConfigPath());
			json j = json::parse(inFile);
			nlohmann::ordered_json j2;
			j2["currentLanguage"] = selectLanguage;
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
	}
}

void LanguageScreen::closeLanguage()
{
	ScreenManager::instance().removeScreen(ScreenType::LANGUAGE);
}
