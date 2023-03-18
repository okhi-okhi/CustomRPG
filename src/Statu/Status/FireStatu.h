#pragma once
#include <iostream>
#include"../Statu.h"

class FireStatu : public Statu
{
private:
	int damage;

public:
	FireStatu(int duration, int damage);

	virtual void onEveryTurn(Entity& target);
	virtual void onEnd(Entity& target);
};

