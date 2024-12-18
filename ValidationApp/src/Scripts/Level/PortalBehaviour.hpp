#pragma once

#include <Engine/Delta.hpp>

struct PortalData
{
	std::string identifier;
	bool canPassThrough;
};

class PortalManager;

class PortalBehaviour : public BehaviourScript
{
public:
	PortalBehaviour(PortalData data)
		: _data{data}
	{

	}

	friend class PortalManager;

	void OnStart() override
	{
		BoxCollider* collider = gameObject->AddComponent<BoxCollider>();
		collider->SetTrigger(true);
		gameObject->SetTag("portal");
		Sprite* sprite = gameObject->AddComponent<Sprite>("portal");
		sprite->SetLayer(Layer::Foreground);

		// If can passthrough, set portal TP
		if (_data.canPassThrough)
		{
			Rigidbody* rb = gameObject->AddComponent<Rigidbody>();
			rb->onTriggerEnter.Register(
				[this](Collider& other) 
				{ 
					if (other.transform.gameObject->GetTag() == "player")
					{
						Teleport(other.transform.gameObject);
					}
				}
			);
		}
	}

private:
	PortalData _data;
	PortalManager* _portalManager;

	void Teleport(GameObject* object)
	{
		PortalBehaviour* other = _portalManager->GetOther(this);
		if (other != nullptr)
		{
			object->transformRef.position = other->transform->position;
		}
	}
};