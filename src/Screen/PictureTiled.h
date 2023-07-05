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

