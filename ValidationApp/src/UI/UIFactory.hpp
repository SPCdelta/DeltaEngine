#pragma once

#include <Engine/Delta.hpp>

class UIFactory
{
public:
	static std::shared_ptr<GameObject> CreateText(Scene* scene, const std::string& text, const std::string& font, int fontSize, const Rendering::Color color)
	{
		std::shared_ptr<GameObject> textObj = scene->Instantiate();
		textObj->AddComponent<Ui::Text>(text, font, fontSize, color);
		return textObj;
	}

	static std::shared_ptr<GameObject> CreateButton(Scene* scene, const std::string& text, const std::string& font, int fontSize, const Rendering::Color textColor, Layer layer)
	{
		std::shared_ptr<GameObject> buttonObj = scene->Instantiate();
		buttonObj->AddComponent<Ui::Button>(Vector2{ 100.0f, 100.0f }, Vector2{ 100.0f, 50.0f });
		buttonObj->AddComponent<Ui::Text>(text, font, fontSize, textColor);
		buttonObj->AddComponent<Ui::Image>("scroll3")->SetLayer(layer);
		return buttonObj;
	}

	static std::shared_ptr<GameObject> CreateImage(Scene* scene, const std::string& spriteName, Layer layer)
	{
		std::shared_ptr<GameObject> imageObj = scene->Instantiate();
		imageObj->AddComponent<Ui::Image>(spriteName)->SetLayer(layer);
		return imageObj;
	}
};