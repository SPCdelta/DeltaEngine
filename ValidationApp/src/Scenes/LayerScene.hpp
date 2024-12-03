#pragma once

#include "Engine/Delta.hpp"
#include "../Scripts/EnemyBehaviour.hpp"

class LayerScene : public Scene
{
   public:
	LayerScene(const std::string& sceneName) : Scene(sceneName)
	{
		// Create Player
		std::shared_ptr<GameObject> playerObject{Instantiate({{1.0f, 1.0f}, 0.0f, {3.0f, 3.0f}})};

		std::shared_ptr<AnimationSheet> sheet = std::make_shared<AnimationSheet>(playerObject->GetComponent<Transform>(), 9, 64, 64, 9, 11, 10, 12);

		//sheet->AddIdleAnimation(4, 1, 200); TODO

		sheet->AddCustomAnimation("attackUp", 8, 5, 60);
		sheet->AddCustomAnimation("attackDown", 8, 7, 60);
		sheet->AddCustomAnimation("attackLeft", 8, 6, 60);
		sheet->AddCustomAnimation("attackRight", 8, 8, 60);

		sheet->AddCustomAnimation("death", 6, 21, 150);	// TODO 100?

		playerObject->AddComponent<Sprite>("player", sheet);

		playerObject->AddComponent<BoxCollider>();
		playerObject->AddComponent<Rigidbody>();

		playerObject->AddComponent<PlayerBehaviour>();
		playerObject->AddComponent<Audio::SFXSource>();
				
		std::shared_ptr<GameObject> hurtfulObject{Instantiate({{10.0f, 10.0f}, 0.0f, {3.0f, 3.0f}})};
		hurtfulObject->AddComponent<Sprite>("spritesheet2");
		hurtfulObject->AddComponent<BoxCollider>()->SetTrigger(true);
		hurtfulObject->SetTag("ouch");

		std::shared_ptr<GameObject> pokemonObject{Instantiate({{10.0f, 1.0f}, 0.0f, {3.0f, 3.0f}})};
		pokemonObject->AddComponent<Sprite>("spritesheet");

		pokemonObject->AddComponent<BoxCollider>();
		pokemonObject->AddComponent<Rigidbody>();

		pokemonObject->AddComponent<EnemyBehaviour>();

		pokemonObject->SetLayer(Layer::Foreground);
		hurtfulObject->SetLayer(Layer::Default);
		playerObject->SetLayer(Layer::Background);	
	}
};
