#pragma once
#include "Picture.h"

class PictureTiled final : public Picture
{
public:
	PictureTiled(const std::string& fileName, int textureFrameNum,
		int tileWidth, raylib::Vector2 tiledBounds,
		ParentFolder parentFolder = ParentFolder::AUTO);
	PictureTiled(raylib::Vector2 pos, const std::string& fileName,
		int textureFrameNum, int tileWidth, raylib::Vector2 tiledBounds,
		ParentFolder parentFolder = ParentFolder::AUTO);
};

