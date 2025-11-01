#include "main.h"

int main()
{
	const static int DIMENSION = 4;
	using RoomGrid = std::array<std::array<std::unique_ptr<Room>, DIMENSION>, DIMENSION>; // a 2D array of pointers to Rooms
	RoomGrid allRooms;
	for (int i = 0; i < DIMENSION; i++)
	{
		for (int j = 0; j < DIMENSION; j++)
		{
			allRooms[i][j] = std::make_unique<Room>();
		}
	}
#pragma region Create Rooms
	// the handcrafted map
	/* Map:
	Key: Entry, Treasure, Item, eXit, eNemy, Blank, Key, !dark, =door, -| not a path
	-----------------
	| T!= N | X | B!|
	| = |---| = | = |
	| T = I = I = T!|
	| = |---|---| = |
	| I | I = E = B |
	|---| = |---| = |
	| K!= N | N!= I |
	-----------------
	00 01 02 03
	10 11 12 13
	20 21 22 23
	30 31 32 33
	room 21 is a sword which you can use to fight. room 33 is a better sword. room 12 is a torch to see in dark rooms. room 30 is a key to exit the exit room at 03.
*/
	// set up rooms
	allRooms[0][0] = std::make_unique <RoomTreasure>();
	allRooms[0][1] = std::make_unique <RoomEnemy>();
	allRooms[0][2] = std::make_unique <RoomExit>();
	allRooms[0][3] = std::make_unique <Room>();
	allRooms[1][0] = std::make_unique <RoomTreasure>();
	allRooms[1][1] = std::make_unique <RoomItem>();
	allRooms[1][2] = std::make_unique <RoomItem>();
	allRooms[1][3] = std::make_unique <RoomTreasure>();
	allRooms[2][0] = std::make_unique <RoomItem>();
	allRooms[2][1] = std::make_unique <RoomItem>();
	allRooms[2][2] = std::make_unique <Room>();
	allRooms[2][3] = std::make_unique <Room>();
	allRooms[3][0] = std::make_unique <RoomItem>();
	allRooms[3][1] = std::make_unique <RoomEnemy>();
	allRooms[3][2] = std::make_unique <RoomEnemy>();
	allRooms[3][3] = std::make_unique <RoomItem>("You see some hooks on the wall.", "There is a stand for a large sword on the wall.", "", false, nullptr, nullptr, nullptr, nullptr, "Sarkis the Broadsword", "Sarkis is not just a weapon, it's an enemy-shredding machine. Don't drop it on your foot.", false, 4);
	
	// set up their exits
	allRooms[0][0]->setExits(nullptr, allRooms[0][1].get(), allRooms[1][0].get(), nullptr);
	allRooms[0][1]->setExits(nullptr, nullptr, nullptr, allRooms[0][0].get());
	allRooms[0][2]->setExits(nullptr, nullptr, allRooms[1][2].get(), nullptr);
	allRooms[0][3]->setExits(nullptr, nullptr, allRooms[1][3].get(), nullptr);
	allRooms[1][0]->setExits(allRooms[0][0].get(), allRooms[1][1].get(), allRooms[2][0].get(), nullptr);
	allRooms[1][1]->setExits(nullptr, allRooms[1][2].get(), nullptr, allRooms[1][0].get());
	allRooms[1][2]->setExits(nullptr, nullptr, nullptr, nullptr);
	allRooms[1][3]->setExits(nullptr, nullptr, nullptr, nullptr);
	allRooms[2][0]->setExits(nullptr, nullptr, nullptr, nullptr);
	allRooms[2][1]->setExits(nullptr, nullptr, nullptr, nullptr);
	allRooms[2][2]->setExits(nullptr, nullptr, nullptr, nullptr);
	allRooms[2][3]->setExits(nullptr, nullptr, nullptr, nullptr);
	allRooms[3][0]->setExits(nullptr, nullptr, nullptr, nullptr);
	allRooms[3][1]->setExits(nullptr, nullptr, nullptr, nullptr);
	allRooms[3][2]->setExits(nullptr, nullptr, nullptr, nullptr);
	allRooms[3][3]->setExits(allRooms[2][3].get(), nullptr, nullptr, allRooms[3][2].get());

#pragma endregion
	
	
	for (int i = 0; i < DIMENSION; i++)
	{
		for (int j = 0; j < DIMENSION; j++)
		{
			std::cout << (i * 4) + j;
			allRooms[i][j]->DebugDisplay();
		}
	}
	Game game;
	game.setup(2, 2, std::move(allRooms));
	std::cout << "You fall down a trapdoor into a dungeon. Your adventure begins now!\n";
	game.command();

	system("pause");
	return 0;
	// no deletes needed because smart pointers
}

