#pragma once

#include <iostream>
#include "../BehaviourScript.hpp"


class TempInput : public BehaviourScript
{
   public:

	// DONE Combinaties van toetsen gebruiken om een actie uit te voeren.
	// DONE Inputs verwijderen als het venster niet gefocust is.
	// DONE Alle inputs omzetten naar ENUMS of een klasse.
	// DONE Categoriseer het type invoer, zodat deze eenvoudig gepauzeerd kan worden.
	// DONE Voeg alle inputwaarden toe aan het event bij de dispatch()-aanroep.
	//
	// TODO Zorg ervoor dat InputManager::GetInstance() niet overal expliciet hoeft te worden aangeroepen.
	// 
	// TODOMISS Mogelijkheid toevoegen om input aftewijzen tijdens update-tijd.
	// TODOMISS Ondersteuning voor combinaties van toetsen en knoppen om acties uit te voeren.
	// TODOMISS Functionaliteit toevoegen om invoer te kunnen verwijderen?


	// Components

	// Methods
	void OnStart() override
	{

		std::cout << "OnStart" << std::endl;
		
		InputManager::onKeyPressed(
			{KEY_B, KEY_H},
			[](Input& key) { std::cout << "SD test" << std::endl; });

		InputManager::onKeyPressed(
			KEY_Z, [](Input& key) { std::cout << "Z test" << std::endl; },
			"test");

		InputManager::onKeyPressed(
			KEY_P, [](Input& key) { std::cout << "P test" << std::endl; },
			"test");

		InputManager::deactivateCategory("test");
		InputManager::activateCategory("test");
		InputManager::keyPressed(
			{KEY_I, KEY_W},
			[](Input& key)
			{
				std::cout << "Gaat naar boven: ";
				std::for_each(key.keys.begin(), key.keys.end(),
							  [](Key k)
							  { std::cout  << InputsEnum::toStr(k); });
				std::cout << '\n';
			});


		InputManager::keyPressed(
			KEY_A,
			[](Input& key)
			{
				std::cout << "Gaat naar boven: ";
				std::for_each(key.keys.begin(), key.keys.end(),
							  [](Key k)
							  { std::cout << InputsEnum::toStr(k); });
			});

		InputManager::onKeyRealesed(
			KEY_SPACE,
			[](Input& key)
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

		InputManager::onMouseButtonDown(
			Button::Left,
			[](Input& button) { std::cout << "left: ";
				std::for_each(button.buttons.begin(), button.buttons.end(),
							  [](Button k)
							  {
								  int d = static_cast<int>(k);
								  std::cout << d;
							  });
				std::cout << std::endl;

			});

		InputManager::onMouseButtonUp(
			Button::Right,
			[](Input& button) {
				std::cout << "right: ";
				std::for_each(button.buttons.begin(), button.buttons.end(),
							  [](Button k)
							  { 
						int d = static_cast<int>(k);
						std::cout << d; });
				std::cout << std::endl;
			});

		/*InputManager::GetInstance().onMouseMove(
			[](Input& mouse) {
				std::cout << mouse.mouseX << " - " << mouse.mouseY << std::endl;
			});*/

		InputManager::onMouseWheel(
			[](Input& mouse) {
				std::cout << mouse.mouseX << " - " << mouse.wheelVertically
						  << " : \n";
			});
	}

	void OnUpdate() override {}
};