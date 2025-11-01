#include "Game.h"

int const static NUM_COMMANDS = 9;
std::string const static COMMANDS[NUM_COMMANDS] = { "help", "look", "move", "use", "fight", "collect", "inventory", "restart", "quit" };
std::string const static HURTING_COMMANDS[5] = { "look", "move", "use", "collect", "inventory" };

void Game::setup(unsigned int _startX, unsigned int _startY, RoomGrid&& _allRooms)
{
	// take ownership of the provided grid
	allRooms = std::move(_allRooms);
	// fill in the grid
	this->createRooms();

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

#pragma region Create Rooms
void Game::createRooms()
{
	// the handcrafted map
	/* Map:
	Legend: Entry, Treasure, Item, eXit, eNemy, Blank, Key, !dark, =door, -| not a path
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
	room 21 is a sword which you can use to fight. room 33 is a better sword. room 12 is a torch to see in dark rooms. room 30 is a key to exit the exit room at 03.*/
	// set up items - not used ingame, but for reference
	Item		candle("candle", 
				"This is slightly more useful than the other candle. You can wave it round a bit and it doesn't go out, because it's battery operated. Yay.", false);
	ItemFood	kfc("chicken bucket", 
				"One of those KFC bucket hats, but it's upside down and filled with Finger-Licking-Good delicious chicken.", 8, true);
	ItemFood	apples("apple basket", 
				"A laundry basket, devoid of laundry, with a giant shiny red apple in the bottom.", 4, true);
	ItemWeapon	dagger("dagger", 
				"An adorable dagger, looks like it will tickle enemies to death.", false, 2);
	Item		key("key", 
				"A rusty key, but don't let that stop you trying it in a lock - rusty or otherwise.", false);
	ItemWeapon	broadsword("broadsword", 
				"Sarkis the broadsword is not just a weapon, it's an enemy-shredding machine. Don't drop it on your foot.", false, 4);

	// set up rooms
	allRooms[0][0] = std::make_unique <RoomTreasure>("The floor appears to be shiny.", "You have walked into a full-on hoard. Pity you don't have more pockets. Just stuff them full.", "It's too dark to see anything, but the floor... clinks?", true, "Gringott's gots nothing on this. Gold and more gold.", 10);
	allRooms[0][1] = std::make_unique <RoomEnemy>("Ugh, more dead adventurers.", "Ok not all of them are dead. Or adventurers. Maybe now is the time to bring out a weapon if you have one.", "", false, true, "Thatsa Leopard", 4, 4, 3);
	allRooms[0][2] = std::make_unique <RoomExit>("You can hear music faintly.", "The room illuminates as you walk in, and you can hear \"Never Gonna Give you Up\". There's a ladder leading out of the dungeon. But it's behind a locked gate. You're trapped here with Rick Astley unless you have a key.", "", false);
	allRooms[0][3] = std::make_unique <Room>("A liminal space.", "Now you got that candle you realise it wasn't worth it. This room is empty apart from the bones of dead adventurers, one of which seems to be a leopard.", "Your eyes seem to not be working.", true);
	allRooms[1][0] = std::make_unique <RoomTreasure>("Something squeaks and runs away from you.", "That was a rodent of unusual size! Bet you didn't think they existed.", "", false, "Rodent gold. Smells like cheese, but isn't.", 1);
	allRooms[1][1] = std::make_unique <RoomItem>("There is a flickering light in this room.", "The light from a battery operated candle illuminates a sign on the wall saying \"beware of the leopard.\"", "", false, "candle", "This is slightly more useful than the other candle. You can wave it round a bit and it doesn't go out, because it's battery operated. Yay.", false);
	allRooms[1][2] = std::make_unique <RoomItem>("This room smells, but not in a bad way.", "There's a hint of grease, salt, and stickiness in the air. You see, faintly glowing, a red and white striped bucket on the floor. The smell seems to be coming from the bucket.", "", false, "KFC Bucket", "One of those KFC bucket hats, but it's upside down and filled with Finger-Licking-Good delicious chicken.", 8, true, 'f');
	allRooms[1][3] = std::make_unique <RoomTreasure>("As you walk in, you trip over a box.", "Lucky you didn't hurt yourself on that box, but you did break it open.", "You're going to need more light to see anything.", true, "Shiny shiny gems, helpfully in stashable pouches.", 5);
	allRooms[2][0] = std::make_unique <RoomItem>("This room smells like summer.", "Are you one of those people who likes the smell of clean laundry? There's a laundry basket in front of you. Unluckily, it doesn't appear to have clean laundry in it.", "", false, "apple basket", "A laundry basket, devoid of laundry, with a giant shiny red apple in the bottom.", 4, true, 'f');
	allRooms[2][1] = std::make_unique <RoomItem>("There's a faint glint on the floor.", "As you step to the glint, you suddenly clutch your foot in pain. Did you stub your toe? No, you stabbed it on a teeny dagger.", "", false, "dagger", "An adorable dagger, looks like it will tickle enemies to death.", false, 2);
	allRooms[2][2] = std::make_unique <Room>("You land with a thud. What happened?", "Ok this is not encouraging. This room has almost nothing in it apart from the hole you fell in from and a poster of a kitten saying \"Hang in there\" and a lit candle.");
	allRooms[2][3] = std::make_unique <Room>("A utilitarian space.", "This room couldn't even be called a broom closet because there are not even any brooms.");
	allRooms[3][0] = std::make_unique <RoomItem>("There is something in this room.", "You see a pile of garbage in the corner. Might be worth getting stinky to see what's in it.", "You're going to need more light to see anything.", true, "key", "A rusty key, but don't let that stop you trying it in a lock - rusty or otherwise.", false);
	allRooms[3][1] = std::make_unique <RoomEnemy>("There's bones in here.", "Is that an animated skeleton?", "", false, true, "Lesser Bonewalker", 2, 1, 1);
	allRooms[3][2] = std::make_unique <RoomEnemy>("This room smells really bad.", "Did something die in here? You better be careful, because that might be you next.", "You can't see anything, but you can smell something bad.", true, true, "Hungry Brainchomper", 4, 2, 5);
	allRooms[3][3] = std::make_unique <RoomItem>("You see some hooks on the wall.", "There is a stand for a large sword on the wall.", "", false, "broadsword", "Sarkis the broadsword is not just a weapon, it's an enemy-shredding machine. Don't drop it on your foot.", false, 4);

	// set up their exits
	allRooms[0][0]->setExits(nullptr, allRooms[0][1].get(), allRooms[1][0].get(), nullptr);
	allRooms[0][1]->setExits(nullptr, nullptr, nullptr, allRooms[0][0].get());
	allRooms[0][2]->setExits(nullptr, nullptr, allRooms[1][2].get(), nullptr);
	allRooms[0][3]->setExits(nullptr, nullptr, allRooms[1][3].get(), nullptr);
	allRooms[1][0]->setExits(allRooms[0][0].get(), allRooms[1][1].get(), allRooms[2][0].get(), nullptr);
	allRooms[1][1]->setExits(nullptr, allRooms[1][2].get(), nullptr, allRooms[1][0].get());
	allRooms[1][2]->setExits(allRooms[0][2].get(), allRooms[1][3].get(), nullptr, allRooms[1][1].get());
	allRooms[1][3]->setExits(allRooms[0][3].get(), nullptr, allRooms[2][3].get(), nullptr);
	allRooms[2][0]->setExits(allRooms[1][0].get(), nullptr, nullptr, nullptr);
	allRooms[2][1]->setExits(nullptr, allRooms[2][2].get(), allRooms[3][1].get(), nullptr);
	allRooms[2][2]->setExits(nullptr, allRooms[2][1].get(), nullptr, allRooms[2][3].get());
	allRooms[2][3]->setExits(allRooms[1][3].get(), nullptr, allRooms[3][3].get(), allRooms[2][2].get());
	allRooms[3][0]->setExits(nullptr, allRooms[3][1].get(), nullptr, nullptr);
	allRooms[3][1]->setExits(allRooms[2][1].get(), nullptr, nullptr, allRooms[3][0].get());
	allRooms[3][2]->setExits(nullptr, allRooms[3][3].get(), nullptr, nullptr);
	allRooms[3][3]->setExits(allRooms[2][3].get(), nullptr, nullptr, allRooms[3][2].get());

}
#pragma endregion

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
