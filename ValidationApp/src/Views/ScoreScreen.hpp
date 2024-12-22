#pragma once

#include "Engine/Delta.hpp"
#include "IView.hpp"

class ScoreScreen : public IView
{
public:
	ScoreScreen(Scene& scene, const std::string& fontName, const Math::Vector2& startPos, const Math::Vector2& scale,
		const std::string& title, const Rendering::Color& textColor, int coins);
	const Math::Vector2& GetSize() const override;
	void SetCenter() override;
private:
	void InitTitle(const std::string& title, const Rendering::Color& textColor);
	void InitBody(int coins);
	void InitButtons();
	void InitQuitBtn();
	void InitHomeBtn();
	const Rendering::Color BODY_TEXT_COLOR = {255, 255 ,255, 255};
	const float TITLE_SCALE = 0.05f;
	const float TITLE_MARGINY_SCALE = 0.15f;
	const float BODY_TEXT_SCALE = 0.03f;
	const float BUTTON_TEXT_SCALE = 0.015f;
	const float HOME_BTN_MARGINX_SCALE = 0.15f;
	const float QUIT_BTN_MARGINX_SCALE = 0.8f;
	const float BTN_MARGINY_SCALE = 0.15f;
	const std::string WINDOW_FRAME_SPRITENAME = "window_frame";
	std::shared_ptr<GameObject> _window;
};

