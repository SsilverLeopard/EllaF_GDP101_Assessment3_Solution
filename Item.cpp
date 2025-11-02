#include "Item.h"

void Item::Display() const 
{ 
	std::cout << "==Basic Item==\n";
	std::cout << "Name: " << itemName << "\n";
	std::cout << "Description: " << itemDesc << "\n";
	std::cout << "Consumable: " << (consumable ? "yes" : "no") << "\n";
}

void ItemWeapon::Display() const
{ 
	std::cout << "==Weapon Item==\n";
	std::cout << "Name: " << itemName << "\n";
	std::cout << "Description: " << itemDesc << "\n";
	std::cout << "Consumable: " << (consumable ? "yes" : "no") << "\n";
	std::cout << "Damage Amount: " << damageAmount << "\n";
}

void ItemFood::Display() const
{
	std::cout << "==Food Item==\n";
	std::cout << "Name: " << itemName << "\n";
	std::cout << "Description: " << itemDesc << "\n";
	std::cout << "Consumable: " << (consumable ? "yes" : "no") << "\n";
	std::cout << "Heal Amount: " << healAmount << "\n";
}
