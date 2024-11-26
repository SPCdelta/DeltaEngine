#pragma once
#include "Input/InputManager.hpp"


#include <string>

#include "GameObject.hpp"
//class GameObject;

class BehaviourScript
{
public:
	friend class GameObject;

	virtual void OnStart() { };
	virtual void OnUpdate() { };

	void LoadScene(const std::string& name) { gameObject->LoadScene(name); }

	virtual ~BehaviourScript();

	//Inputs

	void keyPressed(Key keyDown, Events::EventCallback<Input&> keyEvent, std::string category = InputManager::defaultCategory);
	void keyPressed(std::set<Key> keysDown, Events::EventCallback<Input&> keyEvent, std::string category = InputManager::defaultCategory);
	
	void onKeyPressed(Key keyDown,Events::EventCallback<Input&> keyEvent, std::string category = InputManager::defaultCategory);
	void onKeyReleased(Key keyUp, Events::EventCallback<Input&> keyEvent, std::string category = InputManager::defaultCategory);


	void onMouseButtonDown(Button button, Events::EventCallback<Input&> buttonEvent, std::string category = InputManager::defaultCategory);
	void onMouseButtonUp(Button button, Events::EventCallback<Input&> buttonEvent, std::string category = InputManager::defaultCategory);
	void onMouseMove(Events::EventCallback<Input&> mouseEvent);
	void onMouseWheel(Events::EventCallback<Input&> wheelEvent);

	void unregisterInputs();

   protected:
	GameObject* gameObject = nullptr;
	std::vector<InputLocation> registerdInputs;

	Camera* camera = nullptr;

};

