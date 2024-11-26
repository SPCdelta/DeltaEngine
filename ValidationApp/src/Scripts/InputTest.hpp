#pragma once

#include <iostream>
#include "Engine/Delta.hpp"

class InputTest : public BehaviourScript
{
   public:
	// DONE Combinaties van toetsen gebruiken om een actie uit te voeren.
	// DONE Inputs verwijderen als het venster niet gefocust is.
	// DONE Alle inputs omzetten naar ENUMS of een klasse.
	// DONE Categoriseer het type invoer, zodat deze eenvoudig gepauzeerd kan worden.
	// DONE Voeg alle inputwaarden toe aan het event bij de dispatch()-aanroep.
	// DONE Zorg ervoor dat InputManager::GetInstance() niet overal expliciet hoeft te worden aangeroepen.
	// DONE Functionaliteit toevoegen om invoer te kunnen verwijderen?
	//
	// TODOMISS Mogelijkheid toevoegen om input aftewijzen tijdens update-tijd.
	// TODOMISS Ondersteuning voor combinaties van toetsen en knoppen om acties uit te voeren.


	// Methods
	void OnStart() override;

	void OnUpdate() override{};
};