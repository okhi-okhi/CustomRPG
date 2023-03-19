#include "Team.h"
#include <iostream>
#include "../System/Exceptions.hpp"

Team::Team() {
    this->team.clear();
    this->allyNum = 0;

	for(int i = 0; i<this->capacity; i++) {
        this->team.push_back(nullptr);
	}
}

bool Team::isSlotEmpty(const int idx) const {
    return team[idx] == nullptr;
}

int Team::getEmptySlot() const {
    for(int idx = 0; idx < this->capacity; idx++) {
        if (isSlotEmpty(idx)) {
            return idx;
        }
    }
    return -1;
}

Ally* Team::operator[](const int index) const
{
    if(index < 0 || index >= this->capacity) {
        throw OutOfRangeException(index, this->capacity);
    }
    return this->team[index];
}

bool Team::addMember(Ally& ally) {
    const int slot = getEmptySlot();
    if(slot == -1) {
        return false;
    }
    replaceMember(ally, slot);
    return true;
}

void Team::replaceMember(Ally& ally, const int index)
{
    if(index < 0 || index >= this->capacity) {
        throw OutOfRangeException(index, this->capacity);
    }
    if(this->team[index] == nullptr) {
        this->allyNum++;
    }
    else {
        this->team[index]->setInTeam(false);
    }
    this->team[index] = &ally;
    ally.setInTeam(true);
}

void Team::removeMember(const std::string& id) {
    int i = 0;
    for (const auto& member : this->team) {
        if (member != nullptr) {
            if (member->getId() == id) {
                removeMember(i);
            }
        }
        i++;
    }
}

void Team::removeMember(const int index) {
    if(index < 0 || index >= this->capacity) {
        throw OutOfRangeException(index, this->capacity);
    }
    if(!isSlotEmpty(index)) {
        this->team[index]->setInTeam(false);
        this->team[index] = nullptr;
        this->allyNum--;
    }
}

void Team::setOrder(const std::vector<int>& indexList)
{
    std::vector<Ally*> temp;
    temp.reserve(indexList.size());
    for(int i = 0; i < indexList.size(); i++) {
        temp.push_back(nullptr);
    }
    for(int i = 0; i < indexList.size(); i++) {
    	temp[indexList[i]] = this->team[i];
    }
    this->team = temp;
    for(size_t i = indexList.size(); i < this->capacity; i++) {
        this->team.push_back(nullptr);
    }
}

void Team::optimized() {
	for(int i = 0; i < team.size(); i++) {
		if(isSlotEmpty(i)) {
			for(int j = i+1; j < team.size(); j++) {
				if(!isSlotEmpty(j)) {
                    this->team[i] = this->team[j];
                    this->team[j] = nullptr;
                    break;
				}
			}
		}
	}
}

void Team::print() const {
    using std::cout, std::endl, std::to_string;
    const int lineCapacity = GameConfig::instance().getLineCapacity();
    const int lineAmount = static_cast<int>(std::ceil(static_cast<float>(this->capacity) / static_cast<float>(lineCapacity)));

    for(int i = 0; i < lineAmount; i++) {
        int itemRemain = this->capacity - (lineCapacity * i);
        if(itemRemain > lineCapacity) {
            itemRemain = lineCapacity;
        }

	    for(int j = 0; j < itemRemain; j++)
	    {
		    const int slot = j + (lineCapacity * i);
            if (this->team[slot] != nullptr) {
                cout << I18n::instance().get("player.team.print.info", 
                    { {"slot", to_string(slot + 1)},
                      {"name", this->team[slot]->getName()},
                      {"level", to_string(this->team[slot]->getLevel())} });
            }
            else {
                cout << I18n::instance().get("player.team.print.none", { {"slot", to_string(slot + 1)} });
            }
            cout << " | ";
	    }
        cout << endl;
    }
}