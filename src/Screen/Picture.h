#pragma once
#include <Image.hpp>
#include <memory>
#include <Texture.hpp>
#include "Element.h"
#include "../../System/PathProvider.h"

enum class ScaleMode
{
	NN,
	BICUBIC,
};

class Picture : public Element
{
protected:
	Texture2D spriteTexture;
	int textureFrameNum;
	int currentFrame;

public:
	Picture() : spriteTexture(), textureFrameNum(0), currentFrame(0) {}
	explicit Picture(const File& file, ScaleMode mode = ScaleMode::NN);
	Picture(raylib::Vector2 pos, const File& file, ScaleMode mode = ScaleMode::NN);
	Picture(const File& file, int textureFrameNum, int width, ScaleMode mode = ScaleMode::NN);
	Picture(raylib::Vector2 pos, const File& file, int textureFrameNum, int width, ScaleMode mode = ScaleMode::NN);

	void draw() override;
	void updatePosition() override;

	void setCurrentFrame(int frame);

	const Texture2D& getSpriteTexture() const { return this->spriteTexture; }
	float getHeight() const { return static_cast<float>(this->spriteTexture.height) / static_cast<float>(this->textureFrameNum); }
	const int& getCurrentFrame() const { return this->currentFrame; }
};

class PictureBuilder : public ElementBuilder<PictureBuilder>
{
protected:
    File file{};
    int textureFrameNum = 1;
    int width = -1;
    ScaleMode scaleMode = ScaleMode::NN;

public:
    PictureBuilder() = default;

    PictureBuilder& setFile(const File& file) {
        this->file = file;
        return *this;
    }

    PictureBuilder& setTextureFrameNum(const int textureFrameNum) {
        this->textureFrameNum = textureFrameNum;
        return *this;
    }

    PictureBuilder& setWidth(const int width) {
        this->width = width;
        return *this;
    }

    PictureBuilder& setScaleMode(const ScaleMode scaleMode) {
        this->scaleMode = scaleMode;
        return *this;
    }

    shared_ptr<Element> build() const override
    {
        return make_shared<Picture>(this->position, this->file, this->textureFrameNum, this->width, this->scaleMode);
    }
};