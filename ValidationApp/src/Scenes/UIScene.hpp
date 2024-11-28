#pragma once

#include "Engine/Delta.hpp"
#include <iostream>
#include "../Scripts/PlayerBehaviour.hpp"
#include "../Scripts/TempBehaviour.hpp"

class UIScene : public Scene
{
   public:
	UIScene(const std::string& name) : Scene(name)
	{
		std::shared_ptr<GameObject> g {Instantiate({{100.0f, 100.0f}, 0.0f, {100.0f, 100.0f}})};
		g->AddComponent<Ui::Image>("Assets\\Textures\\default_texture.png")->SetColor({255, 255, 255, 255});
		g->AddComponent<Ui::Text>("Hallo Wereld!", "Assets\\Fonts\\knight_warrior.otf", Rendering::Color{0, 0, 0, 0});
		auto func1 = [this]{ LoadScene("PhysicsScene"); };
		auto button = g->AddComponent<Ui::Button>();
		// Voorbeeld van onClick instellen:
		button->SetOnLeftMouseClick(func1, "Default"); // Klikken op tekst roept de lambda niet aan omdat de tekst buiten de size kan vallen van gameObject.
		// Of je kunt dingen zoals dit doen:
		std::string message = "Hihi, je hebt mij geklikt :)!\n";
		button->SetOnLeftMouseClick([message]() -> void 
			{
				std::cout << message;
			}, "Default");
		g->GetComponent<Ui::Text>().SetPosition(Math::Vector2{500, 500});
		g->GetComponent<Ui::Text>().SetFontSize(100);
	}
};