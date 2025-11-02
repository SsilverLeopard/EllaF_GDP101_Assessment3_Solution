#include "main.h"
#include <memory> // for unique_ptr
#include <utility> // for std::move

// horizontal and vertical size of the room grid
const static int DIMENSION = 4;

int main()
{
	// a 2D array of unique pointers to Rooms
	using RoomGrid = std::array<std::array<std::unique_ptr<Room>, DIMENSION>, DIMENSION>; 
	RoomGrid allRooms;
	// set up all the memory first
	for (int i = 0; i < DIMENSION; i++)
	{
		for (int j = 0; j < DIMENSION; j++)
		{
			allRooms[i][j] = std::make_unique<Room>();
		}
	}
	// instantiate the game master class
	Game game;
	// set up the game with starting position and the empty room grid, wiht 6 health
	game.setup(2, 2, std::move(allRooms), 6, 0);
	// print welcome message
	std::cout << "You fall down a trapdoor into a dungeon. Hopefully you can get out quickly, and maybe find something shiny while you're down here.\n";
	// display first room message
	game.getCurrentRoom()->EnterDisplay();
	// main game loop
	while (game.getReturning() == 0) // wait until the player wants to quit or has won/lost
	{
		// get player input. the command function handles everything.
		game.command();
		std::cout << std::endl;
		if (game.getPlayerHealth() <= 0) // if player dies
		{
			std::cout << "You died! Oops.\n";
			// let the player restart or quit
			game.limitedCommand();
			continue;
		}
		if (game.getReturning() == 2) // 2 signals win
		{
			// print winning message
			std::cout << "You climb up the ladder to escape as the melodious voice fades into the distance.\nYou win!\n";
			// let the player restart or quit
			game.limitedCommand();
			continue;
		}
	}
	// pause before exiting
	system("pause");
	return 0;
	// no deletes needed because smart pointers
}

