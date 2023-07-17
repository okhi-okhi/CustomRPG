#pragma once
#include <Image.hpp>
#include "Element.h"
#include "../../System/PathProvider.h"

class PictureGallery final : public Element
{
private:
	std::vector<Texture2D> pictures;
	raylib::Rectangle bounds;
	int currentIndex;

public:
	PictureGallery() : currentIndex(0) {}
	PictureGallery(raylib::Rectangle bounds, const std::vector<File>& files);

	void draw() override;
	void updatePosition() override;

	void nextPicture();
	void previousPicture();

	void setPictures(const std::vector<File>& files);

	const std::vector<Texture2D>& getPictures() const { return this->pictures; }
	const raylib::Rectangle& getBounds() const { return this->bounds; }
	const int& getCurrentIndex() const { return this->currentIndex; }
};