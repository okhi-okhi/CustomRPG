#pragma once
#include <raylib-cpp.hpp>
#include "I18n.h"
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

	static raylib::Font loadFont(const Language& lang, const std::string& rootPath);

public:
	explicit FontProvider(token) { defaultFont = GetFontDefault(); }
	void loadSystemFont();
	void loadGameFont();

	const raylib::Font& get(const std::string& key) const;
};

