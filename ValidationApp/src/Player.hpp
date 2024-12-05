#pragma once

#include "Inventory/Inventory.hpp"
#include "Items/Item.hpp"

class Player
{
   public:
	Player(int shield, int damage, int speed, int health)
		: _shield{shield}, _attackDamage{damage}, _speed{speed}, _health{health}
	{
	}

	void SetShield(int shield);
	void SetAttackDamage(int damage);
	void SetSpeed(int speed);
	void SetHealth(int health);

	void AddHealth(int health);

	int GetShield() const;
	int GetAttackDamage() const;
	int GetSpeed() const;
	int GetHealth() const;

	const int _maxHealth = 100;

	void AddItemToInventory(Item item, int amount);
	void RemoveItemFromInventory(Item item, int amount);

	int GetInventorySize();
	InventoryItem* GetInventoryItem(int index);

   private:
	int _shield;
	int _attackDamage;
	int _speed;
	int _health;

	Inventory _inventory;
};
