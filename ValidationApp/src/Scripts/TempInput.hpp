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

		const std::string downKey = "K";
		auto keyPresSim = new IKeyListener("M");
		InputManager::GetInstance().onKeyDown(
			downKey,
			[](IKeyListener& key)
			{
				std::cout << "Key event: " << key.key
						  << std::endl;
			} );  //Simularen dat er een sdl event komt

		InputManager::GetInstance().onKeyDown(
			"M",
			[](IKeyListener& key)
			{
				std::cout << "key event: " << key.key
						  << std::endl;
			});	 //Simularen dat er een sdl event komt

	}

	void OnUpdate() override {

	}
};