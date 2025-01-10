#pragma once

#include "Engine/Delta.hpp"

#include <string>

class IView
{
public:
	IView(Scene& scene, const std::string& fontName, const Math::Vector2& startPos, const Math::Vector2& scale);

	void SetFont(const std::string& fontName);

	const virtual Math::Vector2& GetSize() const = 0;

	virtual void SetCenter()
	{
		auto vp = _scene.GetWindow()->GetViewport();
		auto xPos = vp.width / 2 - GetSize().GetX() / 2;
		auto yPos = vp.height / 2 - GetSize().GetY() / 2;
		_pos = { xPos, yPos };
	}

	const Math::Vector2& GetPos() const;

	virtual void SetPosition(const Math::Vector2& pos)
	{
		_pos = pos;
	}

protected:
	const std::string DEFAULT_FONT = "goblin";
	const Rendering::Color DEFAULT_COLOR{255, 255, 255, 255};

	std::string _fontName;

	Scene& _scene;

	Math::Vector2 _scale;
	Math::Vector2 _pos;
};