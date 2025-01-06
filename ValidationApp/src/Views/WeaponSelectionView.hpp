#pragma once

#include "Engine/Delta.hpp"
#include "IView.hpp"

class WeaponSelectionView : public IView
{
public:
	WeaponSelectionView(Scene& scene, const std::string& fontName, const Math::Vector2& startPos, const Math::Vector2& scale);
	const Math::Vector2& GetSize() const override;
	void SetCenter() override;
private:
	void InitTitle();
	void InitBody();
	void InitWeapons();
	const Rendering::Color TEXT_COLOR = { 255, 255 ,255, 255 };
	const float TITLE_SCALE = 0.02f;
	const float TITLE_MARGINY_SCALE = 0.15f;
	const float BODY_TEXT_SCALE = 0.03f;
	const float BTN_MARGINY_SCALE = 0.15f;
	const std::string WINDOW_FRAME_SPRITENAME = "window_frame";
	std::shared_ptr<GameObject> _window;
	const std::string TITLE = "SELECT YOUR WEAPON";
};

