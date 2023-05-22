#pragma once
#include "Picture.h"

class FullPicture final : public Picture
{
public:
	FullPicture() = default;
	FullPicture(const std::string& fileName, int textureFrameNum);

	void draw() override;
	FullPicture* clone() const override;
	void updatePosition() override;
};

