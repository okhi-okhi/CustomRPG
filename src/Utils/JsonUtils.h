#pragma once
#include <json.hpp>

using json = nlohmann::json;

namespace JsonUtils {
	float readValueFromNum(const json& j);

	float readValueFromString(const json& j);
	float readValueFromString(const json& j, const std::map<std::string, int>& vars);

	float readSingleValue(const json& j);
	float readSingleValue(const json& j, const std::map<std::string, int>& vars);

	float readValueFromRange(const json& j);
	float readValueFromRange(const json& j, const std::map<std::string, int>& vars);

	float readValueFromExpect(const json& j);
	float readValueFromExpect(const json& j, const std::map<std::string, int>& vars);

	float readValueFromRarity(const json& j, const int& rarity);
	float readValueFromRarity(const json& j, const int& rarity, const std::map<std::string, int>& vars);

	bool isRarityTable(const json& j);
};

