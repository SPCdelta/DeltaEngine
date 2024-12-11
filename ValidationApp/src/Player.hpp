#pragma once

#include "Inventory/Inventory.hpp"
#include "Items/Item.hpp"

class Player
{
   public:
	Player(int shield = 25, float damage = 10, float speed = 10, int health = 95) : _shield{shield}, _attackDamage{damage}, _speed{speed}, _health{health}, _coins{0} {}

	void SetShield(int shield);
	void SetAttackDamage(float damage);
	void SetSpeed(float speed);
	void SetHealth(int health);

	void AddHealth(int health);

	int GetShield() const;
	float GetAttackDamage() const;
	float GetSpeed() const;
	int GetHealth() const;

	const int _maxHealth = 100;

	void AddItemToInventory(Item item, int amount);
	void RemoveItemFromInventory(std::string itemName, int amount);
	void ResetInventory();
	void PrintInventory();

	size_t GetInventorySize();
	InventoryItem* GetInventoryItem(int index);

	int GetCoins() const;
	void SetCoins(int coins);

   private:
	int _shield;
	float _attackDamage;
	float _speed;
	int _health;
	int _coins;

	Inventory _inventory;
};
