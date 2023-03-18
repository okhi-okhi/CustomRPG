#include "FireStatu.h"
#include "../../Entity/Entity.h"

#include <iostream>

FireStatu::FireStatu(int duration, int damage): Statu(duration)
{
	this->damage = damage;
}

void FireStatu::onEveryTurn(Entity& target) {
	target.takeDamage(this->damage);
	std::cout << "燃燒對 " << target.getName() << "造成了 " << this->damage << "點傷害";
}

void FireStatu::onEnd(Entity& target) {
	std::cout << "end";
}