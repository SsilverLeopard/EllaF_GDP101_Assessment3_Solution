#pragma once
#include "Room.h" // room includes Item.h
#include <array>
#include <string>
#include <iostream>
#include <memory> // for unique_ptr
#include <algorithm>

class Game
{
private:
	unsigned short playerX;
	unsigned short playerY;
	unsigned int playerHealth;
	unsigned int playerScore;
	unsigned int returning = 0;
	static const unsigned int INVENTORY_SIZE = 6;
	static const unsigned int DIMENSION = 4;
	// type alias for 2D array of unique_ptrs to rooms
	using RoomGrid = std::array<std::array<std::unique_ptr<Room>, DIMENSION>, DIMENSION>;
	// non-owning pointer to the current room (owned in allRooms)
	Room* currentRoom = nullptr;
	// owning container of rooms
	RoomGrid allRooms;
	// stl array of unique_ptrs to items for inventory
	std::array<std::unique_ptr<Item>, INVENTORY_SIZE> inventory;

public:
	// Default constructor
	Game() : playerX(0), playerY(0), playerHealth(1), playerScore(0), currentRoom(nullptr) {} // unique_ptrs default to nullptr so don't need to initialize

	// setup function that moves the game grid and places the player
	void setup(unsigned int _startX, unsigned int _startY, RoomGrid&& _allRooms);
	// setup function that moves the game grid and places the player and sets their stats
	void setup(unsigned int _startX, unsigned int _startY, RoomGrid&& _allRooms,
		unsigned int playerHealth, unsigned int playerScore);

	// Interface functions
	unsigned short getPlayerX() const { return playerX; }
	unsigned short getPlayerY() const { return playerY; }
	unsigned int getPlayerHealth() const { return playerHealth; }
	unsigned int getPlayerScore() const { return playerHealth; }


	// command processing function
	void command();

	// Command functions
	void help();
	void look();
	void move(char _direction);
	void use(std::string _itemName);
	void fight();
	void collect();
	void viewInventory();
	void restart();
	void quit();

	// Game functions
	void health(int _change);


	// default destructor because unique_ptr cleans itself up
	~Game() = default;
};

