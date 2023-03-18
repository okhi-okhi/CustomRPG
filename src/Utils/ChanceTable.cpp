#include "ChanceTable.h"
#include <fstream>
#include <iostream>
#include "../Utils/Utilities.h"
#include "../System/Exceptions.hpp"
#include "JsonUtils.h"
#include "../System/GlobalVariable.h"

ChanceTable::ChanceTable() {
	this->chanceMax = 1.0;
}

ChanceTable::ChanceTable(std::string& fileName) {
	using json = nlohmann::json;
	fileName = "ChanceTables/" + fileName + ".json";
	std::ifstream inFile(fileName);
	if (!inFile.good()) {
		throw InvalidFileException(fileName);
	}
	json j = json::parse(inFile);
	int n = 0;
	float remain = 1.0;
	for (const auto& item : j.items()) {
		if (item.value() == -1) {
			n++;
		}
		else {
			float value = readValue(item.value());
			this->chanceTable.insert(std::pair(item.key(), value));
			remain = remain - value;
		}
	}
	if (n > 0) {
		this->chanceMax = 1.0;
	}
	else {
		this->chanceMax = static_cast<float>(1.0 - remain);
	}
	if (this->chanceMax <= 0.0) {
		throw BadChanceException(static_cast<int>(remain - this->chanceMax));
	}
	remain /= n;
	for (const auto& item : j.items()) {
		if (item.value() == -1) {
			this->chanceTable.insert(std::pair(item.key(), remain));
		}
	}
	inFile.close();
}

ChanceTable::ChanceTable(const json& j) {
	int n = 0;
	float remain = 1.0;
	for (const auto& item : j.items()) {
		if (item.value() == -1) {
			n++;
		}
		else {
			float value = readValue(item.value());
			this->chanceTable.insert(std::pair(item.key(), value));
			remain = remain - value;
		}
	}
	if (n > 0) {
		this->chanceMax = 1.0;
	}
	else {
		this->chanceMax = static_cast<float>(1.0 - remain);
	}
	if (this->chanceMax <= 0.0) {
		throw BadChanceException(static_cast<int>(remain - this->chanceMax));
	}
	remain /= n;
	for (const auto& item : j.items()) {
		if (item.value() == -1) {
			this->chanceTable.insert(std::pair(item.key(), remain));
		}
	}
}

std::string ChanceTable::getRandomItem() const
{
	auto r = Utils::randomFromRange<float>(0.0, this->chanceMax);
	for (const auto& [fst, snd] : this->chanceTable) {
		r -= snd;
		if (r <= 0)
			return fst;
	}
	return "";
}

std::set<std::string> ChanceTable::getRandomItems(const int& num)const {
	std::set<std::string> s;
	for (int i = 0; i < num; i++) {
		s.insert(getRandomItem());
	}
	return s;
}

std::set<std::string> ChanceTable::drawItems() const
{
	std::set<std::string> s;
	for (const auto& [fst, snd] : this->chanceTable) {
		const auto r = Utils::randomFromRange<float>(0.0, this->chanceMax);
		if (snd < r) {
			s.insert(fst);
		}
	}
	return s;
}

void ChanceTable::debugPrint()const {
	for (const auto& [fst, snd] : this->chanceTable)
	{
		std::cout << "    - " << fst << " : " << snd << "\n";
	}
}

float ChanceTable::readValue(const json& j) const
{
	std::map<std::string, int> vars;
	vars["distance"] = playerDistance;
	if (j.is_number()) {
		return JsonUtils::readValueFromNum(j);
	}
	if (j.is_string()) {
		return JsonUtils::readValueFromString(j, vars);
	}
	throw NoReadFunctionException(j);
}