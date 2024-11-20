#pragma once

#include <iostream>
#include "../BehaviourScript.hpp"

class TempInput : public BehaviourScript
{
   public:

	// DONE Combinaties van toetsen gebruiken om een actie uit te voeren.
	// DONE Inputs verwijderen als het venster niet gefocust is.
	// DONE Alle inputs omzetten naar ENUMS of een klasse.
	//
	// TODO Categoriseer het type invoer, zodat deze eenvoudig gepauzeerd kan worden.
	// TODO Voeg alle inputwaarden toe aan het event bij de dispatch()-aanroep.
	// TODO Ondersteuning voor combinaties van toetsen en knoppen om acties uit te voeren.
	// TODO Zorg ervoor dat InputManager::GetInstance() niet overal expliciet hoeft te worden aangeroepen.
	// 
	// TODOMISS Mogelijkheid toevoegen om input aftewijzen tijdens update-tijd.
	// TODOMISS Functionaliteit toevoegen om invoer te kunnen verwijderen?


	// Components

	// Methods
	void OnStart() override
	{

		std::cout << "OnStart" << std::endl;
		
		InputManager::GetInstance().onKeyDown(
			{KEY_B, KEY_H},
			[](KeyListener& key) { std::cout << "SD test" << std::endl; });
		InputManager::GetInstance().onKeyDown(
			KEY_Z, [](KeyListener& key) { std::cout << "Z test" << std::endl; },
			"test");

		InputManager::GetInstance().deactivateCategory("test");
		InputManager::GetInstance().activateCategory("test");
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

		/*InputManager::GetInstance().onMouseButtonDown(
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
			});

		InputManager::GetInstance().onMouseWheel(
			[](WheelListener& mouse) {
				std::cout << mouse.h << " - " << mouse.v << " : "
						  << mouse.preciseX << " - " << mouse.preciseY << ":"
						  << mouse.direction << std::endl;
			});*/
	}

	void OnUpdate() override {}
};