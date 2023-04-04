#pragma once
#include <raylib-cpp.hpp>

namespace RaylibUtils
{
	int getWindowWidth();
	int getWindowHeight();

	raylib::Font getContainTextFont(const std::string& fileName, const std::string& text);

	void drawTextBoxed(const raylib::Font& font, const std::string& text, const raylib::Rectangle& rec,
		const float& fontSize, const float& spacing, const raylib::Color& tint);
}

