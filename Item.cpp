#include "Item.h"

#pragma region Base Item
void Item::DebugDisplay() const 
{ 
	std::cout << "==Basic Item==\n";
	std::cout << "Name: " << itemName << "\n";
	std::cout << "Description: " << itemDesc << "\n";
	std::cout << "Consumable: " << (consumable ? "yes" : "no") << "\n";
}

#pragma endregion

#pragma region Weapon Item
void ItemWeapon::DebugDisplay() const
{ 
	std::cout << "==Weapon Item==\n";
	std::cout << "Name: " << itemName << "\n";
	std::cout << "Description: " << itemDesc << "\n";
	std::cout << "Consumable: " << (consumable ? "yes" : "no") << "\n";
	std::cout << "Damage Amount: " << damageAmount << "\n";
}

#pragma endregion

#pragma region Food Item
void ItemFood::DebugDisplay() const
{
	std::cout << "==Food Item==\n";
	std::cout << "Name: " << itemName << "\n";
	std::cout << "Description: " << itemDesc << "\n";
	std::cout << "Consumable: " << (consumable ? "yes" : "no") << "\n";
	std::cout << "Damage Amount: " << healAmount << "\n";
}

#pragma endregion
