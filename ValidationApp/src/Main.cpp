#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "ValidationApp.hpp"

//class MonoBehaviour 
//{
//public:
//    virtual void Update() = 0;
//    virtual ~MonoBehaviour() = default;
//};
//
//class FirstBehaviour : public MonoBehaviour {
//public:
//    void Update() override 
//    {
//        std::cout << "First" << std::endl;
//    }
//
//    void First()
//    {
//        std::cout << "FirstBehaviour" << std::endl;
//    }
//};
//
//class SecondBehaviour : public MonoBehaviour {
//public:
//    void Update() override 
//    {
//        std::cout << "Second" << std::endl;
//    }
//
//    void Second()
//    {
//        std::cout << "SecondBehaviour" << std::endl;
//    }
//};
//
//class MonoBehaviourSystem : public ecs::System<std::unique_ptr<MonoBehaviour>>
//{
//public:
//	MonoBehaviourSystem(ecs::View<std::unique_ptr<MonoBehaviour>> view) 
//        : ecs::System<std::unique_ptr<MonoBehaviour>>(view)
//    {
//
//    }
//
//    void Update()
//    {
//        for (ecs::EntityId entityId : _view)
//        {
//			_view.get<std::unique_ptr<MonoBehaviour>>(entityId)->Update();
//        }
//    }
//};

int main() 
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

 //   ecs::Registry reg;
	//ecs::EntityId firstEntity = reg.CreateEntity();
	//ecs::EntityId secondEntity = reg.CreateEntity();

 //   FirstBehaviour* firstBehaviour = reg.AddBehaviour<FirstBehaviour>(firstEntity);
	//SecondBehaviour* secondBehaviour = reg.AddBehaviour<SecondBehaviour>(secondEntity);

 //   std::shared_ptr<MonoBehaviourSystem> behaviourSystem = reg.CreateSystem<MonoBehaviourSystem, std::unique_ptr<MonoBehaviour>>();
	//behaviourSystem->Update();

	//firstBehaviour->First();
	//secondBehaviour->Second();

 //   reg.DestroyEntity(firstEntity);
	//reg.DestroyEntity(secondEntity);
 //   return 0;

	ValidationApp app{};
	return 0;
}