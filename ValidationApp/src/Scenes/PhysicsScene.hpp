#pragma once

#include "Engine/Delta.hpp"

#include "../Scripts/PhysicsBehaviour.hpp"

class PhysicsScene : public Scene
{
public:
	PhysicsScene(const std::string& name) 
		: Scene(name)
	{
		std::shared_ptr<GameObject> player{ Instantiate({{3.0f, 6.0f}, 0.0f, {1.0f, 1.0f}}) };
		player->AddComponent<Sprite>("Assets\\Textures\\player.png");
		player->AddComponent<BoxCollider>();
		player->AddComponent<Rigidbody>();
		player->AddComponent<PhysicsBehaviour>();

		std::shared_ptr<GameObject> floor1{ Instantiate({{3.0f, 3.0f}, 0.0f, {1.0f, 1.0f}}) };
		floor1->AddComponent<Sprite>("Assets\\Textures\\player.png");
		floor1->AddComponent<BoxCollider>()->SetTrigger(true);

		std::shared_ptr<GameObject> floor2{ Instantiate({{3.0f, 0.0f}, 0.0f, {1.0f, 1.0f}}) };
		floor2->AddComponent<Sprite>("Assets\\Textures\\player.png");
		floor2->AddComponent<BoxCollider>();

		Instantiate({{200.0f, 400.0f}, 0.0f, {100.0f, 150.0f}})->AddComponent<Image>("Assets\\Textures\\square.png")->SetColor({ 0, 0, 0, 255 });
	}
};