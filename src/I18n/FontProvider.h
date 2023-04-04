#pragma once
#include <raylib-cpp.hpp>
#include "../Utils/Singleton.h"

struct FontsWrapper
{
	raylib::Font defaultFont;
	raylib::Font currentFont;
};

class FontProvider : public Singleton<FontProvider>
{
private:
	FontsWrapper systemFont;
	FontsWrapper gameFont;
	raylib::Font defaultFont;

public:
	explicit FontProvider(token) { defaultFont = GetFontDefault(); }
	void loadSystemFont(const std::string& currentLanguage, const std::string& defaultLanguage);
	void loadGameFont(const std::string& currentLanguage, const std::string& defaultLanguage);

	const raylib::Font& get(const std::string& key) const;
};

