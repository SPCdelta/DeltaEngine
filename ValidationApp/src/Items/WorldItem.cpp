#include "WorldItem.hpp"

WorldItem::WorldItem(std::shared_ptr<Item> item, int amount) : _item{std::move(item)}, _amount{amount}
{
}
