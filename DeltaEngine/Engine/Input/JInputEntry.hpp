#pragma once

#include <functional>
#include <string>

#include "DeltaInputs.hpp"

using JInputFunction = std::function<void(Input&)>;

class JInputLifetime;

class JInputEntry
{
public:
	JInputEntry(Key key, const std::string& category, JInputFunction function)
		:  _id{ ID_GIVER++ }, _key{ (int)key }, _type{ InputType::KEYBOARD }, _category{ category }, _function{ function }
	{ 

	}

	JInputEntry(MouseButton key, const std::string& category, JInputFunction function)
		:  _id{ ID_GIVER++ }, _key{ (int)key }, _type{ InputType::MOUSEBUTTON }, _category{ category }, _function{ function }
	{ 

	}

	void Execute(Input& e) 
	{ 
		_function(e);
	}

	friend class JInputLifetime;

	const size_t GetId() const
	{ 
		return _id;
	}

private:
	static size_t ID_GIVER;

	int _key;
	InputType _type;
	std::string _category;
	JInputFunction _function;
	size_t _id;
};