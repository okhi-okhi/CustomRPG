#pragma once
#include "Picture.h"
class PictureBoarder : public Picture
{
public:
	PictureBoarder(raylib::Vector2 pos, const File& conner,
		const File& side, const File& padding, int tileWidth, raylib::Vector2 bounds);
	PictureBoarder(raylib::Vector2 pos, const File& conner,
		const File& side, int tileWidth, raylib::Vector2 bounds);
};

