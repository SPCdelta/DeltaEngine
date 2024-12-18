#pragma once

#include <Engine/Delta.hpp>

#include "../Scripts/Level/EntitySpawner.hpp"

class SpawnerScene : public Scene
{
public:
	SpawnerScene(const std::string& name)
		: Scene(name)
	{
		std::shared_ptr<GameObject> spawnerObj = Instantiate({{1.0f, 1.0f}, 0.0f, {1.0f, 1.0f}});
		Sprite* sprite = spawnerObj->AddComponent<Sprite>("player");
		sprite->SetLayer(Layer::Foreground);
		sprite->SetColor({ 0, 255, 0 });
		spawnerObj->AddComponent<EntitySpawner>(
			EntitySpawnerData
			{
				// Spawn interval
				0.1f,
				0.2f,

				// Spawn amount | OnStart
				2, 3, true,

				// Spawn Radius
				2.5f
			},
			[this](std::shared_ptr<GameObject>& entity)
			{ 
				entity->AddComponent<Sprite>("player")->SetLayer(Layer::Projectiles);
				// TODO: add extra components...
			}
		);
	}
};