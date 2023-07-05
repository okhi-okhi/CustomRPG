#include "Picture.h"
#include "ScreenManager.h"
#include "../System/Exceptions.hpp"
#include "../Utils/RaylibUtils.h"

Picture::Picture(const File& file, const int textureFrameNum, const int width) :
	Picture(Vector2(0, 0), file, textureFrameNum, width)
{
}

Picture::Picture(const raylib::Vector2 pos, const File& file,
	const int textureFrameNum, int width)
{
	this->elementType = ElementType::PICTURE;

	raylib::Image image(PathProvider::instance().get(file, ResourcesFolder::TEXTURES));
	width = static_cast<int>(RaylibUtils::getRealLength(width));
	image.Resize(width, static_cast<int>(std::ceil(width * static_cast<float>(image.height) / static_cast<float>(image.width))));
	this->spriteTexture = image;
		
	this->textureFrameNum = textureFrameNum;

	this->position = RaylibUtils::getRealLength(pos);
	Picture::updatePosition();

	this->currentFrame = 0;
}

void Picture::draw()
{
	const raylib::Rectangle sourceRec(0, static_cast<float>(this->currentFrame) * this->getHeight(),
		static_cast<float>(this->spriteTexture.width), this->getHeight());
	DrawTextureRec(this->spriteTexture, sourceRec, this->originPos, WHITE);
}

void Picture::updatePosition()
{
	this->originPos = 
		Vector2(this->position.x - static_cast<float>(spriteTexture.width) / 2, this->position.y - this->getHeight() / 2);
	this->hitbox.clear();
	this->hitbox.emplace_back(
		Rectangle(this->originPos.x, this->originPos.y,
			static_cast<float>(spriteTexture.width), this->getHeight()));
	ScreenManager::instance().updateHitbox();
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
