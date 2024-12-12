#include "GameSpeedComponent.hpp"

GameSpeedComponent::GameSpeedComponent(Scene& scene, const std::string& fontName, 
	const Math::Vector2& startPos, const Math::Vector2& scale) : IView(scene, fontName)
{
	GameObject* gameSpeed = _scene.Instantiate({startPos, 0.0f, scale});

	// TODO: for now, display hardcoded gamespeed since it cannot be adjusted yet.
	gameSpeed->AddComponent<Ui::Text>("1x", fontName, DEFAULT_FONT_SIZE, DEFAULT_COLOR);
}
