#pragma once
#include "Picture.h"
class PictureBorder : public Picture
{
public:
	PictureBorder(raylib::Vector2 pos, const File& corner,
		const File& side, const File& padding, int textureFrameNum, int tileWidth, raylib::Vector2 bounds);
	PictureBorder(raylib::Vector2 pos, const File& corner,
		const File& side, int tileWidth, raylib::Vector2 bounds);
};

