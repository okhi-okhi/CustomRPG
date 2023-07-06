#pragma once
#include <raylib-cpp.hpp>

namespace RaylibUtils
{
	int getWindowWidth();
	int getWindowHeight();

	float getRealLength(float length);
	float getRealLength(int length);
	Vector2 getRealLength(Vector2 vector2);
	Rectangle getRealLength(Rectangle rec);

	bool checkCollisionPointRecs(const raylib::Vector2& point, const std::vector<raylib::Rectangle>& recs);

	raylib::Font getContainTextFont(const std::string& fileName, const std::string& text);
	int* codepointRemoveDuplicates(const int* codepoints, int codepointCount, int* codepointsResultCount);

	void drawTextBoxed(const raylib::Font& font, const std::string& text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint);
}

