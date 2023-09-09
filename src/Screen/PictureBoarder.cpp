#include "PictureBoarder.h"
#include "../Utils/RaylibUtils.h"

PictureBoarder::PictureBoarder(const raylib::Vector2 pos, const File& conner, const File& side,
							   const File& padding, int tileWidth, raylib::Vector2 bounds)
{
	this->elementType = ElementType::PICTURE_BOARDER;
	this->position = RaylibUtils::getRealLength(pos);
	this->textureFrameNum = textureFrameNum;
	this->currentFrame = 0;
	tileWidth = static_cast<int>(RaylibUtils::getRealLength(tileWidth));
	raylib::Image connerImage(PathProvider::instance().get(conner, ResourcesFolder::TEXTURES));
	connerImage.ResizeNN(tileWidth, tileWidth);
	raylib::Image sideImage(PathProvider::instance().get(side, ResourcesFolder::TEXTURES));
	sideImage.ResizeNN(tileWidth, tileWidth);
	raylib::Image paddingImage(PathProvider::instance().get(padding, ResourcesFolder::TEXTURES));
	paddingImage.ResizeNN(tileWidth, tileWidth);
	bounds = RaylibUtils::getRealLength(bounds);
	raylib::Image image = GenImageColor(static_cast<int>(bounds.x / tileWidth) * tileWidth, static_cast<int>(bounds.y / tileWidth) * tileWidth, BLANK);
}

PictureBoarder::PictureBoarder(raylib::Vector2 pos, const File& conner, const File& side, int tileWidth,
	raylib::Vector2 bounds)
{
}
