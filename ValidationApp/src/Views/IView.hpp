#pragma once

#include "Engine/Delta.hpp"
#include <string>

class IView
{
public:
	IView(Scene& scene, const std::string& fontName, const Math::Vector2& startPos, const Math::Vector2& scale);
	void SetFont(const std::string& fontName);
	const virtual Math::Vector2& GetSize() const = 0;
	const Math::Vector2& GetPos() const;
protected:
	std::string _fontName;
	Scene& _scene;
	Math::Vector2 _scale;
	Math::Vector2 _pos;
	const Rendering::Color DEFAULT_COLOR{ 0, 0, 0, 255 };
};