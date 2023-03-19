#include "Script.h"
#include <iostream>
#include <json.hpp>
#include "../System/Exceptions.hpp"
#include "../Utils/Utilities.h"

using json = nlohmann::json;

Script::Script(std::string fileName)
{
	json j = Utils::readJsonFile("Games/Scripts/" + fileName);
	try {
		this->scnario = j["scnario"];

		for (const auto& item : j["options"].items()) {
			option o;

			o.text = item.value()["text"];
			o.resultText = item.value()["resultText"];
			o.exp = item.value()["rewards"]["exp"];
			o.gold = item.value()["rewards"]["gold"];
			o.statPoint = item.value()["rewards"]["statPoint"];

			this->options.push_back(o);
		}
	}
	catch (json::type_error& e) {
		throw BadValueException(fileName, e.what());
	}
}

std::string Script::getAsString() const
{
	std::string answers;

	for (size_t i = 0; i < this->options.size(); i++){
		answers += std::to_string(i + 1) + ") " + this->options[i].text + "\n";
	}

	return this->scnario + "\n" + "\n" + answers + "\n";
}
