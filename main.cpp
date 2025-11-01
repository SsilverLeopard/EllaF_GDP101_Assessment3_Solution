#include "main.h"

std::string const static COMMANDS[9] = { "help", "look", "move", "use", "fight", "get", "inventory", "restart", "exit" };

void ParseCommand(const std::string& input)
{
	
}

int main()
{
	const int DIMENSION = 4;
	Room* (*help)[DIMENSION] = new Room*[DIMENSION][DIMENSION]; // a 2D array of pointers to Rooms
	for (int i = 0; i < DIMENSION; i++)
	{
		for (int j = 0; j < DIMENSION; j++)
		{
			help[i][j] = new Room();
		}
	}
	help[0][0] = new Room();
	help[0][1] = new RoomEnemy();
	help[0][2] = new RoomItem(*help[0][0]);
	help[0][3] = new RoomExit();
	help[1][0] = new RoomTreasure();
	help[1][1] = new RoomItem(*dynamic_cast<RoomItem*>(help[0][2])); // need to do that because i am bad at programming
	for (int i = 0; i < DIMENSION; i++)
	{
		for (int j = 0; j < DIMENSION; j++)
		{
			std::cout << (i * 4) + j;
			help[i][j]->DebugDisplay();
		}
	}

	for (int i = 0; i < DIMENSION; i++)
	{
		for (int j = 0; j < DIMENSION; j++)
		{
			std::cout << i << j;
			delete help[i][j];
		}
	}
	delete[] help;

	std::cout << "Hello World!\n";
}

