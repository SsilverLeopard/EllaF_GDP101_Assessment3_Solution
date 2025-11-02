#include "Game.h"
#include <algorithm>
#include <iostream>
#include <cctype> // for ::tolower
#include <utility> // for std::move

int const static NUM_COMMANDS = 10;
std::string const static COMMANDS[NUM_COMMANDS] = { "help", "look", "move", "use", "fight", "collect", "inventory", "restart", "quit", "debug" };

void Game::setup(unsigned int _startX, unsigned int _startY, RoomGrid&& _allRooms)
{
	// take ownership of the provided grid
	allRooms = std::move(_allRooms);
	// fill in the grid
	this->createRooms();
	// set the player's starting position
	playerX = _startX;
	playerY = _startY;

	// set non-owning currentRoom pointer
	currentRoom = allRooms[playerY][playerX].get();

	// debug display of all rooms
	/*for (int i = 0; i < DIMENSION; ++i)
	{
		for (int j = 0; j < DIMENSION; ++j)
		{
			if (allRooms[i][j])
			{
				allRooms[i][j]->DebugDisplay();
			}
		}
	}
	// debug display of current room
	std::cout << "current room\n";
	currentRoom->DebugDisplay();*/
	// clear inventory
	for (unsigned int i = 0; i < INVENTORY_SIZE; i++)
	{
		inventory[i] = nullptr;
	}

	
}

void Game::setup(unsigned int _startX, unsigned int _startY, RoomGrid&& _allRooms,
	unsigned int _playerHealth, unsigned int _playerScore)
{
	this->setup(_startX, _startY, std::move(_allRooms));
	playerHealth = _playerHealth;
	playerScore = _playerScore;
}

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
	// set up items - not used in game, but for reference
	Item		candle("candle", 
				"This is slightly more useful than the other candle. You can wave it round a bit and it doesn't go out, because it's battery operated. Yay.", false);
	ItemFood	kfc("chicken bucket", 
				"One of those KFC bucket hats, but it's upside down and filled with Finger-Licking-Good delicious chicken.", 8, true);
	ItemFood	apples("red apple", 
				"A laundry basket, devoid of laundry, with a giant shiny red apple in the bottom.", 4, true);
	ItemWeapon	dagger("dagger", 
				"An adorable dagger, looks like it will tickle enemies to death.", false, 2);
	Item		key("key", 
				"A rusty key, but don't let that stop you trying it in a lock - rusty or otherwise.", false);
	ItemWeapon	broadsword("broadsword", 
				"Sarkis the broadsword is not just a weapon, it's an enemy-shredding machine. Don't drop it on your foot.", false, 4);

	// set up rooms
	allRooms[0][0] = std::make_unique <RoomTreasure>("The floor appears to be shiny.", 
		"You have walked into a full-on hoard. Pity you don't have more pockets. Just stuff them full.", 
		"It's too dark to see anything, but the floor... clinks?", true, 
		"Gringott's gots nothing on this. Gold and more gold.", 10);
	allRooms[0][1] = std::make_unique <RoomEnemy>("Ugh, more dead adventurers.", 
		"Ok not all of them are dead. Or adventurers. Maybe now is the time to bring out a weapon if you have one.", 
		"", false, 
		"Thatsa Leopard", 4, 4, 3);
	allRooms[0][2] = std::make_unique <RoomExit>("You can hear music faintly.", 
		"The room illuminates as you walk in, and you can hear \"Never Gonna Give You Up\". There's a ladder leading out of the dungeon. But it's behind a locked gate. You're trapped here with Rick Astley unless you have a key.", 
		"", false);
	allRooms[0][3] = std::make_unique <Room>("A liminal space.", 
		"Now you got that candle you realise it wasn't worth it. This room is empty apart from the bones of dead adventurers, one of which seems to be a leopard.",
		"Your eyes seem to not be working.", true);
	allRooms[1][0] = std::make_unique <RoomTreasure>("Something squeaks and runs away from you.",
		"That was a rodent of unusual size! Bet you didn't think they existed.",
		"", false,
		"Rodent gold. Smells like cheese, but isn't.", 1);
	allRooms[1][1] = std::make_unique <RoomItem>("There is a flickering light in this room.",
		"The light from a battery operated candle illuminates a sign on the wall saying \"beware of the leopard.\"", 
		"", false,
		"candle", "This is slightly more useful than the other candle. You can wave it round a bit and it doesn't go out, because it's battery operated. Yay.", false);
	allRooms[1][2] = std::make_unique <RoomItem>("This room smells, but not in a bad way.",
		"There's a hint of grease, salt, and stickiness in the air. You see, faintly glowing, a red and white striped bucket on the floor. The smell seems to be coming from the bucket.",
		"", false,
		"chicken bucket", "One of those KFC bucket hats, but it's upside down and filled with Finger-Licking-Good delicious chicken.", 8, true, 'f');
	allRooms[1][3] = std::make_unique <RoomTreasure>("As you walk in, you trip over a box.",
		"Lucky you didn't hurt yourself on that box, but you did break it open.",
		"You're going to need more light to see anything.", true,
		"Shiny shiny gems, helpfully in stashable pouches.", 5);
	allRooms[2][0] = std::make_unique <RoomItem>("This room smells like summer.",
		"Are you one of those people who likes the smell of clean laundry? There's a laundry basket in front of you. Unluckily, it doesn't appear to have clean laundry in it.",
		"", false,
		"red apple", "A laundry basket, devoid of laundry, with a giant shiny red apple in the bottom.", 4, true, 'f');
	allRooms[2][1] = std::make_unique <RoomItem>("There's a faint glint on the floor.",
		"As you step to the glint, you suddenly clutch your foot in pain. Did you stub your toe? No, you stabbed it on a teeny dagger.",
		"", false,
		"dagger", "An adorable dagger, looks like it will tickle enemies to death.", false, 2);
	allRooms[2][2] = std::make_unique <Room>("You landed with quite a thud. What happened?",
		"Ok this is not encouraging. This room has almost nothing in it apart from the hole you fell in from and a poster of a kitten saying \"Hang in there\" and a lit candle.",
		"", false);
	allRooms[2][3] = std::make_unique <Room>("A utilitarian space.",
		"This room couldn't even be called a broom closet because there are not even any brooms.",
		"", false);
	allRooms[3][0] = std::make_unique <RoomItem>("There is something in this room.",
		"You see a pile of garbage in the corner. Might be worth getting stinky to see what's in it.",
		"You're going to need more light to see anything.", true,
		"key", "A rusty key, but don't let that stop you trying it in a lock - rusty or otherwise.", false);
	allRooms[3][1] = std::make_unique <RoomEnemy>("There's bones in here.",
		"Is that an animated skeleton?",
		"", false,
		"Lesser Bonewalker", 2, 1, 1);
	allRooms[3][2] = std::make_unique <RoomEnemy>("This room smells really bad.",
		"Did something die in here? You better be careful, because that might be you next.",
		"You can't see anything, but you can smell something bad.",true,
		"Hungry Brainchomper", 4, 2, 5);
	allRooms[3][3] = std::make_unique <RoomItem>("You see some hooks on the wall.",
		"There is a stand for a large sword on the wall.",
		"", false, "broadsword",
		"Sarkis the broadsword is not just a weapon, it's an enemy-shredding machine. Don't drop it on your foot.", false, 4);

	// set up their exits
	allRooms[0][0]->setExits(false, true,  true,  false);
	allRooms[0][1]->setExits(false, false, false, true);
	allRooms[0][2]->setExits(false, false, true,  false);
	allRooms[0][3]->setExits(false, false, true,  false);
	allRooms[1][0]->setExits(true,  true,  true,  false);
	allRooms[1][1]->setExits(false, true,  false, true);
	allRooms[1][2]->setExits(true,  true,  false, true);
	allRooms[1][3]->setExits(true,  false, true,  true);
	allRooms[2][0]->setExits(true,  false, false, false);
	allRooms[2][1]->setExits(false, true,  true,  false);
	allRooms[2][2]->setExits(false, true,  false, true);
	allRooms[2][3]->setExits(true,  false, true,  true);
	allRooms[3][0]->setExits(false, true,  false, false);
	allRooms[3][1]->setExits(true,  false, false, true);
	allRooms[3][2]->setExits(false, true,  false, false);
	allRooms[3][3]->setExits(true,  false, false, true);
}

void Game::command()
{
	std::cout << "What do you do? ";
	std::string input;
	getline(std::cin, input);
	std::transform(input.begin(), input.end(), input.begin(), ::tolower); // convert to lowercase for easier parsing
	int fails = 0;
	hurt = false; // reset player hurt flag
	for (int i = 0; i < NUM_COMMANDS; i++)
	{
		if (input.find(COMMANDS[i]) != std::string::npos)
		{
			std::string command = input.substr(input.find(COMMANDS[i]), COMMANDS[i].length());
			//std::cout << "Command recognised: " << command << "\n";
			if (command == "help")
			{
				this->help();
			}
			else if (command == "look")
			{
				hurt = true; // looking while there is an enemy hurts player
				this->look();
			}
			else if (input.find("move") != std::string::npos)
			{
				if (input.find("north") != std::string::npos || input.find(" n") != std::string::npos)
				{
					this->move('n');
				}
				else if (input.find("east") != std::string::npos || input.find(" e") != std::string::npos)
				{
					this->move('e');
				}
				else if (input.find("south") != std::string::npos || input.find(" s") != std::string::npos)
				{
					this->move('s');
				}
				else if (input.find("west") != std::string::npos || input.find(" w") != std::string::npos)
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
				hurt = true; // using an item while there is an enemy hurts player
				std::string itemName = input.substr(input.find("use") + 3); // get everything after "use"
				this->use(itemName);
			}
			else if (command == "fight")
			{
				this->fight();
			}
			else if (command == "collect")
			{
				hurt = true; // trying to collect while there is an enemy hurts player
				this->collect();
			}
			else if (command == "inventory")
			{
				hurt = true; // checking inventory while there is an enemy hurts player
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
			else if (command == "debug") // secret command to debug display current room
			{
				this->currentRoom->DebugDisplay();
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
	if (hurt)
	{
		if (RoomEnemy* enemyRoom = dynamic_cast<RoomEnemy*>(currentRoom))
		{
			if (enemyRoom->isEnemyAlive())
			{
				std::cout << "A " << enemyRoom->getEnemyName() << " attacks you while you are distracted!\n";
				this->health(-(int)enemyRoom->getEnemyDamage());
				std::cout << "You lose " << enemyRoom->getEnemyDamage() << " health.\nCurrent health: " << playerHealth << "\n";
			}
		}
	}
}

void Game::limitedCommand()
{
	std::cout << "You may restart the game or quit. What do you do? ";
	std::string input;
	getline(std::cin, input);
	std::transform(input.begin(), input.end(), input.begin(), ::tolower); // convert to lowercase for easier parsing
	if (input.find("restart") != std::string::npos)
	{
		this->restart();
	}
	else if (input.find("quit") != std::string::npos)
	{
		this->quit();
	}
	else
	{
		std::cout << "Command not recognised. Quitting game.\n";
		this->quit();
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
	std::cout << " * If you can't see anything, try using a candle.\n";
	std::cout << " * Eat food items to restore your health.\n";
	std::cout << " * If you encounter an enemy, it is a good idea to defeat it before anything else.\n";
}

void Game::look()
{
	if (currentRoom->getDark())
	{
		std::cout << currentRoom->getDarkDesc() << "\n";
	}
	else
	{
		// hopefully the current room always exists, otherwise something has gone very wrong
		if (currentRoom != nullptr)
		{
			currentRoom->LongDisplay(); // polymorphed function that displays all room information depending on room type.
		}
	}
}

void Game::move(char _direction)
{
	if (_direction == 'n')
	{
		if (!currentRoom->getExitNorth())
		{
			std::cout << "You walk into a wall to the north. You can't go that way.\n";
		}
		else
		{
			std::cout << "You walk to the north.\n";
			playerY -= 1;
			currentRoom = allRooms[playerY][playerX].get();
			currentRoom->EnterDisplay();
		}
	}
	else if (_direction == 'e')
	{
		if (!currentRoom->getExitEast())
		{
			std::cout << "You walk into a wall to the east. You can't go that way.\n";
		}
		else
		{
			std::cout << "You walk to the east.\n";
			playerX += 1;
			currentRoom = allRooms[playerY][playerX].get();
			currentRoom->EnterDisplay();
		}
	}
	else if (_direction == 's')
	{
		if (!currentRoom->getExitSouth())
		{
			std::cout << "You walk into a wall to the south. You can't go that way.\n";
		}
		else
		{
			std::cout << "You walk to the south.\n";
			playerY += 1;
			currentRoom = allRooms[playerY][playerX].get();
			currentRoom->EnterDisplay();
		}
	}
	else if (_direction == 'w')
	{
		if (!currentRoom->getExitWest())
		{
			std::cout << "You walk into a wall to the west. You can't go that way.\n";
		}
		else
		{
			std::cout << "You walk to the west.\n";
			playerX -= 1;
			currentRoom = allRooms[playerY][playerX].get();
			currentRoom->EnterDisplay();
		}
	}
}

void Game::use(std::string _itemName)
{
	// check if there is an item name provided, this isn't just to stop people using nothing, but also without it, the loop would return the first empty inventory slot
	if (_itemName.empty())
	{
		std::cout << "Please specify an item to use.";
		return;
	}
	int fails = 0;
	bool found = false;
	for (auto& itemPtr : inventory)
	{
		if (itemPtr == nullptr)
		{
			fails++;
			continue; // skip empty inventory slots
		}
		if (_itemName.find(itemPtr->getItemName()) != std::string::npos)
		{
			found = true;
			// Use dynamic_cast to determine the actual derived type of the item
			if (ItemWeapon* weapon = dynamic_cast<ItemWeapon*>(itemPtr.get())) {
				ItemWeapon useItem = (*weapon);
				std::cout << "You swing your " << useItem.getItemName() << " around. The air takes no damage.";
			}
			else if (ItemFood* food = dynamic_cast<ItemFood*>(itemPtr.get())) {
				ItemFood useItem = *food;
				std::cout << "You eat the " << useItem.getItemName() << ".\n";
				this->health((int)useItem.getHealAmount());
				std::cout << "You gain " << useItem.getHealAmount() << " health.\nCurrent health: " << playerHealth << "";
				if (useItem.isConsumable())
				{
					itemPtr = nullptr; // remove item from inventory
				}
			}
			else 
			{ 
				Item useItem = (*itemPtr);
				if (useItem.getItemName() == "candle")
				{
					std::cout << "You wave the candle around, illuminating the room.\n";
					if (currentRoom->getDark())
					{
						currentRoom->setDark(false);
						std::cout << "The room is no longer dark.\n" << currentRoom->getShortDesc();
					}
					else
					{
						std::cout << "The room was already lit. Why did you do that?";
					}
				}
				else if (useItem.getItemName() == "key")
				{
					// Use dynamic_cast to determine if this is the exit
					if (RoomExit* room = dynamic_cast<RoomExit*>(currentRoom))
					{
						std::cout << "You unlock the gate.";
						returning = 2; // tell the game we won
					}
					else
					{
						std::cout << "There is nothing to unlock here.";
					}
				}
			}
			break; // item was used, so stop looking
		}
	}
	if (!found)
	{
		std::cout << "You don't have a \"" << std::string(_itemName, 1, std::string::npos) << "\". ";
	}
	if (fails == inventory.size())
	{
		std::cout << "In fact, you don't have anything. Maybe you should look for some items before trying to use them, hey?";
	}
	std::cout << std::endl;
}

void Game::fight()
{
	ItemWeapon weapons[2] = {}; // I know there are exactly 2 weapons in the game because I wrote them, so this is safe, if bad practice.
	unsigned int slot = 0;
	unsigned int attackDamage = 1;
	std::string weaponName = "fists";
	RoomEnemy* currentEnemyRoom = dynamic_cast<RoomEnemy*>(currentRoom);
	if (currentEnemyRoom)
	{
		for (auto& itemPtr : inventory)
		{
			// Use dynamic_cast to determine the actual derived type of the item
			if (ItemWeapon* weapon = dynamic_cast<ItemWeapon*>(itemPtr.get())) 
			{
				weapons[slot] = *weapon;
				slot++;
			}
		}
		// find highest damage weapon
		for (ItemWeapon weapon : weapons)
		{
			if (weapon.getDamageAmount() > attackDamage)
			{
				attackDamage = weapon.getDamageAmount();
				weaponName = weapon.getItemName();
			}
		}
		std::cout << "You attack the " << currentEnemyRoom->getEnemyName() << " using your " << weaponName << " for " << attackDamage << " damage.\n";
		playerScore += currentEnemyRoom->damageEnemy(attackDamage);
		if (!currentEnemyRoom->isEnemyAlive())
		{
			std::cout << "You kill the " << currentEnemyRoom->getEnemyName() << ", and you collect " << currentEnemyRoom->getEnemyScore() << " gold from it!\n";
		}
	}
	else
	{
		std::cout << "You attack the air. It takes no damage.\n";
	}
}

void Game::collect()
{
	if (!currentRoom->getDark())
	{
		// use dynamic cast to determine if current room is a treasure or item room
		if (RoomItem* type = dynamic_cast<RoomItem*>(currentRoom))
		{
			if (type->getItem() != nullptr)
			{
				std::cout << "You get a " << type->getItem()->getItemName() << ".\n";
				for (auto& itemPtr : inventory)
				{
					// find first empty inventory slot
					if (itemPtr == nullptr)
					{
						std::unique_ptr<Item> newItem = type->collectItem();
						if (newItem != nullptr)
						{
							itemPtr = std::move(newItem);
						}
						break;
					}
				}
			}
			else
			{
				std::cout << "There was an item here, but it is gone.\n";
			}
		}
		else if (RoomTreasure* type = dynamic_cast<RoomTreasure*>(currentRoom)) {
			if (type->isCollected())
			{
				std::cout << "There was treasure in this room, but it is gone.\n";
			}
			else
			{
				std::cout << type->getTreasureDesc() << '\n';
				std::cout << "You gain " << type->getTreasureScore() << " gold.\n";
				playerScore += type->getTreasureScore();
				type->setCollected(true);
			}
		}
		else
		{
			std::cout << "There is nothing here to collect.\n";
		}
	}
	else
	{
		std::cout << "You feel around in the dark, but you can't find anything to collect it.\n";
	}
}
void Game::viewInventory()
{
	std::cout << "==Player Inventory==\n";
	for (const auto& itemPtr : inventory)
	{
		if (itemPtr)
		{
			itemPtr->Display();
		}
	}
	std::cout << "==Player Stats==\n";
	std::cout << "Player health: " << playerHealth << "\n";
	std::cout << "Player gold: " << playerScore << "\n";
}
void Game::restart()
{
	std::cout << "Restarting game. Final player state: \n";
	this->viewInventory();
	this->setup(2, 2, std::move(allRooms), 6, 0);
	std::cout << "You fall down a trapdoor into a dungeon. Hopefully you can get out quickly, and maybe find something shiny while you're down here.\n";
	this->getCurrentRoom()->EnterDisplay();
	returning = 0;
}
void Game::quit()
{
	std::cout << "Exiting game. Final player state: \n";
	this->viewInventory();
	returning = 1;
}

void Game::health(int _change)
{
	playerHealth += _change; // change can be negative to reduce health
}
