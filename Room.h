#pragma once
#include <string>
#include <iostream>
#include "Item.h"
// Base Room class
class Room
{
protected:
	std::string shortDesc;
	std::string longDesc;
	std::string darkDesc;
	bool exitNorth = false;
	bool exitEast = false;
	bool exitSouth = false;
	bool exitWest = false;
	bool dark;
public:
	// Default constructor
	Room() : shortDesc(""), longDesc(""), darkDesc(""), dark(false), exitNorth(false), exitEast(false), exitSouth(false), exitWest(false) {}

	// Parameterised constructor
	Room(const std::string& _shortDesc, const std::string& _longDesc, const std::string& _darkDesc = "", bool _dark = false) :

		shortDesc(_shortDesc), longDesc(_longDesc), darkDesc(_darkDesc), dark(_dark) {}

	// Copy constructor
	Room (const Room& other) : 
		shortDesc(other.shortDesc), longDesc(other.longDesc), darkDesc(other.darkDesc), dark(other.dark),
		exitNorth(other.exitNorth), exitEast(other.exitEast), exitSouth(other.exitSouth), exitWest(other.exitWest) {}

	// Destructor
	virtual ~Room() = default;

	// Interface functions
	const std::string& getShortDesc() const { return shortDesc; }
	const std::string& getLongDesc() const { return longDesc; }
	const std::string& getDarkDesc() const { return darkDesc; }
	bool getExitNorth() const { return exitNorth; }
	bool getExitEast() const { return exitEast; }
	bool getExitSouth() const { return exitSouth; }
	bool getExitWest() const { return exitWest; }
	bool getDark() const { return dark; }
	void setDark(bool _dark) { dark = _dark; }

	void setExits(bool _exitNorth, bool _exitEast, bool _exitSouth, bool _exitWest)
	{ 
		exitNorth = _exitNorth; 
		exitEast = _exitEast;
		exitSouth = _exitSouth;
		exitWest = _exitWest;
	}

	// Display function that prints all information without conditions, for debugging
	virtual void DebugDisplay() const;

	// Game display function that prints information based on room state for entering a room
	virtual void EnterDisplay() const;

	// Game display function that prints long description depending on room state
	virtual void LongDisplay() const;
};
// Enemy Room derived class, has enemy information with name, damage, health, score, alive status
class RoomEnemy : public Room
{
protected:
	std::string enemyName;
	int enemyHealth;
	unsigned int enemyDamage;
	unsigned int enemyScore;
	bool enemyAlive;
public:
	// Default constructor
	RoomEnemy() : Room(), enemyName(""), enemyHealth(1), enemyDamage(0), enemyScore(0), enemyAlive(true) {}
	// Parameterised constructor
	RoomEnemy(const std::string& _shortDesc, const std::string& _longDesc, const std::string& _darkDesc, bool _dark,
		const std::string& _enemyName,
		unsigned int _enemyHealth, unsigned int _enemyDamage, unsigned int _enemyScore) :

		Room(_shortDesc, _longDesc, _darkDesc, _dark),
		enemyAlive(true), enemyName(_enemyName),
		enemyHealth(_enemyHealth), enemyDamage(_enemyDamage), enemyScore(_enemyScore) {}
	
	// Copy constructor
	RoomEnemy(const RoomEnemy& other) : Room(other), 
		enemyAlive(other.enemyAlive), enemyName(other.enemyName),
		enemyHealth(other.enemyHealth), enemyDamage(other.enemyDamage), enemyScore(other.enemyScore) {}
	// Copy constructor from base class
	RoomEnemy(const Room& other) : Room(other),
		enemyName(""), enemyHealth(1), enemyDamage(0), enemyScore(0), enemyAlive(true) {}

	// Destructor
	~RoomEnemy() = default;

	// Interface functions
	std::string getEnemyName() const { return enemyName; }
	int getEnemyHealth() const { return enemyHealth; }
	unsigned int getEnemyDamage() const { return enemyDamage; }
	unsigned int getEnemyScore() const { return enemyScore; }
	bool isEnemyAlive() const { return enemyAlive; }

	// Game functions
	// Damage the enemy, return score if enemy dies
	unsigned int damageEnemy(int _damage);
	// Game display function that prints long description depending on room state
	virtual void LongDisplay() const override;

	// Display function that prints all information without conditions, for debugging
	virtual void DebugDisplay() const override;
};
// Item Room derived class, has item pointer
class RoomItem : public Room
{
protected:
	Item* item = nullptr;
public:
	// Default constructor
	RoomItem() : Room(), item(nullptr) {}

	// Parameterised constructor with existing item
	RoomItem(const std::string& _shortDesc, const std::string& _longDesc, const std::string& _darkDesc, bool _dark, Item* _item = nullptr) :
		Room(_shortDesc, _longDesc, _darkDesc, _dark)
	{
		if (_item != nullptr) {
			// Use dynamic_cast to determine the actual derived type of the item
			if (ItemWeapon* weapon = dynamic_cast<ItemWeapon*>(_item)) {
				item = new ItemWeapon(*weapon);
			}
			else if (ItemFood* food = dynamic_cast<ItemFood*>(_item)) {
				item = new ItemFood(*food);
			}
			else { item = new Item(*_item); }
		}
		else { item = nullptr; }
	}

	// Parameterised constructor with item parameters, basic item
	RoomItem(const std::string& _shortDesc, const std::string& _longDesc, const std::string& _darkDesc, bool _dark,
		const std::string& _itemName, const std::string& _itemDesc, bool _itemConsumable) :

		Room(_shortDesc, _longDesc, _darkDesc, _dark),
		item(new Item(_itemName, _itemDesc, _itemConsumable)) {}

	// Parameterised constructor with item parameters, weapon item
	RoomItem(const std::string& _shortDesc, const std::string& _longDesc, const std::string& _darkDesc, bool _dark,
		const std::string& _itemName, const std::string& _itemDesc, bool _itemConsumable, unsigned int _itemDamage) :

		Room(_shortDesc, _longDesc, _darkDesc, _dark),
		item(new ItemWeapon(_itemName, _itemDesc, _itemConsumable, _itemDamage)) {}

	// Parameterised constructor with item parameters, food item (excess char for distinction)
	RoomItem(const std::string& _shortDesc, const std::string& _longDesc, const std::string& _darkDesc, bool _dark,
		const std::string& _itemName, const std::string& _itemDesc, unsigned int _itemHeal, bool _itemConsumable, char f) :

		Room(_shortDesc, _longDesc, _darkDesc, _dark),
		item(new ItemFood(_itemName, _itemDesc, _itemHeal, _itemConsumable)) {}

	// Copy constructor
	RoomItem(const RoomItem& other) : Room(other) {
		if (other.item != nullptr) {
			// Use dynamic_cast to determine the actual derived type of the item
			if (ItemWeapon* weapon = dynamic_cast<ItemWeapon*>(other.item)) {
				item = new ItemWeapon(*weapon); }
			else if (ItemFood* food = dynamic_cast<ItemFood*>(other.item)) {
				item = new ItemFood(*food); }
			else { item = new Item(*other.item); }
		}
		else { item = nullptr; }
	}
	// Copy constructor from base class
	RoomItem(const Room& other) : Room(other), item(nullptr) {}

	// Destructor
	~RoomItem() { delete item; }

	// Interface functions
	Item* getItem() const { return item; }

	// Gameplay functions
	// Transfer ownership of the item to the caller
	std::unique_ptr<Item> collectItem() 
	{
		std::unique_ptr<Item> temp = std::unique_ptr<Item>(item);
		item = nullptr;
		return temp;
	}
	// Game display function that prints long description depending on room state
	virtual void LongDisplay() const override;

	// Display function that prints all information without conditions, for debugging
	virtual void DebugDisplay() const override;
};
// Treasure Room derived class, has treasure description, score, collected status
class RoomTreasure : public Room
{
protected:
	std::string treasureDesc;
	unsigned int treasureScore;
	bool collected = false;
public:
	// Default constructor
	RoomTreasure() : Room(), treasureDesc(""), treasureScore(0) {}
	// Parameterised constructor
	RoomTreasure(const std::string& _shortDesc, const std::string& _longDesc, const std::string& _darkDesc, bool _dark,
		const std::string& _treasureDesc, unsigned int _treasureScore) :
		Room(_shortDesc, _longDesc, _darkDesc, _dark),
		treasureDesc(_treasureDesc), treasureScore(_treasureScore) {}
	// Copy constructor
	RoomTreasure(const RoomTreasure& other) : Room(other), treasureDesc(other.treasureDesc), treasureScore(other.treasureScore), collected(other.collected) {}
	// Copy constructor from base class
	RoomTreasure(const Room& other) : Room(other), treasureDesc(""), treasureScore(0) {}

	// Destructor
	~RoomTreasure() = default;

	// Interface functions
	std::string getTreasureDesc() const { return treasureDesc; }
	unsigned int getTreasureScore() const { return treasureScore; }
	bool isCollected() const { return collected; }
	void setCollected(bool _collected) { collected = _collected; }

	// Game display function that prints long description depending on room state
	virtual void LongDisplay() const override;

	// Display function that prints all information without conditions, for debugging
	virtual void DebugDisplay() const override;
};

// This class is fundamentally the same as a blank room, but is separated for clarity and easy checking.
class RoomExit : public Room
{
public:
	// Default constructor
	RoomExit() : Room() {}
	// Parameterised constructor
	RoomExit(const std::string& _shortDesc, const std::string& _longDesc, const std::string& _darkDesc, bool _dark) :
		Room(_shortDesc, _longDesc, _darkDesc, _dark) {}
	// Copy constructor from base class
	RoomExit(const Room& other) : Room(other) {}
	// Copy constructor
	RoomExit(const RoomExit& other) : Room(other) {}

	// Destructor
	~RoomExit() = default;

	// Display function that prints all information without conditions, for debugging
	virtual void DebugDisplay() const override;
};
