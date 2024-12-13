#pragma once

#include <memory>

#include "Engine/Delta.hpp"

#include "../Scripts/EnemyBehaviour.hpp"
#include "../Scripts/EnemyHitboxBehaviour.hpp"
#include "../Items/Potions/HealingPotion.hpp"
#include "../Views/HUDView.hpp"

class LayerScene : public Scene
{
   public:
	LayerScene(const std::string& sceneName) : Scene(sceneName) {}
	void OnStart() override
	{
		// Create Player
		std::shared_ptr<GameObject> playerObject{ Instantiate({{4.0f, 4.0f}, 0.0f, {3.0f, 3.0f}}) };
		std::shared_ptr<AnimationSheet> playerSheet = std::make_shared<AnimationSheet>(playerObject->GetComponent<Transform>(), 9, 64, 64, 9, 11, 10, 12);
		playerSheet->AddCustomAnimation("death", 6, 21, 150);
		playerObject->AddComponent<Sprite>("layerPlayer", playerSheet)->SetLayer(Layer::Player);
		playerObject->AddComponent<Audio::SFXSource>("", false, false);
		playerObject->AddComponent<BoxCollider>();
		playerObject->AddComponent<Rigidbody>();	
		playerObject->AddComponent<PlayerBehaviour>();
		playerObject->SetTag("player");

		// Create object that gets hurt when a weapon touches it
		std::shared_ptr<GameObject> enemyObj{ Instantiate({{10.0f, 10.0f}, 0.0f, {3.0f, 3.0f}}) };
		std::shared_ptr<AnimationSheet> goblinSheet = std::make_shared<AnimationSheet>(enemyObj->GetComponent<Transform>(), 6, 64, 64, 3, 1, 4, 2);
		enemyObj->AddComponent<Sprite>("goblin", goblinSheet);
		enemyObj->AddComponent<Audio::SFXSource>("", false, false);
		enemyObj->AddComponent<BoxCollider>()->SetTrigger(true);
		enemyObj->AddComponent<Rigidbody>()->SetGravityScale(0.0f);
		enemyObj->AddComponent<EnemyBehaviour>()->SetPlayerPosition(&playerObject->GetComponent<Transform>().position);
		enemyObj->SetTag("goblin");
		
		// Create hitbox for the enemy so it can get hurt by the projectiles
		std::shared_ptr<GameObject> enemyDmgObj{ Instantiate(enemyObj->GetComponent<Transform>()) };
		enemyDmgObj->AddComponent<Sprite>("goblin")->SetVisible(false);
		enemyDmgObj->AddComponent<BoxCollider>();
		enemyDmgObj->AddComponent<Rigidbody>()->SetGravityScale(0.0f);
		enemyDmgObj->AddComponent<EnemyHitboxBehaviour>()->SetEnemyPosition(&enemyObj->GetComponent<Transform>().position) ;
		auto behaviour = &enemyObj->GetComponent<EnemyBehaviour>();
		behaviour->SetDamageBehaviour(enemyDmgObj->GetComponent<Rigidbody>());

		// Create potion object to pick up
		/*WorldItem worldItem1 = WorldItem(HealingPotion(10, 10, "healingpotion", "cyanPotion"), 1);
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
		effrvscntPotionObj2->SetTag("item");*/

		_hud = std::make_unique<HUDView>(*this, "goblin", playerObject->GetComponent<PlayerBehaviour>().GetPlayer());
	}

private:
	std::unique_ptr<HUDView> _hud;
};
