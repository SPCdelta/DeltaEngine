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
			"BH",
			[](KeyListener& key)
			{
				std::cout << "SD test" << std::endl;
			});
		InputManager::GetInstance().onKeyDown(
			"Z",
			[](KeyListener& key) { std::cout << "Z test" << std::endl; });

		InputManager::GetInstance().keyPressed(
			"IW",
			[](KeyListener& key)
			{
				std::cout << "Gaat naar boven: " << key.keys[0] << " "
						  << key.keys[1]
						  << std::endl;
			});

		InputManager::GetInstance().keyPressed(
			"A",
			[](KeyListener& key)
			{ std::cout << "Gaat naar rechts: " << key.keys[0]
						  << std::endl;
			});
		InputManager::GetInstance().keyPressed(
			"D", 
			[](KeyListener& key)
			{ std::cout << "Gaat naar onder: " << key.keys[0] << std::endl; });
		InputManager::GetInstance().keyPressed(
			"S", [](KeyListener& key)
			{ std::cout << "Gaat naar links: " << key.keys[0] << std::endl; });


		//InputManager::GetInstance().onKeyUp(
		//	"Space", [](KeyListener& key)
		//	{ 
		//		std::cout << "Spatie is los gelaten: " << key.key << std::endl; 
		//	});


		/*InputManager::GetInstance().onKeyDown(
			"Space",
			[](KeyListener& key) {
				InputManager::GetInstance().onMouseButtonDown(
					1,
					[](MouseListener& button) {
						std::cout << "linkermuis click attack: " << button.button
								  << std::endl;
					});

			});*/


		//InputManager::GetInstance().onMouseButtonDown(
		//	1,
		//	[](MouseListener& button) {
		//		std::cout << "linkermuis click: " << button.button << std::endl;
		//	});

		//InputManager::GetInstance().onMouseButtonUp(
		//	2,
		//	[](MouseListener& button) {
		//		std::cout << "weel los gelaten: " << button.button << std::endl;
		//	});

		//InputManager::GetInstance().onMouseMove(
		//	[](MouseListener& mouse) {
		//		std::cout << mouse.mouseX << " - " << mouse.mouseY << std::endl;
		//	});

		//InputManager::GetInstance().onMouseWheel(
		//	[](WheelListener& mouse) {
		//		std::cout << mouse.h << " - " << mouse.v << " : "
		//				  << mouse.preciseX << " - " << mouse.preciseY << ":"
		//				  << mouse.direction << std::endl;
		//	});
	}

	void OnUpdate() override {

	}
};