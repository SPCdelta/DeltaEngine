#pragma once
#include <optional>
#include <vector>
#include <iostream>

template <typename T>
class StableIndexList
{
   private:
	std::vector<std::optional<T>>
		data;  // Store elements with optional to mark empty slots
	std::vector<size_t> freeList;  // Track indices of free slots

   public:
	// Add an item to the list and return its index
	size_t add(const T& item)
	{
		if (!freeList.empty())
		{
			// Reuse an index from the free list
			size_t index = freeList.back();
			freeList.pop_back();
			data[index] = item;
			return index;
		}
		else
		{
			// No free slots, append to the end of the vector
			data.emplace_back(item);
			return data.size() - 1;
		}
	}

	// Remove an item by index
	void remove(size_t index)
	{
		if (index < data.size() && data[index].has_value())
		{
			data[index].reset();		// Mark the slot as empty
			freeList.push_back(index);	// Add index to the free list
		}
		else
		{
			throw std::out_of_range("Invalid index or item already removed");
		}
	}

	// Get an item by index
	T& get(size_t index)
	{
		if (index < data.size() && data[index].has_value())
		{
			return *data[index];
		}
		else
		{
			throw std::out_of_range("Invalid index or item already removed");
		}
	}

	// Check if an index is valid
	bool isValid(size_t index) const
	{
		return index < data.size() && data[index].has_value();
	}

	// Get the size of the list (excluding free slots)
	size_t size() const { return data.size() - freeList.size(); }
};
