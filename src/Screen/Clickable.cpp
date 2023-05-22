#include "Clickable.h"
#include "ScreenManager.h"

void Clickable::checkCollision(const std::vector<raylib::Rectangle>& recs)
{
	for(const auto& rec : recs)
	{
		for(const auto& hitbox : this->hitbox)
		{
			if (CheckCollisionRecs(rec, hitbox))
			{
				addReserveRec(rec);
			}
		}
	}
}

void Clickable::addReserveRec(const raylib::Rectangle hitbox)
{
	this->reserveRec.push_back(hitbox);
}

void Clickable::draw()
{
}

Clickable* Clickable::clone() const
{
	return new Clickable(*this);
}

void Clickable::updatePosition()
{
	ScreenManager::instance().updateHitbox();
}
