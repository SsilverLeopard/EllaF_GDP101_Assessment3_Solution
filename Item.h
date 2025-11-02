#pragma once
#include <string>
#include <iostream>

class Item
{
protected:
	std::string itemName;
	std::string itemDesc;
	bool consumable;
public:
	// Default constructor
	Item() : itemName(""), itemDesc(""), consumable(false) {}
	// Parameterised constructor
	Item(std::string _itemName, std::string _itemDesc, bool _consumable) :
		itemName(_itemName), itemDesc(_itemDesc), consumable(_consumable) {}
	// Copy constructor
	Item(const Item& other) : itemName(other.itemName), itemDesc(other.itemDesc), consumable(other.consumable) {}
	
	// Destructor
	virtual ~Item() = default;

	// Interface functions
	std::string getItemName() const { return itemName; }
	std::string getItemDesc() const { return itemDesc; }
	bool isConsumable() const { return consumable; }

	// Display function that prints all information about the item
	virtual void Display() const;
};

class ItemWeapon : public Item
{
protected:
	unsigned int damageAmount;
public:
	// Default constructor
	ItemWeapon() : Item(), damageAmount(0) {}
	// Parameterised constructor, amount after bool for distinction from food
	ItemWeapon(std::string _itemName, std::string _itemDesc, bool _consumable, unsigned int _damageAmount) : Item(_itemName, _itemDesc, _consumable), damageAmount(_damageAmount) {}
	// Copy constructor from base class
	ItemWeapon(const Item& other) : Item(other), damageAmount(0) {}
	// Copy constructor
	ItemWeapon(const ItemWeapon& other) : Item(other), damageAmount(other.damageAmount) {}

	// Interface function
	unsigned int getDamageAmount() const { return damageAmount; }

	// Display function that prints all information about the item
	virtual void Display() const override;
};

class ItemFood : public Item
{
protected:
	unsigned int healAmount;
public:
	// Default constructor
	ItemFood() : Item(), healAmount(0) {}
	// Parameterised constructor, amount before bool for distinction from weapon
	ItemFood(std::string _itemName, std::string _itemDesc, unsigned int _healAmount, bool _consumable) : Item(_itemName, _itemDesc, _consumable), healAmount(_healAmount) {}
	// Copy constructor from base class
	ItemFood(const Item& other) : Item(other), healAmount(0) {}
	// Copy constructor
	ItemFood(const ItemFood& other) : Item(other), healAmount(other.healAmount) {}

	// Interface function
	unsigned int getHealAmount() const { return healAmount; }

	// Display function that prints all information about the item
	virtual void Display() const override;
};
