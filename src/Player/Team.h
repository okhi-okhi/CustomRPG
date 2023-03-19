#pragma once
#include "../Entity/Ally.h"
#include "../Game/gameConfig.h"

class Team
{
private:
	const int capacity = GameConfig::instance().getTeamCapacity();
	std::vector<Ally*> team;
	int allyNum;

	int getEmptySlot() const;

public:
	Team();

	Ally* operator[](int index) const;

	bool addMember(Ally& ally);
	void replaceMember(Ally& ally, int index);

	void removeMember(const std::string& id);
	void removeMember(int index);

	void setOrder(const std::vector<int>& indexList);
	void optimized();

	bool isSlotEmpty(int idx) const;
	void print() const;

	const int& getAllyNum() const { return this->allyNum; }
};

