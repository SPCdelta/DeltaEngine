#pragma once

#include <Engine/Delta.hpp>

class UIFactory
{
public:
	static std::shared_ptr<GameObject> CreateText(Scene* scene, const std::string& text, const std::string& font, int fontSize, const Rendering::Color color);
	static std::shared_ptr<GameObject> CreateButton(Scene* scene, const std::string& text, const std::string& font, int fontSize, const Rendering::Color textColor, 
		Layer layer);
	static std::shared_ptr<GameObject> CreateImage(Scene* scene, const std::string& spriteName, Layer layer);
};