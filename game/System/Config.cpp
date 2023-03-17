#include "Config.h"
#include <fstream>
#include <iostream>
#include <json.hpp>
#include "Exceptions.hpp"

void Config::load(const std::string& fileName) {
	using json = nlohmann::json;
	std::ifstream inFile(fileName);
	if (!inFile.good()) {
		std::cout << "Can't find file:" << fileName << std::endl;
		exit(1);
	}
	json j = json::parse(inFile, nullptr, true, true);

	try {
		this->defaultLanguage = j["system"]["defaultLanguage"];
		this->currentLanguage = j["system"]["currentLanguage"];
		this->playerFilePath = j["system"]["playerFilePath"];

		this->nextPlaceNum = j["game"]["nextPlaceNum"];
		this->teamCapacity = j["game"]["teamCapacity"];
		this->lineCapacity = j["game"]["lineCapacity"];

		json j2 = j["formula"].flatten();
		for(const auto& formula : j2.items())
		{
			std::string s = formula.key();
			s.erase(0, 1);
			formulas[s] = formula.value();
		}

		this->talents = j["talents"].get<std::vector<std::string>>();

		this->armorSlots = j["armorSlots"].get<std::vector<std::string>>();
	}
	catch (json::exception& e) {
		std::cout << "Conversion failed while reading " << j << std::endl;
		std::cout << e.what() << std::endl;
		inFile.close();
		exit(2);
	}
	inFile.close();
}

const std::string& Config::getFormula(const std::string& key) const
{
	if(this->formulas.contains(key)) {
		return this->formulas.find(key)->second;
	}
	throw InvalidKeyException(key);
}
