#include "GameObject.hpp"

GameObject::GameObject(ecs::Registry& reg, Audio::AudioFacade& audioFacade, Events::EventDispatcher<const std::string&>& changeScene, Transform newTransform)
	: _reg(reg), _changeScene{ changeScene }, _audioFacade(audioFacade)
{
	_id = reg.CreateEntity();
	transform = &_reg.AddComponent<Transform>(_id, newTransform);
}

GameObject::~GameObject()
{

}