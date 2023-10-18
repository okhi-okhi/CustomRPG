#include "Utilities.h"
#include <fstream>
#include "../System/Exceptions.hpp"

int Utils::getFromFormula(json& j, const int& level) {
	return static_cast<int>(round(randomFromRange(static_cast<float>(j["base"]),
		static_cast<float>(j["base"]) + static_cast<float>(j["scale"])*level)));
}

int Utils::checkInRange(int n, const int min, const int max) {
	if (n < min) n = min;
	else if (n > max) n = max;
	return n;
}

int Utils::lengthOfNumber(int n)
{
	unsigned int numberOfDigits = 0;
	do {
		++numberOfDigits;
		n /= 10;
	} while (n);
	return numberOfDigits;
}

int Utils::lengthOfString(const std::string& str)
{
	int c, i, ix, q;
	for (q = 0, i = 0, ix = static_cast<int>(str.length()); i < ix; i++, q++)
	{
		c = static_cast<unsigned char>(str[i]);
		if (c >= 0 && c <= 127) i += 0;
		else if ((c & 0xE0) == 0xC0) i += 1;
		else if ((c & 0xF0) == 0xE0) i += 2;
		else if ((c & 0xF8) == 0xF0) i += 3;
		//else if (($c & 0xFC) == 0xF8) i+=4; // 111110bb //byte 5, unnecessary in 4 byte UTF-8
		//else if (($c & 0xFE) == 0xFC) i+=5; // 1111110b //byte 6, unnecessary in 4 byte UTF-8
		else return 0;//invalid utf8
	}
	return q;
}


std::string Utils::floatToPercent(const float& value) {
	return std::to_string(static_cast<int>(value * 100)) + "%";
}

std::string Utils::boolToString(const bool& boolean) {
	return boolean ? "true" : "false";
}

json Utils::loadJsonFile(std::string fileName, const bool addSuffix) {
	if(addSuffix)
		fileName += ".json";
	std::ifstream inFile(fileName);
	if (!inFile.good()) {
		throw InvalidFileException(fileName);
	}
	try
	{
		return json::parse(inFile);
	}
	catch (json::parse_error& e)
	{
		throw BadValueException(fileName, e.what());
	}
}