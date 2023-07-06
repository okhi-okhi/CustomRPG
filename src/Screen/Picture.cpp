#include "Picture.h"
#include "ScreenManager.h"
#include "../System/Exceptions.hpp"
#include "../Utils/RaylibUtils.h"

Picture::Picture(const File& file) :
	Picture(Vector2(0, 0), file)
{
}

Picture::Picture(const raylib::Vector2 pos, const File& file)
{
	this->elementType = ElementType::PICTURE;

	raylib::Image image(PathProvider::instance().get(file, ResourcesFolder::TEXTURES));
	this->spriteTexture = image;

	this->textureFrameNum = 1;

	this->position = pos;
	Picture::updatePosition();

	this->currentFrame = 0;
}

Picture::Picture(const File& file, const int textureFrameNum, const int width, const ScaleMode mode) :
	Picture(Vector2(0, 0), file, textureFrameNum, width, mode)
{
}

Picture::Picture(const raylib::Vector2 pos, const File& file,
	const int textureFrameNum, int width, const ScaleMode mode)
{
	this->elementType = ElementType::PICTURE;

	raylib::Image image(PathProvider::instance().get(file, ResourcesFolder::TEXTURES));
	width = static_cast<int>(RaylibUtils::getRealLength(width));
	switch (mode)
	{
		case ScaleMode::NN:
			image.ResizeNN(width, static_cast<int>(std::ceil(width * static_cast<float>(image.height) / static_cast<float>(image.width))));
			break;

		case ScaleMode::BICUBIC:
			image.Resize(width, static_cast<int>(std::ceil(width * static_cast<float>(image.height) / static_cast<float>(image.width))));
			break;
	}
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
	this->originPos = this->position -
		Vector2( static_cast<float>(this->spriteTexture.width) / 2, this->getHeight() / 2);
	this->hitbox.clear();
	this->hitbox.emplace_back(
		this->originPos.x, this->originPos.y,
		static_cast<float>(spriteTexture.width), this->getHeight());

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
