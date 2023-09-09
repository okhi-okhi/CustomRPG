#include "PictureTiled.h"
#include "../Utils/RaylibUtils.h"

PictureTiled::PictureTiled(const File& file, const int textureFrameNum,
	const int tileWidth, const raylib::Vector2 tiledBounds) :
	PictureTiled(raylib::Vector2{ 0, 0 }, file, textureFrameNum, tileWidth, tiledBounds)
{
}

PictureTiled::PictureTiled(const raylib::Vector2 pos, const File& file,
	const int textureFrameNum, int tileWidth, raylib::Vector2 tiledBounds)
{
	this->elementType = ElementType::PICTURE_TILED;
	this->position = RaylibUtils::getRealLength(pos);
	this->textureFrameNum = textureFrameNum;
	this->currentFrame = 0;

	tileWidth = static_cast<int>(RaylibUtils::getRealLength(tileWidth));
	raylib::Image image(PathProvider::instance().get(file, ResourcesFolder::TEXTURES));
	image.ResizeNN(tileWidth, static_cast<int>(tileWidth * static_cast<float>(image.height) / static_cast<float>(image.width)));

	const int imageFrameHeight = image.height / textureFrameNum;

	tiledBounds = RaylibUtils::getRealLength(tiledBounds);
	raylib::Image tiledImage = GenImageColor(static_cast<int>(tiledBounds.x), static_cast<int>(tiledBounds.y * textureFrameNum), BLANK);
	for (int frame = 0; frame < textureFrameNum; frame++)
	{
		for (int y = static_cast<int>(tiledBounds.y) * frame; y < static_cast<int>(tiledBounds.y) * (frame + 1); y += imageFrameHeight)
		{
			for (int x = 0; x < static_cast<int>(tiledBounds.x); x += image.width)
			{
				tiledImage.Draw(image,
					Rectangle(0, static_cast<float>(imageFrameHeight * frame), static_cast<float>(image.width), static_cast<float>(imageFrameHeight)),
					Rectangle(static_cast<float>(x), static_cast<float>(y), static_cast<float>(image.width), static_cast<float>(imageFrameHeight)), WHITE);
			}
		}
	}
	this->spriteTexture = tiledImage;
	Picture::updatePosition();
}