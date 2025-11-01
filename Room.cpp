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
	if (exitNorth != nullptr) 
	{ 
		std::cout << "Exit exists to the north, short desc: " << exitNorth->getShortDesc() << "\n";
	}
	else
	{
		std::cout << "No exit to the north.\n";
	}
	if (exitEast != nullptr) 
	{ 
		std::cout << "Exit exists to the east, short desc: " << exitEast->getShortDesc() << "\n"; 
	}
	else
	{ 
		std::cout << "No exit to the east.\n"; 
	}
	if (exitSouth != nullptr)
	{
		std::cout << "Exit exists to the south, short desc: " << exitSouth->getShortDesc() << "\n";
	}
	else
	{
		std::cout << "No exit to the south.\n";
	}
	if (exitWest != nullptr)
	{
		std::cout << "Exit exists to the west, short desc: " << exitWest->getShortDesc() << "\n";
	}
	else
	{
		std::cout << "No exit to the west.\n";
	}
}

void Room::EnterDisplay() const
{
	if (dark)
	{
		std::cout << darkDesc << '\n';
	}
	else
	{
		std::cout << shortDesc << '\n';
		for (auto &d : DIRECTION_NAMES)
		{
			const Room* exitPtr = nullptr;
			if (d == "north") exitPtr = exitNorth;
			else if (d == "east") exitPtr = exitEast;
			else if (d == "south") exitPtr = exitSouth;
			else if (d == "west") exitPtr = exitWest;
			if (exitPtr != nullptr)
			{
				std::cout << "There is an exit to the " << d << ".\n";
			}
		}
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
	if (exitNorth != nullptr)
	{
		std::cout << "Exit exists to the north, short desc: " << exitNorth->getShortDesc() << "\n";
	}
	else
	{
		std::cout << "No exit to the north.\n";
	}
	if (exitEast != nullptr)
	{
		std::cout << "Exit exists to the east, short desc: " << exitEast->getShortDesc() << "\n";
	}
	else
	{
		std::cout << "No exit to the east.\n";
	}
	if (exitSouth != nullptr)
	{
		std::cout << "Exit exists to the south, short desc: " << exitSouth->getShortDesc() << "\n";
	}
	else
	{
		std::cout << "No exit to the south.\n";
	}
	if (exitWest != nullptr)
	{
		std::cout << "Exit exists to the west, short desc: " << exitWest->getShortDesc() << "\n";
	}
	else
	{
		std::cout << "No exit to the west.\n";
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
	if (exitNorth != nullptr)
	{
		std::cout << "Exit exists to the north, short desc: " << exitNorth->getShortDesc() << "\n";
	}
	else
	{
		std::cout << "No exit to the north.\n";
	}
	if (exitEast != nullptr)
	{
		std::cout << "Exit exists to the east, short desc: " << exitEast->getShortDesc() << "\n";
	}
	else
	{
		std::cout << "No exit to the east.\n";
	}
	if (exitSouth != nullptr)
	{
		std::cout << "Exit exists to the south, short desc: " << exitSouth->getShortDesc() << "\n";
	}
	else
	{
		std::cout << "No exit to the south.\n";
	}
	if (exitWest != nullptr)
	{
		std::cout << "Exit exists to the west, short desc: " << exitWest->getShortDesc() << "\n";
	}
	else
	{
		std::cout << "No exit to the west.\n";
	}
	if (item != nullptr)
	{
		std::cout << "Room contains an item:\n";
		item->DebugDisplay();
	}
	else
	{
		std::cout << "Room contains no item.\n";
	}
}

#pragma endregion

#pragma region Treasure Room
void RoomTreasure::DebugDisplay() const 
{
	std::cout << "==Item Room==\n";
	std::cout << "Short Description: " << shortDesc << "\n";
	std::cout << "Long Description: " << longDesc << "\n";
	std::cout << "Dark Description: " << darkDesc << "\n";
	std::cout << "Is Dark: " << (dark ? "yes" : "no") << "\n";
	if (exitNorth != nullptr)
	{
		std::cout << "Exit exists to the north, short desc: " << exitNorth->getShortDesc() << "\n";
	}
	else
	{
		std::cout << "No exit to the north.\n";
	}
	if (exitEast != nullptr)
	{
		std::cout << "Exit exists to the east, short desc: " << exitEast->getShortDesc() << "\n";
	}
	else
	{
		std::cout << "No exit to the east.\n";
	}
	if (exitSouth != nullptr)
	{
		std::cout << "Exit exists to the south, short desc: " << exitSouth->getShortDesc() << "\n";
	}
	else
	{
		std::cout << "No exit to the south.\n";
	}
	if (exitWest != nullptr)
	{
		std::cout << "Exit exists to the west, short desc: " << exitWest->getShortDesc() << "\n";
	}
	else
	{
		std::cout << "No exit to the west.\n";
	}
	std::cout << "Treasure score: " << treasureScore << ".\n";
	std::cout << "Treasure collected: " << (collected ? "yes" : "no") << ".\n";
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
	if (exitNorth != nullptr)
	{
		std::cout << "Exit exists to the north, short desc: " << exitNorth->getShortDesc() << "\n";
	}
	else
	{
		std::cout << "No exit to the north.\n";
	}
	if (exitEast != nullptr)
	{
		std::cout << "Exit exists to the east, short desc: " << exitEast->getShortDesc() << "\n";
	}
	else
	{
		std::cout << "No exit to the east.\n";
	}
	if (exitSouth != nullptr)
	{
		std::cout << "Exit exists to the south, short desc: " << exitSouth->getShortDesc() << "\n";
	}
	else
	{
		std::cout << "No exit to the south.\n";
	}
	if (exitWest != nullptr)
	{
		std::cout << "Exit exists to the west, short desc: " << exitWest->getShortDesc() << "\n";
	}
	else
	{
		std::cout << "No exit to the west.\n";
	}
}

#pragma endregion

