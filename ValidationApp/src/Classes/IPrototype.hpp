#pragma once

template<typename T>
class IPrototype
{
public:
	virtual T* Clone() const = 0;
	virtual ~IPrototype() = default;
};

