#pragma once
#include "Item.h"

namespace CustomRPG {
	class Material final : public Item
	{
	private:
		std::string description;
		//recipe stuff

		virtual float readValue(const json& j) const override;
		virtual std::string readString(const json& j, const std::string& key) const override;

	public:
		Material() : Item() {}
		Material(std::string id, std::string name, const int& buyPrice, const int& sellPrice,
			const enum rarity& rarity, std::string description) :
			Item(itemTypes::MATERIAL, std::move(id), std::move(name), buyPrice, sellPrice, rarity, true),
			description(std::move(description)) {}

		explicit Material(const std::string& fileName);

		Material* clone()const override;
		ordered_json getAsJson()const override;
		std::vector<std::string> getDataKey() const override;
		std::map<std::string, std::string> getData() const override;

		void print() const override;
		void debugPrint() const override;

		std::string getDescription()const { return I18n::instance().get(this->description); }
	};
}

