#pragma once
#include <map>
#include <string>
#include <vector>

class Sheet
{
private:
	std::vector<std::string> keys;
	std::vector<std::map<std::string, std::string>> itemData;

public:
	Sheet() = default;
	explicit Sheet(std::vector<std::string> keys) : keys(std::move(keys)) {}

	void addItem(const std::map<std::string, std::string>& item) { itemData.push_back(item); }

	std::vector<std::string> getSheetText() const;

	std::string utf8LeftAlign(const std::string& str, const int& width) const;
};

