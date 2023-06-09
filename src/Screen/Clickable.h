#pragma once
#include <vector>
#include "Element.h"

class Clickable : public Element
{
protected:
	std::vector<raylib::Rectangle> reserveRec{};

public:
	void draw() override;
	void updatePosition() override;

	virtual void checkCollision(const std::vector<raylib::Rectangle>& recs);
	virtual void addReserveRec(raylib::Rectangle hitbox);
	void clearReserveRec() { this->reserveRec.clear(); }

	const std::vector<raylib::Rectangle>& getReserveRec() const { return this->reserveRec; }
};

