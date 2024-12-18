#pragma once

#include <memory>

template<typename T>
class IPrototype
{
public:
	virtual std::unique_ptr<T> Clone() const = 0;
	virtual ~IPrototype() = default;
};

