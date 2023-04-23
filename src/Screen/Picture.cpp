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
	image.Resize(realWidth, realWidth * (image.width / image.height));
	this->spriteTexture = image;
		
	this->textureFrameNum = textureFrameNum;

	this->hitbox = Rectangle(RaylibUtils::getWindowWidth() * position.x - static_cast<float>(spriteTexture.width) / 2,
		RaylibUtils::getWindowHeight() * position.y - this->getHeight() / 2, spriteTexture.width, this->getHeight());

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
