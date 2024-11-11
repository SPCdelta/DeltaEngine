#pragma once

#include <iostream>
#include "../Ecs/Registry.hpp"

struct A
{
	int a{5};
};

struct B
{
	int b{9};
};

struct C
{
	int c{17};
};

class DebugSystem : public ecs::System<A, B>
{
public:
	DebugSystem(ecs::View<A, B> view)
		: ecs::System<A, B>(view) { }

	void Update()
	{
		for (ecs::EntityId entityId : _view)
		{
			//std::cout << "A: " << _view.get<A>(entityId).a << std::endl;
			//std::cout << "B: " << _view.get<B>(entityId).b << std::endl;
		}
	}
};

//class DebugSystem : public ecs::System<A, B>
//{
//public:
//	DebugSystem(const ecs::Registry* reg)
//		: ecs::System<A, B>(reg) { }
//
//	void Update()
//	{
//		//for (ecs::EntityId entityId : _view)
//		//{
//		//	std::cout << "A: " << _view.get<A>(entityId).a << std::endl;
//		//	std::cout << "B: " << _view.get<B>(entityId).b << std::endl;
//		//}
//	}
//};
