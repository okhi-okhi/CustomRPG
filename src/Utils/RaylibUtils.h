#pragma once
#include <raylib-cpp.hpp>

namespace RaylibUtils
{
	int getWindowWidth();
	int getWindowHeight();

	raylib::Font getContainTextFont(const std::string& fileName, const std::string& text);
	int* codepointRemoveDuplicates(const int* codepoints, int codepointCount, int* codepointsResultCount);

	void drawTextBoxed(const raylib::Font& font, const std::string& text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint);
}

