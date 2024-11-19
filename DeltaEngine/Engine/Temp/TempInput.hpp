#pragma once

#include <iostream>
#include "../BehaviourScript.hpp"

class TempInput : public BehaviourScript
{
   public:

	// DONE Combinatie van toetsen indrukken om een actie uit te voeren.
	// DONE remove inputs if window is not focesed
	//
	// TODO Make All Inputs ENUMS or class.
	// TODO maak het zo dat je niet de hele tijd InputManager::GetInstance() hoeft neer te zetten.
	// TODO Categoriseren welk type invoer het is, zodat het gemakkelijk gepauzeerd kan worden.
	// TODO Combinatie van toets en knop om een actie uit te voeren.
	// TODO Miss zorgen dat een input kan toegevoegd worden onder update time?
	// TODO Invoer verwijderen ?

	// Components

	// Methods
	void OnStart() override
	{

		std::cout << "OnStart" << std::endl;
		

		InputManager::GetInstance().onKeyDown(
			{KEY_B, KEY_H},
			[](KeyListener& key) { std::cout << "SD test" << std::endl; });
		InputManager::GetInstance().onKeyDown(
			KEY_Z, [](KeyListener& key) { std::cout << "Z test" << std::endl; });

		InputManager::GetInstance().keyPressed(
			{KEY_I, KEY_W},
			[](KeyListener& key)
			{
				std::cout << "Gaat naar boven: ";
				std::for_each(key.keys.begin(), key.keys.end(),
							  [](Key k)
							  { std::cout  << InputsEnum::toStr(k); });
				std::cout << '\n';
			});


		InputManager::GetInstance().keyPressed(
			KEY_A,
			[](KeyListener& key)
			{
				std::cout << "Gaat naar boven: ";
				std::for_each(key.keys.begin(), key.keys.end(),
							  [](Key k)
							  { std::cout << InputsEnum::toStr(k); });
				std::cout << '\n';
			});

		InputManager::GetInstance().onKeyUp(
			KEY_SPACE, [](KeyListener& key)
			{
				std::for_each(key.keys.begin(), key.keys.end(),
							  [](Key k)
							  { std::cout << InputsEnum::toStr(k); });
				std::cout << '\n';
			});

		/*InputManager::GetInstance().onKeyDown( //TODO checken of dit niet fout gaat!!
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

	void OnUpdate() override {}
};