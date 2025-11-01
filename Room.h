#pragma once
#include <string>
#include <iostream>
#include "Item.h"

class Room
{
protected:
	std::string shortDesc;
	std::string longDesc;
	std::string darkDesc;
	const Room* exitNorth = nullptr;
	const Room* exitEast = nullptr;
	const Room* exitSouth = nullptr;
	const Room* exitWest = nullptr;
	bool dark;
public:
	// Default constructor
	Room() : shortDesc(""), longDesc(""), darkDesc(""), dark(false), exitNorth(nullptr), exitEast(nullptr), exitSouth(nullptr), exitWest(nullptr) {}

	// Parameterised constructor
	Room(const std::string& _shortDesc, const std::string& _longDesc, const std::string& _darkDesc, bool _dark,
	const Room* _exitNorth = nullptr, const Room* _exitEast = nullptr, const Room* _exitSouth = nullptr, const Room* _exitWest = nullptr) :

		shortDesc(_shortDesc), longDesc(_longDesc), darkDesc(_darkDesc), dark(_dark),
		exitNorth(_exitNorth), exitEast(_exitEast), exitSouth(_exitSouth), exitWest(_exitWest) {}

	// Copy constructor
	Room (const Room& other) : 
		shortDesc(other.shortDesc), longDesc(other.longDesc), darkDesc(other.darkDesc), dark(other.dark),
		exitNorth(other.exitNorth), exitEast(other.exitEast), exitSouth(other.exitSouth), exitWest(other.exitWest) {}

	// Destructor
	virtual ~Room() { std::cout << "destructor basic\n"; }

	// Interface functions
	const std::string& getShortDesc() const { return shortDesc; }
	const std::string& getLongDesc() const { return longDesc; }
	const std::string& getDarkDesc() const { return darkDesc; }
	const Room* getExitNorthPtr() const { return exitNorth; }
	const Room getExitNorth() const { return *exitNorth; }
	const Room* getExitEastPtr() const { return exitEast; }
	const Room getExitEast() const { return *exitEast; }
	const Room* getExitSouthPtr() const { return exitSouth; }
	const Room getExitSouth() const { return *exitSouth; }
	const Room* getExitWestPtr() const { return exitWest; }
	const Room getExitWest() const { return *exitWest; }
	bool getDark() const { return dark; }

	void setExits(const Room* _exitNorth = nullptr, const Room* _exitEast = nullptr, const Room* _exitSouth = nullptr, const Room* _exitWest = nullptr)
	{ 
		exitNorth = _exitNorth; 
		exitEast = _exitEast;
		exitSouth = _exitSouth;
		exitWest = _exitWest;
	}


	// Display function that prints all information without conditions, for debugging
	virtual void DebugDisplay() const;
};

class RoomEnemy : public Room
{
protected:
	std::string enemyName;
	unsigned int enemyHealth;
	unsigned int enemyDamage;
	unsigned int enemyScore;
	bool enemyAlive;
public:
	// Default constructor
	RoomEnemy() : Room(), enemyName(""), enemyHealth(1), enemyDamage(0), enemyScore(0), enemyAlive(true) {}
	// Parameterised constructor
	RoomEnemy(const std::string& _shortDesc, const std::string& _longDesc, const std::string& _darkDesc, bool _dark,
		Room* _exitNorth = nullptr, Room* _exitEast = nullptr, Room* _exitSouth = nullptr, Room* _exitWest = nullptr,
		bool _enemyAlive = true, const std::string& _enemyName = "",
		unsigned int _enemyHealth = 1, unsigned int _enemyDamage = 0, unsigned int _enemyScore = 0) :

		Room(_shortDesc, _longDesc, _darkDesc, _dark, _exitNorth, _exitEast, _exitSouth, _exitWest),
		enemyAlive(_enemyAlive), enemyName(_enemyName),
		enemyHealth(_enemyHealth), enemyDamage(_enemyDamage), enemyScore(_enemyScore) {}
	
	// Copy constructor
	RoomEnemy(const RoomEnemy& other) : Room(other), 
		enemyAlive(other.enemyAlive), enemyName(other.enemyName),
		enemyHealth(other.enemyHealth), enemyDamage(other.enemyDamage), enemyScore(other.enemyScore) {}
	// Copy constructor from base class
	RoomEnemy(const Room& other) : Room(other),
		enemyName(""), enemyHealth(1), enemyDamage(0), enemyScore(0), enemyAlive(true) {}

	// Destructor
	~RoomEnemy() { std::cout << "destructor enemy\n"; }

	// Interface functions


	// Display function that prints all information without conditions, for debugging
	virtual void DebugDisplay() const override;
};

class RoomItem : public Room
{
protected:
	Item* item = nullptr;
public:
	// Default constructor
	RoomItem() : Room(), item(nullptr) {}

	// Parameterised constructor with existing item
	RoomItem(const std::string& _shortDesc, const std::string& _longDesc, const std::string& _darkDesc, bool _dark,
		Room* _exitNorth = nullptr, Room* _exitEast = nullptr, Room* _exitSouth = nullptr, Room* _exitWest = nullptr,
		Item* _item = nullptr) :
		Room(_shortDesc, _longDesc, _darkDesc, _dark, _exitNorth, _exitEast, _exitSouth, _exitWest)
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
		Room* _exitNorth = nullptr, Room* _exitEast = nullptr, Room* _exitSouth = nullptr, Room* _exitWest = nullptr,
		const std::string& _itemName = "", const std::string& _itemDesc = "", bool _itemConsumable = false) :

		Room(_shortDesc, _longDesc, _darkDesc, _dark, _exitNorth, _exitEast, _exitSouth, _exitWest),
		item(new Item(_itemName, _itemDesc, _itemConsumable)) {}

	// Parameterised constructor with item parameters, weapon item (amount after bool for distinction from food)
	RoomItem(const std::string& _shortDesc, const std::string& _longDesc, const std::string& _darkDesc, bool _dark,
		Room* _exitNorth = nullptr, Room* _exitEast = nullptr, Room* _exitSouth = nullptr, Room* _exitWest = nullptr,
		const std::string& _itemName = "", const std::string& _itemDesc = "", bool _itemConsumable = false, unsigned int _itemDamage = 0) :

		Room(_shortDesc, _longDesc, _darkDesc, _dark, _exitNorth, _exitEast, _exitSouth, _exitWest),
		item(new ItemWeapon(_itemName, _itemDesc, _itemConsumable, _itemDamage)) {}

	// Parameterised constructor with item parameters, food item (amount before bool for distinction from weapon)
	RoomItem(const std::string& _shortDesc, const std::string& _longDesc, const std::string& _darkDesc, bool _dark,
		Room* _exitNorth = nullptr, Room* _exitEast = nullptr, Room* _exitSouth = nullptr, Room* _exitWest = nullptr,
		const std::string& _itemName = "", const std::string& _itemDesc = "", unsigned int _itemHeal = 0, bool _itemConsumable = false) :

		Room(_shortDesc, _longDesc, _darkDesc, _dark, _exitNorth, _exitEast, _exitSouth, _exitWest),
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
	~RoomItem() { delete item; std::cout << "destructor item\n"; }

	// Display function that prints all information without conditions, for debugging
	virtual void DebugDisplay() const override;
};

class RoomTreasure : public Room
{
protected:
	std::string treasureDesc;
	unsigned int treasureScore;
	bool collected;
public:
	// Default constructor
	RoomTreasure() : Room(), treasureDesc(""), treasureScore(0), collected(false) {}
	// Parameterised constructor
	RoomTreasure(const std::string& _shortDesc, const std::string& _longDesc, const std::string& _darkDesc, bool _dark,
		Room* _exitNorth = nullptr, Room* _exitEast = nullptr, Room* _exitSouth = nullptr, Room* _exitWest = nullptr, 
		const std::string& _treasureDesc = "", unsigned int _treasureScore = 0, bool _collected = false) :
		Room(_shortDesc, _longDesc, _darkDesc, _dark, _exitNorth, _exitEast, _exitSouth, _exitWest),
		treasureDesc(_treasureDesc), treasureScore(_treasureScore), collected(_collected) {}
	// Copy constructor
	RoomTreasure(const RoomTreasure& other) : Room(other), treasureDesc(other.treasureDesc), treasureScore(other.treasureScore), collected(other.collected) {}
	// Copy constructor from base class
	RoomTreasure(const Room& other) : Room(other), treasureDesc(""), treasureScore(0), collected(false) {}

	// Destructor
	~RoomTreasure() { std::cout << "destructor treasure\n"; }

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
	RoomExit(const std::string& _shortDesc, const std::string& _longDesc, const std::string& _darkDesc, bool _dark,
		Room* _exitNorth = nullptr, Room* _exitEast = nullptr, Room* _exitSouth = nullptr, Room* _exitWest = nullptr) :
		Room(_shortDesc, _longDesc, _darkDesc, _dark, _exitNorth, _exitEast, _exitSouth, _exitWest) {}
	// Copy constructor from base class
	RoomExit(const Room& other) : Room(other) {}
	// Copy constructor
	RoomExit(const RoomExit& other) : Room(other) {}

	// Destructor
	~RoomExit() { std::cout << "destructor exit\n"; }

	// Display function that prints all information without conditions, for debugging
	virtual void DebugDisplay() const override;
};
