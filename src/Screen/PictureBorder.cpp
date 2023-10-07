#include "PictureBorder.h"
#include "../Utils/RaylibUtils.h"

raylib::Image PictureBorder::generateBorder(const raylib::Image& cornerImage,
	const raylib::Image& sideImage, const raylib::Image& paddingImage,
	const int textureFrameNum, const int tileWidth, const raylib::Vector2 bounds, const bool needPadding) const
{
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

		raylib::Image cornerUpperLeftImage = ImageFromImage(cornerImage, Rectangle(0,   static_cast<float>(tileWidth * frame),static_cast<float>(tileWidth), static_cast<float>(tileWidth)));
		raylib::Image cornerUpperRightImage = cornerUpperLeftImage;
		cornerUpperRightImage.FlipHorizontal();
		raylib::Image cornerLowerLeftImage = cornerUpperLeftImage;
		cornerLowerLeftImage.FlipVertical();
		raylib::Image cornerLowerRightImage = cornerUpperLeftImage;
		cornerLowerRightImage.FlipHorizontal();
		cornerLowerRightImage.FlipVertical();

		raylib::Image sideTopImage = ImageFromImage(sideImage, Rectangle(0, static_cast<float>(tileWidth * frame),static_cast<float>(tileWidth), static_cast<float>(tileWidth)));
		raylib::Image sideLeftImage = sideTopImage;
		sideLeftImage.RotateCCW();
		raylib::Image sideRightImage = sideTopImage;
		sideRightImage.RotateCW();
		raylib::Image sideBottomImage = sideTopImage;
		sideBottomImage.FlipVertical();

		for (int indexY = 0; indexY < tileNumY; indexY++, posY += tileWidth)
		{
			int posX = 0;
			for (int indexX = 0; indexX < tileNumX; indexX++, posX += tileWidth)
			{
				if (indexY >= 1 && indexY <= tileNumY - 2 && indexX >= 1 && indexX <= tileNumX - 2 && needPadding) //padding
				{
					image.Draw(paddingImage,
						Rectangle(0, static_cast<float>(tileWidth * frame), static_cast<float>(tileWidth), static_cast<float>(tileWidth)),
						Rectangle(static_cast<float>(posX), static_cast<float>(posY), static_cast<float>(tileWidth), static_cast<float>(tileWidth)), WHITE);
				}
				else if ((indexY == 0 && indexX == 0) || (indexY == 0 && indexX == tileNumX - 1) || (indexY == tileNumY - 1 && indexX == 0) || (indexY == tileNumY - 1 && indexX == tileNumX - 1)) //corner
				{
					cornerCount++;
					if (cornerCount == 1) //upper left
					{
						image.Draw(cornerUpperLeftImage,
							Rectangle(0, static_cast<float>(tileWidth * frame), static_cast<float>(tileWidth), static_cast<float>(tileWidth)),
							Rectangle(static_cast<float>(posX), static_cast<float>(posY), static_cast<float>(tileWidth), static_cast<float>(tileWidth)), WHITE);
					}
					else if (cornerCount == 2) //upper right
					{
						image.Draw(cornerUpperRightImage,
							Rectangle(0, static_cast<float>(tileWidth * frame), static_cast<float>(tileWidth), static_cast<float>(tileWidth)),
							Rectangle(static_cast<float>(posX), static_cast<float>(posY), static_cast<float>(tileWidth), static_cast<float>(tileWidth)), WHITE);
					}
					else if (cornerCount == 3) //lower left
					{
						image.Draw(cornerLowerLeftImage,
							Rectangle(0, static_cast<float>(tileWidth * frame), static_cast<float>(tileWidth), static_cast<float>(tileWidth)),
							Rectangle(static_cast<float>(posX), static_cast<float>(posY), static_cast<float>(tileWidth), static_cast<float>(tileWidth)), WHITE);
					}
					else if (cornerCount == 4) //lower right
					{
						image.Draw(cornerLowerRightImage,
							Rectangle(0, static_cast<float>(tileWidth * frame), static_cast<float>(tileWidth), static_cast<float>(tileWidth)),
							Rectangle(static_cast<float>(posX), static_cast<float>(posY), static_cast<float>(tileWidth), static_cast<float>(tileWidth)), WHITE);
					}
				}
				else //side
				{
					if (indexY == 0) //top
					{
						image.Draw(sideTopImage,
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
	return image;
}

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
	double startTime = GetTime();
	this->spriteTexture = generateBorder(cornerImage, sideImage, paddingImage, this->textureFrameNum, tileWidth, bounds, true);
	double endTime = GetTime();
	std::cout << "Time: " << endTime - startTime << std::endl;
	Picture::updatePosition();
}

PictureBorder::PictureBorder(const raylib::Vector2 pos, const File& corner, const File& side,
	const int textureFrameNum, int tileWidth, raylib::Vector2 bounds)
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
	bounds = RaylibUtils::getRealLength(bounds);

	this->spriteTexture = generateBorder(cornerImage, sideImage, Image(), this->textureFrameNum, tileWidth, bounds, false);
	Picture::updatePosition();
}
