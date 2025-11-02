#include "Room.h"

std::string DIRECTION_NAMES[4] = { "north", "east", "south", "west" };

#pragma region Base Room
void Room::DebugDisplay() const 
{ 
	std::cout << "==Basic Room==\n";
	std::cout << "Short Description: " << shortDesc << "\n";
	std::cout << "Long Description: " << longDesc << "\n";
	std::cout << "Dark Description: " << darkDesc << "\n";
	std::cout << "Is Dark: " << (dark ? "yes" : "no") << "\n";
	if (exitNorth) 
	{ std::cout << "Exit exists to the north.\n"; }
	else { std::cout << "No exit to the north.\n"; }
	if (exitEast) { std::cout << "Exit exists to the east.\n"; }
	else { std::cout << "No exit to the east.\n"; }
	if (exitSouth) { std::cout << "Exit exists to the south.\n"; }
	else { std::cout << "No exit to the south.\n"; }
	if (exitWest) { std::cout << "Exit exists to the west.\n"; }
	else { std::cout << "No exit to the west.\n"; }
}

void Room::EnterDisplay() const
{
	if (dark) { std::cout << darkDesc << '\n'; }
	else
	{
		std::cout << shortDesc << '\n';
	}
}

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
	if (!enemyAlive) 
	{
		std::cout << "It is a dead " << enemyName << ".\n";
	}
	else
	{
		std::cout << "It is a " << enemyName << ".\n";
	}
	
}
unsigned int RoomEnemy::damageEnemy(int _damage)
{
	if (enemyAlive)
	{
		enemyHealth -= _damage;
		if (enemyHealth <= 0)
		{
			enemyHealth = 0;
			enemyAlive = false;
			return enemyScore;
		}
	}
	return 0;
}

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
		item->Display();
	}
	else
	{
		std::cout << "Room contains no item.\n";
	}
}

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
	std::cout << "Treasure collected: " << (collected ? "yes" : "no") << ".\n";
	std::cout << "Treasure description: " << treasureDesc << "\n";
}

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

