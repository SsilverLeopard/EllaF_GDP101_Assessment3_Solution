#include "Game.h"

int const static NUM_COMMANDS = 9;
std::string const static COMMANDS[NUM_COMMANDS] = { "help", "look", "move", "use", "fight", "collect", "inventory", "restart", "quit" };
std::string const static HURTING_COMMANDS[5] = { "look", "move", "use", "collect", "inventory" };

void Game::setup(unsigned int _startX, unsigned int _startY, RoomGrid&& _allRooms)
{
	// take ownership of the provided grid
	allRooms = std::move(_allRooms);

	playerX = _startX;
	playerY = _startY;

	// set non-owning currentRoom pointer
	currentRoom = allRooms[playerX][playerY].get();

	// debug display of all rooms
	for (int i = 0; i < DIMENSION; ++i)
	{
		for (int j = 0; j < DIMENSION; ++j)
		{
			if (allRooms[i][j])
			{
				allRooms[i][j]->DebugDisplay();
			}
		}
	}

	std::cout << "current room\n";
	currentRoom->DebugDisplay();
}

void Game::setup(unsigned int _startX, unsigned int _startY, RoomGrid&& _allRooms,
	unsigned int _playerHealth, unsigned int _playerScore)
{
	this->setup(_startX, _startY, std::move(_allRooms));
	playerHealth = _playerHealth;
	playerScore = _playerScore;
}

void Game::command()
{
	std::cout << "What do you do? ";
	std::string input;
	getline(std::cin, input);
	std::transform(input.begin(), input.end(), input.begin(), ::tolower); // convert to lowercase for easier parsing
	int fails = 0;
	for (int i = 0; i < NUM_COMMANDS; i++)
	{
		if (input.find(COMMANDS[i]) != std::string::npos)
		{
			std::string command = input.substr(input.find(COMMANDS[i]), COMMANDS[i].length());
			std::cout << "Command recognised: " << command << "\n";
			if (command == "help")
			{
				this->help();
			}
			else if (command == "look")
			{
				this->look();
			}
			else if (input.find("move") != std::string::npos)
			{
				if (input.find("north") != std::string::npos || input.find("n") != std::string::npos)
				{
					this->move('n');
				}
				else if (command.find("east") != std::string::npos || input.find("e") != std::string::npos)
				{
					this->move('e');
				}
				else if (command.find("south") != std::string::npos || input.find("s") != std::string::npos)
				{
					this->move('s');
				}
				else if (command.find("west") != std::string::npos || input.find("w") != std::string::npos)
				{
					this->move('w');
				}
				else
				{
					std::cout << "Direction not recognised. Please specify north, east, south, or west (or n, e, s or w).\n";
				}
			}
			else if (input.find("use") != std::string::npos)
			{
				std::string itemName = command.substr(command.find("use") + 4);
				this->use(itemName);
			}
			else if (command == "fight")
			{
				this->fight();
			}
			else if (command == "collect")
			{
				this->collect();
			}
			else if (command == "inventory")
			{
				this->viewInventory();
			}
			else if (command == "restart")
			{
				this->restart();
			}
			else if (command == "quit")
			{
				this->quit();
			}
			break;
		}
		else
		{
			fails++;
		}
	}
	if (fails == NUM_COMMANDS)
	{
		std::cout << "Command not recognised. Type 'help' for a list of commands.\n";
	}
}

void Game::help()
{
	std::cout << "== Game Help ==\n";
	std::cout << "Available commands:\n";
	std::cout << " - help: Display this help message.\n";
	std::cout << " - look: Look around the current room.\n";
	std::cout << " - move <direction>: Move in the specified direction (north, east, south, west or n, e, s, w).\n";
	std::cout << " - use <item name>: Use an item from your inventory.\n";
	std::cout << " - inventory: View your current inventory, including health and gold.\n";
	std::cout << " - fight: Attack an enemy in the room.\n";
	std::cout << " - collect: Collect an item or treasure in the room.\n";
	std::cout << " - restart: Restart the game from the beginning.\n";
	std::cout << " - quit: Exit the game and this program.\n";
	std::cout << "\nOther tips:\n";
	std::cout << "If you can't see anything, try using a torch.\n";
	std::cout << "Eat food items to restore your health.\n";
	std::cout << "If you encounter an enemy, it is a good idea to defeat it before anything else.\n";
}

void Game::look()
{

}

void Game::move(char _direction)
{

}

void Game::use(std::string _itemName)
{

}

void Game::fight()
{

}

void Game::collect()
{

}
void Game::viewInventory()
{

}
void Game::restart()
{
	std::cout << "Restarting game. Your score was: " << playerScore << "\n";
	returning = 2;
}
void Game::quit()
{
	std::cout << "Exiting game. Your score was: " << playerScore << "\n";
	returning = 1;
}

void Game::health(int _change)
{
	playerHealth += _change; // change can be negative to reduce health
}
