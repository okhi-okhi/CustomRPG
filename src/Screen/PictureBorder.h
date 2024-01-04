#pragma once
#include "Picture.h"

class PictureBorder final : public Picture
{
private:
	raylib::Image generateBorder(const raylib::Image& cornerImage,
		const raylib::Image& sideImage, const raylib::Image& paddingImage,
		int textureFrameNum, int tileWidth, raylib::Vector2 bounds, bool needPadding) const;
public:
	PictureBorder(raylib::Vector2 pos, const File& corner,
		const File& side, const File& padding, int textureFrameNum,
		int tileWidth, raylib::Vector2 bounds);
	PictureBorder(raylib::Vector2 pos, const File& corner,
		const File& side, int textureFrameNum, int tileWidth, raylib::Vector2 bounds);
};

