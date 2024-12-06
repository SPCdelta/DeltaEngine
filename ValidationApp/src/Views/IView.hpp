#pragma once

#include "Engine/Delta.hpp"
#include <string>

class IView
{
public:
	IView(Scene& scene, const std::string& pathToFont);
	void SetFont(const std::string& pathToFont);
protected:
	std::string _fontName;
	Scene& _scene;
};