#pragma once
#include "Item.h"

class Prop final : public Item
{
private:
	std::string description;
	//onUse stuff

	virtual float readValue(const json& j) const override;
	virtual std::string readString(const json& j, const std::string& key) const override;

public:
	Prop() : Item() {}
	Prop(std::string id, std::string name, const int& buyPrice, const int& sellPrice,
		const enum rarity& rarity, std::string description) :
		Item(itemTypes::PROP, std::move(id), std::move(name), buyPrice, sellPrice, rarity, true),
		description(std::move(description)) {}

	explicit Prop(const std::string& fileName);

	Prop* clone()const override;
	ordered_json getAsJson()const override;
	std::vector<std::string> getDataKey() const override;
	std::map<std::string, std::string> getData() const override;

	void print() const override;
	void debugPrint() const override;

	void onUse() const;

	std::string getDescription()const { return I18n::instance().get(this->description); }
};

