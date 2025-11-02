#include "Room.h"

#pragma region Base Room
// Display function that prints all information without conditions, for debugging. Polymorphed for derived classes.
void Room::DebugDisplay() const 
{ 
	std::cout << "==Basic Room==\n";
	std::cout << "Short Description: " << shortDesc << "\n";
	std::cout << "Long Description: " << longDesc << "\n";
	std::cout << "Dark Description: " << darkDesc << "\n";
	std::cout << "Is Dark: " << (dark ? "yes" : "no") << "\n"; // use a ternary to print a word instead of booleans, which are 0 or 1

	// print exits
	if (exitNorth) { std::cout << "Exit exists to the north.\n"; }
	else { std::cout << "No exit to the north.\n"; }
	if (exitEast) { std::cout << "Exit exists to the east.\n"; }
	else { std::cout << "No exit to the east.\n"; }
	if (exitSouth) { std::cout << "Exit exists to the south.\n"; }
	else { std::cout << "No exit to the south.\n"; }
	if (exitWest) { std::cout << "Exit exists to the west.\n"; }
	else { std::cout << "No exit to the west.\n"; }
}

// Game display function that prints information based on room state for entering a room
void Room::EnterDisplay() const
{
	if (dark) { std::cout << darkDesc << '\n'; }
	else { std::cout << shortDesc << '\n'; }
}
// Game display function that prints long description depending on room state. Polymorphed for derived classes.
void Room::LongDisplay() const
{
	if (dark) { std::cout << darkDesc << '\n'; }
	else
	{
		std::cout << longDesc << '\n';
		if (exitNorth) { std::cout << "There is an exit to the north.\n"; }
		if (exitEast) { std::cout << "There is an exit to the east.\n"; }
		if (exitSouth) { std::cout << "There is an exit to the south.\n"; }
		if (exitWest) { std::cout << "There is an exit to the west.\n"; }
	}
}

#pragma endregion

#pragma region Enemy Room
// Display function that prints all information without conditions, for debugging. Polymorphed for derived classes: enemy information
void RoomEnemy::DebugDisplay() const 
{
	std::cout << "==Enemy Room==\n";
	std::cout << "Short Description: " << shortDesc << "\n";
	std::cout << "Long Description: " << longDesc << "\n";
	std::cout << "Dark Description: " << darkDesc << "\n";
	std::cout << "Is Dark: " << (dark ? "yes" : "no") << "\n";
	if (exitNorth) { std::cout << "Exit exists to the north.\n"; }
	else { std::cout << "No exit to the north.\n"; }
	if (exitEast) { std::cout << "Exit exists to the east.\n"; }
	else { std::cout << "No exit to the east.\n"; }
	if (exitSouth) { std::cout << "Exit exists to the south.\n"; }
	else { std::cout << "No exit to the south.\n"; }
	if (exitWest) { std::cout << "Exit exists to the west.\n"; }
	else { std::cout << "No exit to the west.\n"; }
	std::cout << "There is an enemy in this room.\n";
	std::cout << "Enemy name: " << enemyName << "\n";
	std::cout << "Enemy damage: " << enemyDamage << "\n";
	std::cout << "Enemy alive: " << (enemyAlive ? "yes" : "no") << ".\n"; // use a ternary to print a word instead of booleans, which are 0 or 1
	std::cout << "Enemy score: " << enemyScore << ".\n";
}
// Game function to damage the enemy, returns score if enemy dies
unsigned int RoomEnemy::damageEnemy(int _damage)
{
	if (enemyAlive)
	{
		// damage enemy health
		enemyHealth -= _damage;
		if (enemyHealth <= 0)
		{
			// avoid negative health
			enemyHealth = 0;
			// tell the room the enemy is dead
			enemyAlive = false;
			// return the score for killing the enemy
			return enemyScore;
		}
	}
	// return no score if enemy is still alive
	return 0;
}
// Game display function that prints long description depending on room state. Polymorphed for derived classes: enemy information
void RoomEnemy::LongDisplay() const
{
	if (dark) { std::cout << darkDesc << '\n'; }
	else
	{
		std::cout << longDesc << '\n';
		if (exitNorth) { std::cout << "There is an exit to the north.\n"; }
		if (exitEast) { std::cout << "There is an exit to the east.\n"; }
		if (exitSouth) { std::cout << "There is an exit to the south.\n"; }
		if (exitWest) { std::cout << "There is an exit to the west.\n"; }
		std::cout << "There is an enemy in this room.\n";
		if (!enemyAlive)
		{
			// Doesn't display enemy stats if it is already dead
			std::cout << "It is a dead " << enemyName << ".\n";
		}
		else
		{
			std::cout << "It is a " << enemyName << ".\n";
			std::cout << "It has " << enemyHealth << " health, can deal " << enemyDamage << " damage, and is carrying " << enemyScore << " gold.\n";
		}
	}
}

#pragma endregion

#pragma region Item Room
// Display function that prints all information without conditions, for debugging. Polymorphed for derived classes: item information
void RoomItem::DebugDisplay() const 
{ 
	std::cout << "==Item Room==\n";
	std::cout << "Short Description: " << shortDesc << "\n";
	std::cout << "Long Description: " << longDesc << "\n";
	std::cout << "Dark Description: " << darkDesc << "\n";
	std::cout << "Is Dark: " << (dark ? "yes" : "no") << "\n";
	if (exitNorth) { std::cout << "Exit exists to the north.\n"; }
	else { std::cout << "No exit to the north.\n"; }
	if (exitEast) { std::cout << "Exit exists to the east.\n"; }
	else { std::cout << "No exit to the east.\n"; }
	if (exitSouth) { std::cout << "Exit exists to the south.\n"; }
	else { std::cout << "No exit to the south.\n"; }
	if (exitWest) { std::cout << "Exit exists to the west.\n"; }
	else { std::cout << "No exit to the west.\n"; }
	if (item != nullptr)
	{
		std::cout << "Room contains an item:\n";
		item->Display(); // use the item's own display function instead of reprinting all its info here
	}
	else
	{
		// if the item pointer is null, there is no item in the room, so I can't even print what its name was.
		std::cout << "Room contains no item.\n";
	}
}
// Game display function that prints long description depending on room state. Polymorphed for derived classes: item information
void RoomItem::LongDisplay() const
{
	if (dark) { std::cout << darkDesc << '\n'; }
	else
	{
		std::cout << longDesc << '\n';
		if (exitNorth) { std::cout << "There is an exit to the north.\n"; }
		if (exitEast) { std::cout << "There is an exit to the east.\n"; }
		if (exitSouth) { std::cout << "There is an exit to the south.\n"; }
		if (exitWest) { std::cout << "There is an exit to the west.\n"; }
		if (item != nullptr)
		{
			// display item information only if it exists using the item's interface functions
			std::cout << "There is a " << item->getItemName() << " here.\n";
			std::cout << item->getItemDesc() << '\n';
		}
		else
		{
			std::cout << "There was an item here, but it is gone.\n";
		}
	}
}

#pragma endregion

#pragma region Treasure Room
// Display function that prints all information without conditions, for debugging. Polymorphed for derived classes: treasure information
void RoomTreasure::DebugDisplay() const 
{
	std::cout << "==Treasure Room==\n";
	std::cout << "Short Description: " << shortDesc << "\n";
	std::cout << "Long Description: " << longDesc << "\n";
	std::cout << "Dark Description: " << darkDesc << "\n";
	std::cout << "Is Dark: " << (dark ? "yes" : "no") << "\n";
	if (exitNorth) { std::cout << "Exit exists to the north.\n"; }
	else { std::cout << "No exit to the north.\n"; }
	if (exitEast) { std::cout << "Exit exists to the east.\n"; }
	else { std::cout << "No exit to the east.\n"; }
	if (exitSouth) { std::cout << "Exit exists to the south.\n"; }
	else { std::cout << "No exit to the south.\n"; }
	if (exitWest) { std::cout << "Exit exists to the west.\n"; }
	else { std::cout << "No exit to the west.\n"; }
	std::cout << "Treasure score: " << treasureScore << ".\n";
	std::cout << "Treasure collected: " << (collected ? "yes" : "no") << ".\n"; // use a ternary to print a word instead of booleans, which are 0 or 1
	std::cout << "Treasure description: " << treasureDesc << "\n";
}
// Game display function that prints long description depending on room state. Polymorphed for derived classes: treasure information
void RoomTreasure::LongDisplay() const
{
	if (dark) { std::cout << darkDesc << '\n'; }
	else
	{
		std::cout << longDesc << '\n';
		if (exitNorth) { std::cout << "There is an exit to the north.\n"; }
		if (exitEast) { std::cout << "There is an exit to the east.\n"; }
		if (exitSouth) { std::cout << "There is an exit to the south.\n"; }
		if (exitWest) { std::cout << "There is an exit to the west.\n"; }
		if (collected)
		{
			// don't print treasure stats if it is collected
			std::cout << "There was treasure in this room, but it is gone.\n";
		}
		else
		{
			std::cout << "There is treasure in this room!\n";
			std::cout << treasureDesc << '\n';
			std::cout << "It is worth " << treasureScore << " gold.\n";
		}
	}
}

#pragma endregion

#pragma region Exit Room
// Display function that prints all information without conditions, for debugging. Polymorphed for derived classes: extra line for exit room
void RoomExit::DebugDisplay() const 
{
	std::cout << "==Exit Room==\n";
	std::cout << "Unlock this room to beat the game.\n";
	std::cout << "Short Description: " << shortDesc << "\n";
	std::cout << "Long Description: " << longDesc << "\n";
	std::cout << "Dark Description: " << darkDesc << "\n";
	std::cout << "Is dark: " << (dark ? "yes" : "no") << ".\n";
	if (exitNorth) { std::cout << "Exit exists to the north.\n"; }
	else { std::cout << "No exit to the north.\n"; }
	if (exitEast) { std::cout << "Exit exists to the east.\n"; }
	else { std::cout << "No exit to the east.\n"; }
	if (exitSouth) { std::cout << "Exit exists to the south.\n"; }
	else { std::cout << "No exit to the south.\n"; }
	if (exitWest) { std::cout << "Exit exists to the west.\n"; }
	else { std::cout << "No exit to the west.\n"; }
}

#pragma endregion

