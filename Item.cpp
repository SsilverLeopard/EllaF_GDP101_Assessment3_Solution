#include "Item.h"

#pragma region Base Item
void Item::DebugDisplay() const { std::cout << "base item\n"; }

#pragma endregion

#pragma region Weapon Item
void ItemWeapon::DebugDisplay() const { std::cout << "weapon item\n"; }

#pragma endregion

#pragma region Food Item
void ItemFood::DebugDisplay() const { std::cout << "food item\n"; }

#pragma endregion
