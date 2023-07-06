#pragma once
#include "Picture.h"

class FullPicture final : public Picture
{
public:
	FullPicture() = default;
	FullPicture(const File& file, int textureFrameNum, ScaleMode mode = ScaleMode::NN);

	void draw() override;
	void updatePosition() override;
};

