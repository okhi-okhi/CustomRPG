#include "PictureGallery.h"
#include "ScreenManager.h"
#include "../../Utils/RaylibUtils.h"

PictureGallery::PictureGallery(raylib::Rectangle bounds, const std::vector<File>& files) :
	Element(ElementType::PICTURE_GALLERY, bounds.GetPosition())
{
	using RaylibUtils::getRealLength;
	this->elementType = ElementType::PICTURE_GALLERY;
	this->bounds = getRealLength(Rectangle(bounds.x - bounds.width / 2, bounds.y - bounds.height / 2,
		bounds.width, bounds.height));
	this->currentIndex = 0;

	const float frameRatio = this->bounds.width / this->bounds.height;
	for(const auto& file : files)
	{
		raylib::Image image(PathProvider::instance().get(file, ResourcesFolder::TEXTURES));
		const float imageRatio = static_cast<float>(image.width) / static_cast<float>(image.height);
		std::cout << "i: " << imageRatio << " f: " << frameRatio << "\n";
		if (imageRatio > frameRatio)
		{
			image.Resize(this->bounds.width, this->bounds.width / imageRatio);
			std::cout << "h: " << this->bounds.width / imageRatio << "\n";
			this->pictures.emplace_back(image);
		}
		else
		{
			image.Resize(this->bounds.height * imageRatio, this->bounds.height);
			std::cout << "w: " << this->bounds.height * imageRatio << "\n";
			this->pictures.emplace_back(image);
		}
	}
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

	this->originPos = this->position - Vector2(this->pictures[this->currentIndex].width / 2, this->pictures[this->currentIndex].height / 2);
	this->hitbox.clear();
	this->hitbox.emplace_back(
		this->originPos.x, this->originPos.y,
		static_cast<float>(this->pictures[this->currentIndex].width), static_cast<float>(this->pictures[this->currentIndex].height));

	ScreenManager::instance().updateHitbox();
}

void PictureGallery::nextPicture()
{
	this->currentIndex++;
	updatePosition();
}

void PictureGallery::previousPicture()
{
	this->currentIndex--;
	updatePosition();
}
