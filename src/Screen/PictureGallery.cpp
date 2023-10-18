#include "PictureGallery.h"
#include "ScreenManager.h"
#include "../../Utils/RaylibUtils.h"

PictureGallery::PictureGallery(raylib::Rectangle bounds, const std::vector<File>& files) :
	Element(ElementType::PICTURE_GALLERY, bounds.GetPosition())
{
	using RaylibUtils::getRealLength;
	this->bounds = getRealLength(Rectangle(bounds.x - bounds.width / 2, bounds.y - bounds.height / 2,
		bounds.width, bounds.height));
	this->currentIndex = 0;
	setPictures(files);
	updatePosition();
}

void PictureGallery::draw()
{
	DrawTextureV(this->pictures[this->currentIndex], this->originPos, WHITE);
}

void PictureGallery::updatePosition()
{
	this->bounds.x = this->position.x - this->bounds.width / 2;
	this->bounds.y = this->position.y - this->bounds.height / 2;

	this->originPos = this->position - 
		Vector2( static_cast<float>(this->pictures[this->currentIndex].width) / 2,
			static_cast<float>(this->pictures[this->currentIndex].height) / 2);
}

void PictureGallery::nextPicture()
{
	if(this->currentIndex < this->pictures.size() - 1)
	{
		this->currentIndex++;
		updatePosition();
	}
}

void PictureGallery::previousPicture()
{
	if (this->currentIndex > 0)
	{
		this->currentIndex--;
		updatePosition();
	}
}

void PictureGallery::setPictures(const std::vector<File>& files)
{
	this->currentIndex = 0;
	this->pictures.clear();
	const float frameRatio = this->bounds.width / this->bounds.height;
	for (const auto& file : files)
	{
		raylib::Image image(PathProvider::get(file, ResourcesFolder::TEXTURES));
		const float imageRatio = static_cast<float>(image.width) / static_cast<float>(image.height);
		if (imageRatio > frameRatio)
		{
			image.Resize(static_cast<int>(this->bounds.width), static_cast<int>(this->bounds.width / imageRatio));
			this->pictures.emplace_back(image);
		}
		else
		{
			image.Resize(static_cast<int>(this->bounds.height * imageRatio), static_cast<int>(this->bounds.height));
			this->pictures.emplace_back(image);
		}
	}
}
