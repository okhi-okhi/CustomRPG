#pragma once
#include <json.hpp>
#include "../System/I18n.h"
using ordered_json = nlohmann::ordered_json;
using json = nlohmann::json;

enum class itemTypes { ARMOR = 0, WEAPON, MATERIAL, PROP };

enum class rarity {
	COMMON = 1,
	UNCOMMON,
	RARE,
	EPIC,
	LEGENDARY
};

class Item
{
protected:
	itemTypes itemType;
	std::string id;
	std::string name;
	int buyPrice;
	int sellPrice;
	rarity rarity;
	bool stackable;

	virtual float readValue(const json& j) const;
	virtual std::string readString(const json& j, const std::string& key) const = 0;
	static enum rarity readRarity(const json& j);

public:
	Item() : itemType(itemTypes::ARMOR), id("NONE"), name("stat.none"), buyPrice(0), sellPrice(0), rarity(rarity::COMMON), stackable(false) {}
	Item(const itemTypes& iT, std::string id, std::string n,
		const int& bV, const int& sV, const enum rarity& r, const bool& s) :
		itemType(iT), id(std::move(id)), name(std::move(n)),
		buyPrice(bV), sellPrice(sV), rarity(r), stackable(s) {}
	virtual ~Item() = default;

	virtual Item* clone() const = 0;
	virtual ordered_json getAsJson() const;
	virtual std::vector<std::string> getDataKey() const;
	virtual std::map<std::string, std::string> getData() const;

	virtual void print() const;
	virtual void debugPrint() const;

	static std::string getRarityName(const enum rarity& rarity);

	//Accessors
	const itemTypes& getItemType() const { return this->itemType; }
	const std::string& getId() const { return this->id; }
	std::string getRawName() const { return I18n::instance().get(this->name); }
	std::string getName() const;
	const int& getBuyPrice() const { return this->buyPrice; }
	const int& getSellPrice() const { return this->sellPrice; }
	const enum rarity& getRarity() const { return this->rarity; }
	const bool& isStackable() const { return this->stackable; }
};

