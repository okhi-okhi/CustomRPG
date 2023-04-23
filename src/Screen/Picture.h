#pragma once
#include <Image.hpp>
#include "Element.h"

class Picture : public Element
{
protected:
	Texture2D spriteTexture;
	int textureFrameNum;
	int currentFrame;

public:
	Picture() : spriteTexture(), textureFrameNum(0), currentFrame(0) {}
	Picture(const std::string& fileName, Vector2 position, int textureFrameNum, float zoomPercent);

	void draw() override;
	Picture* clone() const override;

	void setCurrentFrame(int frame);

	const Texture2D& getSpriteTexture() const { return this->spriteTexture; }
	float getHeight() const { return static_cast<float>(this->spriteTexture.height) / static_cast<float>(this->textureFrameNum); }
	const int& getCurrentFrame() const { return this->currentFrame; }
};

