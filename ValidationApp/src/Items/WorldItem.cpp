#include "WorldItem.hpp"

WorldItem::WorldItem(Item* item, int amount) 
    : _item{item}, 
      _amount{amount}
{

}

WorldItem::WorldItem(const WorldItem& other)
    : _amount(other._amount), 
      _item(other._item->Clone())
{

}

WorldItem& WorldItem::operator=(const WorldItem& other)
{
    if (this != &other)
    {
        _amount = other._amount;
        _item = std::unique_ptr<Item>(other._item->Clone());
    }
    return *this;
}

WorldItem::WorldItem(WorldItem&& other) noexcept
    : _amount(other._amount), 
      _item(std::move(other._item))
{
    other._amount = 0;
}

WorldItem& WorldItem::operator=(WorldItem&& other) noexcept
{
    if (this != &other)
    {
        _amount = other._amount;
        _item = std::move(other._item);

        other._amount = 0;
    }
    return *this;
}