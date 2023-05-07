#include "Picture.h"
#include "../System/Exceptions.hpp"
#include "../System/PathProvider.h"
#include "../Utils/RaylibUtils.h"

Picture::Picture(const std::string& fileName, const Vector2 position,
	const int textureFrameNum, const float zoomPercent)
{
	this->elementType = elementTypes::PICTURE;

	raylib::Image image(PathProvider::instance().get(resourcesFolder::TEXTURES, fileName));
	const int realWidth = static_cast<int>(RaylibUtils::getWindowWidth() * zoomPercent);
	image.Resize(realWidth, static_cast<int>(realWidth * static_cast<float>(image.height) / static_cast<float>(image.width)));
	this->spriteTexture = image;
		
	this->textureFrameNum = textureFrameNum;

	this->hitbox = Rectangle(RaylibUtils::getWindowWidth() * position.x - static_cast<float>(spriteTexture.width) / 2,
		RaylibUtils::getWindowHeight() * position.y - this->getHeight() / 2, static_cast<float>(spriteTexture.width), this->getHeight());

	this->currentFrame = 0;
}

Picture::Picture(const std::string& fileName, const Vector2 position,
	const int textureFrameNum, const float tileZoomPercent, const Vector2 tileNumBounds)
{
	this->elementType = elementTypes::PICTURE;

	raylib::Image image(PathProvider::instance().get(resourcesFolder::TEXTURES, fileName));
	const int realWidth = static_cast<int>(RaylibUtils::getWindowWidth() * tileZoomPercent);
	image.ResizeNN(realWidth, static_cast<int>(realWidth * static_cast<float>(image.height) / static_cast<float>(image.width)));

	const int imageFrameHeight = image.height / textureFrameNum;
	const Vector2 realBounds(image.width * tileNumBounds.x, imageFrameHeight * tileNumBounds.y);

	raylib::Image tiledImage = GenImageColor(static_cast<int>(realBounds.x), static_cast<int>(realBounds.y * textureFrameNum), BLANK);
	for(int frame = 0; frame < textureFrameNum; frame++)
	{
		for (float y = realBounds.y * frame; y < realBounds.y * (frame + 1); y += imageFrameHeight)
		{
			for (float x = 0; x < realBounds.x; x += image.width)
			{
				tiledImage.Draw(image,
					Rectangle(0, imageFrameHeight * frame, static_cast<float>(image.width), static_cast<float>(imageFrameHeight)),
					Rectangle(x, y, static_cast<float>(image.width), static_cast<float>(imageFrameHeight)), WHITE);
			}
		}
	}
	this->spriteTexture = tiledImage;

	this->textureFrameNum = textureFrameNum;

	const Vector2 realPos(RaylibUtils::getWindowWidth() * position.x, RaylibUtils::getWindowHeight() * position.y);
	this->hitbox = Rectangle(realPos.x - static_cast<float>(spriteTexture.width) / 2.0f,
		realPos.y - this->getHeight() / 2, static_cast<float>(spriteTexture.width), this->getHeight());

	this->currentFrame = 0;
}

void Picture::draw()
{
	const raylib::Rectangle sourceRec(0, static_cast<float>(this->currentFrame) * this->getHeight(),
		static_cast<float>(this->spriteTexture.width), this->getHeight());
	DrawTextureRec(this->spriteTexture, sourceRec, getPosition(), WHITE);
}

Picture* Picture::clone() const
{
	return new Picture(*this);
}

void Picture::setCurrentFrame(const int frame)
{
	if(frame < this->textureFrameNum)
	{
		this->currentFrame = frame;
	}
	else
	{
		throw OutOfRangeException(frame, this->textureFrameNum);
	}
}
