#pragma once
#include "Input/InputManager.hpp"


#include <string>

#include "GameObject.hpp"

class BehaviourScript
{
public:
	friend class GameObject;

	virtual void OnStart() { };
	virtual void OnUpdate() { };

	void LoadScene(const std::string& name) { transform->gameObject->LoadScene(name); }

	virtual ~BehaviourScript() = default;

	//Inputs

	void keyPressed(Key keyDown, Events::EventCallback<Input&> keyEvent, std::string category = InputManager::defaultCategory);
	void keyPressed(std::set<Key> keysDown, Events::EventCallback<Input&> keyEvent, std::string category = InputManager::defaultCategory);
	
	void onKeyPressed(Key keyDown,Events::EventCallback<Input&> keyEvent, std::string category = InputManager::defaultCategory);
	void onKeyReleased(Key keyUp, Events::EventCallback<Input&> keyEvent, std::string category = InputManager::defaultCategory);


	void onMouseButtonDown(MouseButton button, Events::EventCallback<Input&> buttonEvent, std::string category = InputManager::defaultCategory);
	void onMouseButtonUp(MouseButton button, Events::EventCallback<Input&> buttonEvent, std::string category = InputManager::defaultCategory);
	void onMouseMove(Events::EventCallback<Input&> mouseEvent);
	void onMouseWheel(Events::EventCallback<Input&> wheelEvent);

	Transform* transform = nullptr;
	Camera* camera = nullptr;

protected:
	InputHandler _inputListeners;

	std::shared_ptr<GameObject> Instantiate()
	{
		return transform->gameObject->Instantiate();
	}

	std::shared_ptr<GameObject> Instantiate(Transform transformComponent)
	{
		return transform->gameObject->Instantiate(transformComponent);
	}
};

