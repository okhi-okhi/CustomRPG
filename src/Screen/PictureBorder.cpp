#include "PictureBorder.h"
#include "../Utils/RaylibUtils.h"

PictureBorder::PictureBorder(const raylib::Vector2 pos, const File& corner, const File& side,
							   const File& padding, const int textureFrameNum, int tileWidth, raylib::Vector2 bounds)
{
	this->elementType = ElementType::PICTURE_BORDER;
	this->position = RaylibUtils::getRealLength(pos);
	this->textureFrameNum = textureFrameNum;
	this->currentFrame = 0;
	tileWidth = static_cast<int>(RaylibUtils::getRealLength(tileWidth));
	raylib::Image cornerImage(PathProvider::instance().get(corner, ResourcesFolder::TEXTURES));
	cornerImage.ResizeNN(tileWidth, tileWidth * this->textureFrameNum);
	raylib::Image sideImage(PathProvider::instance().get(side, ResourcesFolder::TEXTURES));
	sideImage.ResizeNN(tileWidth, tileWidth * this->textureFrameNum);
	raylib::Image paddingImage(PathProvider::instance().get(padding, ResourcesFolder::TEXTURES));
	paddingImage.ResizeNN(tileWidth, tileWidth * this->textureFrameNum);
	bounds = RaylibUtils::getRealLength(bounds);
	raylib::Image image = GenImageColor(static_cast<int>(bounds.x / tileWidth) * tileWidth, static_cast<int>(bounds.y / tileWidth) * tileWidth * this->textureFrameNum, BLANK);

	const int frameHeight = image.height / textureFrameNum;
	const int frameWidth = image.width;
	const int tileNumY = frameHeight / tileWidth;
	const int tileNumX = frameWidth / tileWidth;
	const int sideNum = frameWidth / tileWidth - 2;

	for (int frame = 0; frame < textureFrameNum; frame++)
	{
		int posY = frame * frameHeight;
		int cornerCount = 0;

		raylib::Image sideLeftImage = sideImage;
		sideLeftImage.RotateCCW();
		raylib::Image sideRightImage = sideImage;
		sideRightImage.RotateCW();
		raylib::Image sideBottomImage = sideImage;
		sideBottomImage.FlipVertical();

		for (int indexY = 0; indexY < tileNumY; indexY++, posY += tileWidth)
		{
			int posX = 0;
			for (int indexX = 0; indexX < tileNumX; indexX++, posX += tileWidth)
			{
				if (indexY >= 1 && indexY <= tileNumY - 2 && indexX >= 1 && indexX <= tileNumX - 2) //padding
				{
					image.Draw(paddingImage,
						Rectangle(0, static_cast<float>(tileWidth * frame), static_cast<float>(tileWidth), static_cast<float>(tileWidth)),
						Rectangle(static_cast<float>(posX), static_cast<float>(posY), static_cast<float>(tileWidth), static_cast<float>(tileWidth)), WHITE);
				}
				else if ((indexY == 0 && indexX == 0) || (indexY == 0 && indexX == tileNumX-1) || (indexY == tileNumY-1 && indexX == 0) || (indexY == tileNumY-1 && indexX == tileNumX - 1)) //corner
				{
					cornerCount++;
					if (cornerCount == 2) //upper left
					{
						cornerImage.FlipHorizontal();
					}
					else if (cornerCount == 3) //lower right
					{
						cornerImage.FlipHorizontal();
						cornerImage.FlipVertical();
					}
					else if (cornerCount == 4) //lower left
					{
						&cornerImage.FlipHorizontal();
					}
					image.Draw(cornerImage,
						Rectangle(0, static_cast<float>(tileWidth * frame), static_cast<float>(tileWidth), static_cast<float>(tileWidth)),
						Rectangle(static_cast<float>(posX), static_cast<float>(posY), static_cast<float>(tileWidth), static_cast<float>(tileWidth)), WHITE);
				}
				else //side
				{
					if (indexY == 0) //top
					{
						image.Draw(sideImage,
							Rectangle(0, static_cast<float>(tileWidth * frame), static_cast<float>(tileWidth), static_cast<float>(tileWidth)),
							Rectangle(static_cast<float>(posX), static_cast<float>(posY), static_cast<float>(tileWidth), static_cast<float>(tileWidth)), WHITE);
					}
					else if (indexX == 0) //left
					{
						image.Draw(sideLeftImage,
							Rectangle(0, static_cast<float>(tileWidth * frame), static_cast<float>(tileWidth), static_cast<float>(tileWidth)),
							Rectangle(static_cast<float>(posX), static_cast<float>(posY), static_cast<float>(tileWidth), static_cast<float>(tileWidth)), WHITE);
					}
					else if (indexX == tileNumX - 1) //right
					{
						image.Draw(sideRightImage,
							Rectangle(0, static_cast<float>(tileWidth * frame), static_cast<float>(tileWidth), static_cast<float>(tileWidth)),
							Rectangle(static_cast<float>(posX), static_cast<float>(posY), static_cast<float>(tileWidth), static_cast<float>(tileWidth)), WHITE);
					}
					else if (indexY == tileNumY - 1) //bottom
					{
						image.Draw(sideBottomImage,
							Rectangle(0, static_cast<float>(tileWidth * frame), static_cast<float>(tileWidth), static_cast<float>(tileWidth)),
							Rectangle(static_cast<float>(posX), static_cast<float>(posY), static_cast<float>(tileWidth), static_cast<float>(tileWidth)), WHITE);
					}
				}
			}
		}
	}
	this->spriteTexture = image;
	Picture::updatePosition();
}

PictureBorder::PictureBorder(raylib::Vector2 pos, const File& corner, const File& side, int tileWidth,
	raylib::Vector2 bounds)
{
}
