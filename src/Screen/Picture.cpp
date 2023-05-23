#include "Picture.h"
#include "../System/Exceptions.hpp"
#include "../System/PathProvider.h"
#include "../Utils/RaylibUtils.h"

Picture::Picture(const std::string& fileName, const int textureFrameNum, const int width) :
	Picture(fileName, Vector2(0, 0), textureFrameNum, width)
{
}

Picture::Picture(const std::string& fileName, const Vector2 position, const int textureFrameNum, int width)
{
	this->elementType = elementTypes::PICTURE;

	width = static_cast<int>(RaylibUtils::getRealLength(width));
	raylib::Image image(PathProvider::instance().get(resourcesFolder::TEXTURES, fileName));
	image.Resize(width, static_cast<int>(width * static_cast<float>(image.height) / static_cast<float>(image.width)));
	this->spriteTexture = image;
		
	this->textureFrameNum = textureFrameNum;

	this->position = position;
	Picture::updatePosition();

	this->hitbox.emplace_back(
		Rectangle(RaylibUtils::getRealLength(position.x) - static_cast<float>(spriteTexture.width) / 2,
				  RaylibUtils::getRealLength(position.y) - this->getHeight() / 2,
				  static_cast<float>(spriteTexture.width), this->getHeight()));

	this->currentFrame = 0;
}

Picture::Picture(const std::string& fileName, const int textureFrameNum, const int tileWidth, const Vector2 tiledBounds) :
	Picture(fileName, Vector2(0, 0), textureFrameNum, tileWidth, tiledBounds)
{
}

Picture::Picture(const std::string& fileName, const Vector2 position,
	const int textureFrameNum, int tileWidth, Vector2 tiledBounds)
{
	this->elementType = elementTypes::PICTURE;

	tileWidth = static_cast<int>(RaylibUtils::getRealLength(tileWidth));
	raylib::Image image(PathProvider::instance().get(resourcesFolder::TEXTURES, fileName));
	image.ResizeNN(tileWidth, static_cast<int>(tileWidth * static_cast<float>(image.height) / static_cast<float>(image.width)));

	const int imageFrameHeight = image.height / textureFrameNum;

	tiledBounds = RaylibUtils::getRealLength(tiledBounds);
	raylib::Image tiledImage = GenImageColor(static_cast<int>(tiledBounds.x), static_cast<int>(tiledBounds.y * textureFrameNum), BLANK);
	for(int frame = 0; frame < textureFrameNum; frame++)
	{
		for (int y = tiledBounds.y * frame; y < tiledBounds.y * (frame + 1); y += imageFrameHeight)
		{
			for (int x = 0; x < tiledBounds.x; x += image.width)
			{
				tiledImage.Draw(image,
					Rectangle(0, imageFrameHeight * frame, static_cast<float>(image.width), static_cast<float>(imageFrameHeight)),
					Rectangle(x, y, static_cast<float>(image.width), static_cast<float>(imageFrameHeight)), WHITE);
			}
		}
	}
	this->spriteTexture = tiledImage;

	this->textureFrameNum = textureFrameNum;

	this->position = position;
	Picture::updatePosition();

	this->hitbox.emplace_back(
		Rectangle(RaylibUtils::getRealLength(position.x) - static_cast<float>(spriteTexture.width) / 2,
				  RaylibUtils::getRealLength(position.y) - this->getHeight() / 2,
				  static_cast<float>(spriteTexture.width), this->getHeight()));

	this->currentFrame = 0;
}

void Picture::draw()
{
	const raylib::Rectangle sourceRec(0, static_cast<float>(this->currentFrame) * this->getHeight(),
		static_cast<float>(this->spriteTexture.width), this->getHeight());
	DrawTextureRec(this->spriteTexture, sourceRec, this->position, WHITE);
}

Picture* Picture::clone() const
{
	return new Picture(*this);
}

void Picture::updatePosition()
{
	this->position = Vector2(RaylibUtils::getRealLength(position.x) - static_cast<float>(spriteTexture.width) / 2,
		RaylibUtils::getRealLength(position.y) - this->getHeight() / 2);
	this->hitbox.clear();
	this->hitbox.emplace_back(
		Rectangle(this->position.x, this->position.y,
			static_cast<float>(spriteTexture.width), this->getHeight()));
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
