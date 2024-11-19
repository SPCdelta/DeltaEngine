#include "GameObject.hpp"

GameObject::GameObject(ecs::Registry& reg, Audio::AudioFacade& audioFacade,
					   Transform newTransform)
	: _reg(reg), _audioFacade(audioFacade)
{
	_id = reg.CreateEntity();
	transform = &_reg.AddComponent<Transform>(_id, newTransform);
}

GameObject::~GameObject()
{

}