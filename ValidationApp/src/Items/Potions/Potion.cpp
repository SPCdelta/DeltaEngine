#include "Potion.hpp"

Potion::Potion(float time, float value, const std::string& name, const std::string& spriteName) 
	: ConsumableItem{name, spriteName}, _time{time}, _value{value}
{
}
