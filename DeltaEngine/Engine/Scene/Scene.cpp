#include "Scene.hpp"

Scene::Scene(std::string name) : name{name} 
{}

void Scene::Instantiate()
{
	// gameobjecten aanmaken
}

void Scene::print()
{
	std::cout << name << std::endl;
}

std::string Scene::getName() const {
	return name;
}


