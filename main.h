#pragma once

// ============= PLEASE NOTE =============
//  this header is just my planning.
//  there is a lot of comments but no code.

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
  N
W   E
  S
*/

/*
* room types: blank (base), enemy, item, exit, treasure
* don't need entrance room specifically because i can just hardcode the starting room indices
* room properties: dark (need to use torch to see or move)
* commands: help, look (prints long description and valid directions), move (nesw), use (item name), fight, get, inventory, restart, exit
* player has hp and can use items from health rooms to heal
* player has score that increases when you get treasure or kill enemy
* start off with nothing at all. room 21 is a sword which you can use to fight. room 33 is a better sword. room 12 is a torch to see in dark rooms. room 30 is a key to exit the exit room at 03.
* fighting with no sword you punch things for low damage, fighting with sword you deal more damage
*
* classes: room, item, enemy
*
* room things
* blank room class things:
	* enter message (display on entry)
	* long desc (display on look)
	* bool for dark
	* dark desc (display on entry or look when dark)
	* north, east, south, west: pointers to other rooms or null
* item room subclass things:
	* item class instance
	* item desc (display on look)
	* polymorph look so that it also describes the item if it is not collected -- bool for collected, or nullptr? shared or unique pointers might work?
	* ability to collect the item (get command)
* treasure room subclass things:
	* score int, bool collected, string treasure desc
	* ability to collect the treasure (get command)
	* polymorph look so that it also describes the treasure if it is not collected
* enemy room subclass things:
	* enemy class instance (only one enemy per room)
		* might be easier to build the enemy into the room instead
	* polymorph look so it also describes the enemy if it is alive
* exit room subclass things:
	* needs key to be used, if it is you win
	* desc shows there is an exit that is locked
*
* enemy things
	* name string, desc string, health int, damage int, score int
	* attack function, get hurt function
*
* item things
	* name string, desc string, consumable bool
	* display function used in inventory
	* use function -- key unlocks the door, torch makes a room not dark
* subclass for sword
	* damage int
	* polymorph display to show damage as well
	* polymorph use sword doesn't fight, just swings at the air or smth
* subclass for food
	* health int
	* polymorph display to show health as well
	* polymorph use to heal player
*
* collect item system -- pointer? then set the pointer to null and add the pointer to the inventory?
* movement system -- check if current room has anything in the given direction. the direction will be nullptr if it is a wall. update current room indices to new room, display appropriate entrance desc
* use item system -- eat food to restore hp, use key to open door, use torch to make light. using something with consumable is true removes it from inv. all items are unique, can't have 3 bread because that's hard
* inventory system -- an array of item instances that can be displayed. displays them plus current score plus current health.
* player health system -- can take damage from fights, can heal using food. if you run out of health you lose
* combat system -- if you are in an enemy room and do something other than fight, you take damage. if you fight, you deal damage.
	* example: move n: (dark desc) the room is dark. you hear footsteps. use torch: you raise your torch. you can see now. the Bad Guy attacks you for 2 damage. fight: you hit the Bad Guy for 4 damage. look: (room desc). there are doors to the (directions). there is a Bad Guy. the Bad Guy attacks you for 2 damage. fight: you hit the Bad Guy for 4 damage. the Bad Guy dies. You get 6 gold.
* winning -- reach the exit room by using key on door
*
* Player data: current room indices (2D array so x and y), pointer to current room, health int, score int, inventory array of item pointers -- could just use a static array that is big enough for all the items, since its pointers them being different types/classes doesn't matter... or maybe it does. that might be a problem
*
*/
