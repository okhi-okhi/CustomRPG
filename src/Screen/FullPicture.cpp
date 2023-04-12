#include "FullPicture.h"
#include "../System/PathProvider.h"
#include "../Utils/RaylibUtils.h"

FullPicture::FullPicture(const std::string& fileName, const int textureFrameNum)
{
	this->elementType = elementTypes::FULL_PICTURE;

	raylib::Image image(PathProvider::instance().getResourcesPath() + fileName);
	image.Resize(RaylibUtils::getWindowWidth(), RaylibUtils::getWindowHeight());
	this->spriteTexture = image;

	this->textureFrameNum = textureFrameNum;
	this->position = Vector2(0.0f, 0.0f);
	this->currentFrame = 0;
}

void FullPicture::draw()
{
	Picture::draw();
}

FullPicture* FullPicture::clone() const
{
	return new FullPicture(*this);
}
