#pragma once

#include "Engine/Delta.hpp"
#include "../Views/EndScreen.hpp"

class EndScene : public Scene
{
public:
	EndScene(const std::string& name)
		: Scene(name) {}

	void OnStart() override
	{
		_endScene = std::make_unique<EndScreen>(*this, std::string{"goblin"}, Math::Vector2{0, 0}, Math::Vector2{500, 500}, 
			std::string{"You died"}, Rendering::Color{255, 255, 255, 255}, 10); // TODO: Cleanup
	}
private:
	std::unique_ptr<EndScreen> _endScene;
};