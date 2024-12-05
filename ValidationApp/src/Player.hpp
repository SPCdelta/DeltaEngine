#pragma once

#include "Inventory/Inventory.hpp"
#include "Items/Item.hpp"

class Player
{
   public:
	Player(int shield = 25, int damage = 10, int speed = 10, int health = 95) : _shield{shield}, _attackDamage{damage}, _speed{speed}, _health{health}, _coins{0} {}

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
	void ResetInventory();
	void PrintInventory();

	int GetInventorySize();
	InventoryItem* GetInventoryItem(int index);

	int GetCoins() const;
	void AddCoins(int amount);
	void RemoveCoins(int amount);
	void SetCoins(int coins);

   private:
	int _shield;
	int _attackDamage;
	int _speed;
	int _health;
	int _coins;

	Inventory _inventory;
};
