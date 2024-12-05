#pragma once

#include "Engine/Delta.hpp"
#include "../Scripts/EnemyBehaviour.hpp"
#include "../Classes/WorldItemBehaviour.hpp"

class LayerScene : public Scene
{
   public:
	LayerScene(const std::string& sceneName) : Scene(sceneName)
	{
		// Create Player
		std::shared_ptr<GameObject> playerObject{Instantiate({{1.0f, 1.0f}, 0.0f, {3.0f, 3.0f}})};

		std::shared_ptr<AnimationSheet> sheet = std::make_shared<AnimationSheet>(playerObject->GetComponent<Transform>(), 9, 64, 64, 9, 11, 10, 12);

		sheet->AddCustomAnimation("attackUp", 8, 5, 60);
		sheet->AddCustomAnimation("attackDown", 8, 7, 60);
		sheet->AddCustomAnimation("attackLeft", 8, 6, 60);
		sheet->AddCustomAnimation("attackRight", 8, 8, 60);

		sheet->AddCustomAnimation("death", 6, 21, 150);

		playerObject->AddComponent<Sprite>("layerPlayer", sheet)->SetLayer(Layer::Player);	

		playerObject->AddComponent<BoxCollider>();
		playerObject->AddComponent<Rigidbody>();

		playerObject->AddComponent<Audio::SFXSource>();
		playerObject->AddComponent<PlayerBehaviour>();
					
		// Create object that hurts player when player touches it
		std::shared_ptr<GameObject> hurtfulObject{Instantiate({{10.0f, 10.0f}, 0.0f, {3.0f, 3.0f}})};
		hurtfulObject->AddComponent<Sprite>("spritesheet2");
		hurtfulObject->AddComponent<BoxCollider>()->SetTrigger(true);
		hurtfulObject->SetTag("enemy");

		// Create object that gets hurt when a weapon touches it
		std::shared_ptr<GameObject> pokemonObject{Instantiate({{10.0f, 1.0f}, 0.0f, {3.0f, 3.0f}})};
		pokemonObject->AddComponent<Sprite>("spritesheet");

		pokemonObject->AddComponent<BoxCollider>();
		pokemonObject->AddComponent<Rigidbody>();

		pokemonObject->AddComponent<EnemyBehaviour>();

		// TODO Create potion object to pick up
		/*std::shared_ptr<GameObject> cyanPotionObj{Instantiate({{1.0f, 10.0f}, 0.0f, {1.0f, 1.0f}})};
		cyanPotionObj->AddComponent<Sprite>("cyanPotion");
		cyanPotionObj->AddComponent<BoxCollider>()->SetTrigger(true);
		cyanPotionObj->AddComponent<WorldItemBehaviour>();
		cyanPotionObj->SetTag("item");*/
	}
};
