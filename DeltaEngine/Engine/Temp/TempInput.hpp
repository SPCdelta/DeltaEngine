#pragma once

#include <iostream>
#include "../BehaviourScript.hpp"

class TempInput : public BehaviourScript
{
   public:
	// Components

	// Methods
	void OnStart() override { 
		std::cout << "OnStart" << std::endl; 

		InputManager::GetInstance().onKeyDown(
			"K",
			[](KeyListener& key)
			{
				std::cout << "Key event: " << key.key
						  << std::endl;
			} );  //Simularen dat er een sdl event komt

		InputManager::GetInstance().onKeyUp(
			"M",
			[](KeyListener& key)
			{
				std::cout << "key event: " << key.key
						  << std::endl;
			});	 //Simularen dat er een sdl event komt

	}

	void OnUpdate() override {

	}
};