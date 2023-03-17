#pragma once
class Entity;
#include "../Entity/Entity.h"

class Statu
{
private:
	int duration;

public:
	explicit Statu(const int duration) : duration(duration) {}
	// virtual void onEveryTurn(Entity& target) =0;
	// virtual void onEnd(Entity& target)=0;

	const int& getDuration() const { return this->duration; }
};

