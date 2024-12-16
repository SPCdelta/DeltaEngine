#pragma once

#include <memory>

#include "Engine/Delta.hpp"

#include "../Scripts/PlayerBehaviour.hpp"
#include "../Scripts/EnemyBehaviour.hpp"
#include "../Scripts/EnemyHitboxBehaviour.hpp"
#include "../Items/Potions/HealingPotion.hpp"
#include "../Views/HUDView.hpp"

class LayerScene : public Scene
{
   public:
	LayerScene(const std::string& sceneName) : Scene(sceneName){};

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
		WorldItem worldItem1 = WorldItem(std::make_shared<HealingPotion>(10, 10, "healingpotion", "cyanPotion"), 1);
		std::shared_ptr<GameObject> cyanPotionObj{ Instantiate({{1.0f, 10.0f}, 0.0f, {1.0f, 1.0f}}) };
		cyanPotionObj->AddComponent<Sprite>("cyanPotion");
		cyanPotionObj->AddComponent<BoxCollider>()->SetTrigger(true);
		cyanPotionObj->AddComponent<WorldItem>(worldItem1);
		cyanPotionObj->SetTag("item");

		WorldItem worldItem2 = WorldItem(std::make_shared<Item>("somepotion", "potion_effervescent"), 1);
		std::shared_ptr<GameObject> effrvscntPotionObj1{ Instantiate({{20.0f, 10.0f}, 0.0f, {1.0f, 1.0f}}) };
		effrvscntPotionObj1->AddComponent<Sprite>("potion_effervescent");
		effrvscntPotionObj1->AddComponent<BoxCollider>()->SetTrigger(true);
		effrvscntPotionObj1->AddComponent<WorldItem>(worldItem2);
		effrvscntPotionObj1->SetTag("item");

		WorldItem worldItem3 = WorldItem(std::make_shared<DefensePotion>(10, 1, "defensepotion", "potion_effervescent"), 1);
		std::shared_ptr<GameObject> effrvscntPotionObj2{ Instantiate({{30.0f, 10.0f}, 0.0f, {1.0f, 1.0f}}) };
		effrvscntPotionObj2->AddComponent<Sprite>("potion_effervescent");
		effrvscntPotionObj2->AddComponent<BoxCollider>()->SetTrigger(true);
		effrvscntPotionObj2->AddComponent<WorldItem>(worldItem3);
		effrvscntPotionObj2->SetTag("item");

		_hud = std::make_unique<HUDView>(*this, "goblin", playerObject->GetComponent<PlayerBehaviour>().GetPlayer());
	}
private:
	std::unique_ptr<HUDView> _hud;
};
