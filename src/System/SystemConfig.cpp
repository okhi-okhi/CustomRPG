#include "SystemConfig.h"
#include <fstream>
#include <iostream>
#include <json.hpp>

void SystemConfig::load(const std::string& fileName) {
	using json = nlohmann::json;
	using ordered_json = nlohmann::ordered_json;
	std::ifstream inFile(fileName);

	if (inFile.good()) {
		json j = json::parse(inFile, nullptr, true, true);
		try {
			this->defaultLanguage = j["defaultLanguage"];
			this->currentLanguage = j["currentLanguage"];
		}
		catch (json::exception& e) {
			std::cout << "ERROR: Conversion failed while reading " << fileName << std::endl;
			std::cout << e.what() << std::endl;
			inFile.close();
			exit(2);
		}
		inFile.close();
	}
	else
	{
		inFile.close();
		std::cout << "ERROR: Couldn't find file: " << fileName << ", will create one" << std::endl;

		std::ofstream outFile(fileName);
		ordered_json j = {
			{"defaultLanguage", this->defaultLanguage},
			{"currentLanguage", this->currentLanguage},
		};
		outFile << j.dump(4);
		outFile.close();
	}
}
