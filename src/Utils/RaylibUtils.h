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

	std::vector<int> hexDecode(const std::string& str, unsigned char charsPerNum = 2);

	raylib::Font getContainTextFont(const std::string& fileName, const std::string& text);
	int* codepointRemoveDuplicates(const int* codepoints, int codepointCount, int* codepointsResultCount);
}

