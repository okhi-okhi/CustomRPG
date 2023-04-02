#pragma once
#include <string>
#include <raylib-cpp.hpp>

enum class buttonState
{
	IDLE = 0,
	HOVER
};

class Button
{
private:
	Texture2D spriteTexture;
	std::string i18nKey;
	Vector2 pos;
	buttonState buttonState;

public:
	Button() = default;
	Button(const std::string& fileName, const std::string& i18nKey, Vector2 pos, float zoomPercent);

	void draw() const;
};

