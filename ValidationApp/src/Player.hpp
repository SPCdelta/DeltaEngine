#pragma once

#include "Inventory/Inventory.hpp"
#include "Items/Item.hpp"
#include <vector>
#include <functional>

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
	void RemoveItemFromInventory(std::string itemName, int amount);
	void ResetInventory();
	void PrintInventory();

	int GetInventorySize();
	InventoryItem* GetInventoryItem(int index);

	int GetCoins() const;
	void SetCoins(int coins);

	void AddHealthObserver(std::function<void(int)> observer) { _healthObservers.emplace_back(observer); }
	void AddInventoryObserver(std::function<void(const Item& item, int amount)> observer) { _inventoryObservers.emplace_back(observer); }
   private:
	void NotifyHealthChanged();
	void NotifyInventoryChanged(const Item& item, int amount);
	int _shield;
	int _attackDamage;
	int _speed;
	int _health;
	int _coins;

	std::vector<std::function<void(int)>> _healthObservers;
	std::vector<std::function<void(const Item& item, int amount)>> _inventoryObservers;
	Inventory _inventory;
};
