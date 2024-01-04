#pragma once
#include "Picture.h"

class PictureTiled final : public Picture
{
public:
	PictureTiled(const File& file, int textureFrameNum,
		int tileWidth, raylib::Vector2 tiledBounds);
	PictureTiled(raylib::Vector2 pos, const File& file,
		int textureFrameNum, int tileWidth, raylib::Vector2 tiledBounds);
};

class PictureTiledBuilder final : public PictureBuilder
{
private:
    raylib::Vector2 tiledBounds;

public:
    PictureTiledBuilder() = default;

    PictureTiledBuilder& setTiledBounds(const raylib::Vector2& tiledBounds) {
        this->tiledBounds = tiledBounds;
        return *this;
    }

    shared_ptr<Element> build() const override
    {
        return make_shared<PictureTiled>(this->position, this->file, this->textureFrameNum, this->width, this->tiledBounds);
    }
};