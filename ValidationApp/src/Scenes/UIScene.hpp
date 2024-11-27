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
		auto func = []{ std::cout << "Hihi, je hebt mij geklikt :)!\n"; };
		g->AddComponent<Ui::Button>()->SetOnLeftMouseClick(func);
	}
};