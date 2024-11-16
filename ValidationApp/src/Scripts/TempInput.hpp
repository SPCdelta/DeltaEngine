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

		/*InputManager::GetInstance().onKeyDown(
			"W",
			[](KeyListener& key)
			{
				std::cout << "Gaat naar boven: " << key.key
						  << std::endl;
			});

		InputManager::GetInstance().onKeyDown(
			"A",
			[](KeyListener& key)
			{
				std::cout << "Gaat naar rechts: " << key.key
						  << std::endl;
			});
		InputManager::GetInstance().onKeyDown(
			"D", 
			[](KeyListener& key)
			{ std::cout << "Gaat naar onder: " << key.key << std::endl; });
		InputManager::GetInstance().onKeyDown(
			"S", [](KeyListener& key)
			{ std::cout << "Gaat naar links: " << key.key << std::endl; });

		
		InputManager::GetInstance().onKeyUp(
			"Space", [](KeyListener& key)
			{ std::cout << "Spatie is los gelaten: " << key.key << std::endl; });

		InputManager::GetInstance().onMouseButtonDown(
			1,
			[](MouseListener& button) {
				std::cout << "linkermuis click: " << button.button << std::endl;
			});

		InputManager::GetInstance().onMouseButtonUp(
			2,
			[](MouseListener& button) {
				std::cout << "weel los gelaten: " << button.button << std::endl;
			});

		InputManager::GetInstance().onMouseMove(
			[](MouseListener& mouse) {
				std::cout << mouse.mouseX << " - " << mouse.mouseY << std::endl;
			});*/

		InputManager::GetInstance().onMouseWheel(
			[](WheelListener& mouse) {
				std::cout << mouse.h << " - " << mouse.v << " : "
						  << mouse.preciseX << " - " << mouse.preciseY << ":"
						  << mouse.direction << std::endl;
			});
	}

	void OnUpdate() override {

	}
};