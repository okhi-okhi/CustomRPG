#pragma once
#include "Picture.h"

class FullPicture : public Picture
{
public:
	FullPicture() = default;
	FullPicture(const std::string& fileName, int textureFrameNum);

	void draw() override;
	FullPicture* clone() const override;
};

