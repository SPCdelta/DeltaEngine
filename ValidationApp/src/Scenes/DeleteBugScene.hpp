#pragma once

#include <Engine/Delta.hpp>
#include "../Classes/Projectiles/Projectile.hpp"

class DeleteBugBehaviour : public BehaviourScript
{
public:
	void OnUpdate() override;

	void TestBug();
};

class DeleteBugScene : public Scene
{
public:
	DeleteBugScene(const std::string& name);

	std::vector<std::shared_ptr<Collider>> currentColliders;

	void OnStart() override;
	void OnUpdate() override;

	bool IsColliding(Collider& collider);

private:
	int _spawnCount{0};
	int _collisions{0};

	float _spawnTime{0.0f};
	float _spawnDuration{1.0f};

	void StartSpawn();
	bool CanSpawn() const;
};