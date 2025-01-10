#pragma once

#include <Engine/Delta.hpp>

class UIFactory
{
public:
	static std::shared_ptr<GameObject> CreateText(Scene* scene, const std::string& text, const std::string& font, int fontSize, const Rendering::Color color)
	{
		std::shared_ptr<GameObject> textObj = scene->Instantiate();
		Ui::Text* textComponent = textObj->AddComponent<Ui::Text>(text, font, fontSize, color);
		textObj->transformRef.scale = Font::GetFontSize(textComponent->GetFont(), text);
		return textObj;
	}

	static std::shared_ptr<GameObject> CreateButton(Scene* scene, const std::string& text, const std::string& font, int fontSize, const Rendering::Color textColor, Layer layer)
	{
		std::shared_ptr<GameObject> buttonObj = scene->Instantiate();
		buttonObj->AddComponent<Ui::Button>(Vector2{ 100.0f, 100.0f }, Vector2{ 100.0f, 50.0f });
		Ui::Text* textComponent = buttonObj->AddComponent<Ui::Text>(text, font, fontSize, textColor);
		buttonObj->AddComponent<Ui::Image>("scroll3")->SetLayer(layer);

		buttonObj->transformRef.scale = Font::GetFontSize(textComponent->GetFont(), text) + Math::Vector2{ 32.0f, 32.0f };
		textComponent->SetPosition({ 8.0f, 8.0f });

		return buttonObj;
	}

	static std::shared_ptr<GameObject> CreateImage(Scene* scene, const std::string& spriteName, Layer layer)
	{
		std::shared_ptr<GameObject> imageObj = scene->Instantiate();
		imageObj->AddComponent<Ui::Image>(spriteName)->SetLayer(layer);
		return imageObj;
	}
};