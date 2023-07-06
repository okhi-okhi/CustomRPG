#include "FullPicture.h"
#include "../System/PathProvider.h"
#include "../Utils/RaylibUtils.h"

FullPicture::FullPicture(const File& file, const int textureFrameNum, const ScaleMode mode)
{
	this->elementType = ElementType::FULL_PICTURE;

	raylib::Image image(PathProvider::instance().get(file, ResourcesFolder::TEXTURES));
	switch (mode)
	{
	case ScaleMode::NN:
		image.ResizeNN(RaylibUtils::getWindowWidth(), RaylibUtils::getWindowHeight());
		break;

	case ScaleMode::BICUBIC:
		image.Resize(RaylibUtils::getWindowWidth(), RaylibUtils::getWindowHeight());
		break;
	}
	this->spriteTexture = image;

	this->textureFrameNum = textureFrameNum;
	this->position = Vector2(0.0f, 0.0f);
	this->hitbox.emplace_back(Rectangle(0.0f, 0.0f, static_cast<float>(spriteTexture.width), this->getHeight()));
	this->currentFrame = 0;
}

void FullPicture::draw()
{
	Picture::draw();
}

void FullPicture::updatePosition()
{
	Picture::updatePosition();
}
