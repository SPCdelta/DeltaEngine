#pragma once
#include "Input/InputManager.hpp"


class GameObject;

class BehaviourScript
{
public:
	//Willen we dat de gebruiker deze functie kan aanroepen of dat we 
	//een friend gebruiken zodat de protected gameObject direct gezet kan worden
	//friend class GameObject;
	void SetGameObject(GameObject* gameObject);

	virtual void OnStart() = 0;
	virtual void OnUpdate() = 0;

	virtual ~BehaviourScript();

	//Inputs

	void keyPressed(Key keyDown, Events::EventCallback<Input&> keyEvent, std::string category = InputManager::defaultCategory);
	void keyPressed(std::set<Key> keysDown, Events::EventCallback<Input&> keyEvent, std::string category = InputManager::defaultCategory);
	
	void onKeyPressed(Key keyDown,Events::EventCallback<Input&> keyEvent, std::string category = InputManager::defaultCategory);
	void onKeyRealesed(Key keyUp, Events::EventCallback<Input&> keyEvent, std::string category = InputManager::defaultCategory);


	void onMouseButtonDown(Button button, Events::EventCallback<Input&> buttonEvent, std::string category = InputManager::defaultCategory);
	void onMouseButtonUp(Button button, Events::EventCallback<Input&> buttonEvent, std::string category = InputManager::defaultCategory);
	void onMouseMove(Events::EventCallback<Input&> mouseEvent);
	void onMouseWheel(Events::EventCallback<Input&> wheelEvent);

	void unregesterInputs();

   protected:
	GameObject* gameObject = nullptr;
	std::vector<InputLocation> regesterdInputs;
};

