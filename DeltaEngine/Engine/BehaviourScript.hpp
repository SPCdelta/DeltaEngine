#pragma once

#include <string>

#include "GameObject.hpp"
//class GameObject;

class BehaviourScript
{
public:
	//Willen we dat de gebruiker deze functie kan aanroepen of dat we 
	//een friend gebruiken zodat de protected gameObject direct gezet kan worden
	//friend class GameObject;
	void SetGameObject(GameObject* gameObject);

	virtual void OnStart() = 0;
	virtual void OnUpdate() = 0;

	void LoadScene(const std::string& name) { gameObject->LoadScene(name); }

	virtual ~BehaviourScript() = default;

protected:
	GameObject* gameObject = nullptr;
};

