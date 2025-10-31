/*Create a text adventure game where players navigate a maze of rooms stored in a 2D array.
* Use a custom class for each type of room, derived from a common Room class. Each type of room should output a custom message or obstacle for the player to overcome. 
* Your game map can be hand-crafted, or you may choose to use an algorithm to randomly allocate rooms in your 2D maze.
* Either way, your game does not need to be large (an 4x4 array is sufficient).
* The focus of this assessment is on your use of inheritance, and your ability to parse and process user input.
* For this assessment you must create a console application in C++ that includes the following features:
	* The ability to parse and process commands typed by the user 
	* For example, 'move east' will move the player to the next room east of their current location. 
	* Stores a 'maze' of rooms within a 2D array data structure 
	* Uses custom classes to define a hierarchy of room types. Each room type is to be derived from a common Room class 
	* Each type of room should output a custom message or obstacle for the player to overcome. 
* You are free to design all other aspects of the program.
* You will use version control throughout this assessment to maintain an archive of your work and to track changes. A commit log or screenshot showing the use of version control software is to be submitted with your project.*/

/* Map:
Key: Entry, Treasure, Food, eXit, eNemy, Blank, Key, =door, ~locked door, -| not a path
-----------------
| T = N | X | B |
| = |---| ~ | = |
| T = F = F = T |
| = |---|---| = |
| F | T = E = B |
|---| = |---| = |
| K = N | N = T |
-----------------
00 01 02 03
10 11 12 13
20 21 22 23
30 31 32 33
*/

/*
* room types: enemy, item, entrance, exit, blank
* 
* room properties: dark (need to use torch to see or move), trapped (need to look first or will take damage)
* commands: help, look (prints long description and valid directions), move (nesw), use (item name), fight, get, inventory, restart, exit
* player has hp and can use items from health rooms to heal
* player has score that increases when you get treasure or kill enemy
* start off with one healing item and a sword. some treasures are swords.
* classes: room, item, enemy
* 
* room things
* blank room class things:
	* enter message (display on entry)
	* long desc (display on look)
	* bool for dark and trapped
	* dark desc (display on entry or look when dark)
	* north, east, south, west: pointers to other rooms or null
* item room subclass things:
	* item class instance
	* item desc (display on look)
	* polymorph look so that it also describes the item if it is not collected
	* ability to collect the item
* enemy room subclass things:
	* enemy class instance (only one enemy per room)
	* polymorph look so it also describes the enemy if it is alive
* 
* enemy things
	* name string, desc string, health int, damage int, score int
	* attack function, get hurt function
* 
* item things
	* name string, desc string, consumable bool
	* print function used in inventory
	* use function -- key unlocks the door, torch makes a room not dark
* subclass for swords
	* damage int
	* overload collection to make it overwrite the previous sword
	* can't use sword like other items, or all it does is swing at the air
* subclass for food
	* health int
* 
* collect item system -- -- pointer? then set the pointer to null and add the pointer to the inventory? 
* movement system -- check if current room has anything in the given direction. the direction will be nullptr if it is a wall.
* use item system -- eat food to restore hp, use key to open door, use torch to make light. using something with consumable is true removes it from inv. all items are unique, can't have 3 bread because that's hard
* inventory system -- an array of item instances that can be displayed. displays them plus current score plus current health.
* player health system -- can take damage from fights, can heal using food. if you run out of health you lose
* combat system -- if you are in an enemy room and do something other than fight, you take damage. if you fight, you deal damage.
	* enter: (dark desc) the room is dark. you hear footsteps. use torch: you raise your torch. you can see now. the Bad Guy attacks you for 2 damage. fight: you hit the Bad Guy for 4 damage. look: (room desc). there are doors to the (directions). there is a Bad Guy. the Bad Guy attacks you for 2 damage. fight: you hit the Bad Guy for 4 damage. the Bad Guy dies. You get 6 gold.
* winning -- reach the exit room by using key on door
*/

// Kyle: A good way to show polymorphism would be to use dynamic cast that checks if the current room matches a type that suits the current action.

#include "main.h"

int main()
{
	std::cout << "Hello World!\n";
}

