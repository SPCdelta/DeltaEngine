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
	LayerScene(const std::string& sceneName) : Scene(sceneName) {}
	void OnStart() override
	{
		// Create Player
		std::shared_ptr<GameObject> playerObject{ Instantiate({{1.0f, 1.0f}, 0.0f, {3.0f, 3.0f}}) };

		std::shared_ptr<AnimationSheet> sheet = std::make_shared<AnimationSheet>(playerObject->GetComponent<Transform>(), 9, 64, 64, 9, 11, 10, 12);

		sheet->AddCustomAnimation("death", 6, 21, 150);

		playerObject->AddComponent<Sprite>("layerPlayer", sheet)->SetLayer(Layer::Player);

		playerObject->AddComponent<BoxCollider>();
		playerObject->AddComponent<Rigidbody>();

		playerObject->AddComponent<Audio::SFXSource>();
		playerObject->AddComponent<PlayerBehaviour>();

		// Create object that hurts player when player touches it
		std::shared_ptr<GameObject> hurtfulObject{ Instantiate({{10.0f, 10.0f}, 0.0f, {3.0f, 3.0f}}) };
		hurtfulObject->AddComponent<Sprite>("spritesheet2");
		hurtfulObject->AddComponent<BoxCollider>()->SetTrigger(true);
		hurtfulObject->SetTag("enemy");

		// Create object that gets hurt when a weapon touches it
		std::shared_ptr<GameObject> pokemonObject{ Instantiate({{10.0f, 1.0f}, 0.0f, {3.0f, 3.0f}}) };
		pokemonObject->AddComponent<Sprite>("spritesheet");

		pokemonObject->AddComponent<BoxCollider>();
		pokemonObject->AddComponent<Rigidbody>();

		pokemonObject->AddComponent<EnemyBehaviour>();

		// Create potion object to pick up
		WorldItem worldItem1 = WorldItem(HealingPotion(10, 10, "healingpotion", "cyanPotion"), 1);
		std::shared_ptr<GameObject> cyanPotionObj{ Instantiate({{1.0f, 10.0f}, 0.0f, {1.0f, 1.0f}}) };
		cyanPotionObj->AddComponent<Sprite>("cyanPotion");
		cyanPotionObj->AddComponent<BoxCollider>()->SetTrigger(true);
		cyanPotionObj->AddComponent<WorldItem>(worldItem1);
		cyanPotionObj->SetTag("item");

		WorldItem worldItem2 = WorldItem(HealingPotion(10, 10, "somepotion", "potion_effervescent"), 1);
		std::shared_ptr<GameObject> effrvscntPotionObj1{ Instantiate({{20.0f, 10.0f}, 0.0f, {1.0f, 1.0f}}) };
		effrvscntPotionObj1->AddComponent<Sprite>("potion_effervescent");
		effrvscntPotionObj1->AddComponent<BoxCollider>()->SetTrigger(true);
		effrvscntPotionObj1->AddComponent<WorldItem>(worldItem2);
		effrvscntPotionObj1->SetTag("item");

		WorldItem worldItem3 = WorldItem(HealingPotion(10, 10, "somepotion", "potion_effervescent"), 1);
		std::shared_ptr<GameObject> effrvscntPotionObj2{ Instantiate({{30.0f, 10.0f}, 0.0f, {1.0f, 1.0f}}) };
		effrvscntPotionObj2->AddComponent<Sprite>("potion_effervescent");
		effrvscntPotionObj2->AddComponent<BoxCollider>()->SetTrigger(true);
		effrvscntPotionObj2->AddComponent<WorldItem>(worldItem3);
		effrvscntPotionObj2->SetTag("item");

		const auto viewport = GetWindow()->GetViewport();
		const int windowWidth = viewport.width;
		const int windowHeight = viewport.height;
		_playerHealthBar = std::make_unique<HealthComponent>(
			*this,
			"",
			Math::Vector2{ windowHeight/2, 550 },
			Math::Vector2{ 600, 30 },
			playerObject->GetComponent<PlayerBehaviour>().GetPlayer()
		);
		_playerHotbar = std::make_unique<HotbarComponent>(
			*this, 6, "goblin",
			Math::Vector2{ windowHeight / 2, 620 },
			Math::Vector2{ 100, 100 },
			playerObject->GetComponent<PlayerBehaviour>().GetPlayer());
	}

private:
	std::unique_ptr<HealthComponent> _playerHealthBar; // TODO: encapsulate
	std::unique_ptr<HotbarComponent> _playerHotbar; // TODO: encapsulate
};
