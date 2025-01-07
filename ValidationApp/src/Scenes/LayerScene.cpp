#include "LayerScene.hpp"

void LayerScene::OnStart()
{
	// Create Player
	std::shared_ptr<GameObject> playerObject{ Instantiate({{4.0f, 4.0f}, 0.0f, {2.5f, 2.5f}}) };
	std::shared_ptr<AnimationSheet> playerSheet = std::make_shared<AnimationSheet>(playerObject->GetComponent<Transform>(), 9, 64, 64, 9, 11, 10, 12);
	playerSheet->AddCustomAnimation("death", 6, 21, 150);
	playerObject->AddComponent<Sprite>("layerPlayer", playerSheet)->SetLayer(Layer::Player);
	playerObject->AddComponent<Audio::SFXSource>("", false, false);
	playerObject->AddComponent<BoxCollider>();
	playerObject->AddComponent<Rigidbody>();	
	playerObject->AddComponent<PlayerBehaviour>()->LoadPlayer();
	playerObject->SetTag("player");

	// Create goblin enemy
	std::shared_ptr<GameObject> goblinObj{ Instantiate({{10.0f, 10.0f}, 0.0f, {2.5f, 2.5f}}) };
	std::shared_ptr<AnimationSheet> goblinSheet = std::make_shared<AnimationSheet>(goblinObj->GetComponent<Transform>(), 6, 64, 64, 3, 1, 4, 2);
	goblinObj->AddComponent<Sprite>("goblin", goblinSheet);
	goblinObj->AddComponent<Audio::SFXSource>("", false, false);
	goblinObj->AddComponent<BoxCollider>()->SetTrigger(true);
	goblinObj->AddComponent<Rigidbody>()->SetGravityScale(0.0f);
	goblinObj->SetTag("goblin");
	goblinObj->AddComponent<EnemyBehaviour>()->SetPlayer(&playerObject->GetComponent<Transform>(), playerObject->GetComponent<PlayerBehaviour>().GetPlayer());	

	// Create slime enemy
	std::shared_ptr<GameObject> slimeObj{ Instantiate({{1.0f, 12.0f}, 0.0f, {1.0f, 1.0f}}) };
	std::shared_ptr<AnimationSheet> slimeSheet = std::make_shared<AnimationSheet>(slimeObj->GetComponent<Transform>(), 3, 24, 24, 1, 3, 0, 2);
	slimeObj->AddComponent<Sprite>("slime", slimeSheet);
	slimeObj->AddComponent<Audio::SFXSource>("", false, false);
	slimeObj->AddComponent<BoxCollider>()->SetTrigger(true);
	slimeObj->AddComponent<Rigidbody>()->SetGravityScale(0.0f);
	slimeObj->SetTag("slime");
	slimeObj->AddComponent<EnemyBehaviour>()->SetPlayer(&playerObject->GetComponent<Transform>(), playerObject->GetComponent<PlayerBehaviour>().GetPlayer());

	// Create skeleton enemy
	std::shared_ptr<GameObject> skeletonObj{ Instantiate({{-10.0f, 10.0f}, 0.0f, {2.5f, 2.5f}}) };
	std::shared_ptr<AnimationSheet> skeletonSheet = std::make_shared<AnimationSheet>(skeletonObj->GetComponent<Transform>(), 9, 64, 64, 1, 3, 2, 4);
	skeletonObj->AddComponent<Sprite>("skeleton", skeletonSheet);
	skeletonObj->AddComponent<Audio::SFXSource>("", false, false);
	skeletonObj->AddComponent<BoxCollider>()->SetTrigger(true);
	skeletonObj->AddComponent<Rigidbody>()->SetGravityScale(0.0f);
	skeletonObj->SetTag("skeleton");
	skeletonObj->AddComponent<EnemyBehaviour>()->SetPlayer(&playerObject->GetComponent<Transform>(), playerObject->GetComponent<PlayerBehaviour>().GetPlayer());	

	// Create slime boss
	std::shared_ptr<GameObject> bossObj{ Instantiate({{3.0f, 15.0f}, 0.0f, {5.0f, 5.0f}}) };
	std::shared_ptr<AnimationSheet> bossSheet = std::make_shared<AnimationSheet>(bossObj->GetComponent<Transform>(), 3, 24, 24, 1, 3, 0, 2);
	bossObj->AddComponent<Sprite>("boss", bossSheet);
	bossObj->AddComponent<Audio::MusicSource>("Assets\\Audio\\Music\\Boss_music_1.mp3", false, true)->Play();
	bossObj->AddComponent<Audio::SFXSource>("", false, false);
	bossObj->AddComponent<BoxCollider>()->SetTrigger(true);
	bossObj->AddComponent<Rigidbody>()->SetGravityScale(0.0f);
	bossObj->SetTag("boss");
	bossObj->AddComponent<EnemyBehaviour>()->SetPlayer(&playerObject->GetComponent<Transform>(), playerObject->GetComponent<PlayerBehaviour>().GetPlayer());

	// Create potion object to pick up
	WorldItem worldItem1 = WorldItem(new HealingPotion(10, 10, "healingpotion", "cyanPotion"), 1);
	std::shared_ptr<GameObject> cyanPotionObj{ Instantiate({{1.0f, 10.0f}, 0.0f, {1.0f, 1.0f}}) };
	cyanPotionObj->AddComponent<Sprite>("cyanPotion");
	cyanPotionObj->AddComponent<BoxCollider>()->SetTrigger(true);
	cyanPotionObj->AddComponent<WorldItem>(worldItem1);
	cyanPotionObj->SetTag("item");

	WorldItem worldItem3 = WorldItem(new DefensePotion(10, 1, "defensepotion", "potion_effervescent"), 1);
	std::shared_ptr<GameObject> effrvscntPotionObj2{ Instantiate({{30.0f, 10.0f}, 0.0f, {1.0f, 1.0f}}) };
	effrvscntPotionObj2->AddComponent<Sprite>("potion_effervescent");
	effrvscntPotionObj2->AddComponent<BoxCollider>()->SetTrigger(true);
	effrvscntPotionObj2->AddComponent<WorldItem>(worldItem3);
	effrvscntPotionObj2->SetTag("item");

	for (int i = 0; i < 5; i++)
	{
		WorldItem coin = WorldItem(new Coin("coin", "coin"), 1);
		std::shared_ptr<GameObject> coinObj{ Instantiate({{20.0f, (20.0f + i)}, 0.0f, {0.8f, 0.8f}}) };
		coinObj->AddComponent<Sprite>("coin");
		coinObj->AddComponent<BoxCollider>()->SetTrigger(true);
		coinObj->AddComponent<WorldItem>(coin);
		coinObj->SetTag("coin");
	}

	_hud = std::make_unique<HUDView>(*this, "goblin", playerObject->GetComponent<PlayerBehaviour>().GetPlayer());
}
