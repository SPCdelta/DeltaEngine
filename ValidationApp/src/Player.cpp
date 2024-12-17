#include "Player.hpp"

void Player::SetShield(int shield)
{
	if (shield < 0)
		_shield = 0;
	else
		_shield = shield;

	NotifyShieldChanged();
}

void Player::SetAttackDamage(float damage)
{
	if (damage < 0.0f)
		_attackDamage = 0.0f;
	else
		_attackDamage = damage;
}

void Player::SetSpeed(float speed)
{
	if (speed < 0.0f)
		_speed = 0.0f;
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

float Player::GetAttackDamage() const
{
	return _attackDamage;
}

float Player::GetSpeed() const
{
	return _speed;
}

int Player::GetHealth() const
{
	return _health;
}

void Player::AddItemToInventory(const Item& item, int amount)
{
	_inventory->AddItem(item, amount);

	NotifyInventoryChanged(item, amount);
}

void Player::RemoveItemFromInventory(const Item& item, int amount)
{
	_inventory->RemoveItem(item, amount);

	NotifyInventoryChanged(item, -amount);
}

size_t Player::GetInventorySize()
{
	return _inventory->GetItemAmount();
}

InventoryItem* Player::GetInventoryItem(size_t index)
{
	return _inventory->GetItem(index).get();
}

void Player::ResetInventory() // Empties the inventory
{
	_inventory->Clear();
}

void Player::PrintInventory()
{
	_inventory->PrintInventory();
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
