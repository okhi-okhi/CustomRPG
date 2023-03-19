#include "Sheet.h"
#include <iostream>
#include <format>
#include "../I18n/I18n.h"
#include "../Utils/Utilities.h"

std::vector<std::string> Sheet::getSheetText() const
{
	using std::cout, std::endl;
	std::vector<int> maxGridLength;
	std::vector<std::string> rowText;

	maxGridLength.reserve(this->keys.size());
	for (const auto& key : this->keys)
	{
		maxGridLength.push_back(Utils::lengthOfString(I18n::instance().get("stat." + key)) *
			std::stoi(I18n::instance().get("charWidthFix")));
	}

	for(const auto& item : this->itemData) 
	{
		int index = 0;
		for(const auto& key : this->keys)
		{
			if(static_cast<int>(item.at(key).length()) > maxGridLength[index])
			{
				maxGridLength[index] = static_cast<int>(item.at(key).length());
			}
			index++;
		}
	}

	std::string temp;
	for(std::size_t i = 0; i < this->keys.size(); i++)
	{
		temp += utf8LeftAlign(I18n::instance().get("stat." + this->keys[i]), maxGridLength[i]);
	}
	rowText.push_back(temp);

	temp = "";
	for (const auto& length : maxGridLength)
	{
		temp.append(length, '=');
		temp.append(1, '|');
	}
	rowText.emplace_back(temp);


	for (const auto& item : this->itemData)
	{
		temp = "";
		for (std::size_t i = 0; i < this->keys.size(); i++)
		{
			temp += std::format("{:>{}}|", item.at(this->keys[i]), maxGridLength[i]);
		}
		rowText.push_back(temp);
	}

	return rowText;
}

std::string Sheet::utf8LeftAlign(const std::string& str, const int& width) const
{
	const int charWidthFix = std::stoi(I18n::instance().get("charWidthFix"));
	const int utf8StrLen = Utils::lengthOfString(str) * charWidthFix;
	if(utf8StrLen > width)
	{
		return str + '|';
	}
	std::string result(width - utf8StrLen, ' ');
	result += str;
	result += "|";
	return result;
}
