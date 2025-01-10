#include "JInputLifetime.hpp"
#include "InputManager.hpp"

JInputLifetime::~JInputLifetime()
{
	InputManager::RemoveJInput(_entry->_type, _entry->_key, _entry->_id);
}
