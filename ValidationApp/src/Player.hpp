#pragma once

#include "Inventory/Inventory.hpp"
#include "Items/Item.hpp"
#include <vector>
#include <functional>

class Player
{
   public:
	Player(int shield = 25, float damage = 10.0f, float speed = 10.0f, int health = 95) : _shield{shield}, _attackDamage{damage},
		_speed{speed}, _health{health}, _coins{0}, _inventory{std::make_unique<Inventory>()} {}

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

	void AddItemToInventory(const Item& item, int amount);
	void RemoveItemFromInventory(const Item& item, int amount);
	void ResetInventory();
	void PrintInventory();

	size_t GetInventorySize();
	InventoryItem* GetInventoryItem(size_t index);

	int GetCoins() const;
	void SetCoins(int coins);

	void AddHealthObserver(std::function<void(int)> observer) { _healthObservers.emplace_back(observer); }
	void AddShieldObserver(std::function<void(int)> observer) { _shieldObservers.emplace_back(observer); }
	void AddCoinObserver(std::function<void(int)> observer) { _coinObservers.emplace_back(observer); }
	void AddInventoryObserver(std::function<void(const Item& item, int amount)> observer) { _inventoryObservers.emplace_back(observer); }
   private:
	void NotifyHealthChanged();
	void NotifyCoinsChanged(int coins);
	void NotifyShieldChanged();
	void NotifyInventoryChanged(const Item& item, int amount);
	int _shield;
	float _attackDamage;
	float _speed;
	int _health;
	int _coins;

	std::vector<std::function<void(int)>> _healthObservers;
	std::vector<std::function<void(int)>> _shieldObservers;
	std::vector<std::function<void(int)>> _coinObservers;
	std::vector<std::function<void(const Item& item, int amount)>> _inventoryObservers;
	std::unique_ptr<Inventory> _inventory;
};
