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

void Player::AddItemToInventory(Item* item, Uint8 amount)
{
	_inventory.AddItem(item, amount);

	NotifyInventoryChanged(*item, amount);
}

void Player::RemoveItemFromInventory(const Item& item, Uint8 amount)
{
	_inventory.RemoveItem(item, amount);

	NotifyInventoryChanged(item, -amount);
}

Uint8 Player::GetInventorySize() const
{
	return _inventory.GetSize();
}

const std::optional<InventoryItem>& Player::GetInventoryItem(Uint8 index) const
{
	return _inventory.GetItem(index);
}

std::optional<InventoryItem>& Player::GetInventoryItem(Uint8 index)
{
	return _inventory.GetItem(index);
}

const std::optional<InventoryItem>& Player::GetCurrentInventoryItem() const
{
	return _inventory.GetItem(_inventoryIndex);
}

void Player::ResetInventory()
{
	for (Uint8 i = 0; i < _inventory.GetSize(); ++i)
	{
		auto& item = _inventory.GetItem(i);
		if (item.has_value())
		{
			NotifyInventoryChanged(*item->GetItem().get(), static_cast<int>(-item->GetAmount()));
		}
	}
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