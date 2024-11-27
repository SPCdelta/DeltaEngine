#pragma once

#include "Engine/Delta.hpp"

#include "../Scripts/WalkBehaviour.hpp"

class LayerScene : public Scene
{
   public:
	LayerScene(const std::string& sceneName) : Scene(sceneName)
	{
		// Create Player
		std::shared_ptr<GameObject> playerObject{Instantiate({{1.0f, 1.0f}, 0.0f, {1.0f, 1.0f}})};
		std::shared_ptr<SpriteSheet> sheet = std::make_shared<SpriteSheet>(playerObject->GetComponent<Transform>(), 4, 64, 64, 0, 0, 0, 2);
		sheet->AddIdleAnimation(4, 1, 200);
		playerObject->AddComponent<Sprite>("Assets\\Textures\\spritesheet3.png", sheet);

		playerObject->AddComponent<BoxCollider>();
		playerObject->AddComponent<Rigidbody>();

		playerObject->AddComponent<WalkBehaviour>();
		
		std::shared_ptr<GameObject> skeletonObject{Instantiate({{1.0f, 1.0f}, 0.0f, {1.0f, 1.0f}})};
		skeletonObject->AddComponent<Sprite>("Assets\\Textures\\spritesheet2.png");

		std::shared_ptr<GameObject> pokemonObject{Instantiate({{1.0f, 1.0f}, 0.0f, {1.0f, 1.0f}})};
		pokemonObject->AddComponent<Sprite>("Assets\\Textures\\spritesheet.png");

		// TODO
		/*pokemonObject->SetLayer(Layer::Background);
		skeletonObject->SetLayer(Layer::Default);
		playerObject->SetLayer(Layer::Foreground);*/	
	}
};
