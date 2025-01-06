#pragma once

#include "Inventory/Inventory.hpp"
#include "Items/Item.hpp"
#include "Engine/Delta.hpp"
#include <functional>
#include <optional>

class Player
{
   public:
	Player(int shield = 25, float damage = 10, float speed = 10, int health = 95, Uint8 _inventoryIndex = 0)
		: _shield{shield}, _attackDamage{damage}, 
		_speed{speed}, _health{health}, _coins{0}, _inventoryIndex{0} {}

	void SetShield(int shield);
	void SetAttackDamage(float damage);
	void SetSpeed(float speed);
	void SetHealth(int health);

	void AddHealth(int health);
	void TakeDamage(int damage);

	int GetShield() const;
	float GetAttackDamage() const;
	float GetSpeed() const;
	int GetHealth() const;

	const int _maxHealth = 100;

	void AddItemToInventory(Item* item, Uint8 amount);
	void RemoveItemFromInventory(const Item& item, Uint8 amount);
	void ResetInventory();

	Uint8 GetInventorySize() const;
	const std::optional<InventoryItem>& GetInventoryItem(Uint8 index) const;
	std::optional<InventoryItem>& GetInventoryItem(Uint8 index);
	const std::optional<InventoryItem>& GetCurrentInventoryItem() const;

	int GetCoins() const;
	void SetCoins(int coins);

	void IncrementInventoryIndex();
	void DecrementInventoryIndex();
	void SetInventoryIndex(Uint8 index);
	Uint8 GetInventoryIndex() const;

	void AddHealthObserver(std::function<void(int)> observer) { _healthObservers.emplace_back(observer); }
	void AddShieldObserver(std::function<void(int)> observer) { _shieldObservers.emplace_back(observer); }
	void AddCoinObserver(std::function<void(int)> observer) { _coinObservers.emplace_back(observer); }
	void AddInventoryObserver(std::function<void(const Item& item, int amount)> observer) { _inventoryObservers.emplace_back(observer); }
	void AddInventoryIndexObserver(std::function<void(Uint8 index)> observer) { _inventoryIndexObservers.emplace_back(observer); }
   private:
	void NotifyHealthChanged();
	void NotifyCoinsChanged(int coins);
	void NotifyShieldChanged();
	void NotifyInventoryChanged(const Item& item, int amount);
	void NotifyInventoryIndexChanged();
	int _shield;
	float _attackDamage;
	float _speed;
	int _health;
	int _coins;
	Uint8 _inventoryIndex;

	std::vector<std::function<void(int)>> _healthObservers;
	std::vector<std::function<void(int)>> _shieldObservers;
	std::vector<std::function<void(int)>> _coinObservers;
	std::vector<std::function<void(Uint8 index)>> _inventoryIndexObservers;
	std::vector<std::function<void(const Item& item, int amount)>> _inventoryObservers;
	Inventory _inventory {};
};
