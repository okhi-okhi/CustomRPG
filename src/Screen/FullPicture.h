#pragma once
#include "Picture.h"

class FullPicture final : public Picture
{
public:
	FullPicture() = default;
	FullPicture(const std::string& fileName, int textureFrameNum, ParentFolder parentFolder = ParentFolder::AUTO);

	void draw() override;
	void updatePosition() override;
};

