#include "Item.h"

// Game display function for items and their information
void Item::Display() const 
{ 
	std::cout << "==Basic Item==\n";
	std::cout << "Name: " << itemName << "\n";
	std::cout << "Description: " << itemDesc << "\n";
	std::cout << "Consumable: " << (consumable ? "yes" : "no") << "\n"; // use a ternary to print a word instead of booleans, which are 0 or 1
}
// polymorph to display weapon info
void ItemWeapon::Display() const
{ 
	std::cout << "==Weapon Item==\n";
	std::cout << "Name: " << itemName << "\n";
	std::cout << "Description: " << itemDesc << "\n";
	std::cout << "Consumable: " << (consumable ? "yes" : "no") << "\n";
	std::cout << "Damage Amount: " << damageAmount << "\n";
}
// polymorph to display food info
void ItemFood::Display() const
{
	std::cout << "==Food Item==\n";
	std::cout << "Name: " << itemName << "\n";
	std::cout << "Description: " << itemDesc << "\n";
	std::cout << "Consumable: " << (consumable ? "yes" : "no") << "\n";
	std::cout << "Heal Amount: " << healAmount << "\n";
}
