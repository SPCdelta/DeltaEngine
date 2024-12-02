#pragma once

#include "Engine/Delta.hpp"

class LayerScene : public Scene
{
   public:
	LayerScene(const std::string& sceneName) : Scene(sceneName)
	{
		// Create Player
		std::shared_ptr<GameObject> playerObject{Instantiate({{1.0f, 1.0f}, 0.0f, {3.0f, 3.0f}})};
		std::shared_ptr<AnimationSheet> sheet = std::make_shared<AnimationSheet>(playerObject->GetComponent<Transform>(), 4, 64, 64, 0, 0, 0, 2);
		sheet->AddIdleAnimation(4, 1, 200);
		playerObject->AddComponent<Sprite>("spritesheet3", sheet);

		playerObject->AddComponent<BoxCollider>();
		playerObject->AddComponent<Rigidbody>();

		playerObject->AddComponent<PlayerBehaviour>();
		
		std::shared_ptr<GameObject> skeletonObject{Instantiate({{1.0f, 1.0f}, 0.0f, {3.0f, 3.0f}})};
		skeletonObject->AddComponent<Sprite>("spritesheet2");

		std::shared_ptr<GameObject> pokemonObject{Instantiate({{1.0f, 1.0f}, 0.0f, {3.0f, 3.0f}})};
		pokemonObject->AddComponent<Sprite>("spritesheet");

		pokemonObject->SetLayer(Layer::Foreground);
		skeletonObject->SetLayer(Layer::Default);
		playerObject->SetLayer(Layer::Background);	
	}
};
