#pragma once
#include "Picture.h"

class PictureTiled;

class PictureTiledBuilder final : public ElementBuilder<PictureTiledBuilder, PictureTiled>
{
private:
    File file{};
    int textureFrameNum = 1;
    int tileWidth = 32;
    ScaleMode scaleMode = ScaleMode::NN;
    raylib::Vector2 tiledBounds;

public:
    PictureTiledBuilder() = default;

    PictureTiledBuilder& setFile(const File& file) {
        this->file = file;
        return *this;
    }

    PictureTiledBuilder& setTextureFrameNum(const int textureFrameNum) {
        this->textureFrameNum = textureFrameNum;
        return *this;
    }

    PictureTiledBuilder& setTileWidth(const int width) {
        this->tileWidth = width;
        return *this;
    }

    PictureTiledBuilder& setScaleMode(const ScaleMode scaleMode) {
        this->scaleMode = scaleMode;
        return *this;
    }

    PictureTiledBuilder& setTiledBounds(const raylib::Vector2& tiledBounds) {
        this->tiledBounds = tiledBounds;
        return *this;
    }

    shared_ptr<PictureTiled> build() const override;
};

class PictureTiled final : public Picture
{
public:
    static PictureTiledBuilder builder() { return {}; }
	PictureTiled(raylib::Vector2 pos, const File& file,
		int textureFrameNum, int tileWidth, raylib::Vector2 tiledBounds);
};