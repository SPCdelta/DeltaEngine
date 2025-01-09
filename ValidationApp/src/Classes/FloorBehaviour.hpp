#pragma once

#include "Engine/Delta.hpp"

enum class FloorType
{
	NORMAL = 0,
	ICE = 1,
	MUD = 2,
};

class FloorBehaviour
{
public:
	FloorBehaviour(Rigidbody& rigidbody) 
		: _rigidbody{ rigidbody }
	{
		_rigidbody.onTriggerEnter.Register(
			[this](Collider& collider)
			{ 
				if (!collider.transform.gameObject)
					return;

				const std::string& tag{collider.transform.gameObject->GetTag()};
				if (tag == "ice")
				{
					_iceCount++;
				}
				else if (tag == "mud")
				{
					_mudCount++;
				}
			}
		);

		rigidbody.onTriggerExit.Register(
			[this](Collider& collider)
			{
				if (!collider.transform.gameObject)
					return;

				const std::string& tag{collider.transform.gameObject->GetTag()};
				if (tag == "ice")
				{
					_iceCount--;
				}
				else if (tag == "mud")
				{
					_mudCount--;
				}
			}
		);
	}

	~FloorBehaviour()
	{
		// TODO: Unregister Events

	}

	FloorType GetOnFloor() const
	{
		// Order is important here
		if (_mudCount > 0)
		{
			return FloorType::MUD;
		}
		else if (_iceCount > 0)
		{
			return FloorType::ICE;
		}
		else
		{
			return FloorType::NORMAL;
		}
	}

private:
	Rigidbody& _rigidbody;

	int _iceCount{0};
	int _mudCount{0};
};