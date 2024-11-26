#pragma once

#include "Engine/Delta.hpp"

#include "../Scripts/PhysicsBehaviour.hpp"

class PhysicsScene : public Scene
{
public:
	PhysicsScene(const std::string& name) 
		: Scene(name)
	{
		std::shared_ptr<GameObject> player{ Instantiate({{10.0f, 265.0f}, 0.0f, {64.0f, 64.0f}}) };
		player->AddComponent<Sprite>("Assets\\Textures\\spritesheet.png", nullptr);
		player->AddComponent<BoxCollider>();
		player->AddComponent<Rigidbody>();
		player->AddComponent<PhysicsBehaviour>();

		std::shared_ptr<GameObject> floor1{ Instantiate({{10.0f, 196.0f}, 0.0f, {64.0f, 64.0f}}) };
		floor1->AddComponent<Sprite>("Assets\\Textures\\spritesheet.png", nullptr);
		floor1->AddComponent<BoxCollider>()->SetTrigger(true);

		std::shared_ptr<GameObject> floor2{ Instantiate({{10.0f, 0.0f}, 0.0f, {64.0f, 64.0f}}) };
		floor2->AddComponent<Sprite>("Assets\\Textures\\spritesheet.png", nullptr);
		floor2->AddComponent<BoxCollider>();
	}
};