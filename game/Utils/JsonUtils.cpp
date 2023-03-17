#include "JsonUtils.h"
#include <exprtk.hpp>
#include <iostream>
#include "Utilities.h"
#include "../System/GlobalVariable.h"
#include "../System/Exceptions.hpp"

inline float JsonUtils::readValueFromNum(const json& j) {
	return j.get<float>();
}

float JsonUtils::readValueFromString(const json& j) {
	exprtk::symbol_table<float> symbol_table;
	exprtk::expression<float>   expression;
	exprtk::parser<float>       parser;


	const auto expression_string = static_cast<std::string>(j);
	symbol_table.add_constant("distance", static_cast<float>(playerDistance));
	symbol_table.add_constant("fame", static_cast<float>(playerFame));

	expression.register_symbol_table(symbol_table);

	if (!parser.compile(expression_string, expression))
	{
		for (int i = 0; i < parser.error_count(); ++i)
		{
			typedef exprtk::parser_error::type error_t;

			error_t error = parser.get_error(i);

			std::cout << error.diagnostic.c_str() << std::endl;
		}
		throw BadStringException(j);
	}
	return expression.value();
}

float JsonUtils::readValueFromString(const json& j, const std::map<std::string, int>& vars) {
	exprtk::symbol_table<float> symbol_table;
	exprtk::expression<float>   expression;
	exprtk::parser<float>       parser;


	const auto expression_string = static_cast<std::string>(j);
	symbol_table.add_constant("distance", static_cast<float>(playerDistance));
	symbol_table.add_constant("fame", static_cast<float>(playerFame));
	for (const auto& [fst, snd] : vars) {
		symbol_table.add_constant(fst, static_cast<float>(snd));
	}

	expression.register_symbol_table(symbol_table);

	if (!parser.compile(expression_string, expression))
	{
		for (int i = 0; i < parser.error_count(); ++i)
		{
			typedef exprtk::parser_error::type error_t;

			error_t error = parser.get_error(i);

			std::cout << error.diagnostic.c_str() << std::endl;
		}
		throw BadStringException(j);
	}
	return expression.value();
}

float JsonUtils::readSingleValue(const json& j) {
	if (j.is_number()) {
		return readValueFromNum(j);
	}
	if (j.is_string()) {
		return readValueFromString(j);
	}
	throw BadStringException(j);
}

float JsonUtils::readSingleValue(const json& j, const std::map<std::string, int>& vars) {
	if (j.is_number()) {
		return readValueFromNum(j);
	}
	if (j.is_string()) {
		return readValueFromString(j, vars);
	}
	throw BadStringException(j);
}

float JsonUtils::readValueFromRange(const json& j) {
	return Utils::randomFromRange<float>(readSingleValue(j["min"]), readSingleValue(j["max"]));
}

float JsonUtils::readValueFromRange(const json& j, const std::map<std::string, int>& vars) {
	return Utils::randomFromRange<float>(readSingleValue(j["min"], vars), readSingleValue(j["max"], vars));
}

float JsonUtils::readValueFromExpect(const json& j) {
	return Utils::randomFromRange<float>
		(readSingleValue(j["expect"]) * (1 - readSingleValue(j["floatingRange"])),
		 readSingleValue(j["expect"]) * (1 + readSingleValue(j["floatingRange"])));
}

float JsonUtils::readValueFromExpect(const json& j, const std::map<std::string, int>& vars) {
	return Utils::randomFromRange<float>
		(readSingleValue(j["expect"], vars) * (1 - readSingleValue(j["floatingRange"], vars)),
			readSingleValue(j["expect"], vars) * (1 + readSingleValue(j["floatingRange"], vars)));
}

float JsonUtils::readValueFromRarity(const json& j, const int& rarity) {
	return readSingleValue(j[std::to_string(rarity)]);
}

float JsonUtils::readValueFromRarity(const json& j, const int& rarity, const std::map<std::string, int>& vars) {
	return readSingleValue(j[std::to_string(rarity)], vars);
}

bool JsonUtils::isRarityTable(const json& j) {
	for(const auto& rm : j.items()) {
		if(rm.key() != "1" && rm.key() != "2" && rm.key() != "3" && rm.key() != "4" && rm.key() != "5") {
			return false;
		}
	}
	return true;
}