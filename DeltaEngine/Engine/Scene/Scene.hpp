#pragma once
#include <iostream>
#include <string>
#include "../Ecs/Registry.hpp"


class Scene {
public:
	Scene(std::string name);
	void Instantiate();
	void print();
	std::string getName() const;  

private:
	ecs::Registry registry;
	std::string name;
};