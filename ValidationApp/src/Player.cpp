#include "Player.hpp"

void Player::SetShield(int shield)
{
	if (shield < 0)
		_shield = 0;
	else
		_shield = shield;

	NotifyShieldChanged();
}

void Player::SetAttackDamage(int damage) 
{
	if (damage < 0)
		_attackDamage = 0;
	else
		_attackDamage = damage;
}

void Player::SetSpeed(int speed) 
{
	if (speed < 0)
		_speed = 0;
	else
		_speed = speed;
}

void Player::SetHealth(int health) 
{
	if (health < 0)
		_health = 0;
	else
		_health = health;

	NotifyHealthChanged();
}

void Player::AddHealth(int health) 
{
	if (_health + health > _maxHealth)
		_health = _maxHealth;
	else
		_health += health;

	NotifyHealthChanged();
}

int Player::GetShield() const
{
	return _shield;
}

int Player::GetAttackDamage() const
{
	return _attackDamage;
}

int Player::GetSpeed() const
{
	return _speed;
}

int Player::GetHealth() const
{
	return _health;
}

void Player::AddItemToInventory(Item* item, int amount)
{
	_inventory.AddItem(item, amount);

	NotifyInventoryChanged(*item, amount);
}

void Player::RemoveItemFromInventory(const Item& item, int amount)
{
	_inventory.RemoveItem(item, amount);

	NotifyInventoryChanged(item, -amount);
}

int Player::GetInventorySize()
{
	return _inventory.GetItemAmount();
}

InventoryItem& Player::GetInventoryItem(int index)
{
	return _inventory.GetItem(index);
}

InventoryItem& Player::GetCurrentInventoryItem()
{
	return _inventory.GetItem(_inventoryIndex);
}

void Player::ResetInventory() // Empties the inventory
{
	_inventory.Clear();
}

int Player::GetCoins() const
{
	return _coins;
}

void Player::SetCoins(int coins)
{

	if (coins < 0)
		_coins = 0;
	else
		NotifyCoinsChanged(coins - _coins);
		_coins = coins;
}

void Player::IncrementInventoryIndex()
{
	++_inventoryIndex;
	NotifyInventoryIndexChanged();
}

void Player::DecrementInventoryIndex()
{
	--_inventoryIndex;
	NotifyInventoryIndexChanged();
}

void Player::SetInventoryIndex(Uint8 index)
{
	if (index < 0 || index > _inventory.GetCapacity()-1)
	{
		throw std::exception{"Index cannot be lower than 0 or higher than inventory capacity"};
	}
	_inventoryIndex = index;
	NotifyInventoryIndexChanged();
}

Uint8 Player::GetInventoryIndex() const
{
	return _inventoryIndex;
}


void Player::NotifyHealthChanged()
{
	for (const auto& observer : _healthObservers)
	{
		observer(_health);
	}
}

void Player::NotifyCoinsChanged(int coins)
{
	for (const auto& observer : _coinObservers)
	{
		observer(coins);
	}
}

void Player::NotifyShieldChanged()
{
	for (const auto& observer : _shieldObservers)
	{
		observer(_shield);
	}
}

void Player::NotifyInventoryChanged(const Item& item, int amount)
{
	for (const auto& observer : _inventoryObservers)
	{
		observer(item, amount);
	}
}

void Player::NotifyInventoryIndexChanged()
{
	for (const auto& observer : _inventoryIndexObservers)
	{
		observer(_inventoryIndex);
	}
}