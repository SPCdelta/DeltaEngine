#pragma once

#include "Engine/Delta.hpp"
#include "../Scripts/EnemyBehaviour.hpp"
#include "../Views/Components/HealthComponent.hpp"
#include "../Items/Potions/HealingPotion.hpp"
#include <memory>
#include "../Views/Components/HotbarComponent.hpp"

class LayerScene : public Scene
{
   public:
	LayerScene(const std::string& sceneName) : Scene(sceneName)
	{
		// Create Player
		std::shared_ptr<GameObject> playerObject{Instantiate({{1.0f, 1.0f}, 0.0f, {3.0f, 3.0f}})};

		std::shared_ptr<AnimationSheet> sheet = std::make_shared<AnimationSheet>(playerObject->GetComponent<Transform>(), 9, 64, 64, 9, 11, 10, 12);

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

		// Create potion object to pick up
		WorldItem worldItem = WorldItem(HealingPotion(10, 10, "healingpotion", "cyanPotion"), 1);
		std::shared_ptr<GameObject> cyanPotionObj{Instantiate({{1.0f, 10.0f}, 0.0f, {1.0f, 1.0f}})};
		cyanPotionObj->AddComponent<Sprite>("cyanPotion");
		cyanPotionObj->AddComponent<BoxCollider>()->SetTrigger(true);	
		cyanPotionObj->AddComponent<WorldItem>(worldItem);
		cyanPotionObj->SetTag("item");

		_playerHealthBar = std::make_unique<HealthComponent>(
			*this,
			"",
			Math::Vector2{ 200, 600 },
			Math::Vector2{ 600, 30 },
			playerObject->GetComponent<PlayerBehaviour>().GetPlayer()
		);
		HotbarComponent hotbar{*this, 6, "", Math::Vector2{200, 200}, Math::Vector2{100, 100}, playerObject->GetComponent<PlayerBehaviour>().GetPlayer()};
	}

private:
	std::unique_ptr<HealthComponent> _playerHealthBar; // TODO: encapsulate
};
