#include "main.h"

int main()
{
	const static int DIMENSION = 4;
	using RoomGrid = std::array<std::array<std::unique_ptr<Room>, DIMENSION>, DIMENSION>; // a 2D array of pointers to Rooms
	RoomGrid allRooms;
	// set up all the memory first
	for (int i = 0; i < DIMENSION; i++)
	{
		for (int j = 0; j < DIMENSION; j++)
		{
			allRooms[i][j] = std::make_unique<Room>();
		}
	}

	
	
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

