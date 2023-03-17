#pragma once
#include <json.hpp>
#include <random>
#include <iostream>

using json = nlohmann::json;

namespace Utils {
	int getFromFormula(json& j, const int& level);
	int checkInRange(int n, int min, int max);
	int lengthOfNumber(int n);
	int lengthOfString(const std::string& str);
	std::string floatToPercent(const float& value);
	std::string boolToString(const bool& boolean);
	json readJsonFile(std::string fileName);

	template<typename T>
	T randomFromRange(T range_from, T range_to) {
		std::random_device                  rand_dev;
		std::mt19937                        generator(rand_dev());
		std::uniform_real_distribution<T>   unif(range_from, range_to);
		return unif(generator);
	}

	template <typename T, typename U>
	void printMap(std::map<T, U> map) {
		for (const auto& item : map)
		{
			std::cout << "    " << item.first << " : " << item.second << "\n";
		}
	}
}