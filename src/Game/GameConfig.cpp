#include "GameConfig.h"
#include <fstream>
#include <iostream>
#include <json.hpp>
#include "../System/Exceptions.hpp"

void GameConfig::load(const std::string& fileName) {
	using nlohmann::ordered_json, nlohmann::json;
	std::ifstream inFile(fileName);

	if (inFile.good()) {
		json j = json::parse(inFile, nullptr, true, true);
		try {
			this->defaultLanguage = j["defaultLanguage"];
			this->currentLanguage = j["currentLanguage"];

			this->nextPlaceNum = j["nextPlaceNum"];
			this->teamCapacity = j["teamCapacity"];
			this->lineCapacity = j["lineCapacity"];

			json j2 = j["formula"].flatten();
			for (const auto& formula : j2.items())
			{
				std::string s = formula.key();
				s.erase(0, 1);
				formulas[s] = formula.value();
			}

			this->talents = j["talents"].get<std::vector<std::string>>();

			this->armorSlots = j["armorSlots"].get<std::vector<std::string>>();
		}
		catch (json::exception& e) {
			std::cout << "Conversion failed while reading " << fileName << std::endl;
			std::cout << e.what() << std::endl;
			inFile.close();
			exit(2);
		}
		inFile.close();
	}
	else
	{
		inFile.close();
		std::cout << "Couldn't find " << fileName << ", will create one" << std::endl;

		std::ofstream outFile(fileName);
		ordered_json j = {
			{"nextPlaceNum", this->nextPlaceNum},
			{"teamCapacity", this->teamCapacity},
			{"lineCapacity", this->lineCapacity},
			{"formula", {}},
			{"talents", {"strength", "vitality", "dexterity", "intelligence"}},
			{"armorSlots", {"helmet", "chestplate", "leggings", "boots"}}
		};
		outFile << j.dump(4);
		outFile.close();
	}
}

const std::string& GameConfig::getFormula(const std::string& key) const
{
	if (this->formulas.contains(key)) {
		return this->formulas.find(key)->second;
	}
	throw InvalidKeyException(key);
}