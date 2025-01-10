#pragma once

#include <unordered_map>
#include <functional>
#include <vector>

#include "JInputLifetime.hpp"
#include "JInputEntry.hpp"

using JInputFunction = std::function<void(Input&)>;

class JInputRegistry
{
public:
	JInputLifetime* Add(Key input, const std::string& category, JInputFunction function)
	{
		return new JInputLifetime(&_keys[input].emplace_back(input, category, function));
	}
	JInputLifetime* Add(MouseButton input, const std::string& category, JInputFunction function)
	{
		return new JInputLifetime(&_mouseButtons[input].emplace_back(input, category, function));
	}

	void Remove(InputType type, int input, size_t id)
	{
		std::vector<JInputEntry>& entries = GetEntries(type, input);
		for (auto it = entries.begin(); it != entries.end(); ++it)
		{
			if (it->GetId() == id)
			{
				entries.erase(it);
				break;
			}
		}
	}

	void Execute(Key key, Input& e)
	{
		for (size_t i = 0; i < _keys[key].size(); i++)
		{
			_keys[key][i].Execute(e);
		}
	}

	void Execute(MouseButton mouseButton, Input& e)
	{
		for (size_t i = 0; i < _mouseButtons[mouseButton].size(); i++)
		{
			_mouseButtons[mouseButton][i].Execute(e);
		}
	}

private:
	std::unordered_map<Key, std::vector<JInputEntry>> _keys{};
	std::unordered_map<MouseButton, std::vector<JInputEntry>> _mouseButtons{};

	std::vector<JInputEntry>& GetEntries(InputType type, int input)
	{
		switch (type)
		{
			case InputType::KEYBOARD: return _keys[(Key)input];
			case InputType::MOUSEBUTTON: return _mouseButtons[(MouseButton)input];
			default: throw std::exception("InputType not supported!");
		}
	}
};