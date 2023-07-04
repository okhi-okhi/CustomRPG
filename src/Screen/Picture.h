#pragma once
#include <Image.hpp>
#include "Element.h"
#include "../../System/PathProvider.h"

class Picture : public Element
{
protected:
	Texture2D spriteTexture;
	int textureFrameNum;
	int currentFrame;

public:
	Picture() : spriteTexture(), textureFrameNum(0), currentFrame(0) {}
	explicit Picture(const std::string& fileName, ParentFolder parentFolder = ParentFolder::AUTO);
	Picture(const std::string& fileName, int textureFrameNum,
		int width, ParentFolder parentFolder = ParentFolder::AUTO);
	Picture(raylib::Vector2 pos, const std::string& fileName,
		int textureFrameNum, int width, ParentFolder parentFolder = ParentFolder::AUTO);

	void draw() override;
	void updatePosition() override;

	void setCurrentFrame(int frame);

	const Texture2D& getSpriteTexture() const { return this->spriteTexture; }
	float getHeight() const { return static_cast<float>(this->spriteTexture.height) / static_cast<float>(this->textureFrameNum); }
	const int& getCurrentFrame() const { return this->currentFrame; }
};

