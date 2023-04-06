#pragma once
#include "Image.hpp"

class Picture
{
private:
	Texture2D spriteTexture;
	Vector2 position;
	int textureFrameNum;

	int currentFrame;

public:
	Picture() = default;
	Picture(const std::string& fileName, Vector2 position, int textureFrameNum, float zoomPercent);

	void draw() const;

	void setCurrentFrame(int frame);

	const Texture2D& getSpriteTexture() const { return this->spriteTexture; }
	const Vector2& getPosition() const { return this->position; }
	float getHeight() const { return static_cast<float>(this->spriteTexture.height) / this->textureFrameNum; }
	const int& getCurrentFrame() const { return this->currentFrame; }
};

