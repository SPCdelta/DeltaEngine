#pragma once

#include "Engine/Delta.hpp"
#include <string>

class IView
{
public:
	IView(Scene& scene, const std::string& fontName);
	void SetFont(const std::string& fontName);
protected:
	std::string _fontName;
	Scene& _scene;
	const Rendering::Color DEFAULT_COLOR{ 0, 0, 0, 255 };
};