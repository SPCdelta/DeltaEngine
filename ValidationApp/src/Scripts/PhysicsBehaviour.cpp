#include "PhysicsBehaviour.hpp"

void PhysicsBehaviour::OnStart()
{
	rigidbody = &gameObject->GetComponent<Physics::Rigidbody>();

	rigidbody->onTriggerEnter.Register(
	[this](Collider& collider) 
	{
		std::cout << "OnTriggerEnter" << std::endl;
	});

	rigidbody->onTriggerExit.Register(
	[this](Collider& collider)
	{
		std::cout << "OnTriggerExit" << std::endl;
	});

	rigidbody->onCollisionEnter.Register(
	[this](Collider& collider) 
	{
		std::cout << "OnCollisionEnter" << std::endl;
		rigidbody->AddForce(Math::Vector2::up * 10.0f, ForceMode::IMPULSE);
	});

	rigidbody->onCollisionExit.Register(
	[this](Collider& collider) 
	{
		std::cout << "OnCollisionExit" << std::endl;
	});
}

void PhysicsBehaviour::OnUpdate() 
{

}